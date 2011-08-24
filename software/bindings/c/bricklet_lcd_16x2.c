/*************************************************************
 * This file was automatically generated on 2011-08-23.      *
 *                                                           *
 * If you have a bugfix for this file and want to commit it, *
 * please fix the bug in the generator. You can find a link  *
 * to the generator git on tinkerforge.com                   *
 *************************************************************/

#include "bricklet_lcd_16x2.h"

#include <string.h>

#define TYPE_WRITE_LINE 1
#define TYPE_CLEAR_DISPLAY 2
#define TYPE_BACKLIGHT_ON 3
#define TYPE_BACKLIGHT_OFF 4
#define TYPE_IS_BACKLIGHT_ON 5
#define TYPE_SET_CONFIG 6
#define TYPE_GET_CONFIG 7
#define TYPE_IS_BUTTON_PRESSED 8
#define TYPE_BUTTON_PRESSED 9
#define TYPE_BUTTON_RELEASED 10

typedef void (*button_pressed_func_t)(uint8_t);
typedef void (*button_released_func_t)(uint8_t);

#ifdef _MSC_VER
	#pragma pack(push)
	#pragma pack(1)

	#define PACKED
#else
	#define PACKED __attribute__((packed))
#endif

typedef struct {
	uint8_t stack_id;
	uint8_t type;
	uint16_t length;
	uint8_t line;
	uint8_t position;
	char text[16];
} PACKED WriteLine;

typedef struct {
	uint8_t stack_id;
	uint8_t type;
	uint16_t length;
} PACKED ClearDisplay;

typedef struct {
	uint8_t stack_id;
	uint8_t type;
	uint16_t length;
} PACKED BacklightOn;

typedef struct {
	uint8_t stack_id;
	uint8_t type;
	uint16_t length;
} PACKED BacklightOff;

typedef struct {
	uint8_t stack_id;
	uint8_t type;
	uint16_t length;
} PACKED IsBacklightOn;

typedef struct {
	uint8_t stack_id;
	uint8_t type;
	uint16_t length;
	bool backlight;
} PACKED IsBacklightOnReturn;

typedef struct {
	uint8_t stack_id;
	uint8_t type;
	uint16_t length;
	bool cursor;
	bool blinking;
} PACKED SetConfig;

typedef struct {
	uint8_t stack_id;
	uint8_t type;
	uint16_t length;
} PACKED GetConfig;

typedef struct {
	uint8_t stack_id;
	uint8_t type;
	uint16_t length;
	bool cursor;
	bool blinking;
} PACKED GetConfigReturn;

typedef struct {
	uint8_t stack_id;
	uint8_t type;
	uint16_t length;
	uint8_t button;
} PACKED IsButtonPressed;

typedef struct {
	uint8_t stack_id;
	uint8_t type;
	uint16_t length;
	bool pressed;
} PACKED IsButtonPressedReturn;

typedef struct {
	uint8_t stack_id;
	uint8_t type;
	uint16_t length;
	uint8_t button;
} PACKED ButtonPressedCallback;

typedef struct {
	uint8_t stack_id;
	uint8_t type;
	uint16_t length;
	uint8_t button;
} PACKED ButtonReleasedCallback;

#ifdef _MSC_VER
	#pragma pack(pop)
#endif

int lcd_16x2_write_line(LCD16x2 *lcd_16x2, uint8_t line, uint8_t position, char text[16]) {
	if(lcd_16x2->ipcon == NULL) {
		return E_NOT_ADDED;
	}

	ipcon_sem_wait_write(lcd_16x2);

	WriteLine wl;
	wl.stack_id = lcd_16x2->stack_id;
	wl.type = TYPE_WRITE_LINE;
	wl.length = sizeof(WriteLine);
	wl.line = line;
	wl.position = position;
	strcpy(wl.text, text);


	ipcon_device_write(lcd_16x2, (char *)&wl, sizeof(WriteLine));

	ipcon_sem_post_write(lcd_16x2);

	return E_OK;
}

int lcd_16x2_clear_display(LCD16x2 *lcd_16x2) {
	if(lcd_16x2->ipcon == NULL) {
		return E_NOT_ADDED;
	}

	ipcon_sem_wait_write(lcd_16x2);

	ClearDisplay cd;
	cd.stack_id = lcd_16x2->stack_id;
	cd.type = TYPE_CLEAR_DISPLAY;
	cd.length = sizeof(ClearDisplay);

	ipcon_device_write(lcd_16x2, (char *)&cd, sizeof(ClearDisplay));

	ipcon_sem_post_write(lcd_16x2);

	return E_OK;
}

int lcd_16x2_backlight_on(LCD16x2 *lcd_16x2) {
	if(lcd_16x2->ipcon == NULL) {
		return E_NOT_ADDED;
	}

	ipcon_sem_wait_write(lcd_16x2);

	BacklightOn bo;
	bo.stack_id = lcd_16x2->stack_id;
	bo.type = TYPE_BACKLIGHT_ON;
	bo.length = sizeof(BacklightOn);

	ipcon_device_write(lcd_16x2, (char *)&bo, sizeof(BacklightOn));

	ipcon_sem_post_write(lcd_16x2);

	return E_OK;
}

int lcd_16x2_backlight_off(LCD16x2 *lcd_16x2) {
	if(lcd_16x2->ipcon == NULL) {
		return E_NOT_ADDED;
	}

	ipcon_sem_wait_write(lcd_16x2);

	BacklightOff bo;
	bo.stack_id = lcd_16x2->stack_id;
	bo.type = TYPE_BACKLIGHT_OFF;
	bo.length = sizeof(BacklightOff);

	ipcon_device_write(lcd_16x2, (char *)&bo, sizeof(BacklightOff));

	ipcon_sem_post_write(lcd_16x2);

	return E_OK;
}

