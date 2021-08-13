#define pul1 A0
#define pul2 A1
#define pul3 A2

#define led 2

boolean set;
boolean mas;
boolean menos;

boolean estadoAnterior = 0;
short x;
int tiempo = 100;

void setup() {

  Serial.begin(9600);
  pinMode(pul1, INPUT);
  pinMode(pul2, INPUT);
  pinMode(pul3, INPUT);
  pinMode(led, OUTPUT);
}

void loop() {

  selec();

  if (x == 1) {

    Serial.println(tiempo);

    digitalWrite(led, HIGH);
    delay(tiempo);
    digitalWrite(led, LOW);
    delay(tiempo);

    mas = digitalRead(pul2);
    menos = digitalRead(pul1);

    if (mas == HIGH) {
      tiempo = tiempo + 100;
      delay(10);
    }
    if (menos == HIGH) {
      tiempo = tiempo - 100;
      delay(10);
    }

    if (tiempo <= 100) {
      tiempo = 100;
    }
    if (tiempo > 3000) {
      tiempo = 3000;
    }

    selec();


  } else {

    digitalWrite(led, LOW);
  }


}

void selec() {

  set = digitalRead(pul3);

  if (set != estadoAnterior) {
    if (set == HIGH) {
      x++;
      Serial.println(set);
    }
  }

  estadoAnterior = set;

  if (x == 2 ) {
    x = 0;
  }

  delay(50);
}
