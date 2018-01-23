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
#include <string.h>

#define BT_Control (*(volatile unsigned char *)(0x84000220))
#define BT_Status (*(volatile unsigned char *)(0x84000220))
#define BT_TxData (*(volatile unsigned char *)(0x84000222))
#define BT_RxData (*(volatile unsigned char *)(0x84000222))
#define BT_Baud (*(volatile unsigned char *)(0x84000224))

void wait_1ms(void){
	int i;
	for( i = 0; i < 1000; i++);
}

void init_BT(void){
	// Initialize the Control Register
	BT_Control = 0x15;

	// Initialize the Baud Rate Generator to use 115k Baud
	BT_Baud = 0x01;
}

int putcharBT(int c){

	while(BT_Status & 0x02 != 0x02){
	}

	BT_TxData = c;
	return c ;
}

int getcharBT(void){

	while(!((BT_Status & 0x1) == 0x1)){
	}

	return BT_RxData;
}

int BTTestForReceivedData(void){
	if (BT_Status & 0x1)
		return 1;
	else
		return 0;
}

int main()
{
	// Initialize the bluetooth
	init_BT();
	printf("Initializing...\n");

	// Wait 1 sec
	int j;
	for(j=0; j < 10000; j++){
		wait_1ms();
	}
	for(j=0; j < 10000; j++){
		wait_1ms();
	}
	// Enter Control Mode by writing $$$
	char controlMode[] = "$$$";
	char wVal[strlen(controlMode)];
	int i;
	for(i = 0; i < strlen(controlMode); i++){
		wVal[i]=putcharBT(controlMode[i]);
		wait_1ms();
	}
	printf("Value written: %s\n", wVal);

	// Wait 1 sec
	int s;
	for(s=0; s < 10000; s++){
		wait_1ms();
	}
	for(s=0; s < 10000; s++){
		wait_1ms();
	}
	printf("Entered Control Mode\n");

	// Read Echo
	char readVal[10];
	int r = 0;
	while(BTTestForReceivedData()== 1){
		readVal[r] = getcharBT();
		r++;
	}
	printf("Echo is: %s\n", readVal);

	for(s=0; s < 10000; s++){
		wait_1ms();
	}
	for(s=0; s < 10000; s++){
		wait_1ms();
	}
	/*
	// Toggle the echo
	char echo[] = "+";
	char eVal[strlen(echo)];
	for(i = 0; i < strlen(echo); i++){
		eVal[i]= putcharBT(echo[i]);
		wait_1ms();
	}
	for(s=0; s < 10000; s++){
		wait_1ms();
	}
	for(s=0; s < 10000; s++){
		wait_1ms();
	}
	*/
	// Read Echo
	char readEcho[20];
	r = 0;
	while(BTTestForReceivedData()== 1){
		readEcho[r] = getcharBT();
		r++;
	}
	printf("Echo after name change is: %s\n", readEcho);

	for(s=0; s < 10000; s++){
		wait_1ms();
	}
	for(s=0; s < 10000; s++){
		wait_1ms();
	}

	// Change device name
	char name[] = "SN,Team10\r\n";
	char nVal[strlen(name)];
	int d;
	for(d = 0; d < strlen(name); d++){
		nVal[d]=putcharBT(name[d]);
		wait_1ms();
	}
	printf("Name changed to %s\n", name);
	printf("Value written: %s\n", nVal);

	for(s=0; s < 10000; s++){
		wait_1ms();
	}
	for(s=0; s < 10000; s++){
		wait_1ms();
	}

	// Read Echo
	r = 0;
	while(BTTestForReceivedData()== 1){
		readEcho[r] = getcharBT();
		r++;
	}
	printf("Echo after name change is: %s\n", readEcho);

	for(s=0; s < 10000; s++){
		wait_1ms();
	}
	for(s=0; s < 10000; s++){
		wait_1ms();
	}

	// Change device mode
	char mode[] = "SM,0\r\n";
	char mVal[strlen(mode)];
	int m;
	for(m = 0; m < strlen(mode); m++){
		mVal[m]=putcharBT(mode[m]);
		wait_1ms();
	}
	printf("Mode changed to %s\n", mode);
	printf("Value written: %s\n", mVal);

	for(s=0; s < 10000; s++){
		wait_1ms();
	}
	for(s=0; s < 10000; s++){
		wait_1ms();
	}
	// Read Echo
	r = 0;
	while(BTTestForReceivedData()== 1){
		readEcho[r] = getcharBT();
		r++;
	}
	printf("Echo after name change is: %s\n", readEcho);

	for(s=0; s < 10000; s++){
		wait_1ms();
	}
	for(s=0; s < 10000; s++){
		wait_1ms();
	}
	char controlMode1[] = "---\r\n";
	char wVal1[strlen(controlMode1)];
	for(i = 0; i < strlen(controlMode1); i++){
		wVal1[i]=putcharBT(controlMode1[i]);
		wait_1ms();
	}
	printf("Value written: %s\n", wVal1);

	// Wait 1 sec

	for(s=0; s < 10000; s++){
		wait_1ms();
	}
	for(s=0; s < 10000; s++){
			wait_1ms();
		}
	printf("Exited Control Mode\n");

	/* --- START OF READING AND WRITING WITH BT DEVICE --- */
	char msg1[] = "hello\r";
	//char msg2[strlen(msg1)];
	int i2;
	int s2;
	char readStr[100];
	while(1){

		// Write to device
		for(i2 = 0; i2 < strlen(msg1); i2++){
			putcharBT(msg1[i2]);
			wait_1ms();
		}

		// Read from device
		if(BTTestForReceivedData() == 1){
			for( s2 = 0; s2 < strlen(readStr); s2++){
				readStr[s2] = getcharBT();
				//wait_1ms();
			}
			wait_1ms();
			printf("String Received: %s\n", readStr);
		}
	}

  return 0;
}
