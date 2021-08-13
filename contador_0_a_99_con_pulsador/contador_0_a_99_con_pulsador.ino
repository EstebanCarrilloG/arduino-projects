int pines [] = {0, 1, 2, 3, 4, 5, 6};

#define tr1 8
#define tr2 10
#define pulsador A0

bool estadoP = 0;
byte n1 = 0;
byte n2 = 0;
short pausa = 50;

byte numerosAnodo[] {
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
  pinMode(tr1, OUTPUT);
  pinMode(tr2, OUTPUT);
  pinMode(pulsador, INPUT);

  for (int led = 0; led < 8; led++) {
    pinMode(pines[led], OUTPUT);
  }
}

void loop() {
  
  
  bool  pul = digitalRead(pulsador);

  if (pul != estadoP) {
    if (pul == HIGH) {

      n1++;

      if (n1 == 10 ) {
        n1 = 0;
        n2++;
      }
      if (n2 == 10){
        n2 = 0;
      }
   }
  }
  
  estadoP = pul;
 
  digitalWrite(tr1, HIGH);
  digitalWrite(tr2, LOW);
  PORTD = numerosAnodo[n2];
  delay(pausa);
  digitalWrite(tr1, LOW);
  digitalWrite(tr2, HIGH);
  PORTD = numerosAnodo[n1];
  delay(pausa);

}
