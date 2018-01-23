#include "functions.h"
#include "distance.h"

extern volatile int currentState;
volatile char Time[512];

void wait5s() {
	int i = 0;
	for (i = 0; i < 25000; i++) {
		wait_1ms2();
	}
}

int ifTouched(int p1x, int p1y, int p2x, int p2y, int x1, int x2, int y1,
		int y2) {

	wait_1ms2();

	if ((p1x >= x1 && p1x <= x2) && (p1y >= y1 && p1y <= y2)) {
		return 1;
	}
	return 0;
}

int ifTouched2(int p1x, int p1y, int p2x, int p2y, int x1, int x2, int y1,
		int y2) {
	if (((p1x >= x1 && p1x <= x2) && (p2x >= x1 && p2x <= x2))
			&& ((p1y >= y1 && p1y <= y2) && (p2y >= y1 && p2y <= y2))) {
		return 1;
	}
	return 0;
}

void clearScreen() {
	int y;
	for (y = 0; y <= 480; y++) {
		HLine(0, y, 800, 78);
	}
}

void setScreen(int colour) {
	int y;
	for (y = 0; y <= 480; y++) {
		HLine(0, y, 800, colour);
	}
}

void writeText(char msg[], int x, int y, int margin, int color,
		int backgroundcolor) {
	int i = 0;
	int textmarker = x;
	int tempchar;
	while (msg[i] != NULL) {
		tempchar = msg[i];
		OutGraphicsCharFont2a(textmarker, y, color, backgroundcolor, tempchar,
				1);
		textmarker = textmarker + margin;
		i++;
	}
}

void writeText2(char msg[], int x, int y, int margin, int color,
		int backgroundcolor) {
	int i = 0;
	int textmarker = x;
	int tempchar;
	while (msg[i] != NULL) {
		tempchar = msg[i];
		OutGraphicsCharFont1(textmarker, y, color, backgroundcolor, tempchar,
				1);
		textmarker = textmarker + margin;
		i++;
	}
}

void drawRectangle(int x1, int x2, int y1, int y2, int colour) {
	int i;
	for (i = y1 + 1; i < y2; i++)
		HLine(x1, i, x2 - x1 - 1, colour);
}

void drawBack() {
	drawRectangle(690, 780, 400, 460, BLUE);
	writeText("Back", 710, 430, 15, YELLOW, BLUE);
}


void drawHomeButton() {
	drawRectangle(690, 780, 20, 80, BLUE);
	writeText("Home", 710, 40, 15, YELLOW, BLUE);
}

void drawInner(int color) {
	drawRectangle(20, 780, 20, 460, color);
}

void drawWelcome() {
	clearScreen();
	setScreen(78);
	char msg1[] = "Welcome to Fitup";
	char msg2[] = "Touch Anywhere To Continue";
	writeText(msg1, 230, 150, 22, YELLOW, 78);
	writeText2(msg2, 265, 300, 10, WHITE, 78);
}

void drawHome() {
	clearScreen();
	drawInner(WHITE);
	drawRectangle(200, 600, 75, 150, YELLOW);
	drawRectangle(200, 600, 175, 250, YELLOW);
	drawRectangle(200, 600, 275, 350, YELLOW);
	drawRectangle(200, 600, 375, 450, YELLOW);
	writeText("HOME", 360, 40, 20, DBLUE, WHITE);
	writeText("Start Run", 330, 110, 15, BLACK, YELLOW);
	writeText("Run Stats", 330, 210, 15, BLACK, YELLOW);
	writeText("Sync", 360, 310, 15, BLACK, YELLOW);
	writeText("Profile", 330, 410, 15, BLACK, YELLOW);
	drawBack();
}

void drawStartRun() {
	clearScreen();
	drawInner(WHITE);
	writeText("Currently tracking your run", 100, 150, 22, BLACK, WHITE);
	drawRectangle(200, 600, 250, 400, RED);
	writeText("End Run", 320, 325, 25, YELLOW, RED);
	drawBack();
}

void drawEndRun() {
	clearScreen();
	drawInner(WHITE);
	writeText("One moment please", 275, 125, 15, BLUE, WHITE);
	writeText("Currently analyzing your run", 225, 170, 12, RED, WHITE);
	writeText("Check out your run statistics in the Run Stats menu!", 110, 300,
			12, BLACK, WHITE);
}

