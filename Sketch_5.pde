import oscP5.*;
import netP5.*;

OscP5 oscP5;
NetAddressList IPaddressList = new NetAddressList();

int myListeningPort = 8000;
int myBroadcastPort = 9000;

String yourIPaddress = "127.0.0.1";
String yourMessageTag = "/arduino1";
String arduinoIP = "192.168.2.52";

int pitchFromArduino;
int rollFromArduino;

Snow[] snowflakes = new Snow[200];

void setup() {
  size(1200,800);
  
   oscP5 = new OscP5(this, myListeningPort); 
connect(yourIPaddress);
  connect(arduinoIP); 

 for (int i=0; i<snowflakes.length;i++) {
   snowflakes[i] = new Snow();
 }
}

void draw() {
  background(0);
   for (int i=0; i<snowflakes.length;i++) {
  snowflakes[i].fall();
  snowflakes[i].show();
   }
}
 void oscEvent(OscMessage incomingMessage) 
  {
    println(incomingMessage);
    if(incomingMessage.checkAddrPattern(yourMessageTag)==true) 
    {
      pitchFromArduino = incomingMessage.get(0).intValue();
      rollFromArduino = incomingMessage.get(1).intValue();

    }
    
    
  }



void connect(String theIPaddress) {
     if (!IPaddressList.contains(theIPaddress, myBroadcastPort)) {
       IPaddressList.add(new NetAddress(theIPaddress, myBroadcastPort));
       println("### adding "+theIPaddress+" to the list.");
     } else {
       println("### "+theIPaddress+" is already connected.");
     }
     println("### currently there are "+IPaddressList.list().size()+" remote locations connected.");
 }
