#include <ATMega328PTimer2.h>

ATMega328PTimer2 Timer2;

ISR(TIMER2_COMPA_vect)
{
    static uint8_t counter = 0;
    static bool ledState = false;

    if (++counter == 100)
    {  // Scale down to 1 Hz
        counter = 0;
        ledState = !ledState;
        digitalWrite(LED_BUILTIN, ledState);
    }
}

void setup()
{
    pinMode(LED_BUILTIN, OUTPUT);     // Set built-in LED as output
    Timer2.initialize(10000);         // Initialize Timer2 with a 10 ms period
    Timer2.start();                   // Start Timer2
}

void loop()
{
    // The main loop is empty, LED toggling is handled in the ISR
}
