/*************************************************************
 * This file was automatically generated on 23.08.2011.      *
 *                                                           *
 * If you have a bugfix for this file and want to commit it, *
 * please fix the bug in the generator. You can find a link  *
 * to the generator git on tinkerforge.com                   *
 *************************************************************/

#ifndef BRICKLET_LCD_16X2_H
#define BRICKLET_LCD_16X2_H

#include "ip_connection.h"

typedef Device LCD16x2;

#define LCD_16X2_CALLBACK_BUTTON_PRESSED 9
#define LCD_16X2_CALLBACK_BUTTON_RELEASED 10

void lcd_16x2_create(LCD16x2 *lcd_16x2, const char *uid);

int lcd_16x2_write_line(LCD16x2 *lcd_16x2, uint8_t line, uint8_t position, char text[16]);
int lcd_16x2_clear_display(LCD16x2 *lcd_16x2);
int lcd_16x2_backlight_on(LCD16x2 *lcd_16x2);
int lcd_16x2_backlight_off(LCD16x2 *lcd_16x2);
int lcd_16x2_is_backlight_on(LCD16x2 *lcd_16x2, bool *ret_backlight);
int lcd_16x2_set_config(LCD16x2 *lcd_16x2, bool cursor, bool blinking);
int lcd_16x2_get_config(LCD16x2 *lcd_16x2, bool *ret_cursor, bool *ret_blinking);
int lcd_16x2_is_button_pressed(LCD16x2 *lcd_16x2, uint8_t button, bool *ret_pressed);
int lcd_16x2_button_pressed(LCD16x2 *lcd_16x2, uint8_t *ret_button);
int lcd_16x2_button_released(LCD16x2 *lcd_16x2, uint8_t *ret_button);

void lcd_16x2_register_callback(LCD16x2 *lcd_16x2, uint8_t cb, void *func);

#endif