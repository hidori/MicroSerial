// MicroSerial - Lightweight bit-bang Serial library

/*
 * MIT License
 *
 * Copyright (c) 2025 Hiroaki SHIBUKI
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include <util/delay.h>
#include <avr/io.h>
#if !defined(MICRO_SERIAL_AVR)
#include <Arduino.h>
#endif
#include "MicroSerial.h"

// Initialize serial communication
void MicroSerial_begin(uint16_t handle) {
    uint8_t tx = MICRO_SERIAL_TX(handle);
    #if defined(MICRO_SERIAL_AVR)
    DDRB |= _BV(tx);
    PORTB |= _BV(tx);
    #else
    pinMode(tx, OUTPUT);
    digitalWrite(tx, HIGH);
    #endif
}

// Send a character
void MicroSerial_print(uint16_t handle, char ch) {
    uint8_t tx = MICRO_SERIAL_TX(handle);
    uint16_t delay = MICRO_SERIAL_DELAY(handle);

    #if defined(MICRO_SERIAL_AVR)
    PORTB &= ~_BV(tx);  // Start bit (LOW)
    #else
    digitalWrite(tx, LOW);  // Start bit
    #endif
    _delay_us(delay);

    for (uint8_t i = 0; i < 8; i++) {
        if (ch & (1 << i)) {
            #if defined(MICRO_SERIAL_AVR)
            PORTB |= _BV(tx);
            #else
            digitalWrite(tx, HIGH);
            #endif
        } else {
            #if defined(MICRO_SERIAL_AVR)
            PORTB &= ~_BV(tx);
            #else
            digitalWrite(tx, LOW);
            #endif
        }
        _delay_us(delay);
    }

    #if defined(MICRO_SERIAL_AVR)
    PORTB |= _BV(tx);  // Stop bit (HIGH)
    #else
    digitalWrite(tx, HIGH);  // Stop bit
    #endif
    _delay_us(delay);
}

// Send a string
void MicroSerial_print(uint16_t handle, char* text) {
    while (*text) {
        MicroSerial_print(handle, *text++);
    }
}

// Send a newline
void MicroSerial_println(uint16_t handle) {
  MicroSerial_print(handle, '\n');
}

// Send a 8-bit hex value
void MicroSerial_printhex(uint16_t handle, uint8_t data) {
    uint8_t hi = (data >> 4) & 0x0F;
    uint8_t lo = data & 0x0F;
    MicroSerial_print(handle, hi < 10 ? hi + '0' : hi - 10 + 'A');
    MicroSerial_print(handle, lo < 10 ? lo + '0' : lo - 10 + 'A');
}
