// MicroSerial - Lightweight bit-bang Serial library

/*
 * MIT License
 *
 * Copyright (c) 2025 Hiroaki SHIBUKI a.k.a. hidori
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

#if defined(ARDUINO)
#include <Arduino.h>
#if defined(__AVR__)
#include <avr/io.h>
#include <util/delay.h>
#endif
#else
#include <stdio.h>
#endif

#include "MicroSerial.h"

// Get Serial TX pin number
#define MICRO_SERIAL_TX(handle) ((uint8_t)((handle >> 12) & 0x0f))

// Get Serial bit delay in microseconds
#define MICRO_SERIAL_DELAY(handle) ((unsigned long)(handle & 0x0fff))

// Low-level pin control
#if defined(ARDUINO)
#if defined(__AVR__)
#define MICRO_SERIAL_DELAY_US(x) _delay_us(x)
#else
#define MICRO_SERIAL_DELAY_US(x) delayMicroseconds(x)
#endif
#endif

// Initialize serial communication
void MicroSerial_begin(uint16_t handle) {
  uint8_t tx = MICRO_SERIAL_TX(handle);
  MicroSerial_tx_low(tx);
}

// Send a newline
void MicroSerial_newline(uint16_t handle) {
  MicroSerial_print(handle, '\n');
}

// Send a character
void MicroSerial_print(uint16_t handle, char ch) {
  #if defined(ARDUINO)
  uint8_t tx = MICRO_SERIAL_TX(handle);
  uint16_t delay = MICRO_SERIAL_DELAY(handle);

  MicroSerial_tx_low(tx);
  MICRO_SERIAL_DELAY_US(delay);

  for (uint8_t i = 0; i < 8; i++) {
    if (ch & (1 << i)) {
      MicroSerial_tx_high(tx);
    } else {
      MicroSerial_tx_low(tx);
    }
    MICRO_SERIAL_DELAY_US(delay);
  }

  MicroSerial_tx_high(tx);
  MICRO_SERIAL_DELAY_US(delay);
  #else
  putchar(ch);
  #endif
}

// Send a character and newline
void MicroSerial_println(uint16_t handle, char ch) {
  MicroSerial_print(handle, ch);
  MicroSerial_newline(handle);
}

// Send a string
void MicroSerial_print(uint16_t handle, const char* str) {
  while (*str) { MicroSerial_print(handle, *str++); }
}

// Send a string and newline
void MicroSerial_println(uint16_t handle, const char* str) {
  MicroSerial_print(handle, str);
  MicroSerial_newline(handle);
}

// Send an integer
void MicroSerial_printdec(uint16_t handle, int data) {
  if (data < 0) {
      MicroSerial_print(handle, '-');
      data = -data;
    }
  MicroSerial_printdec(handle, (unsigned int)data);
}

// Send an integer and newline
void MicroSerial_printdecln(uint16_t handle, int data) {
  MicroSerial_printdec(handle, data);
  MicroSerial_newline(handle);
}

// Send an unsigned integer
void MicroSerial_printdec(uint16_t handle, unsigned int data) {
  if (data == 0) {
    MicroSerial_print(handle, '0');
    return;
  }

  int dat = data;
  int col = 0;
  while (dat > 0) {
    dat /= 10;
    col++;
  }

  for (int i = col - 1; i >= 0; i--) {
    int d = 1;
    for (int j = 0; j < i; j++) { d *= 10; }
    int n = data / d;
    MicroSerial_print(handle, '0' + n);
    data -= n * d;
  }
}

// Send an unsigned integer and newline
void MicroSerial_printdecln(uint16_t handle, unsigned int data) {
  MicroSerial_printdec(handle, data);
  MicroSerial_newline(handle);
}

// Send a hex value
void MicroSerial_printhex(uint16_t handle, int data, int digits) {
  for (int i = (digits - 1) * 4; i >= 0; i -= 4) {
    uint8_t nibble = (data >> i) & 0x0F;
    if (nibble < 10) {
      MicroSerial_print(handle, '0' + nibble);
    } else {
      MicroSerial_print(handle, 'A' + (nibble - 10));
    }
  }
}

// Send a hex value and newline
void MicroSerial_printhexln(uint16_t handle, uint16_t data, int digits) {
  MicroSerial_printhex(handle, data, digits);
  MicroSerial_newline(handle);
}

// Low-level API
void MicroSerial_tx_low(uint8_t tx) {
#if defined(ARDUINO)
#if defined(__AVR__)
  PORTB &= ~_BV(tx);
#else
  digitalWrite(tx, LOW);
#endif
#endif
}

// Set TX pin HIGH
void MicroSerial_tx_high(uint8_t tx) {
#if defined(ARDUINO)
#if defined(__AVR__)
  PORTB |= _BV(tx);
#else
  digitalWrite(tx, HIGH);
#endif
#endif
}

#if defined(GCC)
#define HANDLE 0

int main() {
  MicroSerial_newline(HANDLE);
  MicroSerial_print(HANDLE, '-');
  MicroSerial_println(HANDLE, '-');
  MicroSerial_println(HANDLE, "Hi!");

  MicroSerial_print(HANDLE, " int:");
  MicroSerial_printdec(HANDLE, 12345);
  MicroSerial_newline(HANDLE);
  MicroSerial_print(HANDLE, "uint:");
  MicroSerial_printdecln(HANDLE, -12345);

  MicroSerial_print(HANDLE, "byte:");
  MicroSerial_printhex(HANDLE, 0x12, 2);
  MicroSerial_newline(HANDLE);
  MicroSerial_print(HANDLE, "word:");
  MicroSerial_printhexln(HANDLE, 0x1234, 4);

  return 0;
}
#endif
