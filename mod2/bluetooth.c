/*
 * bluetooth.c
 *
 *  Created on: Apr 6, 2016
 *      Author: Kevin
 */

#include "bluetooth.h"

void init_BT(void) {
	// Initialize the Control Register
	BT_Control = 0x15;

	// Initialize the Baud Rate Generator to use 115k Baud
	BT_Baud = 0x01;
}

int putcharBT(int c) {

	while (BT_Status & 0x02 != 0x02) {
	}

	BT_TxData = c;
	return c;
}

int getcharBT(void) {

	while (!((BT_Status & 0x1) == 0x1)) {
	}

	return BT_RxData;
}

int BTTestForReceivedData(void) {
	if (BT_Status & 0x1)
		return 1;
	else
		return 0;
}

int parseBT(char input[]) {

	int i = 0;
	char temp[20];



	i = 0;
	while (input[i] != ',') {
		temp[i] = input[i];
		i++;
	}

	if (strcmp(temp, "NAME") == 0) {
		return NAME;
	} else if (strcmp(temp, "AGE") == 0) {
		return AGE;
	} else if (strcmp(temp, "GENDER") == 0) {
		return GENDER;
	} else if (strcmp(temp, "WEIGHT") == 0) {
		return WEIGHT;
	} else if (strcmp(temp, "HEIGHT") == 0) {
		return HEIGHT;
	} else if (strcmp(temp, "DIST") == 0) {
		return DIST;
	} else if (strcmp(temp, "RANK") == 0) {
		return RANK;
	}

	return -1;
}

char* get_name(char input[]) {
	int i = 5;
	char temp[50];

	while (input[i] != '\0') {
		temp[i - 5] = input[i];
		i++;
	}

	return temp;
}

float get_info(int info, char input[]) {

	int i = 0;
	char temp[50];

	if (info == AGE) {
		i = 4;
		while (input[i] != '\0') {
			temp[i - 4] = input[i];
			i++;
		}

		return atof(temp);
	} else if (info == GENDER) {
		i = 7;
		while (input[i] != '\0') {
			temp[i - 7] = input[i];
			i++;
		}

		return atof(temp);
	} else if (info == WEIGHT) {
		i = 7;
		while (input[i] != '\0') {
			temp[i - 7] = input[i];
			i++;
		}

		return atof(temp);
	} else if (info == HEIGHT) {
		i = 7;
		while (input[i] != '\0') {
			temp[i - 7] = input[i];
			i++;
		}

		return atof(temp);
	} else if (info == DIST) {
		i = 9;
		while (input[i] != '\0') {
			temp[i - 9] = input[i];
			i++;
		}

		return atof(temp);
	} else if (info == RANK) {
		i = 5;
		while (input[i] != '\0') {
			temp[i - 5] = input[i];
			i++;
		}

		return atof(temp);
	}

	return -1;
}

int send_bmi(profile *p) {
	int i = 0;
	char result[20];
	sprintf(result, "BMI,%2.2f\r", p->bmi);

	for (i = 0; i < strlen(result); i++) {
		putcharBT(result[i]);
		wait_1ms2();
	}

	return 1;
}

int send_rank(profile *p) {
	int i = 0;
	char result[20];
	sprintf(result, "RANK,%d\r", p->rank);

	for (i = 0; i < strlen(result); i++) {
		putcharBT(result[i]);
		wait_1ms2();
	}

	return 1;
}

void writetoBT(char msg[]) {
	// Write to device

	int i;
	for (i = 0; i < strlen(msg); i++) {
		putcharBT(msg[i]);
		wait_1ms2();
	}
}

/*
 int s2;
 char readStr[100];
 while(1){

 // Write to device
 for(i2 = 0; i2 < strlen(msg1); i2++){
 putcharBT(msg1[i2]);
 wait_1ms2();
 }

 // Read from device
 if(BTTestForReceivedData() == 1){
 for( s2 = 0; s2 < strlen(readStr); s2++){
 readStr[s2] = getcharBT();
 //wait_1ms2();
 }
 wait_1ms2();
 printf("String Received: %s\n", readStr);
 }
 }

 return 0;
 }*/
void receivebtData() {
	/* --- START OF READING AND WRITING WITH BT DEVICE --- */

	int i2;
	int s2;
	char readStr[100];
	char u_name[50];
	profile p;

	while (1) {//while there is data to read

		// Read from device
	if (BTTestForReceivedData() == 1) {
		for (s2 = 0; s2 < strlen(readStr); s2++) {
			readStr[s2] = getcharBT();
				//wait_1ms2();
		}
			wait_1ms2();
			printf("String Received: %s\n", readStr);
			printf("test");
		}

		int info = parseBT(readStr);

		if (info == -1)
			printf("Invalid information\n");

		if (info == NAME) {
			strcpy(u_name, get_name(readStr));
			printf("Name : %s", u_name);
			set_name(&p, u_name);
		} else if (info == AGE) {
			set_age(&p, get_info(info, readStr));
		} else if (info == GENDER) {
			set_gender(&p, get_info(info, readStr));
		} else if (info == HEIGHT) {
			set_height(&p, get_info(info, readStr));
		} else if (info == WEIGHT) {
			set_weight(&p, get_info(info, readStr));
		} else if (info == DIST) {
			set_dis(&p, get_info(info, readStr));
		}
		else if(info == END){
			break;
		}


	}

	calc_bmi(&p);
	update_score(&p);
	set_rank(&p);

	send_bmi(&p);
	send_rank(&p);
}

