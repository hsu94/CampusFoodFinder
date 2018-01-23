/*
 * SD.c
 *
 *  Created on: 2016-02-17
 *  Author: 2015W2CPEN391 Team 10
		This is the source file containing all functions for using the SD card reader
 */

#include <stdio.h>
#include "altera_up_sd_card_avalon_interface.h"
#include "SD.h"
/*
 * OpenSD opens the SD card and generate corresponding error messages
 */
void OpenSD() {
	alt_up_sd_card_dev *device_reference = NULL;
	int connected = 0;

	printf("Opening SDCard\n");
	if ((device_reference = alt_up_sd_card_open_dev(
			"/dev/Altera_UP_SD_Card_Avalon_Interface_0")) == NULL) {
		printf("SDCard Open FAILED\n");
		return;
	} else
		printf("SDCard Open PASSED\n");
}


/*
 * WriteToSD writes a string passed to a pre-existing file
 * If the file does not exist, try change code to alt_up_sd_Card_fopen(filename, true)
 * The program will fail to run at the first attempt, but should make a new file titled with the filename passed
 * Change the true to false for the following program-run
 */
void WriteToSD(char filename[], char msg[]) {

	short int myFileHandle;
	if (alt_up_sd_card_is_Present() && alt_up_sd_card_is_FAT16()) {
		if ((myFileHandle = alt_up_sd_card_fopen(filename,false)) != -1) {
			volatile short int readVal = 0;
			readVal = alt_up_sd_card_read(myFileHandle);
			while (readVal >= 0) {
				readVal = alt_up_sd_card_read(myFileHandle);
			}
			int i = 0;

			while (msg[i] != NULL) {
				if (alt_up_sd_card_write(myFileHandle, msg[i]) == false) {
					printf("Error writing to file...\n");
				}
				i++;
			}
			//printf("Initial write complete\n");

			alt_up_sd_card_fclose(myFileHandle);
		} else
			printf("could not open the file even though it exists \n");
	} else {
		printf("no sd card or not FAT16\n");
	}
}

/*
 * Reads strings in the file passed and returns the string containing location of the location name passed
 */


char* ReadFromSD(char filename[], char location[]) {
	short int myFileHandle2;
	char* retstr;
	char readstr[512];
	char cmpstr[7];

	int index = 0;
	if (alt_up_sd_card_is_Present() && alt_up_sd_card_is_FAT16()) {
		if ((myFileHandle2 = alt_up_sd_card_fopen(filename, false)) != -1) {
			printf("File reopened\n");

			printf("now reading \n");
			short int result = 1;
			char ctr;
			while(result >= 0){
				index = 0;
				do{
				result = alt_up_sd_card_read(myFileHandle2);
				ctr = result;
				readstr[index] = result;
				++index;
				//printf("%c", result);
				}while (ctr != '\n');


				readstr[index] = '\0';
				strncpy(cmpstr, readstr, 6);
				cmpstr[6] = '\0';

				if(strcmp(cmpstr,location) == 0){

					return parseLoc(readstr);
				}
			}


			printf("\ndone");
			alt_up_sd_card_fclose(myFileHandle2);

		} else
			printf("reopen failed");
	}
	return "non";
}

char* parseLoc(char* loc){
	char ploc[40];
	int i = 0;
	while(*(loc + i)!= ':'){
		++i;

	}

	++i;
	int i2 = 0;
	do{
			ploc[i2] = *(loc + i);
			++i;
			++i2;

	}while(ploc[i2] != '\n');

	++i2;
	ploc[i2] = '\0';
	return ploc;
}
