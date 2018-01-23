/*
 * bluetooth.h
 *
 *  Created on: Apr 6, 2016
 *      Author: Kevin
 */

#ifndef BLUETOOTH_H_
#define BLUETOOTH_H_

#include <stdio.h>
#include <string.h>
#include "profile.h"
#include "GPS.h"
#include "functions.h"

#define BT_Control (*(volatile unsigned char *)(0x84000220))
#define BT_Status (*(volatile unsigned char *)(0x84000220))
#define BT_TxData (*(volatile unsigned char *)(0x84000222))
#define BT_RxData (*(volatile unsigned char *)(0x84000222))
#define BT_Baud (*(volatile unsigned char *)(0x84000224))

#define NAME 0
#define AGE 1
#define GENDER 2
#define WEIGHT 3
#define HEIGHT 4
#define DIST 5
#define RANK 6
#define END 7

// initialize bluetooth
void init_BT(void);
// pass a char via bluetooth
int putcharBT(int c);
// get a char from bluetooth
int getcharBT(void);
// test function for receiving data from bluetooth
int BTTestForReceivedData(void);
// parse incoming BT data
int parseBT(char input[]);
// get user's name from bluetooth
char* get_name(char input[]);
// get user's other information
float get_info(int info, char input[]);
// send user's bmi
int send_bmi(profile *p);
// send user's rank
int send_rank(profile *p);

#endif /* BLUETOOTH_H_ */
