// 2-dimensional array of row pin numbers:
int Row[] = {2,7,A5,5,13,A4,12,A2};
// 2-dimensional array of column pin numbers:
int Column[] = {6,11,10,3,A3,4,8,9};

unsigned char all[8][8] =     {1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1};

void setup()
{
    Serial.begin(9600);

    // iterate over the pins:
    for(int i = 0; i<8; i++)
        // initialize the output pins:
    {
        pinMode(Row[i],OUTPUT);
        pinMode(Column[i],OUTPUT);
    }
}

void loop()
{
    if (Serial.available() > 0)
    {  
      Display(all);
    }
}
void Display(unsigned char dat[8][8])
{
  for(int i = 0; i<100; i++)
  {
    for(int c = 0; c<8; c++)
    {
        digitalWrite(Column[c],LOW);//use thr column
        //loop
        for(int r = 0; r<8; r++)
        {
            digitalWrite(Row[r],dat[r][c]);
        }
        delay(1);
        Clear();  //Remove empty display light
    }
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
