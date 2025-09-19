#ifndef LEDRGB_H
#define LEDRGB_H

#include "Led.h"

class LedRGB : public Led {
private:
  int pinR, pinG, pinB;  // Pines de cada color

public:
  LedRGB(int r, int g, int b);

  void iniciar() override;
  void setColor(int rojo, int verde, int azul);
  void apagar() override;
};

#endif