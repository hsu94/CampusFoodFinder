/*
 * touchscreen.c
 *
 *  Created on: 2016-02-22
 *      Author: steven
 */


#include "touchscreen.h"
#include "altera_up_avalon_character_lcd.h"
#include <stdio.h>
#include <stdlib.h>

void Init_LCD(void) {
	alt_printf("Starting\n");
	alt_up_character_lcd_dev * char_lcd_dev;

	char_lcd_dev = alt_up_character_lcd_open_dev("/dev/character_lcd_0");

	if (char_lcd_dev == NULL)
		alt_printf("Error:could not open character LCD Device\n");
	else
		alt_printf("Opened LCD Device\n");

	alt_up_character_lcd_init(char_lcd_dev);
	alt_up_character_lcd_cursor_blink_on(char_lcd_dev);
}

void Init_Touch(void) {
	touchscreen_Baud = 0x05;
	touchscreen_Control = 0x15;

	char cmd[3];
	cmd[0] = 0x55;
	cmd[1] = 0x01;
	cmd[2] = 0x12;

	while (touchscreen_Status & 0x02 != 0x02) {
	}
	touchscreen_TxData = cmd[0]; //0x68

	while (touchscreen_Status & 0x02 != 0x02) {
	}
	touchscreen_TxData = cmd[1];

	while (touchscreen_Status & 0x02 != 0x02) {
	}
	touchscreen_TxData = cmd[2];

	putchartouch(0x51);
}

int ScreenTouched(void)
{
	return ((touchscreen_Status & 0x1) == 0x1);
}

void WaitForTouch()
{
	while (!ScreenTouched()) {
		printf("waiting for screen\n");
	}
}

Point GetPress(void) {
	Point p1;
	p1.x = -1;
	p1.y = -1;
	int x1, x2, y1, y2;
	int x, y;
	double xf, yf;

	int coord;
	coord = getchartouch();

	if (coord == 0x81) {

		{
			x1 = getchartouch() & 0x7f;
			x2 = getchartouch() & 0x1f;
			y1 = getchartouch() & 0x7f;
			y2 = getchartouch() & 0x1f;
		}
		x = x1 | (x2 << 7);
		y = y1 | (y2 << 7);

		xf = (x - 108) / (4.89875);
		yf = (y - 260) / (7.84167);
		if (xf < 0) {
			xf = 0;
		}
		if (xf > 800) {
			xf = 800;
		}
		if (yf < 0) {
			yf = 0;
		}
		if (yf > 480) {
			yf = 480;
		}
		printf("press %lf %lf \n", xf, yf);
		p1.x = xf;
		p1.y = yf;
	}

	return p1;
}

Point GetRelease(void) {
	Point p1;
	p1.x = -1;
	 p1.y = -1;
	int x1, x2, y1, y2;
	int x, y;
	double xf, yf;

	int coord;
	coord = getchartouch();

	if (coord == 0x80) {
		x1 = getchartouch() & 0x7f;
		x2 = getchartouch() & 0x1f;
		y1 = getchartouch() & 0x7f;
		y2 = getchartouch() & 0x1f;

		x = x1 | (x2 << 7);
		y = y1 | (y2 << 7);
		xf = (x - 108) / (4.89875);
		yf = (y - 260) / (7.84167);
		if (xf < 0) {
			xf = 0;
		}
		if (xf > 800) {
			xf = 800;
		}
		if (yf < 0) {
			yf = 0;
		}
		if (yf > 480) {
			yf = 480;
		}

		printf("release\n");
		p1.x = xf;
		p1.y = yf;

	}
	return p1;

}

int putchartouch(int c) {

	while (touchscreen_Status & 0x02 != 0x02) {
	}

	touchscreen_TxData = c;
	return c;
}

int getchartouch(void) {

	while (!((touchscreen_Status & 0x1) == 0x1)) {
	}

	return touchscreen_RxData;
}
