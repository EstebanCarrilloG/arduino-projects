/* 

* Código escrito por: Esteban Carrillo para EDEPTEC. 
* Página web: https://www.edeptec.com
* Facebook: @edeptec
* Youtube: https://youtube.com/c/EDEPTEC

*/

int pinesLedsDisplay[] = { 0, 1, 2, 3, 4, 5, 6 };

#define transistorDecena 8
#define transistorUnidad 10
byte unidad = 0;
byte decena = 0;
short pausa = 50;
short velocidad = 2;

byte numerosAnodo[]{
  B0000001,  //0
  B1001111,  //1
  B0010010,  //2
  B0000110,  //3
  B1001100,  //4
  B0100100,  //5
  B0100000,  //6
  B0001111,  //7
  B0000000,  //8
  B0000100,  //9
};

byte numerosCatodo[]{
  B1111110,  //0
  B0110000,  //1
  B1101101,  //2
  B1111001,  //3
  B0110011,  //4
  B1011011,  //5
  B1011111,  //6
  B1110000,  //7
  B1111111,  //8
  B1111011,  //9
};

void setup() {
  pinMode(transistorDecena, OUTPUT);
  pinMode(transistorUnidad, OUTPUT);

  for (int led = 0; led < 8; led++) {
    pinMode(pinesLedsDisplay[led], OUTPUT);
  }
}

void loop() {

  unidad++;

  if (unidad == 10) {
    unidad = 0;
    decena++;
  }

  (decena == 10) ? decena = 0 : decena = decena;

  for (int z = 0; z < velocidad; z++) {
    digitalWrite(transistorDecena, HIGH);
    digitalWrite(transistorUnidad, LOW);
    PORTD = numerosAnodo[decena];
    delay(pausa);
    digitalWrite(transistorDecena, LOW);
    digitalWrite(transistorUnidad, HIGH);
    PORTD = numerosAnodo[unidad];
    delay(pausa);
  }
}
