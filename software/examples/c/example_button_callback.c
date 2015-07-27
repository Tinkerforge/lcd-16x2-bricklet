#include <stdio.h>

#include "ip_connection.h"
#include "bricklet_lcd_16x2.h"

#define HOST "localhost"
#define PORT 4223
#define UID "XYZ" // Change to your UID

// Callback function for button pressed callback
void cb_button_pressed(uint8_t button_pressed, void *user_data) {
	(void)user_data; // avoid unused parameter warning

	printf("Button Pressed: %d\n", button_pressed);
}

// Callback function for button released callback
void cb_button_released(uint8_t button_released, void *user_data) {
	(void)user_data; // avoid unused parameter warning

	printf("Button Released: %d\n", button_released);
}

int main() {
	// Create IP connection
	IPConnection ipcon;
	ipcon_create(&ipcon);

	// Create device object
	LCD16x2 lcd162;
	lcd_16x2_create(&lcd162, UID, &ipcon);

	// Connect to brickd
	if(ipcon_connect(&ipcon, HOST, PORT) < 0) {
		fprintf(stderr, "Could not connect\n");
		exit(1);
	}
	// Don't use device before ipcon is connected

	// Register button pressed callback to function cb_button_pressed
	lcd_16x2_register_callback(&lcd162,
	                           LCD_16X2_CALLBACK_BUTTON_PRESSED,
	                           (void *)cb_button_pressed,
	                           NULL);

	// Register button released callback to function cb_button_released
	lcd_16x2_register_callback(&lcd162,
	                           LCD_16X2_CALLBACK_BUTTON_RELEASED,
	                           (void *)cb_button_released,
	                           NULL);

	printf("Press key to exit\n");
	getchar();
	ipcon_destroy(&ipcon); // Calls ipcon_disconnect internally
}
