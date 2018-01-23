#include "GPS.h"
#include "time.h"
#include <stdio.h>

/*
 *	Program stall for 1 millisecond
 */
void wait_1ms2(void) {
	int i;
	for (i = 0; i < 1000; i++)
		;

}

/*
 * init_GPS: Initialises the GPS chip to start sending and recieving data via the Serial Port
 */
void init_GPS(void) {
	// Initialize the Control Register
	GPS_Control = 0x15;

	// Initialize the Baud Rate Generator to use 115k Baud
	GPS_Baud = 0x05;
}

/*
 * putcharGPS sends a character, which is part of a full string command, to the GPS via the Serial Port
 */
int putcharGPS(int c) {

	while ((GPS_Status & 0x02) != 0x02) {
	}
	GPS_TxData = c;
	return c;
}

/*
 * getcharGPS returns the character as part of a string received from the GPS
 */
int getcharGPS(void) {

	while (!((GPS_Status & 0x1) == 0x1)) {
	}

	return GPS_RxData;
}

/*
 * GPSTestForReceivedData returns 1 if there are data received at the Serial Port
 * Else, returns a 0
 */
int GPSTestForReceivedData(void) {
	if (GPS_Status & 0x1)
		return 1;
	else
		return 0;
}

/*
 * checkGPGGA takes a string and compare it with string $GPGGA
 * Returns "0" if the the string passed is "$GPGGA"
 */
int checkGPGGA(char* string) {
	char GGA[] = "$GPGGA";
	return strcmp(string, GGA);
}

/*
 * getGPSTime takes the raw GPS data received and parses out the UTC time.
 * Then, converts the UTC time to PST (local vancouver time)
 * Returns a string of PST time
 */
char* getGPSTime(char *GPS_Data) {
	char Time[512];
	char* timeptr = GPS_Data + 6;

	char HH[3];
	char MM[3];
	char SS[3];
	HH[0] = *(++timeptr);
	HH[1] = *(++timeptr);
	HH[2] = '\0';

	int hour = atoi(HH);
	//if(hour > 20 && hour <= 23){
	//hour = hour - 20;
	//}
	//else{
	//hour = hour + 4;
	//}
	hour = hour - 8;

	sprintf(HH, "%d", hour);

	MM[0] = *(++timeptr);
	MM[1] = *(++timeptr);
	MM[2] = '\0';

	SS[0] = *(++timeptr);
	SS[1] = *(++timeptr);
	SS[2] = '\0';

	strcpy(Time, "LOCAL TIME: ");
	strcat(Time, HH);
	strcat(Time, ":");
	strcat(Time, MM);
	strcat(Time, ":");
	strcat(Time, SS);

	return Time;

}

/*
 * parseGPSData takes the raw GPS data and parses out the Latitude and Longitude
 * Returns a string of the geological coordinates in the format: "+/-XX.YY(Latitude)     +/-XXX.YY(Longitude)"
 *
 */
