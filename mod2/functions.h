#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Graphics.h"
#include "altera_up_avalon_character_lcd.h"
#include "GPS.h"
#include "touchscreen.h"
#include "profile.h"

#define DrawHLine 1
#define DrawVLine 2
#define DrawLine 3
#define PutAPixel 0xA
#define GetAPixel 0xB
#define ProgramPaletteColour 0x10

#define BLACK 0
#define WHITE 1
#define RED 2
#define LIME 3
#define BLUE 4
#define YELLOW 5
#define CYAN 6
#define MAGENTA 7
#define GRAY 9
#define BROWN 115
#define DBLUE 78
#define DGREEN 44
#define DBLUE 78
#define DIMGRAY 144
#define DGRAY 146
#define LGRAY 147

#define XRES 800
#define YRES 480

//States
#define WELCOME 0
#define HOME 1
#define MAP 2
#define SEARCH 3
#define STATS 4
#define FAVOURITE 5
#define TODO 6
#define TIMHORTONS 7
#define REBOOT 8
#define STARBUCKS 9
#define AGORA 10
#define DISTANCE 11

extern int logcount;
extern double totaldistance;
extern double avgspeed;
extern double topspeed;
extern double numspeeds;
extern double timeran;
extern struct tm * starttime;
extern struct tm * endtime;
extern char sendlats[1000];
extern int starthour;
extern int startmin;
extern int endhour;
extern int endmin;


//wait 5 seconds
void wait5s();
//check if the specified area of the screen (a button) is pressed and released
int ifTouched(int p1x, int p1y, int p2x, int p2y, int x1, int x2, int y1, int y2) ;
int ifTouched2(int p1x, int p1y, int p2x, int p2y, int x1, int x2, int y1, int y2) ;
//clearing and setting the screen to a specified colour
void clearScreen();
void setScreen(int colour);
//write text with different fonts (writeText2 has smaller font)
void writeText(char msg[], int x, int y, int margin, int color,	int backgroundcolor);
void writeText2(char msg[], int x, int y, int margin, int color, int backgroundcolor);
//draw a rectangle filled in with color
void drawRectangle(int x1, int x2, int y1, int y2, int colour);
//Commonly used functions to draw buttons onto screen
void drawBack();
void drawTimeButton();
void drawBorder();
void drawDistanceButton();
//draw filled in favourite button
void drawFav();
//draw non-filled favourite button for non-favourited stores
void drawFav2();
//draw a cup for use with the draw map function
void drawCup(int x, int y, int colour);
//calculate the distance you have run
void calculateDistance();
//print the coordinates of your run
void printCoords();


/*****The following functions are used to draw each page of our application******/

//draw the Welcome Page
void drawWelcome();
//draw the home page
void drawHome();
//draw the search page
void drawSearch();
//draw the favourites page
void drawFavourites();
//draw the time page
void drawTime();
//draw the store info for each restaurant
void drawInfo();
//draw the map
void drawMap();
//draw distance page
void drawDistance();
//draw profle page
void drawProfile(profile *p);


#endif /* FUNCTIONS_H_ */
