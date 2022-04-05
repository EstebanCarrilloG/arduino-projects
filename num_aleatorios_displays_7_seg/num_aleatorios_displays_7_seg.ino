/* 

* Código escrito por: Esteban Carrillo para EDEPTEC. 
* Página web: https://www.edeptec.com
* Facebook: @edeptec
* Youtube: https://youtube.com/c/EDEPTEC

*/

int pines [] = {0, 1, 2, 3, 4, 5, 6};

#define decenaTr 8
#define unidadTr 10

bool estado;
int unidad;
int decena;
short pausa = 5;
int randomNum;
byte pulso;

byte numerosAnodo[10] {

  B0000001,//0
  B1001111,//1
  B0010010,//2
  B0000110,//3
  B1001100,//4
  B0100100,//5
  B0100000,//6
  B0001111,//7
  B0000000,//8
  B0000100,//9
};

void setup() {

  pinMode(decenaTr, OUTPUT);
  pinMode(unidadTr, OUTPUT);

  for (int led = 0; led < 8; led++) {
    pinMode(pines[led], OUTPUT);
  }
}

void loop() {

  bool startStop = digitalRead(A0);

  mostarNumero();

  if (startStop != estado) {
    if (startStop == HIGH) {
      pulso++;
    }
  }

  estado = startStop;

  if (pulso % 2 == 0) {} else {

    randomNum = random(0, 99);
    separarNumero();
    mostarNumero();
    delay(10);

  }
}

void separarNumero() {

  unidad = randomNum / 10;
  decena = (randomNum % 10) / 1;

}

void mostarNumero() {

  digitalWrite(decenaTr, HIGH);
  digitalWrite(unidadTr, LOW);
  PORTD = numerosAnodo[decena];
  delay(pausa);
  digitalWrite(decenaTr, LOW);
  digitalWrite(unidadTr, HIGH);
  PORTD = numerosAnodo[unidad];
  delay(pausa);
}
