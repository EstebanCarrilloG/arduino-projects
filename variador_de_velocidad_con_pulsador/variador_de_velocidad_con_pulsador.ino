// PINES DE CONEXION CON EL PUENTE H
#define pwmA  3
#define motorinA  4
#define motorinB  5
#define stby  6
//

// Botón en configuración Pull down
#define button  7
// variable para comprobar el estado del pulsador
boolean estBut = 0;
// variable para setear la velocidad del motor
int vel = 0;
// variable para contar
int contvel = 0;

void setup() {

  Serial.begin(9600);
  pinMode(pwmA, OUTPUT);
  pinMode(motorinA, OUTPUT);
  pinMode(motorinB, OUTPUT);
  pinMode(stby, OUTPUT);
  pinMode(button, INPUT);
}

void loop() {
  digitalWrite(stby, 1); // activamos el stby
  // almacenamos en estBut el estado lógico del pulsador
  estBut = digitalRead(button);
  // comprobando, si se presiono el pulsador entonces
  if (estBut == HIGH) {
    // la variable vel se suma , así aumentamos la velocidad del motor
    vel++;
    // usamos la siguiente condición para que el valor del pwm no sobrepase los 255
    if (vel >= 255) {
      vel = 255;
    }
    //----------------------*-------------------------------//

    // caso contrario, si dejamos de pulsar el botón, entonces
  } else {
    // la variable vel se resta , así disminuimos la velocidad del motor
    vel--;
    // usamos la siguiente condición para que el valor del pwm no sea menor a 0
    if (vel <= 0) {
      vel = 0;
    }
  }
  //----------------------*-------------------------------//
  Serial.println(vel); // imprimimos el valor del pwm en el monitor serial
  setspeed();  // vamos a la función setspeed
}

void setspeed() {
  analogWrite(pwmA, vel); // seteamos la velocidad del giro del motor
  // giro del motor
  digitalWrite(motorinA, 1);
  digitalWrite(motorinB, 0);
  //-------------*----------//
  // esta pausa es para que no aumente abruptamente la velocidad del motor
  delay(20);
}
