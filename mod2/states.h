/*
 * states.h
 *
 *  Created on: 2016-02-22
 *      Author: steven
 */

#ifndef STATES_H_
#define STATES_H_
#include <stdio.h>
#include <stdlib.h>
#include "Graphics.h"
#include "altera_up_avalon_character_lcd.h"
#include "GPS.h"
#include "touchscreen.h"
#include "SD.h"
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

extern int logcount;

//print the distance onto the screen when get distance button pressed
//void printDistance(Storestruct store);
//return 1 if the back button was pressed, 0 otherwise
int backPressed(int p1x, int p1y, int p2x, int p2y);
//return 1 if the time button was pressed, 0 otherwise
int timePressed(int p1x, int p1y, int p2x, int p2y);
//return 1 if the home button was pressed, 0 otherwise
int homePressed(int p1x, int p1y, int p2x, int p2y);
//return 1 if the distance button was pressed, 0 otherwise
int distancePressed(int p1x, int p1y, int p2x, int p2y);
//check if closest button pressed
int closestPressed(int p1x, int p1y, int p2x, int p2y);

/****State transition functions for each page of our application****/
//state function for welcome page
void Welcome();
//state function for home page
void Home();
//state function for search page
void Search();
//state function for favourites page
void Favourites();
//state function for time page
void TimePage();
//state function for info page
void info();
//state function for map page
void Map();
//state function for state page
void Distance();



#endif /* STATES_H_ */