int lcd_16x2_is_backlight_on(LCD16x2 *lcd_16x2, bool *ret_backlight) {
	if(lcd_16x2->ipcon == NULL) {
		return E_NOT_ADDED;
	}

	ipcon_sem_wait_write(lcd_16x2);

	lcd_16x2->answer.type = TYPE_IS_BACKLIGHT_ON;
	lcd_16x2->answer.length = sizeof(IsBacklightOnReturn);
	IsBacklightOn ibo;
	ibo.stack_id = lcd_16x2->stack_id;
	ibo.type = TYPE_IS_BACKLIGHT_ON;
	ibo.length = sizeof(IsBacklightOn);

	ipcon_device_write(lcd_16x2, (char *)&ibo, sizeof(IsBacklightOn));

	if(ipcon_answer_sem_wait_timeout(lcd_16x2) != 0) {
		ipcon_sem_post_write(lcd_16x2);
		return E_TIMEOUT;
	}

	IsBacklightOnReturn *ibor = (IsBacklightOnReturn *)lcd_16x2->answer.buffer;
	*ret_backlight = ibor->backlight;

	ipcon_sem_post_write(lcd_16x2);

	return E_OK;
}

int lcd_16x2_set_config(LCD16x2 *lcd_16x2, bool cursor, bool blinking) {
	if(lcd_16x2->ipcon == NULL) {
		return E_NOT_ADDED;
	}

	ipcon_sem_wait_write(lcd_16x2);

	SetConfig sc;
	sc.stack_id = lcd_16x2->stack_id;
	sc.type = TYPE_SET_CONFIG;
	sc.length = sizeof(SetConfig);
	sc.cursor = cursor;
	sc.blinking = blinking;

	ipcon_device_write(lcd_16x2, (char *)&sc, sizeof(SetConfig));

	ipcon_sem_post_write(lcd_16x2);

	return E_OK;
}

int lcd_16x2_get_config(LCD16x2 *lcd_16x2, bool *ret_cursor, bool *ret_blinking) {
	if(lcd_16x2->ipcon == NULL) {
		return E_NOT_ADDED;
	}

	ipcon_sem_wait_write(lcd_16x2);

	lcd_16x2->answer.type = TYPE_GET_CONFIG;
	lcd_16x2->answer.length = sizeof(GetConfigReturn);
	GetConfig gc;
	gc.stack_id = lcd_16x2->stack_id;
	gc.type = TYPE_GET_CONFIG;
	gc.length = sizeof(GetConfig);

	ipcon_device_write(lcd_16x2, (char *)&gc, sizeof(GetConfig));

	if(ipcon_answer_sem_wait_timeout(lcd_16x2) != 0) {
		ipcon_sem_post_write(lcd_16x2);
		return E_TIMEOUT;
	}

	GetConfigReturn *gcr = (GetConfigReturn *)lcd_16x2->answer.buffer;
	*ret_cursor = gcr->cursor;
	*ret_blinking = gcr->blinking;

	ipcon_sem_post_write(lcd_16x2);

	return E_OK;
}

int lcd_16x2_is_button_pressed(LCD16x2 *lcd_16x2, uint8_t button, bool *ret_pressed) {
	if(lcd_16x2->ipcon == NULL) {
		return E_NOT_ADDED;
	}

	ipcon_sem_wait_write(lcd_16x2);

	lcd_16x2->answer.type = TYPE_IS_BUTTON_PRESSED;
	lcd_16x2->answer.length = sizeof(IsButtonPressedReturn);
	IsButtonPressed ibp;
	ibp.stack_id = lcd_16x2->stack_id;
	ibp.type = TYPE_IS_BUTTON_PRESSED;
	ibp.length = sizeof(IsButtonPressed);
	ibp.button = button;

	ipcon_device_write(lcd_16x2, (char *)&ibp, sizeof(IsButtonPressed));

	if(ipcon_answer_sem_wait_timeout(lcd_16x2) != 0) {
		ipcon_sem_post_write(lcd_16x2);
		return E_TIMEOUT;
	}

	IsButtonPressedReturn *ibpr = (IsButtonPressedReturn *)lcd_16x2->answer.buffer;
	*ret_pressed = ibpr->pressed;

	ipcon_sem_post_write(lcd_16x2);

	return E_OK;
}

int lcd_16x2_callback_button_pressed(LCD16x2 *lcd_16x2, const unsigned char *buffer) {
	ButtonPressedCallback *bpc = (ButtonPressedCallback *)buffer;
	((button_pressed_func_t)lcd_16x2->callbacks[bpc->type])(bpc->button);
	return sizeof(ButtonPressedCallback);
}

int lcd_16x2_callback_button_released(LCD16x2 *lcd_16x2, const unsigned char *buffer) {
	ButtonReleasedCallback *brc = (ButtonReleasedCallback *)buffer;
	((button_released_func_t)lcd_16x2->callbacks[brc->type])(brc->button);
	return sizeof(ButtonReleasedCallback);
}

void lcd_16x2_register_callback(LCD16x2 *lcd_16x2, uint8_t cb, void *func) {
    lcd_16x2->callbacks[cb] = func;
}

void lcd_16x2_create(LCD16x2 *lcd_16x2, const char *uid) {
	ipcon_device_create(lcd_16x2, uid);

	lcd_16x2->device_callbacks[TYPE_BUTTON_PRESSED] = lcd_16x2_callback_button_pressed;
	lcd_16x2->device_callbacks[TYPE_BUTTON_RELEASED] = lcd_16x2_callback_button_released;
}
