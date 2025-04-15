#ifndef HandleLed_h
#define HandleLed_h

class HandleLed
{
  public:
    HandleLed(int buttonPin, int  ledPin);
    void handleLed();
  private:
    int _buttonPin;
    int _ledPin;
    bool _estadoDelLed;
    bool _estadoPrevio;
};
#endif