/* 

* Código escrito por: Esteban Carrillo para EDEPTEC. 
* Página web: https://www.edeptec.com
* Facebook: @edeptec
* Youtube: https://youtube.com/c/EDEPTEC

*/

byte pines [] = {2, 3, 4, 5, 6, 7, 8};

#define decenaTr 11
#define unidadTr 12

int numero;
byte unidad;
byte decena;
byte pausa = 5;
byte digitos[2];
bool numeroCompleto = false;

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
  Serial.begin(9600);
 
  pinMode(decenaTr, OUTPUT);
  pinMode(unidadTr, OUTPUT);

  for (byte led = 0; led < 8; led++) {
    pinMode(pines[led], OUTPUT);
  }
}

void loop() {
  
  byte n;
  int numeroPuertoSerial = lecturaPuertoSerial();

  if (numeroCompleto) {
    numero = numeroPuertoSerial;
    numeroCompleto = false;
  }
  
  separarNumero(numero);

  digitos[0] = numerosAnodo[unidad];
  digitos[1] = numerosAnodo[decena];
    
  digitalWrite(decenaTr, 1);
  digitalWrite(unidadTr, 0);
  mostrarDigito(n);
  n = 1;
  delay(pausa);
  digitalWrite(decenaTr, 0);
  digitalWrite(unidadTr, 1);
  mostrarDigito(n);
  n = 0;
  delay(pausa);
}

int lecturaPuertoSerial() {
  
  while (Serial.available()) {
    
    String numero = Serial.readStringUntil('\n');
    numeroCompleto = true;

    if (numero.length() > 2) {
    } else {
      return numero.toInt();
    }
  }
}

void separarNumero(int numero) {
  decena = numero / 10;
  unidad = (numero % 10) / 1;
}

void mostrarDigito(byte n) {
  
  for (int i = 6; i >= 0; i--) {
    digitalWrite(pines[i], (digitos[n] & (1 << i) ? 1 : 0));
  }
}
