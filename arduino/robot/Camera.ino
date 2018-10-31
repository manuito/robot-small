/*********************************************************************/
void clearRxBuf(){
  while (CAM_SERIAL.available()) {
    CAM_SERIAL.read(); 
  }
}
/*********************************************************************/
void sendCmd(char cmd[], int cmd_len){
  for (char i = 0; i < cmd_len; i++) CAM_SERIAL.write(cmd[i]); 
}
/*********************************************************************/
int readBytes(char *dest, int len, unsigned int timeout){
  int read_len = 0;
  unsigned long t = millis();
  while (read_len < len) {
    while (CAM_SERIAL.available()<1) {
      if ((millis() - t) > timeout) {
        return read_len;
      }
    }
    *(dest+read_len) = CAM_SERIAL.read();
    read_len++;
  }
  return read_len;
}
/*********************************************************************/
void initializeCamera()
{   
  char cmd[] = {0xaa,0x0d|cameraAddr,0x00,0x00,0x00,0x00} ;  
  unsigned char resp[6];

  //Serial.print("initializing camera...");
  
  while (1) {
    sendCmd(cmd,6);
    if (readBytes((char *)resp, 6,1000) != 6) {
      //Serial.print(".");
      continue;
    }
    if (resp[0] == 0xaa && resp[1] == (0x0e | cameraAddr) && resp[2] == 0x0d && resp[4] == 0 && resp[5] == 0) {
      if (readBytes((char *)resp, 6, 500) != 6) continue; 
      if (resp[0] == 0xaa && resp[1] == (0x0d | cameraAddr) && resp[2] == 0 && resp[3] == 0 && resp[4] == 0 && resp[5] == 0) break; 
    }
  }  
  cmd[1] = 0x0e | cameraAddr;
  cmd[2] = 0x0d;
  sendCmd(cmd, 6); 
  //Serial.println("\nCamera initialization done.");
}
/*********************************************************************/

void setCaptureMode(char jpegRes)
{
  char cmd[] = { 0xaa, 0x01 | cameraAddr, 0x00, 0x07, 0x03, jpegRes};  
  unsigned char resp[6]; 
  
  while (1) {
    clearRxBuf();
    sendCmd(cmd, 6);
    if (readBytes((char *)resp, 6, 100) != 6) continue; 
    if (resp[0] == 0xaa && resp[1] == (0x0e | cameraAddr) && resp[2] == 0x01 && resp[4] == 0 && resp[5] == 0) break; 
  }
  
}

void setPacketSize(){
  
  char cmd[] = { 0xaa, 0x06 | cameraAddr, 0x08, PIC_PKT_LEN & 0xff, (PIC_PKT_LEN>>8) & 0xff ,0}; 
  unsigned char resp[6];

  while (1) {
    clearRxBuf();
    sendCmd(cmd, 6);
    if (readBytes((char *)resp, 6, 100) != 6) continue;
    // ACK
    if (resp[0] == 0xaa && resp[1] == (0x0e | cameraAddr) && resp[2] == 0x06 && resp[4] == 0 && resp[5] == 0) break; 
  }
}

// SNAPSHOT
void doSnapshot()
{
  char cmd[] = { 0xaa, 0x05 | cameraAddr, 0, 0, 0, 0}; 
  unsigned char resp[6];

  while (1) {
    clearRxBuf();
    sendCmd(cmd, 6);
    if (readBytes((char *)resp, 6, 100) != 6) continue;
    // ACK
    if (resp[0] == 0xaa && resp[1] == (0x0e | cameraAddr) && resp[2] == 0x05 && resp[4] == 0 && resp[5] == 0) break;
  }
}

unsigned long getPicture(char type){
  
  // GET PICTURE
  char cmd[] = { 0xaa, 0x04 | cameraAddr, type, 0, 0, 0}; 
  unsigned char resp[6];
  
  while (1) {
    clearRxBuf();
    sendCmd(cmd, 6);
    if (readBytes((char *)resp, 6, 100) != 6) continue;
    
    // ACK
    if (resp[0] == 0xaa && resp[1] == (0x0e | cameraAddr) && resp[2] == 0x04 && resp[4] == 0 && resp[5] == 0) {
      
      if (readBytes((char *)resp, 6, 1000) != 6) continue;
      
      // DATA
      if (resp[0] == 0xaa && resp[1] == (0x0a | cameraAddr)) {
        picTotalLen = (resp[3]) | (resp[4] << 8) | (resp[5] << 16); 
        return picTotalLen;
      }
    }
  }

  return -1;
}


/*********************************************************************/
String loadData()
{
  String pic = "";
  unsigned int pktCnt = (picTotalLen) / (PIC_PKT_LEN - 6); 
  if ((picTotalLen % (PIC_PKT_LEN-6)) != 0) pktCnt += 1;
  
  char cmd[] = { 0xaa, 0x0e | cameraAddr, 0x00, 0x00, 0x00, 0x00 };  
  unsigned char pkt[PIC_PKT_LEN];
    
    for (unsigned int i = 0; i < pktCnt; i++)
    {
      cmd[4] = i & 0xff;
      cmd[5] = (i >> 8) & 0xff;
      
      int retry_cnt = 0;
    retry:
      delay(10);
      clearRxBuf(); 
      sendCmd(cmd, 6); 
      uint16_t cnt = readBytes((char *)pkt, PIC_PKT_LEN, 200);
      
      unsigned char sum = 0; 
      for (int y = 0; y < cnt - 2; y++)
      {
        sum += pkt[y];
      }
      if (sum != pkt[cnt-2])
      {
        if (++retry_cnt < 100) goto retry;
        else break;
      }
      
      pic.concat(pkt[4]); 
      //if (cnt != PIC_PKT_LEN) break;
    }
    cmd[4] = 0xf0;
    cmd[5] = 0xf0; 
    sendCmd(cmd, 6); 

    return pic;
}

String loadPreview(){

  setCaptureMode(PRE_RES);
  setPacketSize();
  getPicture(0x05);
  return loadData();

  // Second : snapshot + picture
/*  Serial.println("Get snapshot");
  setCaptureMode(PIC_RES);
  setPacketSize();
  doSnapshot();
  getPicture(0x01);
  loadData(imgName);
*/
}