void drawStats() {
	clearScreen();
	drawInner(WHITE);
	writeText("Stats", 360, 40, 20, DBLUE, WHITE);

	char totdistance[10];
	char avgspd[10];
	char topspd[10];
	char timestarthr[10];
	char timestartmin[10];
	char timeendhr[10];
	char timeendmin[10];
	char timeElapsed[10];

	sprintf(totdistance, "%.2f", totaldistance);
	sprintf(avgspd, "%.2f", avgspeed);
	sprintf(topspd, "%.2f", topspeed);

	sprintf(timestarthr, "%i", starthour);
	sprintf(timestartmin, "%i", startmin);
	sprintf(timeendhr, "%i", endhour);
	sprintf(timeendmin, "%i", endmin);

	sprintf(timeElapsed, "%.2f", timeran);

	writeText("Run started at: ", 40, 120, 15, RED, WHITE);
	writeText(timestarthr, 300, 120, 15, RED, WHITE);
	writeText(":", 330, 120, 15, RED, WHITE);
	writeText(timestartmin, 350, 120, 15, RED, WHITE);
	writeText("PST", 400, 120, 15, RED, WHITE);

	writeText("Run ended at: ", 40, 160, 15, RED, WHITE);
	writeText(timeendhr, 300, 160, 15, RED, WHITE);
	writeText(":", 330, 160, 15, RED, WHITE);
	writeText(timeendmin, 350, 160, 15, RED, WHITE);
	writeText("PST", 400, 160, 15, RED, WHITE);

	writeText("Time Elapsed: ", 40, 200, 15, RED, WHITE);
	writeText(timeElapsed, 300, 200, 15, RED, WHITE);
	writeText("minutes", 400, 200, 15, RED, WHITE);

	writeText("Total Distance: ", 40, 240, 15, RED, WHITE);
	writeText(totdistance, 300, 240, 15, RED, WHITE);
	writeText("metres", 400, 240, 15, RED, WHITE);

	writeText("Average Speed: ", 40, 280, 15, RED, WHITE);
	writeText(avgspd, 300, 280, 15, RED, WHITE);
	writeText("metres/second", 400, 280, 15, RED, WHITE);

	writeText("Top Speed: ", 40, 320, 15, RED, WHITE);
	writeText(topspd, 300, 320, 15, RED, WHITE);
	writeText("metres/second", 400, 320, 15, RED, WHITE);

	drawBack();
	drawHomeButton();

}



void calculateDistance() {
	double distance;
	double speed;
	totaldistance = 0;
	topspeed = 0;
	avgspeed = 0;
	numspeeds = 0;
	int i = 1;
	int j = 0;
	while (i < logcount) {
		double distance = getDistance2(logarray[i - 1].latitude,
				logarray[i - 1].longitude, logarray[i].latitude,
				logarray[i].longitude);
		distance = distance * 1000;
		speed = distance / 6;
		if (speed > topspeed)
			topspeed = speed;
		printf("distance is %f\n", distance);
		totaldistance = totaldistance + distance;
		i++;
		numspeeds++;
	}
	timeran = (numspeeds * 6) / 60;
	avgspeed = totaldistance / (numspeeds * 6);

	printf(
			"total distance is %f, average speed was %f, and top speed was %f, time spent running %f.",
			totaldistance, avgspeed, topspeed, timeran);
}

void findTimes() {
	struct tm * starttime;
	int time2 = swapEndian(logarray[0].time);
	starttime = gmtime(&time2);
	starttime->tm_hour = (starttime->tm_hour - 7) % 24;
	if ((starttime->tm_hour) < 0) {
		starttime->tm_hour = 24 + starttime->tm_hour;
	}
	starthour = starttime->tm_hour;
	startmin = starttime->tm_min;
	printf("\nstart time is :  %2d:%02d\n", (starttime->tm_hour),
			starttime->tm_min);

	struct tm * endtime;
	time2 = swapEndian(logarray[logcount - 1].time);
	endtime = gmtime(&time2);
	endtime->tm_hour = (endtime->tm_hour - 7) % 24;
	if ((endtime->tm_hour) < 0) {
		endtime->tm_hour = 24 + endtime->tm_hour;
	}
	endhour = endtime->tm_hour;
	endmin = endtime->tm_min;
	printf("end time is :  %2d:%02d\n", endtime->tm_hour, endtime->tm_min);
}

void printCoords() {
	int i = 0;
	int j = 0;
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

}






