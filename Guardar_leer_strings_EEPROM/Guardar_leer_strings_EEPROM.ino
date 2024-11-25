/* 

* Código escrito por: Esteban Carrillo para EDEPTEC. 
* Página web: https://www.edeptec.com
* Facebook: @edeptec
* Youtube: https://youtube.com/c/EDEPTEC

*/

#include <EEPROM.h>
/**
 * Escribe una cadena de caracteres en la memoria EEPROM empezando en addrOffset.
 *
 * Primero escribe la longitud de la cadena en addrOffset.
 * Luego escribe cada caracter de la cadena en addrOffset + 1,
 * addrOffset + 2, addrOffset + 3, etc ...
 *
 * @param addrOffset La posición de memoria de la EEPROM donde se
 *                   empezará a escribir.
 * @param strToWrite La cadena de texto a escribir en la EEPROM.
 */
void writeStringToEEPROM(int addrOffset, const String &strToWrite)
{
  byte len = strToWrite.length(); // Calcula la longitud de la cadena
  EEPROM.write(addrOffset, len); // Define en que posicion de la EEPROM empezar a escribir y la longitud de la cadena

  for (int i = 0; i < len; i++) // Recorre la cadena
  {
    EEPROM.write(addrOffset + 1 + i, strToWrite[i]); // Escribe cada caracter en la EEPROM
  }
}

/**
 * Lee una cadena de caracteres almacenada en la memoria EEPROM
 * empezando en addrOffset.
 *
 * Primero lee la longitud de la cadena en addrOffset.
 * Luego lee cada caracter de la cadena en addrOffset + 1,
 * addrOffset + 2, addrOffset + 3, etc ...
 *
 * @param addrOffset La posición de memoria de la EEPROM desde
 *                   la que se leerá.
 * @return La cadena de texto leida de la EEPROM.
 */
String readStringFromEEPROM(int addrOffset)
{
  int newStrLen = EEPROM.read(addrOffset); // Leemos la longitud de la cadena
  char data[newStrLen + 1]; // Creamos un array para almacenar la cadena

  for (int i = 0; i < newStrLen; i++) // Recorre la cadena
  {
    data[i] = EEPROM.read(addrOffset + 1 + i); // Lee cada caracter y lo guarda en el array data
  }
  data[newStrLen] = '\0'; // Termina de leer la cadena
  return String(data); // Devuelve la cadena
}

/**
* Función de configuración. Este es el punto de entrada principal del programa.
*
* En esta función, escribimos una cadena en la EEPROM y la leemos.
* Luego, imprimimos la cadena en el monitor serial.
*/
void setup() {

  Serial.begin(9600);

  writeStringToEEPROM(0, "123A"); // Guardael string en la EEPROM
  
  String retrievedString = readStringFromEEPROM(0); // Leemos el string almacenado

  Serial.print("The String we read from EEPROM: ");
  Serial.println(retrievedString); // Imprimimos el string en el monitor Serial
}

void loop() {}

