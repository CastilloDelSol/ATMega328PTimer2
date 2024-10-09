# ATMega328PTimer2 Library

## Overview

**ATMega328PTimer2** is a lightweight library for the Arduino platform (specifically for the ATMega328P, such as the Arduino Uno or Nano) that simplifies the usage of Timer2. This library allows for easy timer initialization with custom periods in microseconds, enabling precise control of tasks like toggling LEDs or generating periodic interrupts.

The library is ideal for developers who need to offload timing tasks to hardware timers, freeing up the main loop for other activities.

## Features

- Initialize Timer2 with custom periods (in microseconds).
- Set up Timer2 for tasks like blinking an LED or generating regular interrupts.
- Start and stop the timer easily.
- Suitable for Arduino Uno, Nano, or other boards using ATMega328P.
- Supports prescaler configurations for flexible timing options.

## Installation

1. Download the repository as a `.zip` file.
2. In the Arduino IDE, go to **Sketch** > **Include Library** > **Add .ZIP Library...**.
3. Select the downloaded `.zip` file.
4. The library is now ready to use!

Alternatively, you can manually copy the `ATMega328PTimer2` folder into your Arduino `libraries` folder.

## Usage

Below is a simple example that uses Timer2 to blink the built-in LED at a 1-second interval.

### Example: Blink

```cpp
#include <ATMega328PTimer2.h>

ATMega328PTimer2 Timer2;

void setup() {
    pinMode(LED_BUILTIN, OUTPUT);
    Timer2.initialize(10000); // Set up Timer2 with a 10ms period
    Timer2.start();           // Start the timer
}

void loop() {
    // The LED toggling is handled by the ISR, so nothing is needed in the main loop
}

// Interrupt Service Routine for Timer2 Compare Match
ISR(TIMER2_COMPA_vect) {
    static uint8_t counter = 0;
    static bool ledState = false;

    if (++counter == 100) { // Scale down to 1Hz
        counter = 0;
        ledState = !ledState;
        digitalWrite(LED_BUILTIN, ledState);
    }
}
```

### API Documentation

- `ATMega328PTimer2::initialize(uint32_t periodMicros)`
    - Initializes Timer2 with a specified period in microseconds.
    - @param `periodMicros`: Desired period in microseconds.
  
- `ATMega328PTimer2::start()`
    - Starts the timer and enables the compare match interrupt.

- `ATMega328PTimer2::stop()`
    - Stops the timer and disables the compare match interrupt.

- `ATMega328PTimer2::setPrescaler(uint16_t prescaler)`
    - (Private function) Sets the timer prescaler according to the desired frequency.

## License

This library is released under the MIT License. See the [LICENSE](LICENSE) file for more details.
