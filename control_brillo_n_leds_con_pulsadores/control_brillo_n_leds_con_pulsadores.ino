int led[] = {3, 5, 6, 9}; // Pines en donde van conectados los leds
//--- Pines en donde van conectados los pulsadores ---//
#define pul0 A0
#define pul1 A1
#define pul2 A2
//----------------------//
int pwm; //Variable que contendrá el valor del pwm
int x; // Variable para selección de posición del array led

void setup() {
  //--- Declaramos entradas y salidas ---//
  pinMode(pul0, INPUT);
  pinMode(pul1, INPUT);
  pinMode(pul2, INPUT);
  // En este caso como estamos utilizando un array podemos declarar los pines en donde van conectados los leds como salidas, de la siguiente manera:
  for (x = 0 ; x >= 4; x++) {
    pinMode(led[x], OUTPUT);
    Serial.println(x);
  }
  x = 0; // Enceramos la variable x porque la vamos a utilizar luego en el void loop
}

void loop() {

  if (digitalRead(pul0) == HIGH) { // Cada vez que presionemos el pulsador conectado al pin A0 sumamos la variable x, esta variable va a tomar los valores de las posiciones del array led que en este caso es de 4, empezando de la posición 0 a la 3. Así seleccionamos el led al cual controlaremos el brillo.
    x++;
    delay(1000); // Agregamos una pequeña pausa para el anti rebote

    if (x == 4) {
      x = 0;
    }

  }

  if (digitalRead(pul1) == HIGH) { //Si presionamos el pulsador conectado al puerto A1, sumamos la variable pwm, aumentando el brillo del led seleccionado
    pwm++;
  }

  if (digitalRead(pul2) == HIGH) { //Si presionamos el pulsador conectado al puerto A2, restamos la variable pwm, disminuyendo el brillo del led seleccionado
    pwm--;
  }

  //-- Las siguientes lineas de código son para limitar los valores que puede llegar a tomar la variable pwm---//

  if (pwm > 255) {
    pwm = 255;
  }
  if (pwm < 0) {
    pwm = 0;
  }
  // ----------------------- //

  analogWrite(led[x], pwm); // Enviamos por el pin en donde esta conectado el led, los valores de la variable pwm. Ejemplo:
  /* -- int led[] = {3,5,6,9}; // Pines en donde van conectados los leds
        posiciones  {0,1,2,3}

    Si x = 1(led[1]) entonces estaremos trabajando con el led conectado en el pin 5.
    Si x = 3(led[3]) entonces estaremos trabajando con el led conectado en el pin 9.
  */
}
