// HelloSerial - Example of using MicroSerial library

#include <Arduino.h>
#include "MicroSerial.h"

#define HANDLE MICRO_SERIAL_HANDLE(PB0, 9600)

void setup() {
  MicroSerial_begin(HANDLE);
  delay(100);
}

void loop() {
  MicroSerial_print(HANDLE, 'H');
  MicroSerial_print(HANDLE, 'e');
  MicroSerial_print(HANDLE, 'l');
  MicroSerial_print(HANDLE, 'l');
  MicroSerial_print(HANDLE, 'o');
  MicroSerial_print(HANDLE, ' ');
  MicroSerial_print(HANDLE, "MicroSerial!");
  MicroSerial_println(HANDLE);

  MicroSerial_print(HANDLE, "8bit hex: 0x");
  MicroSerial_printhex(HANDLE, 0xAB);
  MicroSerial_println(HANDLE);

  MicroSerial_print(HANDLE, "16bit hex: 0x");
  MicroSerial_printhex(HANDLE, 0x12);
  MicroSerial_printhex(HANDLE, 0x34);
  MicroSerial_println(HANDLE);

  MicroSerial_println(HANDLE);

  delay(3000);
}
