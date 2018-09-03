/* Teste da matrix 8x8 por josegneto.github.io */

// Vetor com os pinos relativos as linhas
int Row[] = {2,7,A5,5,13,A4,12,A2};
// Vetor com os pinos relativos as colunas
int Column[] = {6,11,10,3,A3,4,8,9};

// Cada um dos LEDs está a '1', ou seja, HIGH
unsigned char all[8][8] = {1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1};

void setup()
{
    // Percorre todos os pinos
    for(int i = 0; i<8; i++)
    // Inicializa os pinos como outputs
    {
        pinMode(Row[i],OUTPUT);
        pinMode(Column[i],OUTPUT);
    }
}

void loop()
{
    Display(all);    
}

void Display(unsigned char dat[8][8])
{
    for(int c = 0; c<8; c++)
    {
        digitalWrite(Column[c],LOW); 
        
        for(int r = 0; r<8; r++)
        {
            digitalWrite(Row[r],dat[r][c]);
        }
        delay(1);
        Clear();  
    }
}

void Clear()                               
{
    for(int i = 0; i<8; i++)
    {
        digitalWrite(Row[i],LOW);
        digitalWrite(Column[i],HIGH);
    }
}
