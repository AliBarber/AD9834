#include "AD9834.h"

void AD9834::update_freq(float freq)
{
  long freq_reg = (freq * pow(2,28)) / _clock_freq;
  uint16_t MSB, LSB;
  LSB = freq_reg & 0x3FFF; // 14 LSBs
  MSB = ((freq_reg & 0xFFFC000) >> 14);

  update_freq_reg(MSB, LSB);
  _last_freq = freq;

}

void AD9834::update_freq_reg(uint16_t MSB, uint16_t LSB){
  uint16_t freq_reg_address;
  if(_use_freq_reg_1){
    // Serial.println("Using register 1");
    freq_reg_address = 0x8000;
  }
  else{
    // Serial.println("Using register 0");
    freq_reg_address = 0x4000;
  }

  LSB |= freq_reg_address;
  MSB |= freq_reg_address;

  uint16_t control_reg = 0x2000;
  // OR it with what we are currently using
  // if(!_use_freq_reg_1){
  //   control_reg |= 0x800;
  // }
  _transfer16(control_reg);
  _transfer16(LSB);
  _transfer16(MSB);
  // _transfer16(0xC000);
  // _transfer16(0x2000);

  if(_use_freq_reg_1)
  {
    _transfer16(0x838);
  }
  else{
    _transfer16(0x38);
  }
  _use_freq_reg_1 = !_use_freq_reg_1;

} 

void AD9834::_transfer16(uint16_t data){
  uint16_t MSB, LSB;
  MSB = data >> 8;
  LSB = data & 0xFF;
  SPI.beginTransaction(_spi_settings);
  digitalWriteFast(_FSYNC_PIN,LOW);
  SPI.transfer(MSB);
  SPI.transfer(LSB);
  digitalWriteFast(_FSYNC_PIN,HIGH);
  SPI.endTransaction();
}

