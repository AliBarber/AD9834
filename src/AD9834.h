#ifndef SPIDDS_H
#define SPIDDS_H

#include <SPI.h>

class AD9834 {
public:
  AD9834(int fsync_pin, long clock_freq = 75000000) :
              _FSYNC_PIN(fsync_pin),
              _clock_freq(clock_freq), 
              _spi_settings(10000000,MSBFIRST, SPI_MODE2), 
             _use_freq_reg_1(false),
             _last_freq(){
    SPI.begin();
    pinMode(_FSYNC_PIN, OUTPUT);
    digitalWriteFast(_FSYNC_PIN, HIGH);
    // Reset
    _transfer16(0x100);
  };

  // Updates the frequency register directly - this does
  // not include the register select pin which is tracked
  // by this class.
  void update_freq_reg(uint16_t MSB, uint16_t LSB);
  void update_freq(float freq);
  long get_freq(){ return _last_freq; };

private:
 const int _FSYNC_PIN;
 const long _clock_freq;
 SPISettings _spi_settings;
 bool _use_freq_reg_1;
 long _last_freq;
 void _transfer16(uint16_t data);
 
};

#endif