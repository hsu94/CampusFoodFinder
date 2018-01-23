/*
 * touchscreen.h
 *
 *  Created on: 2016-02-22
 *      Author: steven
 */

#ifndef TOUCHSCREEN_H_
#define TOUCHSCREEN_H_

#define GraphicsCommandReg (*(volatile unsigned short int *)(0x84000000))
#define GraphicsStatusReg (*(volatile unsigned short int *)(0x84000000))
#define GraphicsX1Reg (*(volatile unsigned short int *)(0x84000002))
#define GraphicsY1Reg (*(volatile unsigned short int *)(0x84000004))
#define GraphicsX2Reg (*(volatile unsigned short int *)(0x84000006))
#define GraphicsY2Reg (*(volatile unsigned short int *)(0x84000008))
#define GraphicsColourReg (*(volatile unsigned short int *)(0x8400000E))
#define GraphicsBackGroundColourReg (*(volatile unsigned short int *)(0x84000010))
#define WAIT_FOR_GRAPHICS while((GraphicsStatusReg & 0x0001) != 0x0001);

#define touchscreen_Control (*(volatile unsigned char *)(0x84000230))
#define touchscreen_Status (*(volatile unsigned char *)(0x84000230))
#define touchscreen_TxData (*(volatile unsigned char *)(0x84000232))
#define touchscreen_RxData (*(volatile unsigned char *)(0x84000232))
#define touchscreen_Baud (*(volatile unsigned char *)(0x84000234))


typedef struct {
	int x, y;
} Point;

//initialize the LCD
void Init_LCD(void);
//initialize the touchscreen
void Init_Touch(void);
//check if screen is touched
int ScreenTouched(void);
//wait until the screen is touched
void WaitForTouch();
//return the coordinate when a getpress signal is received
Point GetPress(void);
//return the coordinate when a getrelease signal is received
Point GetRelease(void);
//returns data from the touchscreen
int getchartouch(void);
//send commands to touchscreen
int putchartouch(int c);


#endif /* TOUCHSCREEN_H_ */
