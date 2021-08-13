// Creamos un array
// Con los pines en donde iran conectados los leds
int leds[] = {2, 3, 4, 5, 6, 7};
// Creamos una variable para almacenar el
int i = 0;
// Pausa entre encendido o apagado de cada led
short pausa = 500;
void setup() {

  // Declaramos los pines como salidas
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);

}

void loop() {

  /////// SECUENCIA 1////////

  /* La variable i es para acceder a los valores del array (pines donde van conectados los leds),
      en sus distintas posiciones. En este caso i comenzara en la posicion 0 e ira sumando hasta llegar a la 6
      cuando llegue a la posicion 6 se termina el ciclo for.

      Con posiciones me refiero a los valores que estan dento del array, {2,3,4,5,6,7};

       i va a tomar los valores del array.
                                                                                      |-----------|
      cuando i = 0 toma el valor de la posicion 0 del array | i = pin 2 |
      cuando i = 1 toma el valor de la posicion 1 del array | i = pin 3 |
      cuando i = 2 toma el valor de la posicion 2 del array | i = pin 4 | Como pueden ver, estos son los pines
      cuando i = 3 toma el valor de la posicion 3 del array | i = pin 5 | en donde van conectados los leds
      cuando i = 4 toma el valor de la posicion 4 del array | i = pin 6 |
      cuando i = 5 toma el valor de la posicion 5 del array | i = pin 7 |
                                                                                      |-----------|

  */
  for (i = 0; i < 6; i++) { //creamos un ciclo for que vaya de 0 a 5
    digitalWrite(leds[i], HIGH); //Encendemos los leds
    /* recuerden que i es en valor del pin el cual va a ir cambiando
       Por ejemplo es como si tuviesemos esto:

       digitalWrite(2,HIGH);
       delay(pausa);
       digitalWrite(3,HIGH);
       delay(pausa);
       digitalWrite(4,HIGH);
       delay(pausa);
       digitalWrite(5,HIGH);
       delay(pausa);
       digitalWrite(6,HIGH);
       delay(pausa);
       digitalWrite(7,HIGH);
       delay(pausa);
    */
    delay(pausa); // pausa entre encendido de cada led
  }
  /* Nos ubicamos en la posicion 6 y apagmos los leds de uno en uno */
  for (i = 6; i > -1 ; i--) { // restamos i porque estamos yendo de la posicion 6 a la 0
    digitalWrite(leds[i], LOW); // apagamos los leds

    delay(pausa);// Pausa ente apagado //
  }
  //////////////////////////
  ///// SECUENCIA 2 ////////
  /* En este caso vamos a encender los leds impares
     para eso enceramos i y la ssumamos mas dos
     hasta que llegue a la posicion 6 */
  for (i = 0; i < 6; i = i + 2) {
    digitalWrite(leds[i], HIGH);
    delay(pausa);
  }
  /* Encendemos los leds pares
     para eso igualamos i = 1 y la ssumamos mas dos*/
  for (i = 1; i < 6 ; i = i + 2) {
    digitalWrite(leds[i], HIGH);
    delay(pausa);
  }
  /* Nos ubicamos en la posicion 6 y apagmos los leds de uno en uno */
  for (i = 6; i > -1 ; i--) {
    digitalWrite(leds[i], LOW);
    delay(pausa);
  }
}
