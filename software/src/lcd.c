/* lcd-bricklet
 * Copyright (C) 2011-2012 Olaf Lüke <olaf@tinkerforge.com>
 *
 * lcd.c: Implementation of LCD Bricklet messages
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

#include "lcd.h"

#include "brickletlib/bricklet_entry.h"
#include "bricklib/bricklet/bricklet_communication.h"
#include "bricklib/drivers/adc/adc.h"
#include "config.h"
#include "bricklib/utility/util_definitions.h"
#include "bricklib/utility/init.h"

void invocation(const ComType com, const uint8_t *data) {
	switch(((MessageHeader*)data)->fid) {
		case FID_WRITE_LINE: {
			write_line(com, (WriteLine*)data);
			break;
		}

		case FID_CLEAR_DISPLAY: {
			clear_display(com, (ClearDisplay*)data);
			break;
		}

		case FID_BACKLIGHT_ON: {
			backlight_on(com, (BacklightOn*)data);
			break;
		}

		case FID_BACKLIGHT_OFF: {
			backlight_off(com, (BacklightOff*)data);
			break;
		}

		case FID_IS_BACKLIGHT_ON: {
			is_backlight_on(com, (IsBacklightOn*)data);
			break;
		}

		case FID_SET_CONFIG: {
			set_config(com, (SetConfig*)data);
			break;
		}

		case FID_GET_CONFIG: {
			get_config(com, (GetConfig*)data);
			break;
		}

		case FID_IS_BUTTON_PRESSED: {
			is_button_pressed(com, (IsButtonPressed*)data);
			break;
		}

		case FID_SET_CUSTOM_CHARACTER: {
			set_custom_character(com, (SetCustomCharacter*)data);
			break;
		}

		case FID_GET_CUSTOM_CHARACTER: {
			get_custom_character(com, (GetCustomCharacter*)data);
			break;
		}

		default: {
			BA->com_return_error(data, sizeof(MessageHeader), MESSAGE_ERROR_CODE_NOT_SUPPORTED, com);
			break;
		}
	}
}

void constructor(void) {
	_Static_assert(sizeof(BrickContext) <= BRICKLET_CONTEXT_MAX_SIZE, "BrickContext too big");

	// Disable Reset
    PIN_RESET.type = PIO_OUTPUT_1;
    BA->PIO_Configure(&PIN_RESET, 1);

	// Make all pins output
	io_write(I2C_INTERNAL_ADDRESS_IODIR_A, 0);
	io_write(I2C_INTERNAL_ADDRESS_IODIR_B, 0);
	io_write(I2C_INTERNAL_ADDRESS_GPPU_B, 0);
	lcd_set_a(0);
	lcd_set_b(0);

	// Wait for lcd to start up
	SLEEP_MS(LCD_TIME_MS_STARTUP);

	// Set 8 bit, 2 line and 5x7 character mode
	lcd_set_b(LCD_SET_FUNCTION   |
	          LCD_FUNCTION_8BIT  |
	          LCD_FUNCTION_2LINE |
	          LCD_FUNCTION_5X7);
	lcd_enable();
	SLEEP_US(LCD_TIME_US_SET_MODE);

	// Enable display, no cursor or blinking
	BC->cursor = 0;
	BC->blinking = 0;
	lcd_set_b(LCD_SET_DISPLAY    |
			  LCD_DISPLAY_ON     |
			  LCD_CURSOR_OFF     |
			  LCD_BLINKING_OFF);
	lcd_enable();
	SLEEP_US(LCD_TIME_US_SET_MODE);

	// Increase pointer and no display shift
	lcd_set_b(LCD_SET_ENTRY      |
	          LCD_ENTRY_INCREASE |
	          LCD_ENTRY_NOSHIFT);
	lcd_enable();
	SLEEP_US(LCD_TIME_US_SET_MODE);

	// Clear display
	lcd_set_b(LCD_CLEAR_DISPLAY);
	lcd_enable();
	SLEEP_US(LCD_TIME_US_CLEAR_DISPLAY);

    // Configure buttons
	PIN_BUTTON_0.type = PIO_INPUT;
	PIN_BUTTON_0.attribute = PIO_PULLUP;
    BA->PIO_Configure(&PIN_BUTTON_0, 1);

    PIN_BUTTON_1.type = PIO_INPUT;
    PIN_BUTTON_1.attribute = PIO_PULLUP;
    BA->PIO_Configure(&PIN_BUTTON_1, 1);

    PIN_BUTTON_2.type = PIO_INPUT;
    PIN_BUTTON_2.attribute = PIO_PULLUP;
    BA->PIO_Configure(&PIN_BUTTON_2, 1);

    BC->button_pressed[0] = true;
    BC->button_pressed[1] = true;
    BC->button_pressed[2] = true;
}

void destructor(void) {
	PIN_RESET.type = PIO_INPUT;
	PIN_RESET.attribute = PIO_PULLUP;
    BA->PIO_Configure(&PIN_RESET, 1);
}

void tick(const uint8_t tick_type) {
	if(tick_type & TICK_TASK_TYPE_MESSAGE) {
		bool pressed[3];
		pressed[0] = PIN_BUTTON_0.pio->PIO_PDSR & PIN_BUTTON_0.mask;
		pressed[1] = PIN_BUTTON_1.pio->PIO_PDSR & PIN_BUTTON_1.mask;
		pressed[2] = PIN_BUTTON_2.pio->PIO_PDSR & PIN_BUTTON_2.mask;

		for(uint8_t i = 0; i < NUM_BUTTON; i++) {
			if(!pressed[i]) {
				if(BC->button_pressed[i]) {
					BC->button_pressed[i] = false;
					ButtonPressedCallback bps;
					BA->com_make_default_header(&bps, BS->uid, sizeof(ButtonPressedCallback), FID_BUTTON_PRESSED);
					bps.button = i;

					BA->send_blocking_with_timeout(&bps,
												   sizeof(ButtonPressedCallback),
												   *BA->com_current);
				}
			} else {
				if(!BC->button_pressed[i]) {
					BC->button_pressed[i] = true;
					ButtonReleasedCallback brs;
					BA->com_make_default_header(&brs, BS->uid, sizeof(ButtonReleasedCallback), FID_BUTTON_RELEASED);
					brs.button = i;

					BA->send_blocking_with_timeout(&brs,
												   sizeof(ButtonReleasedCallback),
												   *BA->com_current);
				}
			}
		}
	}
}

void lcd_set_a(const uint8_t value) {
	BC->port_a = value | (BC->port_a & LCD_BL);
	io_write(I2C_INTERNAL_ADDRESS_GPIO_A, BC->port_a);
}

void lcd_set_b(const uint8_t value) {
	BC->port_b = value;
	io_write(I2C_INTERNAL_ADDRESS_GPIO_B, BC->port_b);
}

void lcd_enable(void) {
	lcd_set_a(BC->port_a | LCD_EN);
	SLEEP_US(LCD_TIME_US_ENABLE);
	lcd_set_a(BC->port_a & (~LCD_EN));
}

// TODO: Make twid_write call async
void io_write(const uint8_t internal_address, const uint8_t value) {
	BA->mutex_take(*BA->mutex_twi_bricklet, MUTEX_BLOCKING);
	const uint8_t port = BS->port - 'a';

	uint8_t address;
	if(BS->address == I2C_EEPROM_ADDRESS_HIGH) {
		address = I2C_ADDRESS_HIGH;
	} else {
		address = I2C_ADDRESS_LOW;
	}

	uint8_t write_value = value;
	BA->bricklet_select(port);
    BA->TWID_Write(BA->twid,
                   address,
                   internal_address,
                   I2C_INTERNAL_ADDRESS_BYTES,
                   &write_value,
                   I2C_DATA_LENGTH,
                   NULL);
    BA->bricklet_deselect(port);
    BA->mutex_give(*BA->mutex_twi_bricklet);
}

uint8_t io_read(const uint8_t internal_address) {
	uint8_t address;
	if(BS->address == I2C_EEPROM_ADDRESS_HIGH) {
		address = I2C_ADDRESS_HIGH;
	} else {
		address = I2C_ADDRESS_LOW;
	}

	const uint8_t port = BS->port - 'a';
	uint8_t value;

	BA->mutex_take(*BA->mutex_twi_bricklet, MUTEX_BLOCKING);
	BA->bricklet_select(port);
    BA->TWID_Read(BA->twid,
                  address,
                  internal_address,
                  I2C_INTERNAL_ADDRESS_BYTES,
                  &value,
                  I2C_DATA_LENGTH,
                  NULL);
	BA->bricklet_deselect(port);

    BA->mutex_give(*BA->mutex_twi_bricklet);

	return value;
}

void lcd_putchar(const char c) {
	if(!(BC->port_a & LCD_RS)) {
		lcd_set_a(LCD_RS);
	}
	lcd_set_b((const uint8_t)c);
	lcd_enable();
	SLEEP_US(LCD_TIME_US_SET_DATA);
}

void lcd_putstr(const char *c) {
	while(*c != '\0') {
		lcd_putchar(*c);
		c++;
	}
}

void lcd_move_cursor(const uint8_t line, const uint8_t position) {
	uint8_t command = LCD_SET_DDADR + position;;
	switch(line) {
		case 0:
			command += LCD_OFFSET_LINE0;
			break;
		case 1:
			command += LCD_OFFSET_LINE1;
			break;
		default:
			// Wrong line
			return;
	}

	lcd_set_a(0);
	lcd_set_b(command);
	lcd_enable();
	SLEEP_US(LCD_TIME_US_SET_MODE);
}

void write_line(const ComType com, const WriteLine *data) {
	if(data->line > 1 || data->position > 15) {
		BA->com_return_error(data, sizeof(MessageHeader), MESSAGE_ERROR_CODE_INVALID_PARAMETER, com);
		return;
	}

	lcd_move_cursor(data->line, data->position);
	for(int8_t i = 0; i < MAX_LENGTH - data->position; i++) {
		if(data->text[i] == '\0') {
			break;
		}
		if(data->text[i] > 7 && data->text[i] < 16) {
			lcd_putchar(data->text[i] - 8);
		} else {
			lcd_putchar(data->text[i]);
		}
	}

	BA->com_return_setter(com, data);
}

void clear_display(const ComType com, const ClearDisplay *data) {
	lcd_set_a(0);
	lcd_set_b(LCD_CLEAR_DISPLAY);
	lcd_enable();

	BA->com_return_setter(com, data);
	SLEEP_US(LCD_TIME_US_CLEAR_DISPLAY);
}

void set_config(const ComType com, const SetConfig *data) {
	if(data->blinking) {
		BC->blinking = LCD_BLINKING_ON;
	} else {
		BC->blinking = LCD_BLINKING_OFF;
	}
	if(data->cursor) {
		BC->cursor = LCD_CURSOR_ON;
	} else {
		BC->cursor = LCD_CURSOR_OFF;
	}

	lcd_set_a(0);
	lcd_set_b(LCD_SET_DISPLAY  |
			  LCD_DISPLAY_ON   |
			  BC->cursor       |
			  BC->blinking);
	lcd_enable();

	BA->com_return_setter(com, data);
}

void get_config(const ComType com, const GetConfig *data) {
	GetConfigReturn gcr;

	gcr.header        = data->header;
	gcr.header.length = sizeof(GetConfigReturn);
	gcr.blinking      = !!BC->blinking;
	gcr.cursor        = !!BC->cursor;

	BA->send_blocking_with_timeout(&gcr, sizeof(GetConfigReturn), com);
}

void backlight_on(const ComType com, const BacklightOn *data) {
	BC->port_a = BC->port_a | LCD_BL;
	io_write(I2C_INTERNAL_ADDRESS_GPIO_A, BC->port_a);

	BA->com_return_setter(com, data);
}

void backlight_off(const ComType com, const BacklightOff *data) {
	BC->port_a = BC->port_a & (~LCD_BL);
	io_write(I2C_INTERNAL_ADDRESS_GPIO_A, BC->port_a);

	BA->com_return_setter(com, data);
}

void is_backlight_on(const ComType com, const IsBacklightOn *data) {
	IsBacklightOnReturn ibor;

	ibor.header        = data->header;
	ibor.header.length = sizeof(IsBacklightOnReturn);
	ibor.backlight     = BC->port_a & LCD_BL;

	BA->send_blocking_with_timeout(&ibor, sizeof(IsBacklightOnReturn), com);
}

void is_button_pressed(const ComType com, const IsButtonPressed *data) {
	IsButtonPressedReturn ibpr;

	ibpr.header        = data->header;
	ibpr.header.length = sizeof(IsButtonPressedReturn);

	switch(data->button) {
		case 0:
			ibpr.pressed =!(PIN_BUTTON_0.pio->PIO_PDSR & PIN_BUTTON_0.mask);
			break;
		case 1:
			ibpr.pressed =!(PIN_BUTTON_1.pio->PIO_PDSR & PIN_BUTTON_1.mask);
			break;
		case 2:
			ibpr.pressed =!(PIN_BUTTON_2.pio->PIO_PDSR & PIN_BUTTON_2.mask);
			break;
		default:
			BA->com_return_error(data, sizeof(IsButtonPressedReturn), MESSAGE_ERROR_CODE_INVALID_PARAMETER, com);
			return;
	}

	BA->send_blocking_with_timeout(&ibpr, sizeof(IsButtonPressedReturn), com);
}

void set_custom_character(const ComType com, const SetCustomCharacter *data) {
	if(data->index >= 8) {
		BA->com_return_error(data, sizeof(MessageHeader), MESSAGE_ERROR_CODE_INVALID_PARAMETER, com);
		return;
	}

	lcd_set_b(LCD_SET_CGADR | data->index*8);
	lcd_set_a(0);
	lcd_enable();
	SLEEP_US(LCD_TIME_US_SET_DATA);

	if(!(BC->port_a & LCD_RS)) {
		lcd_set_a(LCD_RS);
	}

	for(uint8_t i = 0; i < 8; i++) {
		lcd_set_b(data->character[i] & 0x1F);
		lcd_enable();
		SLEEP_US(LCD_TIME_US_SET_DATA);
	}

	BA->com_return_setter(com, data);
}

void get_custom_character(const ComType com, const GetCustomCharacter *data) {
	if(data->index >= 8) {
		BA->com_return_error(data, sizeof(GetCustomCharacter), MESSAGE_ERROR_CODE_INVALID_PARAMETER, com);
		return;
	}

	GetCustomCharacterReturn gccr;

	gccr.header        = data->header;
	gccr.header.length = sizeof(GetCustomCharacterReturn);

	lcd_set_b(LCD_SET_CGADR | data->index*8);
	lcd_set_a(0);
	lcd_enable();
	SLEEP_US(LCD_TIME_US_SET_DATA);

	io_write(I2C_INTERNAL_ADDRESS_IODIR_B, 0xFF);
	lcd_set_a(LCD_RS | LCD_RW);

	for(uint8_t i = 0; i < 8; i++) {
		lcd_set_a(BC->port_a | LCD_EN);
		SLEEP_US(LCD_TIME_US_SET_DATA);
		gccr.character[i] = io_read(I2C_INTERNAL_ADDRESS_GPIO_B);
		lcd_set_a(BC->port_a & (~LCD_EN));
	}

	lcd_set_a(LCD_RS);
	io_write(I2C_INTERNAL_ADDRESS_IODIR_B, 0);

	BA->send_blocking_with_timeout(&gccr, sizeof(GetCustomCharacterReturn), com);
}
