/*
I2C to WS2812 (RGB LED) converter

(C) 2021 Tadashi Kadowaki.

### MCU ###

The code is tested on ATtiny212. ATtiny 0 & 1 series may work.
I2C, CCL, SPI, and TCA peripherals are used.

### I2C ###

(1) Write RGB data
Each register for a LED has 3-byte data. You can send <LED #> <Green> <Red> <Blue> followed by the slave address (0x08).
Multiple LED data can be transfered without specifying the next LED.
<LED 0> <Green 0> <Red 0> <Blue 0> <Green 1> <Red 2> <Blue 3> ...
Data exceeding the limit of the memory will be omitted.

(2) Send RGB data to WS2812
When writing the number of LEDs to the special register (0xff), the controller starts to send the data to WS2812.

Register: [ Reg0 ], [ Reg1 ], ..., [  Reg28  ], [ Reg255 ]
Data:     G0,R0,B0, G1,R1,B1, ..., G28,R28,B28, Num_of_LEDs

###  WS2812 (RGB LED) ###

The control signal for WS2812 is generated by CCL described in the reference.
Reference: Microchip Application Notes AN2387 http://ww1.microchip.com/downloads/jp/AppNotes/00002387A_JP.pdf http://ww1.microchip.com/downloads/en/Appnotes/00002387B.pdf

### Pin assignments

Name(Pin#):Function
PA0(6):(SPI SS) (UPDI)
PA1(4):I2C SDA *
PA2(5):I2C SCL *
PA3(7):(SPI SCK)
PA6(2):(SPI MOSI)
PA7(3):(SPI MISO) CCL LUT1-OUT (WS2812 RGB LEDs) *

* 3 pins for I2C and WS2812.

### Test

Test code for I2C master is in the Arduino sketch "arduino/I2C_test_master.ino".
*/

#include <atmel_start.h>
#include <util/delay.h>
#include <atomic.h>
#include <avr/sleep.h>

#define I2C_SADDR 0x08
#define Max_LEDs 29 // max 29(?) for 128 bytes SRAM, try smaller number if it does not work
#define Num_LEDs_REG 0xff
#define Sleep_Mode SLEEP_MODE_PWR_DOWN // SLEEP_MODE_IDLE / SLEEP_MODE_STANDBY/ SLEEP_MODE_PWR_DOWN

uint8_t LED_data[Max_LEDs * 3] = {0};
uint8_t num_LEDs = 0;
uint8_t i2c_count = 0;
uint8_t i2c_reg = 0xff;

void update_LEDs(void);
void write_to_LEDs(void);
void I2C_read_handler(void);
void I2C_write_handler(void);
void I2C_address_handler(void);
void I2C_stop_handler(void);
void I2C_error_handler(void);

int main(void)
{
	/* Initializes MCU, drivers and middleware */
	atmel_start_init();

	/* I2C callbacks */
	I2C_0_set_read_callback(I2C_read_handler);
	I2C_0_set_write_callback(I2C_write_handler);
	I2C_0_set_address_callback(I2C_address_handler);
	I2C_0_set_stop_callback(I2C_stop_handler);
	I2C_0_set_collision_callback(I2C_error_handler);
	I2C_0_set_bus_error_callback(I2C_error_handler);

	/* Sleep mode */
	set_sleep_mode(Sleep_Mode);

	while (1) {
	}
}

void sleep()
{
	ENABLE_INTERRUPTS();
	sleep_mode();
}
void update_LEDs()
{
	if (num_LEDs > 0) {
		DISABLE_INTERRUPTS();
		write_to_LEDs();
		num_LEDs = 0;
		ENABLE_INTERRUPTS();
	}
}

void write_to_LEDs()
{
	// Clear the Write Collision flag, to allow writing
	SPI0.INTFLAGS = SPI0_INTFLAGS;

	// Reset TCA counter register to ensure the first rising edge of PWM is predictable
	TCA0.SINGLE.CNT = 0 /* Count: 0 */;

	// Start TCA
	TCA0.SINGLE.CTRLA = TCA_SPLIT_CLKSEL_DIV1_gc /* System Clock */
	| 1 << TCA_SPLIT_ENABLE_bp /* Module Enable: enabled */;

	for (uint8_t i=0; i < num_LEDs * 3; i++) {
		// Start SPI by writing a byte to SPI data register
		SPI0.DATA = LED_data[i];

		// Wait for transfer to complete
		while ((SPI0.INTFLAGS & SPI_RXCIF_bm) == 0) {
		}
	}

	// Stop TCA
	TCA0.SINGLE.CTRLA = TCA_SPLIT_CLKSEL_DIV1_gc /* System Clock */
	| 0 << TCA_SPLIT_ENABLE_bp /* Module Enable: disabled */;
}

void I2C_address_handler()
{
	I2C_0_send_ack();
	i2c_count = 0xff;
	i2c_reg = 0xff;
}

void I2C_read_handler()
{
	I2C_0_write(0x0c);
}

void I2C_write_handler()
{
	uint8_t data;

	data = I2C_0_read();
	I2C_0_send_ack();
	if (i2c_count == 0xff) {
		i2c_reg = data;
	} else if (i2c_count == 0 && i2c_reg == Num_LEDs_REG) {
		num_LEDs = data;
	} else if (i2c_reg * 3 + i2c_count < Max_LEDs * 3) {
		LED_data[i2c_reg * 3 + i2c_count] = data;
	}
	i2c_count++;
}

void I2C_stop_handler()
{
	update_LEDs();
	sleep();
}

void I2C_error_handler()
{
}
