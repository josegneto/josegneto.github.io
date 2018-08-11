#include <IRremote.h>

const int RECV_PIN = 7; // Pino do recetor
IRrecv irrecv(RECV_PIN);
decode_results results;

void setup(){
  Serial.begin(9600);
  irrecv.enableIRIn();
  irrecv.blink13(true);
}

void loop(){
  if (irrecv.decode(&results)){
        Serial.println(results.value, HEX); // Escreve no Serial Monitor o código HEX correspondente à tecla primida
        irrecv.resume();
  }
}
