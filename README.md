# MsgDrop 
MsgDrop is an open anonymous message passer that may or may not be connected to the Interner(r)(tm). 

### "I said message drop, oh message, oh yeah message gonna drop on you."

# MsgDrop ESP8266
_________________________________________________________________________________________________________
MsgDrop uses an ESP8266 device running a combination Captive Portal and Web Server to allow
users to connect easily via any wifi enabled device. Once connected the user can utilize
any web browser and any traffic will be sent to the Web Server. 


## Installation


### DNSServe.h
I am using the DNSServer.h found in [tzapu's WifiManager](https://github.com/tzapu/WiFiManager)
You can either install through the Arduino Library Manager or checkout the latest changes or a release from github

#### Install through Library Manager
__Currently version 0.8+ works with release 2.0.0 or newer of the [ESP8266 core for Arduino](https://github.com/esp8266/Arduino)__
 - in Arduino IDE got to Sketch/Include Library/Manage Libraries
  ![Manage Libraries](http://i.imgur.com/9BkEBkR.png)

 - search for WiFiManager
  ![WiFiManager package](http://i.imgur.com/18yIai8.png)

 - click Install 

####  Checkout from github
__Github version works with release 2.0.0 or newer of the [ESP8266 core for Arduino](https://github.com/esp8266/Arduino)__
- Checkout library to your Arduino libraries folder [tzapu's WifiManager](https://github.com/tzapu/WiFiManager)


### msgdrop.ino
- Edit the configuration at the top of the .ino file 
- Edit the .ino file to mod the page layout and text that will be served up. 
- Upload it to your ESP8266. 
- Reboot. 

## MsgDrop ESP32
This has been ported over from the ESP8266 version of MsgDrop
You have to install the ESP32 core for Arudino instead

## Current status
- Copied the codebased from Popup-chat
- Stripped blinky led and Serial comms to save cycles and power
- Moded some of the page text

## To Do
- Ability to add urls to connected services
- Possibly add some form of crypto

## License

MIT license. 
 - Based on Captive Portal by M. Ray Burnette 20150831. 
 - Based on PopupChat by @tlack (https://github.com/tlack/popup-chat) 
 - Moded by [tomwsmf] (https://github.com/tomhiggins/)

## Contact
Moded by @tomwsmf on Twitter