void sendCoords() {
	int i = 0;
	int j = 0;
	int k = 0;

	int i2;
	int s2;
	char readStr[100];
	char totaldist[10];
	sprintf(totaldist, "%.2f", totaldistance);
	//char cat[1] = "\r";
	//totaldist = strcat(totaldist, cat);
	totaldist[9] = '\r';

	while (1) { //while there is data to read

		// Read from device
		if (BTTestForReceivedData() == 1) {
			for (s2 = 0; readStr[s2] != '\0'; s2++) {
				readStr[s2] = getcharBT();
				//wait_1ms2();
			}
			wait_1ms2();
			printf("String Received: %s\n", readStr);
		}
		if (strcmp(readStr, "G\0") == 0)
			break;
		if(k == 20000000)
			break;
		k++;
	}
	printf("test");

	writetoBT("STARTLAT\r");
	for (i = 0; i < logcount - 1; i++) {
		//for(j=0; logarray[i].latitude[j]; j++)
		writetoBT(logarray[i].latitude);
	}
	writetoBT("STOPLAT\r");
	k=0;
	while (1) { //while there is data to read

		// Read from device
		if (BTTestForReceivedData() == 1) {
			for (s2 = 0; readStr[s2] != '\0'; s2++) {
				readStr[s2] = getcharBT();
				//wait_1ms2();
			}
			wait_1ms2();
			printf("String Received: %s\n", readStr);
		}
		if (strcmp(readStr, "H\0") == 0)
			break;
		if(k == 20000000)
			break;
		k++;
	}

	writetoBT("STARTLONG\r");
	for (i = 0; i < logcount - 1; i++) {
		//for(j=0; logarray[i].latitude[j]; j++)
		writetoBT(logarray[i].longitude);
	}
	writetoBT("STOPLONG\r");
	/*while (1) { //while there is data to read

		// Read from device
		if (BTTestForReceivedData() == 1) {
			for (s2 = 0; readStr[s2] != '\0'; s2++) {
				readStr[s2] = getcharBT();
				//wait_1ms2();
			}
			wait_1ms2();
			printf("String Received: %s\n", readStr);
		}
		if (strcmp(readStr, "D\0") == 0)
			break;
		if(k == 10000000)
			break;
		k++;
	}
	writetoBT("STARTDIST\r");
	writetoBT(totaldist);*/
}

void drawProfile(profile *p) {
	clearScreen();

	int colour_t = BLACK; //colour of text
	int colour_b = CYAN; //colour of backgrounds(both text background and block background
	int base_x = 40; //base x coord for all blocks
	int base_y = 70; //base upper y coord for all blocks
	int base_y1 = 110; //base lower y coord for all blocks
	int base_y_t = 85; //base y coord for all texts
	int margin_l = 15; //margin between letters for texts
	int ver_margin = 70; //vertical margin between each block
	int hor_margin = 10; //how far the blocks are from the left side of the screen
	char str[20];

	drawBack();
	drawHomeButton();

	// draw name tag
	drawRectangle(XRES / 2 - 100, XRES / 2 + 100, 20, 60, colour_b);
	writeText(p->name, XRES / 2 - 50, 30, 20, colour_t, colour_b);
	// draw age
	drawRectangle(base_x, base_x + 130, base_y, base_y1, colour_b);
	sprintf(str, "Age : %d", p->age);
	writeText(str, base_x + hor_margin, base_y_t, margin_l, colour_t, colour_b);
	// draw gender
	drawRectangle(base_x, base_x + 250, base_y + ver_margin,
			base_y1 + ver_margin, colour_b);
	if (p->gender == 0)
		strcpy(str, "Gender : Female");
	else
		strcpy(str, "Gender : Male");
	writeText(str, base_x + hor_margin, base_y_t + ver_margin, margin_l,
			colour_t, colour_b);
	// draw weight
	drawRectangle(base_x, base_x + 270, base_y + ver_margin * 2,
			base_y1 + ver_margin * 2, colour_b);
	sprintf(str, "Weight : %2.2f kg", p->weight);
	writeText(str, base_x + hor_margin, base_y_t + ver_margin * 2, margin_l,
			colour_t, colour_b);
	// draw height
	drawRectangle(base_x, base_x + 250, base_y + ver_margin * 3,
			base_y1 + ver_margin * 3, colour_b);
	sprintf(str, "Height : %2.2f m", p->height);
	writeText(str, base_x + hor_margin, base_y_t + ver_margin * 3, margin_l,
			colour_t, colour_b);
	// draw bmi
	drawRectangle(base_x, base_x + 350, base_y + ver_margin * 4,
			base_y1 + ver_margin * 4, colour_b);
	sprintf(str, "BMI Calculated : %2.2f", p->bmi);
	writeText(str, base_x + hor_margin, base_y_t + ver_margin * 4, margin_l,
			colour_t, colour_b);
	// draw goal
	//drawRectangle(base_x, base_x + 500, base_y + ver_margin * 5, base_y1 + ver_margin * 5, colour_b);
	//sprintf(str, "%s", p->goal);
	//writeText(p->goal, XRES/2 - 50, 400, 20, colour_t, colour_b);
	//writeText(str, XRES/2 - 50, 400, 20, colour_t, colour_b);
	//strcpy(str, p->goal);
	//writeText(p->goal, base_x + hor_margin, base_y_t + ver_margin * 5, margin_l, colour_t, colour_b);

}

void drawSync() {
	clearScreen();
	drawInner(WHITE);
	writeText("Please wait while your Fitup syncs with your android device", 50,
			225, 12, RED, WHITE);
}
