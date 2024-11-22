/* 

* Código escrito por: Esteban Carrillo para EDEPTEC. 
* Página web: https://www.edeptec.com
* Facebook: @edeptec
* Youtube: https://youtube.com/c/EDEPTEC

*/

// Definición de pines utilizados en el proyecto
#define led 3         // Pin al que está conectado el LED controlado por PWM
#define pulSuma A1    // Pin al que está conectado el botón para aumentar el brillo
#define pulResta A2   // Pin al que está conectado el botón para disminuir el brillo

// Declaración de variable para almacenar el valor del PWM
byte pwm = 0;

void setup() {
  // Configuración de pines como entrada o salida
  pinMode(led, OUTPUT);       // Configura el pin del LED como salida
  pinMode(pulSuma, INPUT);    // Configura el pin del botón de suma como entrada
  pinMode(pulResta, INPUT);   // Configura el pin del botón de resta como entrada
}

void loop() {
  // Incrementar o decrementar el valor del PWM según el estado de los botones
  (digitalRead(pulSuma) == HIGH) && pwm++;  // Si el botón de suma está presionado, incrementa el PWM
  (digitalRead(pulResta) == HIGH) && pwm--; // Si el botón de resta está presionado, decrementa el PWM
  
  delay(20);  // Retardo para evitar rebotes del botón

  // Limitar el rango del valor PWM entre 0 y 255
  if (pwm > 255) pwm = 255;  // Si el valor PWM supera 255, lo limita a 255
  if (pwm < 0) pwm = 0;      // Si el valor PWM baja de 0, lo limita a 0

  // Actualizar el valor del PWM del LED
  analogWrite(led, pwm);     // Escribe el valor PWM en el pin del LED
}
