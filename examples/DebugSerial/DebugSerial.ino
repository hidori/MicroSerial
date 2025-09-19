// DebugSerial - Additional example of using MicroSerial library for debugging

#include <Arduino.h>
#include "MicroSerial.h"

#define DEBUG
#include "DebugSerial.h"

#define __DEBUG_SERIAL_HANDLE__ DEBUG_SERIAL_HANDLE(PB0, 9600)

void setup() {
  DEBUG_SERIAL_BEGIN();
  DEBUG_SERIAL_WAIT_FOR();
}

void loop() {
  DEBUG_SERIAL_PRINT('H');
  DEBUG_SERIAL_PRINT('e');
  DEBUG_SERIAL_PRINT('l');
  DEBUG_SERIAL_PRINT('l');
  DEBUG_SERIAL_PRINT('o');
  DEBUG_SERIAL_PRINT(' ');
  DEBUG_SERIAL_PRINTLN("DebugSerial!");

  DEBUG_SERIAL_PRINT("8bit hex: 0x");
  DEBUG_SERIAL_PRINTLNHEX(0xAB);

  DEBUG_SERIAL_PRINT("16bit hex: 0x");
  DEBUG_SERIAL_PRINTHEX(0x12);
  DEBUG_SERIAL_PRINTLNHEX(0x34);

  DEBUG_SERIAL_PRINTLN("");

  delay(3000);

}
