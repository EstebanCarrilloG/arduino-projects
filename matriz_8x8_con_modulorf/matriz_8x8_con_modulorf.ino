/* 

* Código escrito por: Esteban Carrillo para EDEPTEC. 
* Página web: https://www.edeptec.com
* Facebook: @edeptec
* Youtube: https://youtube.com/c/EDEPTEC

*/

/*
Conexiones del Arduino al Modulo MAX7219:
ARDUINIO    MAX7219
 10          CLK
 9           CS
 8           DIN
 GND         GND
 5V          VCC
 
Conexion  de la cascada de MAX7219(1)  al MAX7219(2)
MAX7219(1)   MAX7219(2)  
  CLK          CLK
   CS           CS
  DOUT         DIN
  GND          GND
  VCC          VCC
La cascada se hace conectano de los pines Superiores a los inferiores del modulo MAX7219
y los modulos se instalan de derecha a izquierda        
*/

#include <MaxMatrix.h> //https://code.google.com/archive/p/arudino-maxmatrix-library/
//#include <avr/pgmspace.h>
PROGMEM unsigned char const CH[] = { // Caracteres
  3, 8, B00000000, B00000000, B00000000, B00000000, B00000000,  // space
  1, 8, B01011111, B00000000, B00000000, B00000000, B00000000,  // !
  3, 8, B00000011, B00000000, B00000011, B00000000, B00000000,  // "
  5, 8, B00010100, B00111110, B00010100, B00111110, B00010100,  // #
  4, 8, B00100100, B01101010, B00101011, B00010010, B00000000,  // $
  5, 8, B01100011, B00010011, B00001000, B01100100, B01100011,  // %
  5, 8, B00110110, B01001001, B01010110, B00100000, B01010000,  // &
  1, 8, B00000011, B00000000, B00000000, B00000000, B00000000,  // '
  3, 8, B00011100, B00100010, B01000001, B00000000, B00000000,  // (
  3, 8, B01000001, B00100010, B00011100, B00000000, B00000000,  // )
  5, 8, B00101000, B00011000, B00001110, B00011000, B00101000,  // *
  5, 8, B00001000, B00001000, B00111110, B00001000, B00001000,  // +
  2, 8, B10110000, B01110000, B00000000, B00000000, B00000000,  // ,
  4, 8, B00001000, B00001000, B00001000, B00001000, B00000000,  // -
  2, 8, B01100000, B01100000, B00000000, B00000000, B00000000,  // .
  4, 8, B01100000, B00011000, B00000110, B00000001, B00000000,  // /
  4, 8, B00111110, B01000001, B01000001, B00111110, B00000000,  // 0
  3, 8, B01000010, B01111111, B01000000, B00000000, B00000000,  // 1
  4, 8, B01100010, B01010001, B01001001, B01000110, B00000000,  // 2
  4, 8, B00100010, B01000001, B01001001, B00110110, B00000000,  // 3
  4, 8, B00011000, B00010100, B00010010, B01111111, B00000000,  // 4
  4, 8, B00100111, B01000101, B01000101, B00111001, B00000000,  // 5
  4, 8, B00111110, B01001001, B01001001, B00110000, B00000000,  // 6
  4, 8, B01100001, B00010001, B00001001, B00000111, B00000000,  // 7
  4, 8, B00110110, B01001001, B01001001, B00110110, B00000000,  // 8
  4, 8, B00000110, B01001001, B01001001, B00111110, B00000000,  // 9
  2, 8, B01010000, B00000000, B00000000, B00000000, B00000000,  // :
  2, 8, B10000000, B01010000, B00000000, B00000000, B00000000,  // ;
  3, 8, B00010000, B00101000, B01000100, B00000000, B00000000,  // <
  3, 8, B00010100, B00010100, B00010100, B00000000, B00000000,  // =
  3, 8, B01000100, B00101000, B00010000, B00000000, B00000000,  // >
  4, 8, B00000010, B01011001, B00001001, B00000110, B00000000,  // ?
  5, 8, B00111110, B01001001, B01010101, B01011101, B00001110,  // @
  4, 8, B01111110, B00010001, B00010001, B01111110, B00000000,  // A
  4, 8, B01111111, B01001001, B01001001, B00110110, B00000000,  // B
  4, 8, B00111110, B01000001, B01000001, B00100010, B00000000,  // C
  4, 8, B01111111, B01000001, B01000001, B00111110, B00000000,  // D
  4, 8, B01111111, B01001001, B01001001, B01000001, B00000000,  // E
  4, 8, B01111111, B00001001, B00001001, B00000001, B00000000,  // F
  4, 8, B00111110, B01000001, B01001001, B01111010, B00000000,  // G
  4, 8, B01111111, B00001000, B00001000, B01111111, B00000000,  // H
  3, 8, B01000001, B01111111, B01000001, B00000000, B00000000,  // I
  4, 8, B00110000, B01000000, B01000001, B00111111, B00000000,  // J
  4, 8, B01111111, B00001000, B00010100, B01100011, B00000000,  // K
  4, 8, B01111111, B01000000, B01000000, B01000000, B00000000,  // L
  5, 8, B01111111, B00000010, B00001100, B00000010, B01111111,  // M
  5, 8, B01111111, B00000100, B00001000, B00010000, B01111111,  // N
  4, 8, B00111110, B01000001, B01000001, B00111110, B00000000,  // O
  4, 8, B01111111, B00001001, B00001001, B00000110, B00000000,  // P
  4, 8, B00111110, B01000001, B01000001, B10111110, B00000000,  // Q
  4, 8, B01111111, B00001001, B00001001, B01110110, B00000000,  // R
  4, 8, B01000110, B01001001, B01001001, B00110010, B00000000,  // S
  5, 8, B00000001, B00000001, B01111111, B00000001, B00000001,  // T
  4, 8, B00111111, B01000000, B01000000, B00111111, B00000000,  // U
  5, 8, B00001111, B00110000, B01000000, B00110000, B00001111,  // V
  5, 8, B00111111, B01000000, B00111000, B01000000, B00111111,  // W
  5, 8, B01100011, B00010100, B00001000, B00010100, B01100011,  // X
  5, 8, B00000111, B00001000, B01110000, B00001000, B00000111,  // Y
  4, 8, B01100001, B01010001, B01001001, B01000111, B00000000,  // Z
  2, 8, B01111111, B01000001, B00000000, B00000000, B00000000,  // [
  4, 8, B00000001, B00000110, B00011000, B01100000, B00000000,  // \ backslash
  2, 8, B01000001, B01111111, B00000000, B00000000, B00000000,  // ]
  3, 8, B00000010, B00000001, B00000010, B00000000, B00000000,  // hat
  4, 8, B01000000, B01000000, B01000000, B01000000, B00000000,  // _
  2, 8, B00000001, B00000010, B00000000, B00000000, B00000000,  // `
  4, 8, B00100000, B01010100, B01010100, B01111000, B00000000,  // a
  4, 8, B01111111, B01000100, B01000100, B00111000, B00000000,  // b
  4, 8, B00111000, B01000100, B01000100, B00101000, B00000000,  // c
  4, 8, B00111000, B01000100, B01000100, B01111111, B00000000,  // d
  4, 8, B00111000, B01010100, B01010100, B00011000, B00000000,  // e
  3, 8, B00000100, B01111110, B00000101, B00000000, B00000000,  // f
  4, 8, B10011000, B10100100, B10100100, B01111000, B00000000,  // g
  4, 8, B01111111, B00000100, B00000100, B01111000, B00000000,  // h
  3, 8, B01000100, B01111101, B01000000, B00000000, B00000000,  // i
  4, 8, B01000000, B10000000, B10000100, B01111101, B00000000,  // j
  4, 8, B01111111, B00010000, B00101000, B01000100, B00000000,  // k
  3, 8, B01000001, B01111111, B01000000, B00000000, B00000000,  // l
  5, 8, B01111100, B00000100, B01111100, B00000100, B01111000,  // m
  4, 8, B01111100, B00000100, B00000100, B01111000, B00000000,  // n
  4, 8, B00111000, B01000100, B01000100, B00111000, B00000000,  // o
  4, 8, B11111100, B00100100, B00100100, B00011000, B00000000,  // p
  4, 8, B00011000, B00100100, B00100100, B11111100, B00000000,  // q
  4, 8, B01111100, B00001000, B00000100, B00000100, B00000000,  // r
  4, 8, B01001000, B01010100, B01010100, B00100100, B00000000,  // s
  3, 8, B00000100, B00111111, B01000100, B00000000, B00000000,  // t
  4, 8, B00111100, B01000000, B01000000, B01111100, B00000000,  // u
  5, 8, B00011100, B00100000, B01000000, B00100000, B00011100,  // v
  5, 8, B00111100, B01000000, B00111100, B01000000, B00111100,  // w
  5, 8, B01000100, B00101000, B00010000, B00101000, B01000100,  // x
  4, 8, B10011100, B10100000, B10100000, B01111100, B00000000,  // y
  3, 8, B01100100, B01010100, B01001100, B00000000, B00000000,  // z
  3, 8, B00001000, B00110110, B01000001, B00000000, B00000000,  // {
  1, 8, B01111111, B00000000, B00000000, B00000000, B00000000,  // |
  3, 8, B01000001, B00110110, B00001000, B00000000, B00000000,  // }
  4, 8, B00001000, B00000100, B00001000, B00000100, B00000000,  // ~
};

