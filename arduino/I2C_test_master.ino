#include "Wire.h"

#define I2C_SADDR 0x08
#define I2C_REG 0xff
#define NUM_LED 5

void setup() {
  Wire.begin();
}

void loop() {
  Wire.beginTransmission(I2C_SADDR);
  Wire.write(0x00);
  Wire.write(0xff);
  Wire.write(0x00);
  Wire.write(0x00);
  Wire.endTransmission();
  Wire.beginTransmission(I2C_SADDR);
  Wire.write(I2C_REG);
  Wire.write(NUM_LED);
  Wire.endTransmission();
  delay(500);

  Wire.beginTransmission(I2C_SADDR);
  Wire.write(0x00);
  Wire.write(0x00);
  Wire.write(0xff);
  Wire.write(0x00);
  Wire.endTransmission();
  Wire.beginTransmission(I2C_SADDR);
  Wire.write(I2C_REG);
  Wire.write(NUM_LED);
  Wire.endTransmission();
  delay(500);

  Wire.beginTransmission(I2C_SADDR);
  Wire.write(0x00);
  Wire.write(0x00);
  Wire.write(0x00);
  Wire.write(0xff);
  Wire.endTransmission();
  Wire.beginTransmission(I2C_SADDR);
  Wire.write(I2C_REG);
  Wire.write(NUM_LED);
  Wire.endTransmission();
  delay(500);
}
