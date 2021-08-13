#define led 3 // Pin en donde va conectado el led
#define pul1 A1 // Pines en donde van conectados los pulsadores
#define pul2 A2
int pwm; //Variable que contendrá el valor del pwm
 
void setup() {
 
//--Declaramos entradas y salidas---
 pinMode(led,OUTPUT);
 pinMode(pul1,INPUT);
 pinMode(pul2,INPUT);
 
 
}
 
void loop() {
 
  if(digitalRead(pul1)== HIGH){ //Si presionamos el pulsador conectado al puerto A1, sumamos el valor de la variable pwm
   
    pwm++;
   
  }
 
  if(digitalRead(pul2)== HIGH){//Si presionamos el pulsador conectado al puerto A2, restamos el valor de la variable pwm
     
    pwm--;
   
  }
 
//-- Las siguientes lineas de codigo son para limitar los valores que puede llegar a tomar la variable pwm---//
  if(pwm > 255){
    pwm = 255;
  }
  if(pwm < 0){
    pwm = 0;
  }
//------------------------//
  analogWrite(led,pwm); // Enviamos por el pin en donde esta conectado el led, los valores de la variable pwm
   
}
