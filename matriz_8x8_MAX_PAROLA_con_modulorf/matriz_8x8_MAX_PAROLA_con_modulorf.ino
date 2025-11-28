#include <MD_Parola.h>
#include <MD_MAX72xx.h>
#include <SPI.h>

#define HARDWARE_TYPE MD_MAX72XX::FC16_HW  ///DR0CR0RR1_HW
#define MAX_DEVICES 5
#define CLK_PIN 4
#define DATA_PIN 2
#define CS_PIN 3

MD_Parola P = MD_Parola(HARDWARE_TYPE, DATA_PIN, CLK_PIN, CS_PIN, MAX_DEVICES);

struct animations {
  textEffect_t anim_in;
  textEffect_t anim_out;
  const char* textOut;
  uint16_t speed;
  uint16_t pause;
  textPosition_t just;
};

animations animList[] = {
  { PA_SCROLL_LEFT, PA_SCROLL_LEFT, "Hola mundo", 4, 0, PA_LEFT },
  { PA_SCROLL_LEFT, PA_SCROLL_LEFT, "Hello world", 4, 0, PA_LEFT }
};

byte pulsadorMsg1 = A0;
byte pulsadorMsg2 = A1;
byte pulsadorParar = A2;

void setup() {
  Serial.begin(9600);
  P.begin();
  P.setIntensity(15);

  for (uint8_t i = 0; i < ARRAY_SIZE(animList); i++) {
    animList[i].speed *= P.getSpeed();
    animList[i].pause *= 500;
  }
}

void loop() {
  if (digitalRead(pulsadorMsg1)) {
    imprimirString(animList[0]);
  }

  if (digitalRead(pulsadorMsg2)) {
    imprimirString(animList[1]);
  }
}
bool detener() {
  if (digitalRead(pulsadorParar)) {
    P.print("");
    return true;
  }
  return false;
}

void imprimirString(animations list) {

  while (!detener()) {
    if (P.displayAnimate()) {
      P.setScrollSpacing(10);
      P.displayText(
        list.textOut,
        list.just,
        list.speed,
        list.pause,
        list.anim_in,
        list.anim_out);
    }
  }
}