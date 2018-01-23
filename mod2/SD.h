/*
 * SD.h
 *
 *  Created on: 2016-02-17
 *  Author: 2015W2CPEN391 Team 10
		This is the header file for the SD.c. It contains all the functions for sending command to the SD card reader
 */

#ifndef SD_H_
#define SD_H_

#include <stdlib.h>

void OpenSD();
void WriteToSD(char filename[], char msg[]);
char* ReadFromSD(char filename[], char location[]);
char* parseLoc(char* loc);

#endif /* SD_H_ */
