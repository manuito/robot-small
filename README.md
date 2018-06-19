# robot-small 

After https://github.com/manuito/robot-large I wanted to make something smaller for kids, with basic drive support through the https://github.com/manuito/wifi-pilote.

## Content

The base kit is once again a (very good) pololu one : Zumo (https://www.pololu.com/product/1418) + two pololu Low Power micro motors (https://www.pololu.com/product/992). 

The feature are limited :
* Driving (Track 2WD)
* Light (1 RGB Band with 8 RGB Leds)
And that's it ! Enough for "rc like" fun for kids, easy to program. I expect to glue so lego on it to make it possible to build anything they want over it. It will not be fast but OK.

For MCU, it's also simpler : ESP8266 with NodeMCU. Plus a pololu "2 motors driver", 1 pololu 5v regulator (even if ESP8266 is 3.3V, it's easier to manage a 5V input in combined electronic plateform like a robot, and the NodeMCU includes a 3.3V regulator itself. 

## Programming
Programmed with Arduino. Not started yet

## Testing

### Use and fix of the Xprotolab plain oscilloscope 

To do my testing, for the first time I wanted to go further in prototyping. So I started to use a **Xprotolab Plain** (http://www.gabotronics.com/oscilloscopes/xprotolab-plain.htm). I don't think a less expensive "*oscilloscope*" could exist, and it seems very promising... until it stoped to work :'( 

It did crash when processing a logic protocol identification, and was "bricked" after that : no more green light, impossible to make it available on computer as usb device.

After many check on documentation, I finally find a way to fix it : as explained on Gabotronics site, the bootloader is never droped, **you just have to reset the firmware to make everything back to normal**.

To add / upgrade the firmeware, you first need to "link pin 1 to 6 in J8 connector" but what is the "J8 connector" is not clear. So I have made deep searchs, and finally identified this PIN Diagram : 

![PIN diagram](xprotolab%20plain%20io%20-%20fix.png?raw=true "PIN diagram")

So yes you have to solder a connector to the 6 soldering points next to the MCU, and then link together the 1st and 6th pins on it before inserting USB. Once connected to computer, you will see a blinking red light : remove the wire from PIN 1 / 6, and start to follow documentation manual about how to upgrade firmeware. As the Atmel website is gone, you have to search into archive.org for the FLIP tool (https://web.archive.org/web/20150929050646if_/http://www.atmel.com/images/JRE%20-%20Flip%20Installer%20-%203.4.7.112.exe) Once restarted everything is back to normal, and this fun little device is ready to go :-)

