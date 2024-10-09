#ifndef ATMEGA328P_TIMER2_H
#define ATMEGA328P_TIMER2_H

#include <Arduino.h>

/**
 * @brief Class for controlling Timer2 on the Atmel ATMega328P (Arduino Uno, Nano).
 * This class allows setting up and controlling Timer2 for generating periodic interrupts
 * based on the desired time period in microseconds with ISR(TIMER2_COMPA_vect){}
 */
class ATMega328PTimer2 {
  public:
    /**
     * @brief Constructor for ATMega328PTimer2.
     * Initializes the timer with a default period of 1000 microseconds (1 kHz).
     */
    ATMega328PTimer2();

    /**
     * @brief Initializes Timer2 with the given period in microseconds.
     * This method calculates and sets the appropriate prescaler and Output Compare Register (OCR2A)
     * to match the desired period, ensuring Timer2 triggers an interrupt at the specified frequency.
     * 
     * @param periodMicros Desired timer period in microseconds (µs).
     *                     For example, 1000000 µs for 1 Hz, or 1000 µs for 1 kHz.
     */
    void initialize(uint32_t periodMicros);

    /**
     * @brief Starts Timer2.
     * Enables the Timer2 Output Compare Match A interrupt, which will trigger the ISR at the configured frequency.
     */
    void start();

    /**
     * @brief Stops Timer2.
     * Disables the Timer2 Output Compare Match A interrupt, effectively stopping the timer.
     */
    void stop();

  private:
    /**
     * @brief Sets the Timer2 prescaler based on the input prescaler value.
     * Configures the Timer2 clock prescaler according to the provided prescaler value (e.g., 1, 8, 64, 256, etc.).
     * This method is used internally by the `initialize()` function to set the prescaler.
     * 
     * @param prescaler The prescaler value to set (valid values: 1, 8, 32, 64, 128, 256, 1024).
     */
    void setPrescaler(uint16_t prescaler);
};

#endif // ATMEGA328P_TIMER2_H
