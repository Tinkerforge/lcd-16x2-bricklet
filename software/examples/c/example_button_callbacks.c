
#include <stdio.h>

#include "ip_connection.h"
#include "bricklet_lcd_16x2.h"

#define HOST "localhost"
#define PORT 4223
#define UID "XYZ" // Change to your UID

// Callback functions for button status
void cb_pressed(uint8_t i) {
	printf("Pressed: %d\n", i);
}

void cb_released(uint8_t i) {
	printf("Released: %d\n", i);
}

int main() {
	// Create IP connection to brickd
	IPConnection ipcon;
	if(ipcon_create(&ipcon, HOST, PORT) < 0) {
		fprintf(stderr, "Could not create connection\n");
		exit(1);
	}

	// Create device object
	LCD16x2 lcd;
	lcd_16x2_create(&lcd, UID); 

	// Add device to IP connection
	if(ipcon_add_device(&ipcon, &lcd) < 0) {
		fprintf(stderr, "Could not connect to Bricklet\n");
		exit(1);
	}
	// Don't use device before it is added to a connection

	// Register button status callbacks to cb_pressed and cb_released
	lcd_16x2_register_callback(&lcd, 
	                           LCD_16X2_CALLBACK_BUTTON_PRESSED, 
	                           cb_pressed);
	lcd_16x2_register_callback(&lcd, 
	                           LCD_16X2_CALLBACK_BUTTON_RELEASED, 
	                           cb_released);

	printf("Press ctrl+c to close\n");
	ipcon_join_thread(&ipcon); // Join mainloop of IP connection
}
