/*

  Código escrito por: Esteban Carrillo para EDEPTEC.
  Página web: https://www.edeptec.com
  Facebook: @edeptec
  Youtube: https://youtube.com/c/EDEPTEC

*/
#define pulsador 9                   // Pulsador en el pin 9
bool estadoAnteriorPulsador = 0;     // Variable para almacenar el estado anterior del pulsador
byte leds[] = {2, 3, 4, 5, 6, 7, 8}; // Pines de los LEDs
byte numeroDeLeds = sizeof(leds);    // Número de LEDs
byte numeroDeSecuencia = 0;          // Variable para almacenar el numero de la secuencia actual
byte numeroTotalDeSecuencias = 4;    // Número total de secuencias
byte const pausa = 60;               // Tiempo de pausa en milisegundos entre cambios de led

char estadosDeLosLeds[]{
    // Estados de los LEDs
    B1111111,
    B0000000,
    B1010101,
    B0101010,
};

/**
 * Inicializa los pines de los LEDs como salidas y el pin del pulsador como
 * entrada.
 *
 * Se llama a pinMode() para establecer el pin del pulsador como entrada y
 * todos los pines de los LEDs como salidas.
 */
void setup()
{
  pinMode(pulsador, INPUT);
  for (int i = 0; i < numeroDeLeds; i++)
  {
    pinMode(leds[i], OUTPUT);
  }
}

/**
 * El bucle principal del programa.
 *
 * En este bucle se verifica el estado del pulsador (pulsador) y se cambia el
 * patrón de encendido de los LEDs dependiendo de la secuencia actual.
 *
 * Se llama a la función botonPulsado() para verificar el estado del pulsador y
 * cambiar la secuencia actual si es necesario.
 *
 * Luego, se utiliza un switch para llamar a la función de secuencia actual que
 * enciende y apaga los LEDs de acuerdo al patrón establecido.
 */
void loop()
{

  botonPulsado();

  switch (numeroDeSecuencia)
  {
  case 0:
    secuenciaUno();
    break;
  case 1:
    secuenciaDos();
    break;
  case 2:
    secuenciaTres();
    break;
  case 3:
    secuenciaCuatro();
    break;
  default:
    break;
  }
}

/**
 * Secuencia de encendido de LEDs que inicia desde el principio y repite el patrón.
 *
 * En este método, los LEDs se encienden y apagan en un patrón que comienza desde el principio
 * del array de LEDs y avanza hacia el final dos veces una para encender y otra para apagar los LEDs.
 */
void secuenciaUno()
{
  inicioFin(0);
  inicioFin(1);
}

/**
 * Secuencia de encendido de LEDs que inicia desde un patrón alterno y
 * termina en otro patrón alterno inverso.
 *
 * En este método, los LEDs se encienden en un patrón alterno que avanza
 * desde el inicio hacia el final y luego desde el final hacia el inicio.
 */
void secuenciaDos()
{
  inicioFin(2);
  inicioFin(3);
  finInicio(2);
  finInicio(3);
}

/**
 * Secuencia de encendido de LEDs que inicia desde el centro y avanza hacia fuera y
 * luego inicia desde afuera hacia el centro.
 *
 * En este método, los LEDs se encienden en un patrón que comienza en el centro del
 * array de LEDs y avanza hacia fuera, luego se revierte el patrón y se encienden
 * los LEDs en orden inverso.
 */
void secuenciaTres()
{
  centroAfuera(0);
  afueraCentro(1);
}

/**
 * Secuencia de encendido de LEDs que inicia desde el principio y termina en el final
 * y luego inicia desde el final y termina en el principio.
 *
 * En este método, los LEDs se encienden en un patrón que comienza desde el principio
 * del array de LEDs y avanza hacia el final y luego comienza desde el final y avanza
 * hacia el principio.
 */
void secuenciaCuatro()
{
  inicioFin(0);
  finInicio(1);
}

/**
 * Verifica si el pulsador ha sido presionado y cambia la secuencia actual si es necesario.
 *
 * En este método, se verifica el estado del pulsador y se actualiza la variable
 * estadoAnteriorPulsador con el valor leido. Luego, si el usuario ha presionado el
 * pulsador, se incrementa el numeroDeSecuencia y se aplica un retraso de 10ms.
 *
 * Después, se verifica si el numeroDeSecuencia ha superado el numeroTotalDeSecuencias y
 * se reemplaza con 0 si es necesario.
 */
void botonPulsado()
{
  bool estadoPulsador = digitalRead(pulsador);
  (estadoPulsador != estadoAnteriorPulsador && estadoPulsador) && numeroDeSecuencia++;
  delay(10);
  estadoAnteriorPulsador = estadoPulsador;
  numeroDeSecuencia = numeroDeSecuencia > numeroTotalDeSecuencias - 1 ? 0 : numeroDeSecuencia;
}

