int pines [] = {0, 1, 2, 3, 4, 5, 6};

#define decenaTr 8
#define unidadTr 10
 
bool estadoUp = 0;
bool estadoDown = 0;
 
byte decena = 0;
byte unidad = 0;
 
short pausa = 5;
 
byte numerosAnodo[] {
  B0000000,//NA
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
 
byte numerosCatodo[] {
 
  B0000000,//NA
  B1111110,//0
  B0110000,//1
  B1101101,//2
  B1111001,//3
  B0110011,//4
  B1011011,//5
  B1011111,//6
  B1110000,//7
  B1111111,//8
  B1111011,//9
};
 
 
void setup() {
 
  pinMode(decenaTr, OUTPUT);
  pinMode(unidadTr, OUTPUT);
 
  for (int led = 0; led < 8; led++) {
    pinMode(pines[led], OUTPUT);
  }
  decena = 1;
  unidad = 1;
}
 
void loop() {
 
  bool  pUp = digitalRead(A0);
  bool  pDown = digitalRead(A1);
 
  if (pUp != estadoUp) {
    if (pUp == HIGH) {
     
      if (unidad == 10 && decena == 10){
        decena = 10;
        unidad = 10;           
      } else {
        decena++;
      }
 
      if (decena == 11 ) {
        decena = 1;
        unidad++;
      }
    }
  }
 
  if (pDown != estadoDown) {
    if (pDown == HIGH) {
 
      decena--;
 
      if (decena == 0) {
        decena = 10;
        unidad--;
      }
    }
  }
 
  if (decena == 10 && unidad == 0){
    decena = 1;
    unidad = 1;
  }
     
  estadoUp = pUp;
  estadoDown = pDown;
 
  digitalWrite(decenaTr, HIGH);
  digitalWrite(unidadTr, LOW);
  PORTD = numerosAnodo[unidad];
  delay(pausa);
  digitalWrite(decenaTr, LOW);
  digitalWrite(unidadTr, HIGH);
  PORTD = numerosAnodo[decena];
  delay(pausa);
  
}
