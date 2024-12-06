/*

* Código escrito por: Esteban Carrillo para EDEPTEC.
* Página web: https://www.edeptec.com
* Facebook: @edeptec
* Youtube: https://youtube.com/c/EDEPTEC

*/

#define botonResta A0 // Pulsador resta en el pin A0
#define botonSuma A1  // Pulsador suma en el pin A1
#define botonOnOff A2 // Pulsador on/off en el pin A2

#define led 2 // led en el pin 2

bool activarDesactivar = 0;      // Variable para controlar el estado del led
bool estadoAnteriorPulOnOff = 0; // Variable para controlar el estado previo del pulsador on/off
int tiempo = 100;                // Variable para controlar la velocidad de parpadeo

int tiempoMinimo = 50;   // Variable para controlar el tiempo minimo
int tiempoMaximo = 5000; // Variable para controlar el tiempo maximo

/**
 * Inicializa los pines de los pulsadores y del led como entrada/salida
 * respectivamente.
 */
void setup()
{
  pinMode(botonResta, INPUT);
  pinMode(botonSuma, INPUT);
  pinMode(botonOnOff, INPUT);
  pinMode(led, OUTPUT);
}

/**
 * El bucle principal del programa.
 *
 * En este bucle se verifica el estado del pulsador de encendido y
 * apagado de los LEDs (pulOnOff), y se controla el estado del LED
 * (encendido o apagado) y su velocidad de parpadeo.
 */
void loop()
{
  if (encenderApagarLed())
  {
    digitalWrite(led, HIGH);
    pausa(tiempo);
    digitalWrite(led, LOW);
    pausa(tiempo);
  }
}
/**
 * Comprueba el estado del pulsador on/off y actualiza la variable
 * activarDesactivar.
 *
 * @return true si el led debe estar encendido, false en caso contrario.
 */
bool encenderApagarLed()
{
  bool estadoBotonOnOff = digitalRead(botonOnOff);
  (estadoBotonOnOff != estadoAnteriorPulOnOff && estadoBotonOnOff) && (activarDesactivar = !activarDesactivar);
  estadoAnteriorPulOnOff = estadoBotonOnOff;

  delay(1);
  return activarDesactivar;
}
/**
 * Realiza una pausa en la ejecución del programa durante un tiempo
 * determinado por el parámetro tiempoDePausa.
 *
 * Durante la pausa, se comprueba el estado del pulsador on/off y
 * se actualiza la variable activarDesactivar. Si el pulsador on/off
 * se encuentra en estado LOW, se sale del bucle y se termina la
 * pausa.
 *
 * @param tiempoDePausa El tiempo de pausa en milisegundos.
 */
int pausa(int tiempoDePausa)
{
  // español
  for (int i = 0; i < tiempoDePausa; i++)
  {
    manejarTiempo();
    if (!encenderApagarLed())
      break;
  }
}

/**
 * Ajusta el valor de la variable tiempo en función del estado de los
 * pulsadores suma y resta.
 *
 * Si el pulsador suma se encuentra en estado HIGH, se incrementa el valor
 * de tiempo en 10 milisegundos y se produce un delay de 10 milisegundos.
 *
 * Si el pulsador resta se encuentra en estado HIGH, se decrementa el valor
 * de tiempo en 10 milisegundos y se produce un delay de 10 milisegundos.
 *
 * Se asegura de que el valor de tiempo no sea menor que tiempoMinimo ni
 * mayor que tiempoMaximo.
 */
void manejarTiempo()
{
  if (digitalRead(botonSuma))
  {
    tiempo = tiempo + 10;
    delay(10);
  }
  if (digitalRead(botonResta))
  {
    tiempo = tiempo - 10;
    delay(10);
  }
  tiempo = (tiempo < tiempoMinimo)
               ? tiempoMinimo
           : (tiempo > tiempoMaximo)
               ? tiempoMaximo
               : tiempo;
}
