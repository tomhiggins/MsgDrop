
// MsgDrop - Offline Captive Poral Web Browser Based Message Board
// based on: PopupChat https://github.com/tlack/popup-chat
// based on: Captive Portal by: M. Ray Burnette 20150831
// moded tomhiggins
#include <WiFi.h>
#include <DNSServer.h> 
#include <WebServer.h>

// User Defined Configuration - Please Change To Suit Your Needs
#define CHATNAME "SpeakFriend"
#define BLURB "Local Msg Board"
#define COMPLAINTSTO "devnull"
#define INDEXTITLE "Hello friend!"
#define INDEXBANNER "This is a local-only, non-cloud msg board that you use through any web browser. Messages are not stored and will not survive at reboot.<a href=/faq>See frequently asked questions..</a>"
#define POSTEDTITLE "Message posted!"
#define POSTEDBANNER "Your message will stay live for a short time or until the server is rebooted."
const String FAQ = "This is an anonymous msg board that only works within the wifi range of a diskless device.<br/>"
"You can not contact the internet from here but you can use this message board and the functions herein.<br/>"
"It is anonymous, only the last few messages are kept, and nothing is saved permanently.<br/>";

// Init System Settings
#define VER "sumcheck 001"
const byte HTTP_CODE = 200; // nyi? 511; // rfc6585
const byte DNS_PORT = 53;  // Capture DNS requests on port 53
const byte TICK_TIMER = 1000;
IPAddress APIP(10, 10, 10, 1);    // Private network for server

// state:
String allMsgs="<i>*system reset and active*</i>";
unsigned long bootTime=0, lastActivity=0, lastTick=0, tickCtr=0; // timers
DNSServer dnsServer; WebServer webServer(80); // standard api servers

String input(String argName) {
  String a=webServer.arg(argName);
  a.replace("<","&lt;");a.replace(">","&gt;");
  a.substring(0,200); return a; }

String quote() { 
  const byte nquotes=3;
  String quotes[nquotes]={
    "Use of Crypto is encouraged", 
    "Msg size is limited",
    "Make talk",
  };
  return quotes[millis() / 1000 / 60 / 60 % nquotes];
}

String footer() { return 
  "</div><div class=q><label>Quote of the hour:</label>"+quote()+"</div>"
  "<div class=by>" VER "</div></body></html>"; }

String header(String t) {
  String a = String(CHATNAME);
  String CSS = "article { background: #f2f2f2; padding: 1em; }" 
    "body { color: #333; font-family: Century Gothic, sans-serif; font-size: 18px; line-height: 24px; margin: 0; padding: 0; }"
    "div { padding: 0.5em; }"
    "h1 { margin: 0.5em 0 0 0; padding: 0; }"
    "input { border-radius: 0; }"
    "label { color: #333; display: block; font-style: italic; font-weight: bold; }"
    "nav { background: #6d6262; color: #fff; display: block; font-size: 1.3em; padding: 1em; }"
    "nav b { display: block; font-size: 1.2em; margin-bottom: 0.5em; } "
    "textarea { width: 100%; }";
  String h = "<!DOCTYPE html><html>"
    "<head><title>"+a+" :: "+t+"</title>"
    "<meta name=viewport content=\"width=device-width,initial-scale=1\">"
    "<style>"+CSS+"</style></head>"
    "<body><nav><b>"+a+"</b> "+BLURB+"</nav><div><h1>"+t+"</h1></div><div>";
  return h; }

String faq() {
  return header("frequently asked questions") + FAQ + footer();
}

String index() {
  return header(INDEXTITLE) + "<div>" + INDEXBANNER + "</div><div><label>Messages:</label><ol>"+allMsgs+
    "</ol></div><div><form action=/post method=post><label>Post new message:</label><br/>"+
    "<i>remember:</i> to stay anonymous do not use names/ids</i><br/>"+
    "<textarea name=m></textarea><br/><input type=submit value=send></form>" + footer();
}

String posted() {
  String msg=input("m"); allMsgs="<li>"+msg+"</li>"+allMsgs;
  return header(POSTEDTITLE) + POSTEDBANNER + "<article>"+msg+"</article><a href=/>Back to Msg Board</a>" + footer();
}

void setup() {
  
  bootTime = lastActivity = millis();
  WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(APIP, APIP, IPAddress(255, 255, 255, 0));
  WiFi.softAP(CHATNAME);
  dnsServer.start(DNS_PORT, "*", APIP);
  webServer.on("/post",[]() { webServer.send(HTTP_CODE, "text/html", posted()); });
  webServer.on("/faq",[]() { webServer.send(HTTP_CODE, "text/html", faq()); });
  webServer.onNotFound([]() { lastActivity=millis(); webServer.send(HTTP_CODE, "text/html", index()); });
  webServer.begin();
}


void loop() { 
  if ((millis()-lastTick)>TICK_TIMER) {lastTick=millis();} 
dnsServer.processNextRequest(); webServer.handleClient(); }
