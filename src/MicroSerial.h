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

#ifndef __MICRO_SERIAL_H__
#define __MICRO_SERIAL_H__

#include <stdint.h>
#include <stdbool.h>

// Platform detection
#if defined(__AVR__)
#define MICRO_SERIAL_AVR
#endif

// Serial configuration
#define MICRO_SERIAL_HANDLE(tx, baudrate) ((uint16_t)(((0x0f & (uint16_t)tx) << 12) | (0x0fff & (1000000UL / (uint16_t)baudrate))))

// Get Serial TX pin number
#define MICRO_SERIAL_TX(handle) ((handle >> 12) & 0x0f)

// Get Serial bit delay in microseconds
#define MICRO_SERIAL_DELAY(handle) (handle & 0x0fff)

// Initialize serial communication
void MicroSerial_begin(uint16_t handle);

// Send a character
void MicroSerial_print(uint16_t handle, char ch);

// Send a string
void MicroSerial_print(uint16_t handle, char* text);

// Send a newline
void MicroSerial_println(uint16_t handle);

// Send a byte as hexadecimal
void MicroSerial_printhex(uint16_t handle, uint8_t data);

#endif  // __MICRO_SERIAL_H__
