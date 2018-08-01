#include <IRLibAll.h>
#include <Servo.h> 

// You will have to set these values depending on the protocol
// and remote codes that you are using. These are For the Adafruit
// Mini Remote
#define MY_PROTOCOL NEC
#define RIGHT_ARROW   0x1FE40BF //Move several clockwise
#define LEFT_ARROW    0x1FE807F //Move servo counterclockwise
#define SELECT_BUTTON 0x1FE609F //Center the servo 
#define UP_ARROW      0x1FEA05F //Increased number of degrees servo moves
#define DOWN_ARROW    0x1FE20DF //Decrease number of degrees servo moves
#define BUTTON_0 0x1FEE01F  //Pushing buttons 0-9 moves to fixed positions
#define BUTTON_1 0x1FE50AF  // each 20 degrees greater
#define BUTTON_2 0x1FED827
#define BUTTON_3 0x1FEF807
#define BUTTON_4 0x1FE30CF
#define BUTTON_5 0x1FEB04F
#define BUTTON_6 0x1FE708F
#define BUTTON_7 0x1FE00FF
#define BUTTON_8 0x1FEF00F
#define BUTTON_9 0x1FE9867

IRrecv myReceiver(2); //pin number for the receiver
IRdecode myDecoder;

Servo myServo;  // create servo object to control a servo 
int16_t pos;         // variable to store the servo position 
int16_t Speed;       // Number of degrees to move each time a left/right button is pressed
uint32_t Previous;//handles NEC repeat codes

void setup() { 
  myServo.attach(9);      // attaches the servo on pin 9 to the servo object 
  pos = 90;               // start at midpoint 90 degrees
  Speed = 3;              // servo moves 3 degrees each time left/right is pushed
  myServo.write(pos);     // Set initial position
  myReceiver.enableIRIn(); // Start the receiver
} 
  
void loop() 
{ 
    if (myReceiver.getResults()) {
       myDecoder.decode();
       if(myDecoder.protocolNum==MY_PROTOCOL) {
         if(myDecoder.value==0xFFFFFFFF)
           myDecoder.value=Previous;
         switch(myDecoder.value) {
            case LEFT_ARROW:    pos=min(180,pos+Speed); break;
            case RIGHT_ARROW:   pos=max(0,pos-Speed); break;
            case SELECT_BUTTON: pos=90; break;
            case UP_ARROW:      Speed=min(10, Speed+1); break;
            case DOWN_ARROW:    Speed=max(1, Speed-1); break;
            case BUTTON_0:      pos=0*20; break;
            case BUTTON_1:      pos=1*20; break;
            case BUTTON_2:      pos=2*20; break;
            case BUTTON_3:      pos=3*20; break;
            case BUTTON_4:      pos=4*20; break;
            case BUTTON_5:      pos=5*20; break;
            case BUTTON_6:      pos=6*20; break;
            case BUTTON_7:      pos=7*20; break;
            case BUTTON_8:      pos=8*20; break;
            case BUTTON_9:      pos=9*20; break;
         }
         myServo.write(pos); // tell servo to go to position in variable 'pos' 
         Previous=myDecoder.value;
       }
       myReceiver.enableIRIn();
    }
}
