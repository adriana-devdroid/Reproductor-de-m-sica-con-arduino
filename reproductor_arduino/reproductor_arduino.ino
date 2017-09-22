#include <TimerOne.h>


/* declaración de variables */
int spk = 13;                             // altavoz a GND y pin 13
int c[5] = {131,262,523,1046,2093};       // frecuencias 4 octavas de Do
int cs[5] = {139,277,554,1108,2217};      // Do#
int d[5] = {147,294,587,1175,2349};       // Re
int ds[5] = {156,311,622,1244,2489};      // Re#
int e[5] = {165,330,659,1319,2637};       // Mi
int f[5] = {175,349,698,1397,2794};       // Fa
int fs[5] = {185,370,740,1480,2960};      // Fa#
int g[5] = {196,392,784,1568,3136};       // Sol
int gs[5] = {208,415,831,1661,3322};      // Sol#
int a[5] = {220,440,880,1760,3520};       // La
int as[5] = {233,466,932,1866,3729};      // La#
int b[5] = {247,494,988,1976,3951};       // Si

int Harry[31][2]= {   
          {b[2], 500},
          {e[3],1000},
          {g[3], 250},
          {fs[3],250},
          {e[3],1000},
          {b[3],500},
          {a[3],1250},
          {fs[3],1000},
          {b[2], 500},
          {e[3],1000},
          {g[3],250},
          {fs[3],250},
          {d[3],1000},
          {e[3],500},
          {b[2],1000},
          {b[2], 500},
          {e[3],1000},
          {g[3], 250},
          {fs[3],250},
          {e[3],1000},
          {b[3],500},
          {d[4],1000},
          {cs[4],500},
          {c[4],1000},
          {a[3],500},
          {c[4],1000},
          {b[3],250},
          {as[3],250},
          {b[2],1000},
          {g[3],500},
          {e[3],1000}
        };

int Star_Wars[19][3] = {  
            {d[1],150,50},
            {d[1],150,50},
            {d[1],150,50},
            {g[1],900,150},
            {d[2],900,50},
            {c[2],150,50},
            {b[1],150,50},
            {a[1],150,50},
            {g[2],900,150},
            {d[2],900,100},
            {c[2],150,50},
            {b[1],150,50},
            {a[1],150,50},
            {g[2],900,150},
            {d[2],900,100},
            {c[2],150,50},
            {b[1],150,50},
            {c[2],150,50},
            {a[1],1200,2000}
          };


int Marcha[9][3]= { 
          {g[2],500,100},
          {g[2],500,100},
          {g[2],500,100},
          {ds[2],500,1},
          {as[2],125,25},
          {g[2],500,100},
          {ds[2],500,1},
          {as[2],125,25},
          {g[2],500,2000}
        };  

int Dos_Aguas[15][3] = {  
          {a[1],400,400},
          {e[1],400,400},
          {a[1],400,200},
          {e[1],200,200},
          {a[1],200,200},
          {as[1],100,100},
          {b[1],400,400},
          {fs[1],400,400},
          {b[1],400,200},
          {fs[1],200,200},
          {b[1],200,200},
          {as[1],100,100},
          {a[1],400,400},
          {e[1],400,400},
          {a[1],400,400}
        };      

void nota(int a, int b);            // declaración de la función auxiliar. Recibe dos números enteros.

void setup()
{  
  pinMode(spk,OUTPUT);
  Serial.begin(9600);
  Timer1.initialize(1000000);
  Timer1.attachInterrupt(reloj);
   
}

void nota(int frec, int t)
{
    tone(spk,frec);     // suena la nota frec recibida
    delay(t);                // para despues de un tiempo t
}

char cmd[3];
int index = 0;
int comienzo1 = 0;
int comienzo2 = 0;
int comienzo3 = 0;
int comienzo4 = 0;
int play1 = 0;
int play2 = 0;
int play3 = 0;
int play4 = 0;

void loop()
{
  leer();
  if (cmd[0] == '1'){
      comienzo2 = 0;
      comienzo3 = 0;
      comienzo4 = 0;
      play1 = atoi(cmd+1);
      if (play1)
      {
        if(comienzo1 < 31)
          Tocar_Harry(comienzo1++);
        else{
          noTone(spk);
          Serial.println("sig");
          comienzo1 = 0;  
                  
        }
      }
      else{
        noTone(spk);
      }
  }
  else if (cmd[0] == '2'){
      comienzo1 = 0;
      comienzo3 = 0;
      comienzo4 = 0;

    play2 = atoi(cmd+1);
      if (play2)
      {
        if(comienzo2 < 19)
          Tocar_Star_Wars(comienzo2++);
        else{
          noTone(spk);
          Serial.println("sig");  
          comienzo2 = 0;
           
        }
      }
      else{
        noTone(spk);
      }
  }
  else if (cmd[0] == '3'){
      comienzo2 = 0;
      comienzo1 = 0;
      comienzo4 = 0;
    play3 = atoi(cmd+1);
      if (play3)
      {
        if(comienzo3 < 9)
          Tocar_Marcha(comienzo3++);
        else{
          noTone(spk);
          Serial.println("sig"); 
          comienzo3 = 0;
           
        }
      }
      else{
        noTone(spk);
      }
  }
  else if(cmd[0] == '4'){
      comienzo2 = 0;
      comienzo3 = 0;
      comienzo1 = 0;
    play4 = atoi(cmd+1);
      if (play4)
      {
        if(comienzo4 < 15)
          Tocar_Dos_Aguas(comienzo4++);
        else{
          noTone(spk);
          
          Serial.println("final");
          comienzo4 = 0;   
        }
      }
      else{
        noTone(spk);
      }
  }
}

void reloj(){
  Serial.println("mas");
}
void Tocar_Harry(int c)
{
    if (c == 15){
        noTone(spk); 
        delay(1000);
    }
    nota(Harry[c][0],Harry[c][1]);  
}

void Tocar_Star_Wars(int c)
{
    nota(Star_Wars[c][0],Star_Wars[c][1]);
    noTone(spk);
    delay(Star_Wars[c][2]);
}

void Tocar_Marcha(int c)
{
    nota(Marcha[c][0],Marcha[c][1]);
    noTone(spk);
    delay(Marcha[c][2]);
}

void Tocar_Dos_Aguas(int c)
{
    nota(Dos_Aguas[c][0],Dos_Aguas[c][1]);
    noTone(spk);
    delay(Dos_Aguas[c][2]);
}

void leer(){
    if(Serial.available() > 0)
    {   
        cmd[index++] = Serial.read();

        if(index == 2) {
            cmd[index] = '\0';
            index = 0;
        }     
    }

}
