#include <Servo.h>
Servo myservo;
#define ldr 7
#define open 6
#define mode 5

int angle = 0;
unsigned long previousTime = 0;
int delayTime = 6000;

void setup() {
  myservo.attach(11);
  pinMode(ldr, INPUT);
  pinMode(open, INPUT);
  pinMode(mode, INPUT);
}

void loop() {
  bool ldrState = digitalRead(ldr);
  bool openState = digitalRead(open);
  bool modeState = digitalRead(mode);

  unsigned long startingTime = millis();

  if (!ldrState && openState ) {
    previousTime = startingTime;
    angle = 90;

  }

  if ((angle == 90 && ldrState && openState) || (!modeState && startingTime - previousTime >= delayTime)) angle = 0;

  myservo.write(angle);

}