/*

  Código escrito por: Esteban Carrillo para EDEPTEC.
  Página web: https://www.edeptec.com
  Facebook: @edeptec
  Youtube: https://youtube.com/c/EDEPTEC

*/
// Definimos los pines de los displays
//
int pines[] = {0, 1, 2, 3, 4, 5, 6}; 
            //{g, f, e, d, c, b, a};

#define decenaTr 10 // Pin para activar el display de decenas
#define unidadTr 8 // Pin para activar el display de unidades

bool estadoAnterior = 0; // Variable para almacenar el estado anterior del botón
int unidad; // Variable para almacenar la unidad del número aleatorio
int decena; // Variable para almacenar la decena del número aleatorio
short pausa = 5;// Variable para almacenar la duración de la pausa entre activación de displays
bool pulso = 0; // Variable para controlar entre start y stop


//Numeros que se mostraran en el display de 7 segmentos en binario
byte numerosAnodo[10]{

    B0000001, // 0
    B1001111, // 1
    B0010010, // 2
    B0000110, // 3
    B1001100, // 4
    B0100100, // 5
    B0100000, // 6
    B0001111, // 7
    B0000000, // 8
    B0000100, // 9
};

/**
 * Inicializa los pines como salidas y establece una semilla para el generador de números aleatorios.
 *
 * El pin decenaTr y unidadTr se establecen como salidas para controlar el transistor
 * que activa el display de decenas o unidades. Luego, se establecen los 8 pines
 * necesarios para controlar cada segmento de los displays como salidas.
 *
 * Por último, se establece una semilla para el generador de números aleatorios
 * leyendo el valor analógico del pin A2.
 */
void setup()
{

  pinMode(decenaTr, OUTPUT);
  pinMode(unidadTr, OUTPUT);

  for (int led = 0; led < 8; led++)
  {
    pinMode(pines[led], OUTPUT);
  }

  randomSeed(analogRead(A2));
}

/**
 * Bucle principal del programa. Se encarga de:
 * - Leer el estado del botón
 * - Cambiar el valor de la variable pulso si se presiona el botón
 * - Generar un número aleatorio entre 0 y 99 si se presiona el botón
 * - Separar el número en decenas y unidades
 * - Mostrar el número en los displays
 * - Hacer una pausa de 10ms
 * - Mostrar el número en los displays
 *
 * @return void
 */
void loop()
{
  bool estadoBoton = digitalRead(A0);

  if (estadoBoton != estadoAnterior && estadoBoton == HIGH)
    pulso = !pulso;

  estadoAnterior = estadoBoton;
  if (pulso)
  {
    byte randomNum = random(100);
    separarNumero(randomNum);
    delay(10);
  }
  mostarNumero();
}

/**
 * Separa un número aleatorio en sus componentes de decenas y unidades.
 *
 * Este método toma un número aleatorio de dos dígitos (0-99) y calcula
 * el valor de las decenas y unidades. Los valores calculados se almacenan
 * en las variables globales 'unidad' y 'decena'.
 *
 * @param randomNum Número aleatorio a ser separado en decenas y unidades.
 */
void separarNumero(byte randomNum)
{
  unidad = randomNum / 10;
  decena = (randomNum % 10) / 1;
}

/**
 * Muestra en los displays el número separado en decenas y unidades.
 *
 * Este método se encarga de mostrar en los displays el número
 * separado en decenas y unidades. Primero activa el transistor
 * de la decena y muestra el valor de la decena en el display,
 * luego espera un tiempo definido en la variable 'pausa' y
 * finalmente hace lo mismo para la unidad.
 */
void mostarNumero()
{
  digitalWrite(decenaTr, HIGH);
  digitalWrite(unidadTr, LOW);
  PORTD = numerosAnodo[decena];
  delay(pausa);
  digitalWrite(decenaTr, LOW);
  digitalWrite(unidadTr, HIGH);
  PORTD = numerosAnodo[unidad];
  delay(pausa);
}