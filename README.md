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
To do my testing, for the first time I wanted to go further in prototyping. So I started to use a Xprotolab Plain (http://www.gabotronics.com/oscilloscopes/xprotolab-plain.htm). I don't think a less expensive "oscilloscope" could exist, and it seems very promising... until it stoped to work :'(

I will maybe publish more details on this and the problem I got, as I'm still looking on a way to fix it. I don't think I have fried something (was working on a ESP8266 output) but it's possible that the firmware transformed into vaporware. 

To add a new firmeware, you need to "link pin 1 to 6 in J8 connector". J8 connector is an external port, not soldered. It's not labeled, nore documented anywhere (and it's NOT the PDI port neither - I did mixed them first!), so I created this diag with pin details : 

![PIN diagram](xprotolab%20plain%20io%20-%20fix.png?raw=true "PIN diagram")

Don't know yet if it's OK, If so I will try to go further in firmware flashing (using Atmel Studio 6 / Atmel FLIP or whatever else I can find)
