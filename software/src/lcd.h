/* lcd-bricklet
 * Copyright (C) 2011-2012 Olaf Lüke <olaf@tinkerforge.com>
 *
 * lcd.h: Implementation of LCD Bricklet messages
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */

#ifndef LCD_H
#define LCD_H

#include <stdint.h>

#include "bricklib/com/com_common.h"

#define MAX_LENGTH 16

// KS0066u defines
// execution times in ns
#define LCD_TIME_US_SET_MODE       (39)
#define LCD_TIME_US_SET_DATA       (43)
#define LCD_TIME_US_CLEAR_DISPLAY  (1530)
#define LCD_TIME_US_CURSOR_HOME    (1530)
#define LCD_TIME_US_ENABLE         (1)
#define LCD_TIME_MS_RESET          (1)
#define LCD_TIME_MS_STARTUP        (30)

// On MCP23017 port B
#define LCD_DB0               (1 << 0)
#define LCD_DB1               (1 << 1)
#define LCD_DB2               (1 << 2)
#define LCD_DB3               (1 << 3)
#define LCD_DB4               (1 << 4)
#define LCD_DB5               (1 << 5)
#define LCD_DB6               (1 << 6)
#define LCD_DB7_BUSY_FLAG     (1 << 7)

// On MCP23017 port A
#define LCD_RW                (1 << 0)
#define LCD_RS                (1 << 1)
#define LCD_EN                (1 << 2)
#define LCD_BL                (1 << 3)

// LCD Commands:

// Clear Display
#define LCD_CLEAR_DISPLAY     0x01

// Curser home
#define LCD_CURSOR_HOME       0x02

// Entry mode
#define LCD_SET_ENTRY         (1 << 2)
#define LCD_ENTRY_NOSHIFT     0
#define LCD_ENTRY_SHIFT       (1 << 0)
#define LCD_ENTRY_DECREASE    0
#define LCD_ENTRY_INCREASE    (1 << 1)

// Display configuration
#define LCD_SET_DISPLAY       (1 << 3)
#define LCD_BLINKING_OFF      0
#define LCD_BLINKING_ON       (1 << 0)
#define LCD_CURSOR_OFF        0
#define LCD_CURSOR_ON         (1 << 1)
#define LCD_DISPLAY_OFF       0
#define LCD_DISPLAY_ON        (1 << 2)

// Shift configuration
#define LCD_SET_SHIFT         (1 << 4)
#define LCD_SHIFT_LEFT        0
#define LCD_SHIFT_RIGHT       (1 << 2)
#define LCD_CURSOR_MOVE       0
#define LCD_DISPLAY_SHIFT     (1 << 3)

// Function configuration
#define LCD_SET_FUNCTION      (1 << 5)
#define LCD_FUNCTION_5X7      0
#define LCD_FUNCTION_5X10     (1 << 2)
#define LCD_FUNCTION_1LINE    0
#define LCD_FUNCTION_2LINE    (1 << 3)
#define LCD_FUNCTION_4BIT     0
#define LCD_FUNCTION_8BIT     (1 << 4)

// Address configuration
#define LCD_SET_CGADR         (1 << 6)
#define LCD_SET_DDADR         (1 << 7)

#define LCD_OFFSET_LINE0      0x0
#define LCD_OFFSET_LINE1      0x40


// MCP23017 defines
#define I2C_EEPROM_ADDRESS_HIGH 84
#define I2C_ADDRESS_HIGH 33 //0b0100001
#define I2C_ADDRESS_LOW 32 //0b0100000
#define I2C_INTERNAL_ADDRESS_BYTES 1
#define I2C_DATA_LENGTH 1

