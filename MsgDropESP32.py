#Non Working Code
#Still Under Construction

from m5stack import *
from uiflow import *
from m5ui import *
import wifiCfg
import socket



#User Defined Configuration - Please Change To Suit Your Needs
Msgs = " init "
ChatName = "MsgDrop"
Blurb = "Local Msg Board"
ComplaintsTo = "devnull"
IndexTitle = "Hello friend!"
IndexBanner = "This is a local-only, non-cloud msg board that you use through any web browser. Messages are not stored and will not survive at reboot.<a href=/faq>See frequently asked questions..</a>"
PostedTitle = "Message posted!"
PostedBanner = "Your message will stay live for a short time or until the server is rebooted."


Faq = """<body><nav>"""+str(ChatName)+"""  """+str(Blurb)+"""</nav>
<div>"""+str(IndexBanner)+""" </div><div>
This is an anonymous msg board that only works within the wifi range of a diskless device.<br/>
You can not contact the internet from here but you can use this message board and the functions herein.<br/>
It is anonymous, only the last few messages are kept, and nothing is saved permanently.<br/>
</div></body>
"""


Footer = "</div><div class=q><label>Quote of the hour:</label>  Fnord!</div><div class=by> VER 0.01a </div></body></html>"

Header = """<!DOCTYPE html><html> <head><title> {ChatName} :: </title>
<meta name=viewport content="width=device-width,initial-scale=1">
<style> article { background: #f2f2f2; padding: 1em; } 
body { color: #333; font-family: Century Gothic, sans-serif; font-size: 18px; line-height: 24px; margin: 0; padding: 0; }
div { padding: 0.5em; }
h1 { margin: 0.5em 0 0 0; padding: 0; }
input { border-radius: 0; }
label { color: #333; display: block; font-style: italic; font-weight: bold; }
nav { background: #6d6262; color: #fff; display: block; font-size: 1.3em; padding: 1em; }
nav b { display: block; font-size: 1.2em; margin-bottom: 0.5em; }
textarea { width: 100%; }</style></header>"""
  
Body = """<body><nav>"""+str(ChatName)+"""  """+str(Blurb)+"""</nav>
<div>"""+str(IndexBanner)+""" </div><div><label>Messages:</label><ol>"""+str(Msgs)+"""
</ol></div><div><form action=/post method=post><label>Post new message:</label><br/>
<i>remember:</i> to stay anonymous do not use names/ids<br/>
<textarea name=m></textarea><br/><input type=submit value=send></form></body>"""

state = 0 
#state variable for the leds

#function for displaying the html 

def web_page():
  html = ""
  html = str(Header)
  html = str(html) + str(Body)
  html = str(html) + str(Footer)
  return html

def faq_page():
  html = ""
  html = str(Header)
  html = str(html) + str(Faq)
  html = str(html) + str(Footer)
  return html


ip = wifiCfg.wlan_sta.ifconfig()

#create labels to display the information on the M5Stack screen
label1 = M5TextBox(0, 0, "Text", lcd.FONT_Default,0xFFFFFF, rotate=0)
label2 = M5TextBox(0, 24, "Text", lcd.FONT_Default,0xFFFFFF, rotate=0)
label3 = M5TextBox(0, 60, "Text", lcd.FONT_Default,0xFFFFFF, rotate=0)
label4 = M5TextBox(0, 85, "Text", lcd.FONT_Default,0xFFFFFF, rotate=0)
label5 = M5TextBox(120, 200, "Text", lcd.FONT_Default,0xFFFFFF, rotate=0)

response = None
wifiCfg.doConnect('NETGEAR75-5G', 'sillygiant')
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.bind(('192.168.1.30', 80))
s.listen(5)

if wifiCfg.wlan_sta.isconnected():
  label1.setText('wifi connected')
  label2.setText('  Your IP ' + str(ip[0]))
else:
  label1.setText('wifi not connected')
  wait_ms(2)

while True:
  conn, addr = s.accept()
  request = conn.recv(1024)
  request = str(request)
  Msgs = str(Msgs) + str(request)
  
  #led_on = request.find('/?led=on')
  #led_off = request.find('/?led=off')
  #btn_press = request.find('/?btn=on')
  
  
  label4.setText('Content = %s' % request)
  label3.setText('Got a connection from %s' % str(addr))
  response = web_page()
  
  dofaq = request.find('/faq')
  if dofaq == 6:
    response = faq_page()

  
  conn.send('HTTP/1.1 200 OK\n')
  conn.send('Content-Type: text/html\n')
  conn.send('Connection: close\n\n')
  conn.sendall(response)
  conn.close()
