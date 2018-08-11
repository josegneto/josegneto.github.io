const int botao1 = 2; // 1o botao
const int botao2 = 3; // 2o botao
const int botao3 = 4; // 3o botao
const int botao4 = 5; // 4o botao
const int led1 = 7;   // LED associado ao 1o botao
const int led2 = 8;   // LED associado ao 2o botao
const int led3 = 9;   // LED associado ao 3o botao
const int led4 = 10;  // LED associado ao 4o botao

const int buzina = 12; // Buzina
const int notas[] = {1915, 1700, 1519, 1432, 2700}; // Notas associadas a cada botão. A ultima corresponde ao botao errado

// Variaveis
int EstadoBotao[] = {0,0,0,0};     // estado atual do botao
//int ultimoEstadoBotao[] = {0,0,0,0}; // estado anterior do botao
//int botaoPushCounter[] = {0,0,0,0};

void TocaNota(int nota, int duracao) {
  for (long i = 0; i < duracao * 1000L; i += nota * 2) {
    digitalWrite(buzina, HIGH);
    delayMicroseconds(nota);
    digitalWrite(buzina, LOW);
  delayMicroseconds(nota);
  }
}

void setup() {
  
  // Inicializa inputs :
  randomSeed(analogRead(0));
  pinMode(botao1, INPUT); 
  pinMode(botao2, INPUT); // Os botoes sao inputs, que enviam comandos ao microcontrolador
  pinMode(botao3, INPUT);
  pinMode(botao4, INPUT);
  
  // Inicializa outputs:
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT); // Os LEDs e a buzina sao outputs, que respondem a comandos (inputs)
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  pinMode(buzina, OUTPUT);

}
int game_on = 0;
int wait = 0;
int currentlevel = 1; // This is the level (also the number of botao presses to pass to next level)
long rand_num = 0; //initialize long variable for random number from 0-100.
int rando = 0; //initialize random integer for loopgame_on. Will be from 1-4 later.
int butwait = 500; //amount of time to wait for next botao input (ghetto de-bounce)
int ledtime = 500; //amount of time each LED flashes for when botao is pressed
int n_levels = 10; //number of levels until the game is won
int pinandnota = 0; //This integer is used when the sequence is displayed
int right = 0; //This variable must be 1 in order to go to the next level
int speedfactor = 5; //This is the final speed of the lights and sounds for the last level. This increases as more games are won
int leddelay = 200; //Initializing time for LED. This will decrease as the level increases
void loop() {

int n_array[n_levels];
int u_array[n_levels];
int i;
//clears arrays both "n_array" and "u_array" and starts a new game
if (game_on == 0){
for(i=0; i<n_levels; i=i+1){
n_array[i]=0;
u_array[i]=0;
rand_num = random(1,200);
if (rand_num <= 50)
rando=0;
else if (rand_num>50 && rand_num<=100)
rando=1;
else if (rand_num>100 && rand_num<=150)
rando=2;
else if (rand_num<=200)
rando=3;
//saves a random number in our n_array
n_array[i]=rando;
}
game_on = 1;
}
//shows the user the current sequence
if (wait == 0){
delay (200);
i = 0;
for (i = 0; i < currentlevel; i= i + 1){
leddelay = ledtime/(1+(speedfactor/n_levels)*(currentlevel - 1));
pinandnota = n_array[i];
digitalWrite(pinandnota+7, HIGH);
TocaNota(notas[pinandnota], leddelay);
digitalWrite(pinandnota+7, LOW);
delay(100/speedfactor);
}
wait = 1;
}
i = 0;
int botaochange = 0;
int j = 0; // This is the current position in the sequence

while (j < currentlevel){
    while (botaochange == 0){
      for (i = 0; i < 4; i = i + 1){
        EstadoBotao[i] = digitalRead(i+2);
        botaochange = botaochange + EstadoBotao[i];
        }
    }

      for (i = 0; i < 4; i = i + 1){
        if (EstadoBotao[i] == HIGH) {
          digitalWrite(i+7, HIGH);
          TocaNota(notas[i], ledtime);
          digitalWrite(i+7, LOW);
          wait = 0;
          u_array[j]=i;
          EstadoBotao[i] = LOW;
          botaochange = 0;
      }
     }
     if (u_array[j] == n_array[j]){
      j++;
      right = 1;
     }
    else{
      right = 0;
      i = 4;
      j = currentlevel;
      wait = 0;
     }
}

if (right == 0){
  delay(300);
  i = 0;
  game_on = 0;
  currentlevel = 1;

    for (i = 0; i < 4; i = i + 1){
      digitalWrite(i+7, HIGH);
    }
    TocaNota(notas[4], ledtime);
    for (i = 0; i < 4; i = i + 1){
      digitalWrite(i+7, LOW);
    }

    delay (200);

    for (i = 0; i < 4; i = i + 1){
      digitalWrite(i+7, HIGH);
    }

    TocaNota(notas[4], ledtime);
    for (i = 0; i < 4; i = i + 1){
      digitalWrite(i+7, LOW);
    }

    delay(500);
    game_on = 0;
}
//if you insert the right sequence it levels up
if (right == 1){
currentlevel++;
wait = 0;
}
//if you finish the game
if (currentlevel == n_levels){
delay(500);
// The following is the victory sound:
int notes[] = {2, 2, 2, 2, 0, 1, 2, 1, 2};
int note = 0;
int tempo[] = {200, 200, 200, 400, 400, 400, 200, 200, 600};
int breaks[] = {100, 100, 100, 200, 200, 200, 300, 100, 200};
for (i = 0; i < 9; i = i + 1){
  note = notes[i];
  digitalWrite(note+7, HIGH);
  TocaNota(notas[note], tempo[i]);
  digitalWrite(note+7, LOW);
  delay(breaks[i]);
}
//sets game_on to 0, so it restarts a new game
game_on = 0;
currentlevel = 1;
n_levels = n_levels + 2;
speedfactor = speedfactor + 1;
}
}
