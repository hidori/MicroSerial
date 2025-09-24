// DebugSerial - Additional example of using MicroSerial library for debugging

#include <Arduino.h>
#include <MicroSerial.h>

#define DEBUG
#include "DebugSerial.h"

#if defined(__AVR__)
#define TX PB0
#else
#define TX 2
#endif
#define __DEBUG_SERIAL_HANDLE__ DEBUG_SERIAL_HANDLE(TX, 9600)

void setup() {
  DEBUG_SERIAL_BEGIN();
  DEBUG_SERIAL_WAIT_FOR();
}

void loop() {
  DEBUG_SERIAL_NEWLINE();
  DEBUG_SERIAL_PRINT('-');
  DEBUG_SERIAL_PRINTLN('-');
  DEBUG_SERIAL_PRINTLN("Hi!");

  DEBUG_SERIAL_PRINT(" int:");
  DEBUG_SERIAL_PRINTDEC(12345);
  DEBUG_SERIAL_NEWLINE();
  DEBUG_SERIAL_PRINT("uint:");
  DEBUG_SERIAL_PRINTDECLN(-12345);

  DEBUG_SERIAL_PRINT("byte:");
  DEBUG_SERIAL_PRINTHEX(0x12, 2);
  DEBUG_SERIAL_NEWLINE();
  DEBUG_SERIAL_PRINT("word:");
  DEBUG_SERIAL_PRINTHEXLN(0x1234, 4);

  delay(3000);
}
