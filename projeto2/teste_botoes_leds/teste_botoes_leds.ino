/* Teste de botões e LEDs por josegneto.github.io */


const int botao1 = 2; // 1o botao
const int botao2 = 3; // 2o botao
const int botao3 = 4; // 3o botao
const int botao4 = 5; // 4o botao
const int led1 = 7;   // LED associado ao 1o botao
const int led2 = 8;   // LED associado ao 2o botao
const int led3 = 9;   // LED associado ao 3o botao
const int led4 = 10;  // LED associado ao 4o botao

int estadobotao[4] = {0, 0, 0, 0}; // Vetor onde é guardado o estado de cada botao (HIGH ou LOW)


void setup() {
  // Inicializa inputs :
  randomSeed(analogRead(0));
  pinMode(botao1, INPUT); 
  pinMode(botao2, INPUT); // Os botoes sao inputs, que enviam comandos ao microcontrolador
  pinMode(botao3, INPUT);
  pinMode(botao4, INPUT);
  
  // Inicializa outputs:
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT); // Os LEDs sao outputs, que respondem a comandos (inputs)
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);

  // Ligamos todos os LEDs, de forma a testar se todos funcionam corretamente
  digitalWrite(led1, HIGH);
  digitalWrite(led2, HIGH);
  digitalWrite(led3, HIGH);
  digitalWrite(led4, HIGH);
  
  delay(2000); // Esperamos dois segundos

  // Desligamos todos os LEDs
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  digitalWrite(led3, LOW);
  digitalWrite(led4, LOW);
}

void loop(){

  // Enviamos para o vetor a leitura do estado do botao
  estadobotao[0] = digitalRead(botao1);
  estadobotao[1] = digitalRead(botao2);
  estadobotao[2] = digitalRead(botao3);
  estadobotao[3] = digitalRead(botao4);

  // Verificamos se o botao foi pressionado. Caso seja, estadobotao está HIGH e acendemos o LED. Caso contrario, apagamo-lo
  
  //BOTAO1 E LED1
  
  if (estadobotao[0] == HIGH) {
    // turn LED on:
    digitalWrite(led1, HIGH);
  }  
  if (estadobotao[0] == LOW){
    // turn LED off:
    digitalWrite(led1, LOW);   
  }

    //BOTAO2 E LED2
    
  if (estadobotao[1] == HIGH) {
    // turn LED on:
    digitalWrite(led2, HIGH);
  }  
  if (estadobotao[1] == LOW){
    // turn LED off:
    digitalWrite(led2, LOW);   
  }
    //BOTAO3 E LED3

  if (estadobotao[2] == HIGH) {
    // turn LED on:
    digitalWrite(led3, HIGH);
  }  
  if (estadobotao[2] == LOW){
    // turn LED off:
    digitalWrite(led3, LOW);   
  }
    //BOTAO4 E LED4

  if (estadobotao[3] == HIGH) {
    // turn LED on:
    digitalWrite(led4, HIGH);
  }  
  if (estadobotao[3] == LOW){
    // turn LED off:
    digitalWrite(led4, LOW);   
  }
}