int data = 8;    // DIN pin del modulo MAX7219
int load = 9;    // CS pin del modulo MAX7219
int clock = 10;  // CLK pin del modulo MAX7219

int numeroDeMatrices = 1;  //Cambie este valor dependiendo del numero de matrices que use

MaxMatrix m(data, load, clock, numeroDeMatrices);  // Crear el objeto de matriz

byte buffer[10]; 

//Define los botones
byte pulsadorMsg1 = A0; 
byte pulsadorMsg2 = A1;
byte pulsadorParar = A2;


String mensaje1 = "HOLA MUNDO ";  // Cadena de caracteres a imprimir
String mensaje2 = "HELLO WORLD "; // Cadena de caracteres a imprimir

/**
 * Inicializa los pines de los pulsadores como entradas, inicializa el modulo
 * MAX7219 y establece la intensidad de los puntos de la matriz. Tambien
 * inicializa el puerto serial.
 */
void setup() {
  pinMode(pulsadorMsg1, INPUT); 
  pinMode(pulsadorMsg2, INPUT);
  pinMode(pulsadorParar, INPUT);
  m.init();            // inicializa el modulo
  m.setIntensity(5);   // intencidad de los puntos de la matriz, entre 1-5
  Serial.begin(9600);  // inicializa el puerto serial
}