#define I2C_INTERNAL_ADDRESS_IODIR_A   0x00
#define I2C_INTERNAL_ADDRESS_IODIR_B   0x01
#define I2C_INTERNAL_ADDRESS_GPINTEN_A 0x04
#define I2C_INTERNAL_ADDRESS_GPINTEN_B 0x05
#define I2C_INTERNAL_ADDRESS_DEFVAL_A  0x06
#define I2C_INTERNAL_ADDRESS_DEFVAL_B  0x07
#define I2C_INTERNAL_ADDRESS_INTCON_A  0x08
#define I2C_INTERNAL_ADDRESS_INTCON_B  0x09
#define I2C_INTERNAL_ADDRESS_GPPU_A    0x0C
#define I2C_INTERNAL_ADDRESS_GPPU_B    0x0D
#define I2C_INTERNAL_ADDRESS_INTF_A    0x0E
#define I2C_INTERNAL_ADDRESS_INTF_B    0x0F
#define I2C_INTERNAL_ADDRESS_INTCAP_A  0x10
#define I2C_INTERNAL_ADDRESS_INTCAP_B  0x11
#define I2C_INTERNAL_ADDRESS_GPIO_A    0x12
#define I2C_INTERNAL_ADDRESS_GPIO_B    0x13
#define I2C_INTERNAL_ADDRESS_OLAT_A    0x14
#define I2C_INTERNAL_ADDRESS_OLAT_B    0x15

void invocation(const ComType com, const uint8_t *data);
void constructor(void);
void destructor(void);
void tick(const uint8_t tick_type);

void lcd_move_cursor(const uint8_t line, const uint8_t position);
void lcd_putchar(const char c);
void lcd_putstr(const char *c);
void lcd_set_a(const uint8_t value);
void lcd_set_b(const uint8_t value);
void lcd_enable(void);
void io_write(const uint8_t internal_address, const uint8_t value);

typedef struct {
	MessageHeader header;
} __attribute__((__packed__)) StandardMessage;

#define FID_WRITE_LINE 1
#define FID_CLEAR_DISPLAY 2
#define FID_BACKLIGHT_ON 3
#define FID_BACKLIGHT_OFF 4
#define FID_IS_BACKLIGHT_ON 5
#define FID_SET_CONFIG 6
#define FID_GET_CONFIG 7
#define FID_IS_BUTTON_PRESSED 8
#define FID_BUTTON_PRESSED 9
#define FID_BUTTON_RELEASED 10

#define NUM_MESSAGE_TYPES 8

typedef struct {
	MessageHeader header;
	uint8_t line;
	uint8_t position;
	char text[20];
} __attribute__((__packed__)) WriteLine;

typedef struct {
	MessageHeader header;
} __attribute__((__packed__)) ClearDisplay;

typedef struct {
	MessageHeader header;
	bool cursor;
	bool blinking;
} __attribute__((__packed__)) SetConfig;

typedef struct {
	MessageHeader header;
} __attribute__((__packed__)) GetConfig;

typedef struct {
	MessageHeader header;
	bool cursor;
	bool blinking;
} __attribute__((__packed__)) GetConfigReturn;

typedef struct {
	MessageHeader header;
} __attribute__((__packed__)) BacklightOn;

typedef struct {
	MessageHeader header;
} __attribute__((__packed__)) BacklightOff;

typedef struct {
	MessageHeader header;
} __attribute__((__packed__)) IsBacklightOn;

typedef struct {
	MessageHeader header;
	bool backlight;
} __attribute__((__packed__)) IsBacklightOnReturn;

typedef struct {
	MessageHeader header;
	uint8_t button;
} __attribute__((__packed__)) IsButtonPressed;

typedef struct {
	MessageHeader header;
	bool pressed;
} __attribute__((__packed__)) IsButtonPressedReturn;

typedef struct {
	MessageHeader header;
	uint8_t button;
} __attribute__((__packed__)) ButtonPressedCallback;

typedef struct {
	MessageHeader header;
	uint8_t button;
} __attribute__((__packed__)) ButtonReleasedCallback;

void write_line(const ComType com, const WriteLine *data);
void clear_display(const ComType com, const ClearDisplay *data);
void set_config(const ComType com, const SetConfig *data);
void get_config(const ComType com, const GetConfig *data);
void backlight_on(const ComType com, const BacklightOn *data);
void backlight_off(const ComType com, const BacklightOff *data);
void is_backlight_on(const ComType com, const IsBacklightOn *data);
void is_button_pressed(const ComType com, const IsButtonPressed *data);

#endif
