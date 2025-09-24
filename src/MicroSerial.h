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

// Macros

// Create handle
#define MICRO_SERIAL_HANDLE(tx, baudrate) ((uint16_t)(((0x0f & (uint16_t)tx) << 12) | (0x0fff & (1000000UL / (uint16_t)baudrate))))

// High-level APIs

// Initialize serial communication
void MicroSerial_begin(uint16_t handle);

// Send a newline
void MicroSerial_newline(uint16_t handle);

// Send a character
void MicroSerial_print(uint16_t handle, char ch);

// Send a character and newline
void MicroSerial_println(uint16_t handle, char ch);

// Send a string
void MicroSerial_print(uint16_t handle, const char* str);

// Send a string and newline
void MicroSerial_println(uint16_t handle, const char* str);

// Send an integer
void MicroSerial_printdec(uint16_t handle, int data);

// Send an integer and newline
void MicroSerial_printdecln(uint16_t handle, int data);

// Send an unsigned integer
void MicroSerial_printdec(uint16_t handle, unsigned int data);

// Send an unsigned integer and newline
void MicroSerial_printdecln(uint16_t handle, unsigned int data);

// Send a hex value
void MicroSerial_printhex(uint16_t handle, int data, int digits);

// Send a hex value and newline
void MicroSerial_printhexln(uint16_t handle, uint16_t data, int digits);

// Low-level APIs

// Set TX pin LOW
void MicroSerial_tx_low(uint8_t tx);

// Set TX pin HIGH
void MicroSerial_tx_high(uint8_t tx);

#endif  // __MICRO_SERIAL_H__
