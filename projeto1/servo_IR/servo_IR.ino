#include <IRLibAll.h>
#include <Servo.h> 

// É necessário definir estes valores, dependendo do protocolo
// e os códigos do comando que utilizamos

#define MY_PROTOCOL NEC
#define CH-           0x1FE48B7
#define CH            0x1FE58A7
#define CH+           0x1FE7887
#define FAST_BACKWARD 0x1FE807F   // Rodar o servo no sentido contrário ao dos ponteiros do relógio
#define FAST_FORWARD  0x1FE40BF   // Rodar o servo no sentido dos ponteiros do relógio
#define PLAY_PAUSE    0x1FEC03F   // Centrar o servo
#define VOLMENOS      0x1FE20DF   // Diminuir a velocidade (número de graus) a que o servo gira
#define VOLMAIS       0x1FEA05F   // Aumentar a velocidade (número de graus) a que o servo gira
#define EQ            0x1FE609F
#define BUTTON_0      0x1FEE01F   // Pressionar os botões 0-9 faz girar 20 graus de cada vez
#define BUTTON_1      0x1FE50AF   // para posições fixas
#define BUTTON_2      0x1FED827
#define BUTTON_3      0x1FEF807      
#define BUTTON_4      0x1FE30CF       
#define BUTTON_5      0x1FEB04F
#define BUTTON_6      0x1FE708F
#define BUTTON_7      0x1FE00FF
#define BUTTON_8      0x1FEF00F
#define BUTTON_9      0x1FE9867

IRrecv myReceiver(11);      // Pino do recetor
IRdecode myDecoder;

Servo myServo;             // Objeto servo que controla o servo
int16_t pos;               // Variável que guarda a posição do servo
int16_t Speed;             // Velocidade (nº de graus) a mover cada vez que os botões VOLMENOS/VOLMAIS são pressionados
uint32_t Previous;         // Lida com códigos repetidos sucessivos

void setup() { 
  myServo.attach(9);       // Relaciona o pino 9 com o objeto servo
  pos = 90;                // Ponto inicial: 90 graus
  Speed = 3;               // O servo move-se 3 graus cada vez que os botões VOLMENOS/VOLMAIS são pressionados
  myServo.write(pos);      // Coloca o servo na posição inicial definida acima
  myReceiver.enableIRIn(); // Ativa o recetor 
} 
  
void loop() 
{ 
    if (myReceiver.getResults()) {
       myDecoder.decode();
       if(myDecoder.protocolNum==MY_PROTOCOL) {
         if(myDecoder.value==0xFFFFFFFF)
           myDecoder.value=Previous;
         switch(myDecoder.value) {
            case FAST_BACKWARD: pos=min(180,pos+Speed); break;
            case FAST_FORWARD:  pos=max(0,pos-Speed); break;
            case PLAY_PAUSE:    pos=90; break;
            case VOLMAIS:       Speed=min(10, Speed+1); break;
            case VOLMENOS:      Speed=max(1, Speed-1); break;
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
         myServo.write(pos); // Comanda o servo para se mover para a posição indicada pela variável 'pos'
         Previous=myDecoder.value;
       }
       myReceiver.enableIRIn();
    }
}
