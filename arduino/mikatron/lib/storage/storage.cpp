#include <avr/io.h>
#include <util/delay.h>
#include "storage.h"
#include "TinyWireM.h"

uint8_t Storage::read(const uint16_t position) {
  TinyWireM.beginTransmission(STORAGE_ADDRESS);
  TinyWireM.write((uint8_t)((position) >> 8));
  TinyWireM.write((uint8_t)((position) & 0xFF));
  TinyWireM.endTransmission();

  TinyWireM.requestFrom(STORAGE_ADDRESS, 1);
  return TinyWireM.read();
}

void Storage::write(const uint16_t position, const uint8_t data) {
  TinyWireM.beginTransmission(STORAGE_ADDRESS);
  TinyWireM.write((uint8_t)((position) >> 8));
  TinyWireM.write((uint8_t)((position) & 0xFF));
  TinyWireM.write(data);
  TinyWireM.endTransmission();

  _delay_ms(50);
}
