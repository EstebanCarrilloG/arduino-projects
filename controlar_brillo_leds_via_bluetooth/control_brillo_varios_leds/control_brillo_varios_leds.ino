int leds[3] = {5, 6, 9};

String str = "";
const char separador = ',';
const int numeroDeDatos = 3;
int dato[numeroDeDatos];

void setup()
{
  Serial.begin(9600);
  for (int i = 0; i < 4; i++) {
    pinMode(leds[i], OUTPUT);
  }
}

void loop()
{
  if (Serial.available())
  {
    str = Serial.readStringUntil(']');
    str.remove(0, 1);
   


    for (int i = 0; i < numeroDeDatos ; i++)
    {
      int index = str.indexOf(separador);
      dato[i] = str.substring(0, index).toInt();
      str = str.substring(index + 1);
    }

  }
   
  for (int i = 0; i < numeroDeDatos; i++) {
    analogWrite(leds[i], dato[i]);
  }
}
