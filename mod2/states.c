#include "states.h"
#include "stack.h"
#include "functions.h"
#include "distance.h"


extern volatile int currentState;
extern Stack lastStates;


int backPressed(int p1x, int p1y, int p2x, int p2y) {
	if (ifTouched(p1x, p1y, p2x, p2y, 700, 800, 400, 480) == 1) { //back button pressed
		return 1;
	}
	return 0;
}

int closestPressed(int p1x, int p1y, int p2x, int p2y) {
	if (ifTouched(p1x, p1y, p2x, p2y, 350, 450, 400, 480) == 1) { //back button pressed
		return 1;
	}
	return 0;
}

int timePressed(int p1x, int p1y, int p2x, int p2y) {
	if (ifTouched(p1x, p1y, p2x, p2y, 700, 800, 0, 100) == 1) { //back button pressed
		return 1;
	}
	return 0;
}

int homePressed(int p1x, int p1y, int p2x, int p2y) {
	if (ifTouched(p1x, p1y, p2x, p2y, 700, 800, 0, 100) == 1) { //back button pressed
		return 1;
	}
	return 0;
}

int distancePressed(int p1x, int p1y, int p2x, int p2y) {
	if (ifTouched(p1x, p1y, p2x, p2y, 130, 230, 400, 480) == 1) { //back button pressed
		return 1;
	}
	return 0;
}

int favPressed(int p1x, int p1y, int p2x, int p2y) {
	if (ifTouched(p1x, p1y, p2x, p2y, 660, 740, 160, 240) == 1) { //back button pressed
		return 1;
	}
	return 0;
}

/****Welcome State****/
void Welcome() {
	while (1) {
		Point p1 = GetPress();
		Point p2 = GetRelease();

		if (ifTouched(p1.x, p1.y, p2.x, p2.y, 0, 800, 0, 480) == 1) { //going to home page
			push(&lastStates, currentState);
			currentState = HOME;
			break;
		}
	}
}

void Home() {
	while (1) {
		Point point1 = GetPress();
		Point point2 = GetRelease();
		if (ifTouched(point1.x, point1.y, point2.x, point2.y, 200, 600, 75,
				150) == 1) { //map button pressed
			push(&lastStates, currentState);
			currentState = STARTRUN;
			break;
		} else if (ifTouched(point1.x, point1.y, point2.x, point2.y, 200, 600,
				175, 250) == 1) { //search button pressed
			push(&lastStates, currentState);
			currentState = STATS;
			break;
		} else if (ifTouched(point1.x, point1.y, point2.x, point2.y, 200, 600,
				275, 350) == 1) { //favourites button pressed
			push(&lastStates, currentState);
			currentState = SYNC;
			break;
		} else if (ifTouched(point1.x, point1.y, point2.x, point2.y, 200, 600,
				375, 450) == 1) { //TODO button pressed
			push(&lastStates, currentState);
			currentState = PROFILE;
			break;
		} else if (backPressed(point1.x, point1.y, point2.x, point2.y)) {
			currentState = pop(&lastStates);
			break;
		}
	}
	return;
}

void StartRun() {
	//changeInterval();
	//eraseLog();
	//startLog();
	while (1) {
		Point p1 = GetPress();
		Point p2 = GetRelease();
		if (backPressed(p1.x, p1.y, p2.x, p2.y) == 1) { //back button pressed
			currentState = pop(&lastStates);
			break;
		}
		if (ifTouched(p1.x, p1.y, p2.x, p2.y, 200, 600, 250, 400) == 1) { //Tim Hortons pressed
					push(&lastStates, currentState);
					currentState = ENDRUN;
					break;
		}
	}
}

void EndRun() {
	stopLog();
	logcount = dumpLog();
	printCoords();
	calculateDistance();
	findTimes();
	//sendCoords();

	//push(&lastStates, currentState);
	currentState = HOME;

}


void Stats() {
	while (1) {
		Point p1 = GetPress();
		Point p2 = GetRelease();
		if (backPressed(p1.x, p1.y, p2.x, p2.y) == 1) { //back button pressed
			currentState = HOME;
			break;
		}
		if (homePressed(p1.x, p1.y, p2.x, p2.y)) {
			push(&lastStates, currentState);
			currentState = HOME;
			break;
		}
	}
}

void Profile(){

	while (1) {


		Point p1 = GetPress();
		Point p2 = GetRelease();
		if (backPressed(p1.x, p1.y, p2.x, p2.y) == 1) { //back button pressed
			currentState = pop(&lastStates);
			break;
		}
		if (homePressed(p1.x, p1.y, p2.x, p2.y)) {
			push(&lastStates, currentState);
			currentState = HOME;
			break;
		}
	}
}


void Sync(){
	sendCoords();
	currentState = HOME;
}