/**
 * Enciende los LEDs en una secuencia desde el inicio hacia el final.
 *
 * En este método, los LEDs se encienden en un patrón que comienza desde el
 * principio del array de LEDs y avanza hacia el final. Se actualiza el estado
 * de los LEDs utilizando la máscara de bits proporcionada por estadosDeLosLeds
 * para el número de secuencia dado. Durante la ejecución, se verifica si el
 * botón ha sido pulsado para cambiar de secuencia y se introduce una pausa
 * entre cada activación de LED.
 *
 * @param numeroDeSecuencia El índice de la secuencia de activación en el array
 *                          estadosDeLosLeds que determina el patrón de encendido
 *                          de los LEDs.
 */
void inicioFin(byte numeroDeSecuencia)
{
  for (int i = 0; i < numeroDeLeds; i++)
  {
    digitalWrite(leds[i], (estadosDeLosLeds[numeroDeSecuencia] & (1 << i) ? 1 : 0));
    botonPulsado();
    delay(pausa);
  }
}

/**
 * Apaga los LEDs en una secuencia desde el final hacia el principio.
 *
 * En este método, los LEDs se apagan en un patrón que comienza en el final
 * del array de LEDs y avanza hacia el principio. Se actualiza el estado de los LEDs
 * utilizando la máscara de bits proporcionada por estadosDeLosLeds para el número
 * de secuencia dado. Durante la ejecución, se verifica si el botón ha sido pulsado
 * para cambiar de secuencia y se introduce una pausa entre cada desactivación de LED.
 *
 * @param numeroDeSecuencia El índice de la secuencia de activación en el array
 *                          estadosDeLosLeds que determina el patrón de encendido
 *                          de los LEDs.
 */
void finInicio(byte numeroDeSecuencia)
{
  for (int i = numeroDeLeds; i > -1; i--)
  {
    digitalWrite(leds[i], (estadosDeLosLeds[numeroDeSecuencia] & (1 << i) ? 1 : 0));
    botonPulsado();
    delay(pausa);
  }
}

/**
 * Enciende los LEDs en una secuencia desde el centro hacia afuera.
 *
 * En este método, los LEDs se encienden en un patrón que comienza en el centro
 * del array de LEDs y avanza hacia fuera. Se actualiza el estado de los LEDs
 * utilizando la máscara de bits proporcionada por estadosDeLosLeds para el número
 * de secuencia dado. Durante la ejecución, se verifica si el botón ha sido pulsado
 * para cambiar de secuencia y se introduce una pausa entre cada activación de LED.
 *
 * @param numeroDeSecuencia El índice de la secuencia de activación en el array
 *                          estadosDeLosLeds que determina el patrón de encendido
 *                          de los LEDs.
 */
void centroAfuera(byte numeroDeSecuencia)
{

  byte mitad = roundf(numeroDeLeds / 2.00);
  String type = (numeroDeLeds % 2 == 0) ? "par" : "impar";

  for (int i = 0; i < numeroDeLeds; i++)
  {
    digitalWrite(leds[type.equals("par") ? (mitad - 1) + i + 1 : (mitad - 1) + i], (estadosDeLosLeds[numeroDeSecuencia] & (1 << i) ? 1 : 0));
    digitalWrite(leds[(mitad - 1) - i], (estadosDeLosLeds[numeroDeSecuencia] & (1 << i) ? 1 : 0));
    botonPulsado();
    delay(pausa);
  }
}

/**
 * Activa los LEDs en una secuencia desde los extremos hacia el centro.
 *
 * En este método, los LEDs se encienden en un patrón que comienza en los extremos
 * del array de LEDs y avanza hacia el centro. Se actualiza el estado de los LEDs
 * utilizando la máscara de bits proporcionada por estadosDeLosLeds para el número
 * de secuencia dado. Durante la ejecución, se verifica si el botón ha sido pulsado
 * para cambiar de secuencia y se introduce una pausa entre cada activación de LED.
 *
 * @param numeroDeSecuencia El índice de la secuencia de activación en el array
 *                          estadosDeLosLeds que determina el patrón de encendido
 *                          de los LEDs.
 */
void afueraCentro(byte numeroDeSecuencia)
{
  for (int i = numeroDeLeds - 1; i > -1; i--)
  {
    digitalWrite(leds[(numeroDeLeds - 1) - i], (estadosDeLosLeds[numeroDeSecuencia] & (1 << i) ? 1 : 0));
    digitalWrite(leds[i], (estadosDeLosLeds[numeroDeSecuencia] & (1 << i) ? 1 : 0));
    botonPulsado();
    delay(pausa);
  }
}
