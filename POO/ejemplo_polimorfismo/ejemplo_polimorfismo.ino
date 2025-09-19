/*
  Ejemplo sencillo de POO y polimorfismo en Arduino con un LED
  Autor: Esteban Carrillo
*/

class Led {
protected:
  int pin;  // el pin donde está conectado el LED
public:
  Led(int p) {  // constructor: se ejecuta al crear el LED
    pin = p;
    pinMode(pin, OUTPUT);
  }
  virtual void encender() = 0;  // función "abstracta": cada LED la hará a su manera
};

// LED que se enciende fijo
class LedFijo : public Led {
public:
  LedFijo(int p)
    : Led(p) {}  // llama al constructor de Led
  void encender() override {
    digitalWrite(pin, HIGH);  // siempre encendido
  }
};

// LED que parpadea
class LedParpadeo : public Led {
private:
  unsigned long tiempoAnterior;
  int intervalo;
  bool estado;
public:
  LedParpadeo(int p, int ms)
    : Led(p) {
    intervalo = ms;
    tiempoAnterior = 0;
    estado = false;
  }
  void encender() override {
    unsigned long tiempoActual = millis();
    if (tiempoActual - tiempoAnterior >= intervalo) {
      estado = !estado;  // cambia el estado (encendido/apagado)
      digitalWrite(pin, estado ? HIGH : LOW);
      tiempoAnterior = tiempoActual;
    }
  }
};

// Creamos un puntero a la clase base (para polimorfismo)
Led* miLed;

void setup() {
  // Aquí decides el tipo de LED:
  // miLed = new LedFijo(13);        // LED siempre encendido
  miLed = new LedParpadeo(13, 500);  // LED parpadea cada 500 ms
}

void loop() {
  miLed->encender();  // siempre llamamos a encender,
                      // pero el resultado depende del tipo de LED
}