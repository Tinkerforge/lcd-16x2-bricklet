/* lcd-bricklet
 * Copyright (C) 2011 Olaf Lüke <olaf@tinkerforge.com>
 *
 * config.h: LCD Bricklet specific configuration
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

#ifndef CONFIG_H
#define CONFIG_H

#include <stdint.h>
#include <stdbool.h>

#include "bricklib/drivers/board/sam3s/SAM3S.h"

#include "lcd.h"

#define BOARD_MCK 64000000

#define INVOCATION_IN_BRICKLET_CODE

#define PIN_BUTTON_0   (BS->pin1_ad)
#define PIN_BUTTON_1   (BS->pin2_da)
#define PIN_BUTTON_2   (BS->pin3_pwm)
#define PIN_RESET      (BS->pin4_io)

#define NUM_BUTTON 3

typedef struct {
	bool button_pressed[3];
	uint8_t port_a;
	uint8_t port_b;
	uint8_t cursor;
	uint8_t blinking;
} BrickContext;

#endif
