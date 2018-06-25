# robot-small 

After https://github.com/manuito/robot-large I wanted to make something smaller for kids, with basic drive support through the https://github.com/manuito/wifi-pilote.

## Content

The base kit is once again a (very good) pololu one : Zumo (https://www.pololu.com/product/1418) + two pololu Low Power micro motors (https://www.pololu.com/product/992). 

The feature are limited :
* Driving (Track 2WD)
* Light (1 RGB Band with 8 NeoPixels)
And that's it ! Enough for "rc like" fun for kids, easy to program. I expect to glue so lego on it to make it possible to build anything they want over it. It will not be fast but OK.

For MCU, it's also simpler : ESP8266 with D1 Mini. Plus a pololu "2 motors driver", 1 pololu 5v regulator (even if ESP8266 is 3.3V, it's easier to manage a 5V input in combined electronic plateform like a robot, and the NodeMCU includes a 3.3V regulator itself. 

### Lego base

Some lego technique bricks are glued to the robot base. The electronic is conceived to be shorter than a lego brick height : this way everything can be "hidden" under some lego bricks. And the kids can build whatever they want.

### Support for extension

A 5v compliant Serial port is available through a groove connector. The idea is to program and add later a Serial Camera Kit, and make the robot able to take pictures (and maybe to display a low FPS real time rendering of what it is able to see)

### Power management

Various power are managed :
* VIN => The bateries direct output. Can be from 4 x 0.9 v (empty NiCad bateries) to 4 * 1.5 v (new AA bateries).
* VCC 5V => VIN regulated by a pololu step-up step-down board.
* VCC 3.3V => D1 Mini (ESP8266) operating voltage + IO level. Provided by the D1 Mini regulator

Available power is different on each source : VIN has max power (whatever the batteries can handle), 5V is from 0.500A to 1A. Most of the time it will be somewhere between 0.500 and 0.700A. 3.3v is very weak : arround 200mA

How it is distributed :
* VIN provided to regulator + Motor VIN in the motor driver
* VCC 5V provided to D1 Mini VIN + a Level shifter V High + The RGB Band VIN
* VCC 3.3V is provided by the D1 Mini to the level shifter low V and to the motor driver input voltage IN 

### Use of the elvel shifter

The Level Shifter was no supposed to be their but :
* The kids wanted to be allowed to add a camera later. I only have a groove camera kit working at 5V, so the serial port needs to be pushed to a 5V level (instead default 3.3V level from ESP8266). It uses 2 Level Shifter IO
* The RGB band *works* with a 5V VIN + 3.3V data input. Put it is not recommanded by Adafruit doc, and I have seen some "interferences" maybe related to the motor noises or whatever. So to have a clean data signal, I use 1 level shifter IO for data input instead of standard 3.3V.


### Add resistances somewhere ?

I should add 330 resistances before the status led, but what I have seen is that the 3.3v from D1 Mini is weak and doesn't seem to need any resistance. All 

For the RGB Band, a resistance is recommanded to lower the power of input. As it is provided by a level shifter (so power is high), it is good to add one. Adafruit recommands a ~ 400 ohms resistance.

## Programming

Programmed with Arduino. Work in progress.

### Driving motors

Motor driver code is fully custom. 

### Wifi

A very basic webserver is used for piloting features. The code organization and definition of actions is copied from my "big-robot" project.

### Camera

Camera code is included but not yet used. Copied from another old project on Arduino Mega.

## Testing

### Use and fix of the Xprotolab plain oscilloscope 

To do my testing, for the first time I wanted to go further in prototyping. So I started to use a **Xprotolab Plain** (http://www.gabotronics.com/oscilloscopes/xprotolab-plain.htm). I don't think a less expensive "*oscilloscope*" could exist, and it seems very promising... until it stoped to work :'( 

It did crash when processing a logic protocol identification, and was "bricked" after that : no more green light, impossible to make it available on computer as usb device.

After many check on documentation, I finally find a way to fix it : as explained on Gabotronics site, the bootloader is never droped, **you just have to reset the firmware to make everything back to normal**.

To add / upgrade the firmeware, you first need to "link pin 1 to 6 in J8 connector" but what is the "J8 connector" is not clear. So I have made deep searchs, and finally identified this PIN Diagram : 

![PIN diagram](xprotolab%20plain%20io%20-%20fix.png?raw=true "PIN diagram")

So yes you have to solder a connector to the 6 soldering points next to the MCU, and then link together the 1st and 6th pins on it before inserting USB. Once connected to computer, you will see a blinking red light : remove the wire from PIN 1 / 6, and start to follow documentation manual about how to upgrade firmeware. As the Atmel website is gone, you have to search into archive.org for the FLIP tool (https://web.archive.org/web/20150929050646if_/http://www.atmel.com/images/JRE%20-%20Flip%20Installer%20-%203.4.7.112.exe) Once restarted everything is back to normal, and this fun little device is ready to go :-)