/**
 * Bucle principal del programa.
 *
 * En este bucle se limpia la matriz, se verifica el estado de los pulsadores
 * y se imprimen los mensajes correspondientes a cada pulsador.
 * La velocidad de desplazamiento se establece en 90 y 60 milisegundos para
 * cada mensaje.
 */
void loop() {
  m.clear();

  if (digitalRead(pulsadorMsg1)) {
    imprimirString(mensaje1, 90);
  }

  if (digitalRead(pulsadorMsg2)) {
    imprimirString(mensaje2, 60);
  }
}
/**
 * Verifica el estado del pulsador de parar y si se ha pulsado, limpia
 * la matriz y devuelve true. En caso contrario, devuelve false.
 * 
 * @return true si se ha pulsado el pulsador de parar, false en caso
 *         contrario.
 */
bool detener() {
  if (digitalRead(pulsadorParar)) {
    m.clear();
    return true;
  }
  return false;
}

/**
 * Imprime una cadena de caracteres en la matriz de LEDs.
 *
 * Este metodo utiliza el metodo writeSprite para escribir los caracteres
 * en la matriz. El caracter a imprimir se obtiene de la cadena de
 * caracteres "texto" y se desplaza hacia la izquierda hasta que se
 * pulsa el pulsador de parar.
 *
 * @param texto cadena de caracteres a imprimir
 * @param velocidadDesplazamiento velocidad de desplazamiento de los caracteres
 */
void imprimirString(String texto, int velocidadDesplazamiento) {  // Imprime cadena de caracteres
  int i = 0;
  int longitudDeCadena = texto.length() - 1;
  while (!detener()) {
    char caracter;
    caracter = texto[i] - 32;

    memcpy_P(buffer, CH + 7 * caracter, 7);
    m.writeSprite(numeroDeMatrices * 8, 0, buffer);
    m.setColumn(numeroDeMatrices * 8 + buffer[0], 0);

    for (int i = 0; i < buffer[0] + 1; i++) {
      delay(velocidadDesplazamiento);
      m.shiftLeft(false, false);
    }
    i++;
    (i > longitudDeCadena) ? i = 0 : 0; // Si i es mayor que la longitud de la cadena, se reinicia
  }
}
