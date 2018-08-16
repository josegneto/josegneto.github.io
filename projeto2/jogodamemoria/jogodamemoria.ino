/* Adaptado de Random Nerd Tutorials por josegneto.github.io */


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
int currentlevel = 1; // Nivel (coincide com o numero de botoes a pressionar para passar para o proximo nivel)
long rand_num = 0;    // Variavel onde sera gerado um numero aleatorio entre 0-100
int rando = 0;        // Inteiro entre 1-4 (botao a pressionar / LED que acende)
int ledtime = 500;    // Tempo durante o qual o LED está aceso quando o botão é primido
int n_levels = 10;    // Numero de niveis do jogo
int pinandnota = 0;   
int right = 0;        // A variavel assume '1' quando a sequencia esta correta, de modo a passar de nivel
int speedfactor = 5;  // Velocidade dos LEDs e sons no ultimo nivel. Aumenta a medida que se ganham jogos
int leddelay = 200;   // Tempo de inicializacao do LED. Diminui a medida que o nivel aumenta

void loop() {

    int n_array[n_levels];
    int u_array[n_levels];
    int i;
    
    if (game_on == 0) { // Limpa os vetores "n_array" e "u_array" e comeca um novo jogo
        for(i=0; i<n_levels; i=i+1) {
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

            n_array[i]=rando; // Guarda um numero aleatorio no vetor "n_array"
        }
        game_on = 1;
    }
    if (wait == 0) {// Mostra ao jogador a sequencia
        delay (200);
        i = 0;
        for (i = 0; i < currentlevel; i= i + 1) {
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
    int j = 0; // Posicao correta na sequencia

    while (j < currentlevel) {
        while (botaochange == 0) {
            for (i = 0; i < 4; i = i + 1) {
                EstadoBotao[i] = digitalRead(i+2);
                botaochange = botaochange + EstadoBotao[i];
            }
        }

        for (i = 0; i < 4; i = i + 1) {
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
        if (u_array[j] == n_array[j]) {
            j++;
            right = 1;
        }
        else {
            right = 0;
            i = 4;
            j = currentlevel;
            wait = 0;
        }
    }

    if (right == 0) {
        delay(300);
        i = 0;
        game_on = 0;
        currentlevel = 1;

        for (i = 0; i < 4; i = i + 1) {
            digitalWrite(i+7, HIGH);
        }
        TocaNota(notas[4], ledtime);
        for (i = 0; i < 4; i = i + 1) {
            digitalWrite(i+7, LOW);
        }

        delay (200);

        for (i = 0; i < 4; i = i + 1) {
            digitalWrite(i+7, HIGH);
        }

        TocaNota(notas[4], ledtime);
        for (i = 0; i < 4; i = i + 1) {
            digitalWrite(i+7, LOW);
        }

        delay(500);
        game_on = 0;
    }
    if (right == 1) { //Se a sequencia for a correta, aumenta o nivel
        currentlevel++;
        wait = 0;
    }
    if (currentlevel == n_levels) { // Caso se ganhe o jogo
        delay(500);
        int notes[] = {2, 2, 2, 2, 0, 1, 2, 1, 2}; // Som da vitoria
        int note = 0;
        int tempo[] = {200, 200, 200, 400, 400, 400, 200, 200, 600};
        int breaks[] = {100, 100, 100, 200, 200, 200, 300, 100, 200};
        for (i = 0; i < 9; i = i + 1) {
            note = notes[i];
            digitalWrite(note+7, HIGH);
            TocaNota(notas[note], tempo[i]);
            digitalWrite(note+7, LOW);
            delay(breaks[i]);
        }
        game_on = 0; // "game_on" é colocado a 0, de modo a iniciar-se um novo jogo
        currentlevel = 1;
        n_levels = n_levels + 2;
        speedfactor = speedfactor + 1;
    }
}
