// HelloSerial - Example of using MicroSerial library

#include <Arduino.h>
#include "MicroSerial.h"

#if defined(__AVR__)
#define TX PB0
#else
#define TX 2
#endif
#define HANDLE MICRO_SERIAL_HANDLE(TX, 9600)

void setup() {
  MicroSerial_begin(HANDLE);
  delay(100);
}

void loop() {
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

  delay(3000);
}
