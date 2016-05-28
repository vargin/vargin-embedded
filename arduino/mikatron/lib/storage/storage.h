#ifndef MIKATRON_STORAGE_H
#define MIKATRON_STORAGE_H

#define STORAGE_ADDRESS  0x57

class Storage {
public:
  static uint8_t read(const uint16_t position);
  static void write(const uint16_t position, const uint8_t data);
};

#endif //MIKATRON_STORAGE_H
