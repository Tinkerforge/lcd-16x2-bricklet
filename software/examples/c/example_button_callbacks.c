
#include <stdio.h>

#include "ip_connection.h"
#include "bricklet_lcd_16x2.h"

#define HOST "localhost"
#define PORT 4223
#define UID "XYZ" // Change to your UID

// Callback functions for button status
void cb_pressed(uint8_t i, void *user_data) {
	(void)user_data; // avoid unused parameter warning

	printf("Pressed: %d\n", i);
}

void cb_released(uint8_t i, void *user_data) {
	(void)user_data; // avoid unused parameter warning

	printf("Released: %d\n", i);
}

int main() {
	// Create IP connection
	IPConnection ipcon;
	ipcon_create(&ipcon);

	// Create device object
	LCD16x2 lcd;
	lcd_16x2_create(&lcd, UID, &ipcon); 

	// Connect to brickd
	if(ipcon_connect(&ipcon, HOST, PORT) < 0) {
		fprintf(stderr, "Could not connect\n");
		exit(1);
	}
	// Don't use device before ipcon is connected

	// Register button status callbacks to cb_pressed and cb_released
	lcd_16x2_register_callback(&lcd, 
	                           LCD_16X2_CALLBACK_BUTTON_PRESSED, 
	                           (void *)cb_pressed,
	                           NULL);

	lcd_16x2_register_callback(&lcd, 
	                           LCD_16X2_CALLBACK_BUTTON_RELEASED, 
	                           (void *)cb_released,
	                           NULL);

	printf("Press key to exit\n");
	getchar();
	ipcon_destroy(&ipcon); // Calls ipcon_disconnect internally
}
