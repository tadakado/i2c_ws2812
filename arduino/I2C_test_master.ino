#include "Wire.h"

#define I2C_SADDR 0x08
#define I2C_DATA_REG 0x00
#define I2C_UPDATE_REG 0xff
#define NUM_LED 5

void setup() {
  Serial.begin(9600);
  Wire.begin();
//  Wire.setClock(20000);
}

void i2c_write(uint8_t addr, uint8_t *data, uint8_t size=1, bool end=true) {
  Wire.beginTransmission(addr);
  for(uint8_t i = 0; i < size; i++) {
    Wire.write(data[i]);
  }
  Wire.endTransmission(end);
}

void i2c_read(uint8_t addr, uint8_t reg, uint8_t *data, uint8_t size=1) {
  i2c_write(addr, &reg, 1, false);
  Wire.requestFrom(addr, size);
  for (uint8_t i=0; i<size; i++){
    while (Wire.available() == 0) {}
    data[i] = Wire.read();
  }
  Wire.endTransmission();
}

void write_led_data(uint8_t green, uint8_t red, uint8_t blue) {
  uint8_t data[4];

  data[0] = I2C_DATA_REG;
  data[1] = green;
  data[2] = red;
  data[3] = blue;
  i2c_write(I2C_SADDR, data, 4);

  data[0] = I2C_UPDATE_REG;
  data[1] = NUM_LED;
  i2c_write(I2C_SADDR, data, 2);
}

void test_write_read(uint8_t green, uint8_t red, uint8_t blue) {
  uint8_t data[3];

  write_led_data(green, red, blue);

  i2c_read(I2C_SADDR, I2C_UPDATE_REG, data, 1);
  Serial.print("Num RGBs, RGB data : ");
  Serial.print(data[0], HEX);
  Serial.print(" ");

  i2c_read(I2C_SADDR, I2C_DATA_REG, data, 3);
  Serial.print(data[0], HEX);
  Serial.print(" ");
  Serial.print(data[1], HEX);
  Serial.print(" ");
  Serial.println(data[2], HEX);

  delay(500);
}

void loop() {
  test_write_read(0x7f, 0x01, 0x02);
  test_write_read(0x03, 0x7f, 0x04);
  test_write_read(0x05, 0x06, 0x7f);
  delay(200);
}
