/*
 * "Hello World" example.
 *
 * This example prints 'Hello from Nios II' to the STDOUT stream. It runs on
 * the Nios II 'standard', 'full_featured', 'fast', and 'low_cost' example
 * designs. It runs with or without the MicroC/OS-II RTOS and requires a STDOUT
 * device in your system's hardware.
 * The memory footprint of this hosted application is ~69 kbytes by default
 * using the standard reference design.
 *
 * For a reduced footprint version of this template, and an explanation of how
 * to reduce the memory footprint for a given application, see the
 * "small_hello_world" template.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include "Graphics.h"
#include "altera_up_avalon_character_lcd.h"

#define GPS_Control (*(volatile unsigned char *)(0x84000210))
#define GPS_Status (*(volatile unsigned char *)(0x84000210))
#define GPS_TxData (*(volatile unsigned char *)(0x84000212))
#define GPS_RxData (*(volatile unsigned char *)(0x84000212))
#define GPS_Baud (*(volatile unsigned char *)(0x84000214))

#define GraphicsCommandReg (*(volatile unsigned short int *)(0x84000000))
#define GraphicsStatusReg (*(volatile unsigned short int *)(0x84000000))
#define GraphicsX1Reg (*(volatile unsigned short int *)(0x84000002))
#define GraphicsY1Reg (*(volatile unsigned short int *)(0x84000004))
#define GraphicsX2Reg (*(volatile unsigned short int *)(0x84000006))
#define GraphicsY2Reg (*(volatile unsigned short int *)(0x84000008))
#define GraphicsColourReg (*(volatile unsigned short int *)(0x8400000E))
#define GraphicsBackGroundColourReg (*(volatile unsigned short int *)(0x84000010))

#define WAIT_FOR_GRAPHICS while((GraphicsStatusReg & 0x0001) != 0x0001);


#define DrawHLine 1
#define DrawVLine 2
#define DrawLine 3
#define PutAPixel 0xA
#define GetAPixel 0xB
#define ProgramPaletteColour 0x10

#define BLACK 0
#define WHITE 1
#define RED 2
#define LIME 3
#define BLUE 4
#define YELLOW 5
#define CYAN 6
#define MAGENTA 7

#define XRES 800
#define YRES 480

void wait_1ms(void) {
	int i;
	for (i = 0; i < 1000; i++)
		;
}

void init_GPS(void) {
	// Initialize the Control Register
	GPS_Control = 0x15;

	// Initialize the Baud Rate Generator to use 115k Baud
	GPS_Baud = 0x05;
}

int putcharGPS(int c) {

	while (GPS_Status & 0x02 != 0x02) {
	}
	GPS_TxData = c;
	return c;
}

int getcharGPS(void) {

	while (!((GPS_Status & 0x1) == 0x1)) {
	}

	return GPS_RxData;
}

int GPSTestForReceivedData(void) {
	if (GPS_Status & 0x1)
		return 1;
	else
		return 0;
}

int checkGPGGA(char* string) {
	char GGA[] = "$GPGGA";
	return strcmp(string, GGA);
}

void printLCD(char* LCD_Data, alt_up_character_lcd_dev * char_lcd_dev) {
	char strpt[50];

	alt_up_character_lcd_set_cursor_pos(char_lcd_dev, 0, 0);
	alt_up_character_lcd_string(char_lcd_dev, "LOG:");
	strncpy(strpt, LCD_Data + 30, 39);
	strpt[10] = LCD_Data[41];
	strpt[11] = '\0';
	alt_up_character_lcd_string(char_lcd_dev, strpt);

	int i = 0;
	int x1 = 100;
	int y1 = 20;
	int Colour = 1;
	int BColour = 0;

	OutGraphicsCharFont2a(x1, y1, Colour, BColour, 'L', 1);
	x1 += 15;
	OutGraphicsCharFont2a(x1, y1, Colour, BColour, 'O', 1);
	x1 += 15;
	OutGraphicsCharFont2a(x1, y1, Colour, BColour, 'G', 1);
	x1 += 15;
	OutGraphicsCharFont2a(x1, y1, Colour, BColour, ':', 1);
	x1 += 30;

	for (i = 0; i < 11; i++){
		OutGraphicsCharFont2a(x1, y1, Colour, BColour, strpt[i], 1);
		x1 += 15;
	}

	alt_up_character_lcd_set_cursor_pos(char_lcd_dev, 0, 1);
	alt_up_character_lcd_string(char_lcd_dev, "LAT:");
	strncpy(strpt, LCD_Data + 18, 26);
	strpt[9] = LCD_Data[28];
	strpt[10] = '\0';
	alt_up_character_lcd_string(char_lcd_dev, strpt);

	x1 = 100;
	y1 = 60;

	OutGraphicsCharFont2a(x1, y1, Colour, BColour, 'L', 1);
	x1 += 15;
	OutGraphicsCharFont2a(x1, y1, Colour, BColour, 'A', 1);
	x1 += 15;
	OutGraphicsCharFont2a(x1, y1, Colour, BColour, 'T', 1);
	x1 += 15;
	OutGraphicsCharFont2a(x1, y1, Colour, BColour, ':', 1);
	x1 += 30;

	for (i = 0; i < 11; i++){
			OutGraphicsCharFont2a(x1, y1, Colour, BColour, strpt[i], 1);
			x1 += 15;
	}

}

int main()
{

	int x1;
	int y1;

	int x2;
	int y2;

	int Colour;
	int BColour;

	Colour = 0;
	BColour = 7;

	for (y1 = 0; y1 <= 480; y1++){
		HLine(0, y1, 850, Colour);
	}

	// Initialize the LCD
	alt_printf("Starting\n");
	alt_up_character_lcd_dev * char_lcd_dev;

	char_lcd_dev = alt_up_character_lcd_open_dev("/dev/character_lcd_0");

	if (char_lcd_dev == NULL)
		alt_printf("Error:could not open character LCD Device\n");
	else
		alt_printf("Opened LCD Device\n");

	alt_up_character_lcd_init(char_lcd_dev);
	alt_up_character_lcd_cursor_blink_on(char_lcd_dev);

	// Initialize the GPS
	init_GPS();
	printf("Initializing...\n");

	/*char cmd[] = "$PMTKLOX,0,43*6E";
	char wVal[strlen(cmd)];
	int j;
	for (j = 0; j < strlen(cmd); j++) {
		wVal[j] = putcharGPS(cmd[j]);
		wait_1ms();
	}
	printf("Cmd written: %\n", wVal);

	// Wait 1 sec
	int s;
	for (s = 0; s < 10000; s++) {
		wait_1ms();
	}
	for (s = 0; s < 10000; s++) {
		wait_1ms();
	}
	*/
	if (GPSTestForReceivedData() == 1) {

		char data[512];
		char str[7];

		int index = 0;
		int i = 0;

		char input;
		input = getcharGPS();
		loop: while (1) {
			index = 0;
			do {
				input = getcharGPS();
				data[index] = input;
				index++;
			} while ((input) != '\n');
			data[index] = '\0';

			strncpy(str, data, 6);
			str[6] = '\0';

			if (checkGPGGA(str) == 0) {
				//alt_up_character_lcd_string(char_lcd_dev, data);
				printLCD(data, char_lcd_dev);
				printf("%s", data);
			}
		}

	}


  return 0;
}