char* parseGPSData(char *GPS_Data) {
	char NS[2];
	char EW[2];
	char LatD[3];
	char LatM[7];

	char LogD[4];
	char LogM[7];

	//Degree digits for Latitude and Longitude
	int Lat, Log;

	char *pointer;
	int i;

	//Latitude Calculation
	pointer = GPS_Data + 17;

	if (*(GPS_Data + 28) == 'N') {
		NS[0] = '+';
	} else {
		NS[0] = '-';
	}
	NS[1] = '\0';

	if (*(GPS_Data + 41) == 'W') {
		EW[0] = '-';
	} else {
		EW[0] = '+';
	}
	EW[1] = '\0';

	LatD[0] = *(++pointer);
	LatD[1] = *(++pointer);
	LatD[2] = '\0';

	LatM[0] = *(++pointer);
	LatM[1] = *(++pointer);
	++pointer; //skip over the comma
	LatM[2] = *(++pointer);
	LatM[3] = *(++pointer);
	LatM[4] = *(++pointer);
	LatM[5] = *(++pointer);
	LatM[6] = '\0';

	//LatM = LatM/60
	Lat = atoi(LatM);
	Lat = Lat / 60;
	sprintf(LatM, "%i", Lat);

	//Longitude Calculation
	pointer = GPS_Data + 29;

	LogD[0] = *(++pointer);
	LogD[1] = *(++pointer);
	LogD[2] = *(++pointer);
	LogD[3] = '\0';

	LogM[0] = *(++pointer);
	LogM[1] = *(++pointer);
	++pointer; //skip over the comma
	LogM[2] = *(++pointer);
	LogM[3] = *(++pointer);
	LogM[4] = *(++pointer);
	LogM[5] = *(++pointer);
	LogM[6] = '\0';

	//LogM = LogM/60
	Log = atoi(LogM);
	Log = Log / 60;
	sprintf(LogM, "%i", Log);

	char LatLog[512];

	strcpy(LatLog, NS);
	strcat(LatLog, LatD);
	strcat(LatLog, ".");
	strcat(LatLog, LatM);

	strcat(LatLog, "|");

	strcat(LatLog, EW);
	strcat(LatLog, LogD);
	strcat(LatLog, ".");
	strcat(LatLog, LogM);
	strcat(LatLog, "\n");

	return LatLog;
}

/*
 * getGPSData retrieves the raw GPS data received and calls either parseGPSData or getGPSTime
 * Returns a strijng of either the geological coordinates or the PST time
 *
 * Note: Call init_GPS() before calling getGPSData
 */

char* getGPSData(int mode) {
	//mode check
	if (mode != GPSCOORD && mode != GPSTIME) {
		printf("Invalid mode entered!!!!\n");
		return NULL;
	}
	char* GPSData;
	if (GPSTestForReceivedData() == 1) {
		int check = 0;

		char data[512];
		char str[7];

		int index = 0;
		int i = 0;

		char input;
		input = getcharGPS();

		while (1) {
			index = 0;
			do {
				input = getcharGPS();
				data[index] = input;
				++index;
			} while (input != '\n');
			data[index] = '\0';

			strncpy(str, data, 6);
			str[6] = '\0';

			if (checkGPGGA(str) == 0) {
				if (mode == GPSCOORD) {
					GPSData = parseGPSData(data);
				} else if (mode == GPSTIME) {
					GPSData = getGPSTime(data);
				}

				break;
			}
		}
	}
	return GPSData;
}

double getDistance(char* loc1, char* loc2) {
	char lat1[10];
	char lat2[10];
	char log1[10];
	char log2[10];

	double la1, la2, lo1, lo2;

	int i = 0;

	while (loc1[i] != '|') {
		lat1[i] = *(loc1 + i);
		lat2[i] = *(loc2 + i);
		++i;
	}
	lat1[i] = '\0';
	lat2[i] = '\0';
	++i;
	int j = 0;
	while (loc1[i] != '\n') {
		log1[j] = *(loc1 + i);
		log2[j] = *(loc2 + i);
		++i;
		++j;
	}
	log1[j] = '\0';
	log2[j] = '\0';

	//printf("log2 %s\n");

	la1 = atof(lat1);
	la2 = atof(lat2);
	lo1 = atof(log1);
	lo2 = atof(log2);

	printf("la1: %f  lat2: %f  log1: %f   log2: %f\n", la1, la2, lo1, lo2);

	double dLat = deg2rad(la2 - la1);
	double dLog = deg2rad(lo2 - lo1);

	double a = sin(dLat / 2) * sin(dLat / 2)
			+ cos(deg2rad(la1)) * cos(deg2rad(la2)) * sin(dLog / 2)
					* sin(dLog / 2);
	double c = 2 * atan2(sqrt(a), sqrt(1 - a));
	double distance = EarthR * c;

	return distance;
}

