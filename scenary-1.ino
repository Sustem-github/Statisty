#include <Servo.h>
#define servoPin1 5
#define servoPin2 6
#define servoPin3 7

int start_point1 = 65;
int start_point2 = 85;
int delta1 = 55;
int delta2 = 85;

int water; // присваиваем имя для значений с аналогового входа A0
int WATER_IN  = 3;
int WATER_OUT = 4;
int water_flag_in  = 1;
int water_flag_out = 0;  
int scenary_start  = 1;

unsigned long timer1 = 10000; //ход корабля вперед 
unsigned long timer2 = 10000; //откачка воды
unsigned long timing = 0;

Servo servo1;
Servo servo2;
Servo servo3;

void setup() {
  pinMode(servoPin1, OUTPUT);
  pinMode(servoPin2, OUTPUT);
  pinMode(servoPin3, OUTPUT);
  servo1.attach(servoPin1);
  servo2.attach(servoPin2);
  servo3.attach(servoPin3);

  //pinMode(A5, INPUT);  // к входу A0 подключим датчик (англ. «intput»)
  Serial.begin(9600);  // подключаем монитор порта
  pinMode(WATER_IN,  OUTPUT);     //накачка
  pinMode(WATER_OUT, OUTPUT);     //откачка
  
  digitalWrite(WATER_IN, HIGH);
  digitalWrite(WATER_OUT,HIGH);  

  servo1.write(start_point1);// ставим угол поворота под 0
  servo2.write(start_point2);
  servo3.write(90);
  GateClose();
}

void loop() 
{
  water = analogRead(A5); // переменная "water" находится в интервале от 0 до 1023
  //Serial.println(water); // выводим значение датчика на монитор
  //WaterIn();
  
  if(scenary_start == 1)
  {
    Shild_on();
    Ship_start();
    delay(10000);
    Ship_back();
    Shild_off();
    scenary_start = 0;
  }
  WaterOut();
  if(water_flag_out == 1)
  {
    GateOpen();
    Ship_start();
    delay(10000);  
    GateClose();    
  }
}

int WaterIn()
{
  if (water < 530) {
    digitalWrite(WATER_IN, LOW); //автоподлив если есть утечка через ворота
  }
  else 
  {
    digitalWrite(WATER_IN, HIGH);
    water_flag_in = 0;
  }
}

int WaterOut()
{
  if (water > 430) {
    digitalWrite(WATER_OUT, LOW);
  }
  else 
  {
    digitalWrite(WATER_OUT, HIGH);
    water_flag_out = 1;
  }
}

int GateClose(void)
{
   
   servo1.write(start_point1);// ставим угол поворота под 0 (открыть)
   servo2.write(start_point2);
   //delay(2000); // ждем 2 секунды
}

int GateOpen(void)
{
   int i,j;
   int step_i=1;
   int step_j=2;
   int end_point = start_point1 - delta1;

   for(i=start_point1,j=start_point2; i>=end_point; i=i-step_i, j=j+step_j)
   {
      servo1.write(i); // ставим угол поворота под 90 (закрыть)
      servo2.write(j);
      delay(200);
   }
}
int Shild_on(void)
{
   servo3.write(0);// ставим угол поворота под 0 (открыть)  
}
int Shild_off(void)
{
   servo3.write(90);// ставим угол поворота под 0 (открыть)  
}
