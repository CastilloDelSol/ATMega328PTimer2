#include "ATMega328PTimer2.h"

ATMega328PTimer2::ATMega328PTimer2()
{
    initialize(1000); // Default period of 1000 microseconds (1 kHz).
}

void ATMega328PTimer2::initialize(uint32_t periodMicros)
{
    noInterrupts();  // Disable interrupts during setup

    // Clear registers and initialize variables
    TCCR2A = 0;
    TCCR2B = 0;
    TCNT2 = 0;

    const uint16_t prescalerValues[] = {1, 8, 32, 64, 128, 256, 1024};
    const size_t numPrescalers = sizeof(prescalerValues) / sizeof(prescalerValues[0]);
    const uint8_t F_CPU_MHZ = F_CPU / 1000000;  // Convert CPU frequency to MHz

    // Find the appropriate prescaler and OCR2A value
    for (size_t i = 0; i < numPrescalers; i++)
	{
        uint32_t ocrValue = (F_CPU_MHZ * periodMicros / prescalerValues[i]) - 1;

        if (ocrValue <= 255)
		{
            OCR2A = ocrValue;
            setPrescaler(prescalerValues[i]);
            break;  // Exit the loop once a valid configuration is found
        }
    }

    interrupts();  // Re-enable interrupts after setup
}

void ATMega328PTimer2::setPrescaler(uint16_t prescaler)
{
    switch (prescaler)
	{
        case 1:
            TCCR2B |= (1 << CS20);
            break;
        case 8:
            TCCR2B |= (1 << CS21);
            break;
        case 32:
            TCCR2B |= (1 << CS21) | (1 << CS20);
            break;
        case 64:
            TCCR2B |= (1 << CS22);
            break;
        case 128:
            TCCR2B |= (1 << CS22) | (1 << CS20);
            break;
        case 256:
            TCCR2B |= (1 << CS22) | (1 << CS21);
            break;
        case 1024:
            TCCR2B |= (1 << CS22) | (1 << CS21) | (1 << CS20);
            break;
        default:
            TCCR2B = 0; // Timer stopped if no valid prescaler
    }
}

void ATMega328PTimer2::start()
{
    TIMSK2 |= (1 << OCIE2A);  // Enable Timer2 Compare Match A interrupt
}


void ATMega328PTimer2::stop()
{
    TIMSK2 &= ~(1 << OCIE2A);  // Disable Timer2 Compare Match A interrupt
}