double getDistance2(char lat1[],char long1[], char lat2[], char long2[]) {

	double la1, la2, lo1, lo2;

	//printf("log2 %s\n");

	la1 = atof(lat1);
	la2 = atof(lat2);
	lo1 = atof(long1);
	lo2 = atof(long2);

	printf("la1: %f  lat2: %f  log1: %f   log2: %f\n", la1, la2, lo1, lo2);

	double dLat = deg2rad(la2 - la1);
	double dLog = deg2rad(lo2 - lo1);

	double a = sin(dLat / 2) * sin(dLat / 2)
			+ cos(deg2rad(la1)) * cos(deg2rad(la2)) * sin(dLog / 2)
					* sin(dLog / 2);
	double c = 2 * atan2(sqrt(a), sqrt(1 - a));
	double distance = EarthR * c;

	return distance;
}


double deg2rad(double deg) {
	return deg * PI / 180;
}

int checkGPVTG(char* string) {
	char VTG[] = "$GPVTG";
	return strcmp(string, VTG);
}

double parseSpeed(char *VTG_Data) {
	double speed;
	char str_speed[6];
	char *ptr = VTG_Data + 25;
	int i;

	for (i = 0; i < 4; ++i) {
		str_speed[i] = *(++ptr);
	}
	++i;
	str_speed[i] = '\0';
	printf("%s\n", str_speed);

	speed = atof(str_speed);
	printf("atof\n %f", speed);
	return speed;
}

double getSpeed(void) {
	double speed;
	if (GPSTestForReceivedData()) {
		int check = 0;
		char data[512];
		char str[7];

		int index = 0;
		int i = 0;

		char input = getcharGPS();

		while (1) {
			index = 0;
			do {
				input = getcharGPS();
				data[index] = input;
				++index;
			} while (input != '\n');
			data[index] = '\0';

			strncpy(str, data, 6);
			str[6] = '\0';

			if (checkGPVTG(str) == 0) {
				printf("%s\n", data);
				speed = parseSpeed(data);
				break;
			}
		}
	}
	return speed;
}

void eraseLog() {
	char cmd[30] = "$PMTK184,1*22\r\n";
	printf("send ");
	int a = 0;
	while (cmd[a] != NULL) {
		printf("%c", cmd[a]);
		putcharGPS(cmd[a]);
		a++;
	}
	wait_1ms2();
	/*char* GPSData;
	 if (GPSTestForReceivedData() == 1) {
	 int check = 0;

	 char data[512];
	 char str[7];

	 int index = 0;
	 int i = 0;

	 char input;
	 input = getcharGPS();

	 int count = 0;
	 while (count < 10) {
	 index = 0;
	 do {
	 input = getcharGPS();
	 data[index] = input;
	 ++index;
	 } while (input != '\n');
	 data[index] = '\0';

	 int index2 = 0;
	 if(data[1] == 'P'){
	 while (data[index2] != 0) {
	 printf("%c", data[index2]);
	 index2++;
	 }
	 }
	 count++;
	 }
	 } else
	 printf("no data\n");*/
}

void changeInterval() {
	char cmd[30] = "$PMTK187,1,1*3C\r\n";
	printf("send ");
	int a = 0;
	while (cmd[a] != NULL) {
		printf("%c", cmd[a]);
		putcharGPS(cmd[a]);
		a++;
	}
	wait_1ms2();
}

void startLog() {
	char cmd[30] = "$PMTK185,0*22\r\n";

	int a = 0;
	printf("send ");
	while (cmd[a] != NULL) {
		printf("%c", cmd[a]);
		putcharGPS(cmd[a]);
		a++;
	}
	wait_1ms2();
	char* GPSData;
	 if (GPSTestForReceivedData() == 1) {
	 int check = 0;

	 char data[512];
	 char str[7];

	 int index = 0;
	 int i = 0;

	 char input;
	 input = getcharGPS();

	 int count = 0;
	 while (count < 10) {
	 index = 0;
	 do {
	 input = getcharGPS();
	 data[index] = input;
	 ++index;
	 } while (input != '\n');
	 data[index] = '\0';

	 int index2 = 0;
	 if(data[1] == 'P'){
	 while (data[index2] != 0) {
	 printf("%c", data[index2]);
	 index2++;
	 }
	 }
	 count++;
	 }
	 } else
	 printf("no data\n");
}

