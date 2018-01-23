/*
 * CPEN 391 TEAM 10 CAMPUS FOOD FINDER
 * Author: Sanaya, Steven, Kevin, and Carol
 * Date: March 1, 2016
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Graphics.h"
#include "altera_up_avalon_character_lcd.h"
#include "stack.h"
#include "GPS.h"
#include "SD.h"
#include "touchscreen.h"
#include "states.h"
#include "functions.h"
#include "distance.h"
#include "bluetooth.h"

//States
#define WELCOME 0
#define HOME 1
#define STARTRUN 2
#define ENDRUN 3
#define STATS 4
#define PROFILE 5
#define SYNC 6
#define TIMHORTONS 7
#define REBOOT 8
#define STARBUCKS 9
#define AGORA 10
#define DISTANCE 11

#define INTERVAL 6

volatile int currentState;
volatile int closest;
Stack lastStates;
logentry logarray[1000];
double RESDIS = 0;
double totaldistance = 0;
double avgspeed = 0;
double topspeed = 0;
double numspeeds = 0; //the number of speed intervals so far
double timeran = 0;
int logcount; // the number of logs we have received.
int runnum;
struct tm * starttime;
struct tm * endtime;
int starthour;
int startmin;
int endhour;
int endmin;
char sendlats[1000];

int main() {
	currentState = WELCOME;
	init_BT();
	Init_LCD(); //initialize LCD
	Init_Touch(); //initialize Touchscreen
	init_GPS();
	clearScreen();
	init(&lastStates); //initialize stack

	profile p;
	profile_init(&p);
	set_name(&p, "Jimmy");
	set_gender(&p, 1);
	set_age(&p, 20);
	set_weight(&p, 55);
	set_height(&p, 1.7);
	p.bmi = calc_bmi(&p);
	//set_goal(&p, "I want to run 10 miles this month");

	//printf("%s\n", p.goal);

	/*
	 while (i < logcount) {
	 j = 0;
	 printf("lat %i is ", i);
	 while (logarray[i].latitude[j] != NULL) {
	 printf("%c", logarray[i].latitude[j]);
	 j++;
	 }
	 printf(" long %i is ", i);
	 j = 0;
	 while (logarray[i].longitude[j] != NULL) {
	 printf("%c", logarray[i].longitude[j]);
	 j++;
	 }
	 printf("\n");
	 i++;
	 }

	 struct tm * ptm;
	 int time2 = swapEndian(logarray[0].time);
	 ptm = gmtime ( &time2);
	 printf ("start time is :  %2d:%02d\n", (ptm->tm_hour-7)%24, ptm->tm_min);
	 int t;
	 for(t=0; t< 10; t++){
	 printf("%c",logarray[0].time[t]);
	 }
	 printf("\n");
	 for(t=0; t< 10; t++){
	 printf("%c",logarray[21].time[t]);
	 }
	 time2 = swapEndian(logarray[20].time);
	 ptm = gmtime ( &time2);
	 printf ("end time is :  %2d:%02d\n", (ptm->tm_hour-7)%24, ptm->tm_min);

	 double distance = getDistance2(logarray[0].latitude, logarray[0].longitude, logarray[1].latitude, logarray[1].longitude);
	 distance = distance*1000;
	 printf("\ndistance is %f metres", distance);

	 printf("\nstarting writetobt");*/

	printf("program starting");
	while (1) {
		if (currentState == WELCOME) {
			drawWelcome();
			Welcome();
		} else if (currentState == HOME) {
			drawHome();
			Home();
		} else if (currentState == STARTRUN) {
			drawStartRun();
			StartRun();
		} else if (currentState == ENDRUN) {
			drawEndRun();
			EndRun();
		} else if (currentState == STATS) {
			drawStats();
			Stats();
		} else if (currentState == PROFILE) {
			//receivebtData();
			drawProfile(&p);
			Profile();
		} else if (currentState == SYNC) {
			drawSync();
			Sync();
		} else {
			currentState = WELCOME;
		}

	}
	return 0;
}

