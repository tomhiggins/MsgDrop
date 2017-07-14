# MsgDrop 
MsgDrop is an open anonymous message passer that is not connected to the Interner(r)(tm).

MsgDrop uses an ESP8266 device running a combination Captive Portal and Web Server to allow
users to connect easily via any wifi enabled device. Once connected the user can utilize
any web browser and any traffic will be sent to the Web Server. 


## Installation
Edit the configuration at the top of the .ino file and upload it to your 8266. Reboot. 
You can edit the .ino file to mod the page layout and text that will be served up. 


## Current status
-Copied the codebased from Popup-chat
-Stripped blinky led and Serial comms to save cycles and power
-Moded some of the page text

## To Do
- Ability to add urls to connected services
- Possibly add some form of crypto

## License

MIT license. 
Based on Captive Portal by M. Ray Burnette 20150831. 
Based on PopupChat by @tlack (https://github.com/tlack/popup-chat) 
Moded by [tomwsmf] (https://github.com/tomhiggins/)

## Contact
Moded by @tomwsmf on Twitter
