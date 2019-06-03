
#include <EEPROM.h>

void save_to_eeprom(unsigned int address, int config) {

  for (byte i = 0; i < sizeof(config); i++) {
    EEPROM.update(address + i, reinterpret_cast<byte*>(&config)[i]);
  }
  delay(50);

}

  int read_from_eeprom(unsigned int address) {// read 
    int config;
    for (byte i = 0; i < sizeof(config); i++) {
      reinterpret_cast<byte*>(&config)[i] = EEPROM.read(address + i);
    }
    return config;
  }