void stopLog() {
	char cmd[30] = "$PMTK185,1*23\r\n";

	int a = 0;
	int temp;
	printf("send ");
	while (cmd[a] != NULL) {
		printf("%c", cmd[a]);
		putcharGPS(cmd[a]);
		a++;
	}

	wait_1ms2();
}

int dumpLog() {
	char cmd[30] = "$PMTK622,1*29\r\n";

	printf("send ");
	int a = 0;
	while (cmd[a] != NULL) {
		printf("%c", cmd[a]);
		putcharGPS(cmd[a]);
		a++;
	}
	wait_1ms2();
	int logcount = 0;
	char* GPSData;
	if (GPSTestForReceivedData() == 1) {
		int check = 0;

		char data[50000]; //string we get from gps characters
		int entry; //which log entry we are on
		int index = 0; //which field in the
		int i = 1;

		char input; //character we get from GPS

		while ((data[0] != '$') || (data[7] != 'X') || (data[9] != '0')) {
			index = 0;
			do {
				input = getcharGPS();
				data[index] = input;
				++index;
			} while (input != '\n');
			data[index] = '\0';
		}

		while ((data[0] != '$') || (data[7] != 'X') || (data[11] != '0')) {
			index = 0;
			do {
				input = getcharGPS();
				data[index] = input;
				++index;
			} while (input != '\n');
			data[index] = '\0';
		}

		char time1[100];
		char lat1[100];
		char long1[100];
		i=0;
		while((data[1] == 'P') && (data[2] == 'M')){// && ((data[13] != 'F') || (data[14]!='F')|| (data[15]!='F'))) {
			index = 0;
			do {
				input = getcharGPS();
				data[index] = input;
				printf("%c", data[index]);
				++index;
			} while (input != '\n');


			int tempi = 0;
			int comma = 0;
			int digits =0;
			while (tempi < 8) {

				if(i > 8){
					digits = 1;
				}
				if(i > 98){
					digits = 2;
				}
				time1[tempi] = data[tempi + 13 + digits];
				lat1[tempi] = data[tempi + 24 + comma + digits];
				long1[tempi] = data[tempi + 33 + comma + digits];
				if (tempi == 5)
					comma = 1;
				tempi++;
			}



			lat1[8] = '\0';
			long1[8] = '\0';
			time1[8] = '\0';
			//int time2 = swapEndian(time1);
			int lat2 = swapEndian(lat1);
			int long2 = swapEndian(long1);
			//printf("%s", ctime(&time2));


			char *flat = FloatToLatitudeConversion(lat2);
			char* flong = FloatToLongitudeConversion(long2);
			char* invalid = "nan";
			int cmp = strcmp(flat, invalid);
			int cmp2 = strcmp(flong, invalid);

			if ((cmp == 0) || (cmp2 == 0)){
				continue;
			}

			strcat(flat, "\r");
			strcat(flong, "\r");
			strcat(flat, "\0");
			strcat(flong, "\0");

			strcpy(logarray[i].latitude, flat);
			strcpy(logarray[i].longitude, flong);
			strcpy(logarray[i].time, time1);



			i++;
			logcount++;
		}
	} else
		printf("no data\n");
	logcount--;
	return logcount;
}

int swapEndian(char *s) {
	register int val;
	val = strtoul(s, NULL, 16); // convert to 4 byte int form in base 16
	val = ((val << 8) & 0xFF00FF00) | ((val >> 8) & 0xFF00FF);
	val = (val << 16) | ((val >> 16) & 0xFFFF);
	return val;
}

char *FloatToLatitudeConversion(int x) //output format is xx.yyyy
{
	static char buff[100];
	float *ptr = (float *) (&x); // cast int to float
	float f = *ptr; // get the float
	sprintf(buff, "%2.4f", f); // write in string to an array
	return buff;
}

char *FloatToLongitudeConversion(int x) // output format is (-)xxx.yyyy
{
	static char buff[100];
	float *ptr = (float *) (&x);
	float f = *ptr;
	sprintf(buff, "%3.4f", f);
	return buff;
}
