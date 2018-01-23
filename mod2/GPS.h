

/*
 * GPS.h
 *
 *  Created on: 2016-02-16
 *  Author: 2015W2CPEN391 Team 10
 *  	This is the header file for GPS. It contains the hardware addresses of the GPS, as well as the declaration of the
 *  	functions and constant implemented in GPS.c
 */

#ifndef GPS_H_
#define GPS_H_

#include <string.h>
#include <stdlib.h>
#include <math.h>



#define GPSCOORD 0
#define GPSTIME  1

#define PI 3.141592653589793238462643383279502887197169399
#define EarthR 6371



#define GPS_Control (*(volatile unsigned char *)(0x84000210))
#define GPS_Status (*(volatile unsigned char *)(0x84000210))
#define GPS_TxData (*(volatile unsigned char *)(0x84000212))
#define GPS_RxData (*(volatile unsigned char *)(0x84000212))
#define GPS_Baud (*(volatile unsigned char *)(0x84000214))

typedef struct
{
	double speed; //distance between prev and current logentry
	double distance;
    char latitude[100];
    char longitude[100];
    char time[100];
} logentry;

extern int temptime[100];
extern logentry logarray[1000];
//extern int logcount;
//extern char *timeptr

//Program stall for 1 millisecond
void wait_1ms2(void);

//Send a character to the GPS
int putcharGPS(int c);

//Get a character received from the GPS
int getcharGPS(void);

//Test to see if any data is received from the GPS
int GPSTestForReceivedData(void);

//Check if the String passed is "$GPGGA"
int checkGPGGA(char* string);

//Check if the String passed is "$GPVTG"

int checkGPVTG(char* string);

//Initializes the GPS
void init_GPS(void);

//getGPSData recieves raw data from  GPS and returns the Latitude and Longitude of //the current position. Call init_GPS before calling any other GPS functions
char* getGPSData(int mode);

//Parse the raw GPSData and returns the Latitude and Longitude
char* parseGPSData(char *GPS_Data);


//Parse the raw GPSData and returns the LOCAL PST time
char* getGPSTime(char *GPS_Data);

//Returns the distance between points
double getDistance(char* loc1, char*loc2);

//return distance between 2 lat and 2 longs
double getDistance2(char lat1[],char long1[], char lat2[], char long2[]);

//Converts degree to radian
double deg2rad(double deg);

//Parse speed data from GPVTG data
double parseSpeed(char *VTG_Data);

//Returns the speed
double getSpeed(void);

//start data logging
void startLog();

//stop data logging
void stopLog();

char *FloatToLatitudeConversion(int x);
char *FloatToLongitudeConversion(int x);

#endif /* GPS_H_ */
