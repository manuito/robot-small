#define satMax 40
#define satMid 30
#define satLes 20
#define satMin 5

// RGB Band
NeoPixelBus<NeoGrbFeature, NeoEsp8266Uart800KbpsMethod> strip(RGB_BAND_PIXEL_COUNT, RGB_PIN);

bool bandSwap = false;
int bandCpt = 0;
int bandCurrentAction;

void startBand(){
    strip.Begin();
    strip.Show();
}

void setBandAction(byte action){
  bandCurrentAction = action - 48;
  bandCpt = 0; 
  bandSwap = false;
  doNothing();
}

void setAll(RgbColor color){
  for(int i = 0; i < 8; i++){
     strip.SetPixelColor(i,color);
  }
}

void doBandShortAction(){
   switch (bandCurrentAction) {
    case 5:
      doFadding();
      break;
    case 2:
      doK2000Light();
      break;
  }
}

void doBandAction(){
   switch (bandCurrentAction) {
    case 4:
      doChristmas();
      break;
    case 3:
      doHeadlights();
      break;
    case 1:
      doPoliceLight();
      break;
    case 0:
      break;
  }
}

void doPoliceLight(){
  if(bandSwap){
    strip.SetPixelColor(0, RgbColor(0, 0, satMax));
    strip.SetPixelColor(7, RgbColor(satMax, 0, 0));
  } else {
    strip.SetPixelColor(0, RgbColor(satMax, 0, 0));
    strip.SetPixelColor(7, RgbColor(0, 0, satMax));
  }
  strip.Show();
  bandSwap = !bandSwap;
}

void doNothing(){
 setAll(RgbColor(0, 0, 0));
 strip.Show();
}
void doK2000Light(){

  if(bandCpt <= 7){;
    strip.SetPixelColor(bandCpt-3, RgbColor(0, 0, 0));
    strip.SetPixelColor(bandCpt-2, RgbColor(satMin, 0, 0));
    strip.SetPixelColor(bandCpt-1, RgbColor(satLes, 0, 0));
    strip.SetPixelColor(bandCpt, RgbColor(satMax, 0, 0));
  } else {
    strip.SetPixelColor(14 - bandCpt, RgbColor(satMax, 0, 0));
    strip.SetPixelColor(15 - bandCpt, RgbColor(satLes, 0, 0));
    strip.SetPixelColor(16 - bandCpt, RgbColor(satMin, 0, 0));
    strip.SetPixelColor(17 - bandCpt, RgbColor(0, 0, 0));
  }

  if(bandCpt >= 14){
    bandCpt = 0;
  } else {
    bandCpt = bandCpt+1;
  }
  strip.Show();
}


void doHeadlights(){

    strip.SetPixelColor(0, RgbColor(satMax, satMax, satMax));
    strip.SetPixelColor(1, RgbColor(satMax, satMax, satMax));

    strip.SetPixelColor(6, RgbColor(satMax, satMax, satMax));
    strip.SetPixelColor(7, RgbColor(satMax, satMax, satMax));

    strip.Show();
}

void doChristmas(){
  
  if(bandSwap){
    strip.SetPixelColor(0, RgbColor(satLes, 0, 0));
    strip.SetPixelColor(2, RgbColor(0, satLes, 0));
    strip.SetPixelColor(4, RgbColor(satLes, satLes, 0));
    strip.SetPixelColor(6, RgbColor(0, 0, satLes));
    
    strip.SetPixelColor(1, RgbColor(0, 0, 0));
    strip.SetPixelColor(3, RgbColor(0, 0, 0));
    strip.SetPixelColor(5, RgbColor(0, 0, 0));
    strip.SetPixelColor(7, RgbColor(0, 0, 0));
  } else {
    strip.SetPixelColor(1, RgbColor(0, 0, satLes));
    strip.SetPixelColor(3, RgbColor(satLes, satLes, 0));
    strip.SetPixelColor(5, RgbColor(0, satLes, 0));
    strip.SetPixelColor(7, RgbColor(satLes, 0, 0));
    
    strip.SetPixelColor(0, RgbColor(0, 0, 0));
    strip.SetPixelColor(2, RgbColor(0, 0, 0));
    strip.SetPixelColor(4, RgbColor(0, 0, 0));
    strip.SetPixelColor(6, RgbColor(0, 0, 0));
  }
  strip.Show();
  bandSwap = !bandSwap;
}


void doFadding(){

  // Fade Yellow
  int r = bandCpt;
  int g = bandCpt;
  int b = 0;
  
  if(bandCpt > satLes || bandCpt == 0){
    bandSwap = !bandSwap;
  }

  if(bandSwap){
    bandCpt++;
  } else {
    bandCpt--;
  }
  
  setAll(RgbColor(r,g,b));
  strip.Show();
}

