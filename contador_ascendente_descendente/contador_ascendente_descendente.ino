/*

* Código escrito por: Esteban Carrillo para EDEPTEC.
* Página web: https://www.edeptec.com
* Facebook: @edeptec
* Youtube: https://youtube.com/c/EDEPTEC

*/

byte pinesDisplays[] = {2, 3, 4, 5, 6, 7, 8}; // Pines de conexion para los displays.
                                              //  {g, f, e, d, c, b, a}

#define decenaTr 11 // Pin para activar el display de decenas
#define unidadTr 12 // Pin para activar el display de unidades

bool estadoAnteriorPulSuma = 0;  // Variable para almacenar el estado anterior del botón de suma
bool estadoAnteriorPulResta = 0; // Variable para almacenar el estado anterior del botón de resta

byte decena = 0; // Variable para almacenar la decena del número
byte unidad = 0; // Variable para almacenar la unidad del número
int numero = 0;  // Variable para almacenar el número

byte digitos[2]; // Array para almacenar los valores que se muestran en los displays

byte pausa = 50; // Variable para almacenar la duración de la pausa

byte numerosAnodo[]{
    // Numeros que se mostraran en el display de 7 segmentos en binario
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

void setup()
{
  // español
  pinMode(decenaTr, OUTPUT);
  pinMode(unidadTr, OUTPUT);

  for (int led = 0; led < 8; led++)
  {
    pinMode(pinesDisplays[led], OUTPUT);
  }
}

/**
 * El bucle principal del programa.
 *
 * En este bucle se verifica el estado de los dos pulsadores (pulSuma y pulResta)
 * y se actualiza el valor de la variable numero en base al estado de
 * los pulsadores. Luego, se verifica que el valor de numero se encuentre
 * dentro del rango [0, 99] y se ajusta en caso de que no sea así.
 *
 * Finalmente, se llama al método separarNumero() para separar el valor
 * de numero en decenas y unidades y se llama al método mostrarDigito()
 * para mostrar en los displays los valores de decena y unidad.
 */
void loop()
{

  bool estadoPulSuma = digitalRead(A0);
  bool estadoPulResta = digitalRead(A1);

  if (estadoPulSuma != estadoAnteriorPulSuma)
  {
    (estadoPulSuma == HIGH) && numero++;
  }

  if (estadoPulResta != estadoAnteriorPulResta)
  {
    (estadoPulResta == HIGH) && numero--;
  }

  if (numero < 0)
    numero = 0;
  if (numero > 99)
    numero = 99;

  estadoAnteriorPulSuma = estadoPulSuma;
  estadoAnteriorPulResta = estadoPulResta;
  separarNumero();

  digitos[0] = numerosAnodo[unidad];
  digitos[1] = numerosAnodo[decena];

  digitalWrite(decenaTr, 1); // Activar el display de decenas
  digitalWrite(unidadTr, 0); // Desactivar el display de unidades
  mostrarDigito("decena");   // Mostrar el valor de decena en el display
  delay(pausa);              // Esperar la duración de la pausa
  digitalWrite(decenaTr, 0); // Desactivar el display de decenas
  digitalWrite(unidadTr, 1); // Activar el display de unidades
  mostrarDigito("unidad");   // Mostrar el valor de unidad en el display
  delay(pausa);              // Esperar la duración de la pausa
}

/**
 * Separa un número en sus componentes de decenas y unidades.
 *
 * Este método toma el valor de la variable 'numero' y lo separa en
 * sus componentes de decenas y unidades. Los valores calculados se
 * almacenan en las variables globales 'decena' y 'unidad'.
 */
void separarNumero()
{
  decena = numero / 10;
  unidad = (numero % 10) / 1;
}
/**
 * Muestra un dígito en el display.
 *
 * Este método toma la posición del dígito que se va a mostrar
 * (ya sea "unidad" o "decena") y muestra el valor correspondiente
 * en el display. Este método utiliza el array 'digitos' que contiene
 * el valor de las decenas y unidades.
 *
 * @param posicion Posición del dígito que se va a mostrar
 */
void mostrarDigito(String posicion)
{
  byte n;
  if (posicion.equals("unidad"))
    n = 0;
  if (posicion.equals("decena"))
    n = 1;

  for (int i = 6; i >= 0; i--)
  {
    digitalWrite(pinesDisplays[i], (digitos[n] & (1 << i) ? 1 : 0));
  }
}
