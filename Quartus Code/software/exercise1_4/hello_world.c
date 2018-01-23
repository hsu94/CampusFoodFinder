#include<stdio.h>
#include<stdbool.h>
#include <string.h>

#define touchscreen_Control (*(volatile unsigned char *)(0x84000230))
#define touchscreen_Status (*(volatile unsigned char *)(0x84000230))
#define touchscreen_TxData (*(volatile unsigned char *)(0x84000232))
#define touchscreen_RxData (*(volatile unsigned char *)(0x84000232))
#define touchscreen_Baud (*(volatile unsigned char *)(0x84000234))


void wait_1s(void){
	int i;
	for( i = 0; i < 1000000; i++);
}

void Init_Touch(void)
{
	touchscreen_Baud = 0x05; // program for 115k baud
	touchscreen_Control = 0x15;

	char cmd[3];
	cmd[0] = 0x55;
	cmd[1] = 0x01;
	cmd[2] = 0x12;

	while(touchscreen_Status & 0x02 != 0x02){
	}
	touchscreen_TxData = cmd[0]; //0x68

	while(touchscreen_Status & 0x02 != 0x02){
	}
	touchscreen_TxData = cmd[1];

	while(touchscreen_Status & 0x02 != 0x02){
	}
	touchscreen_TxData = cmd[2];

	putchartouch(0x51);
	putchartouch(0x41);
}


int ScreenTouched( void )
{
	return((touchscreen_Status & 0x1) == 0x1);
}

void WaitForTouch()
{
while(!ScreenTouched()){
	printf("waiting for screen\n");
	wait_1s();
}
}

typedef struct { int x, y; } Point ;

Point GetPress(void)
{
 Point p1;
 int x1, x2, y1, y2;
 int x,y;
 double xf,yf;

 int coord;
 coord = getchartouch();
 if(coord == 0x81){
	 printf("pen down\n");
	 while (getchartouch() != 0x80);{
		 x1 = getchartouch() & 0x7f;
		 x2 = getchartouch() & 0x1f;
		 y1 = getchartouch() & 0x7f;
		 y2 = getchartouch() & 0x1f;

	 }
	// printf("%d %d %d %d\n", x1,x2, x1, y2);
	 x = x1 | (x2 << 7);
	 y = y1 | (y2 << 7);
	 //x = x;;
	 //y = y;
	 xf = (x-108)/(4.89875);
	 yf = (y-260)/(7.84167);
	 if(xf < 0){
		 xf =0;
	 }
	 if(xf > 800){
		 xf = 800;
	 }
	 if(yf < 0){
		 yf =0;
	 }
	 if(yf > 480){
		 yf = 480;
	 }
	 printf("%lf %lf\n", xf,yf);
	 p1.x = xf;
	 p1.y = yf;
 }

 return p1;
}

Point GetRelease(void)
{
	Point p1;
	int x1, x2, y1, y2;
	 int x,y;
	 double xf,yf;

	 int coord;
	 coord = getchartouch();
	 if(coord == 0x80){
		 printf("pen up\n");
		 //while (getchartouch() != 0x80);{
			 x1 = getchartouch() & 0x7f;
			 x2 = getchartouch() & 0x1f;
			 y1 = getchartouch() & 0x7f;
			 y2 = getchartouch() & 0x1f;

		 //}
		// printf("%d %d %d %d\n", x1,x2, x1, y2);
		 x = x1 | (x2 << 7);
		 y = y1 | (y2 << 7);
		 xf = (x-108)/(4.89875);
		 yf = (y-260)/(7.84167);
		 if(xf < 0){
			 xf =0;
		 }
		 if(xf > 800){
			 xf = 800;
		 }
		 if(yf < 0){
			 yf =0;
		 }
		 if(yf > 480){
			 yf = 480;
		 }
		 //x = x;;
		 //y = y;
		 printf("%lf %lf\n", xf,yf);
		 p1.x = xf;
		 p1.y = yf;
	 }

}

int TestForReceivedData(void){
	if(getchartouch() == 0x81){
		printf("pen down\n");
	}
	if(getchartouch() == 0x80){
		printf("pen up\n");
	}

}

int putchartouch(int c){

	while(touchscreen_Status & 0x02 != 0x02){
	}

	touchscreen_TxData = c;
	return c ;
}

int getchartouch(void){

	while(!((touchscreen_Status & 0x1) == 0x1)){
	}

	return touchscreen_RxData;
}


int main(){

	Point coord1;
	Point coord2;
	Init_Touch();
	printf("init test\n\n\n\n");

	while(1){
		//WaitForTouch();
		GetPress();
		GetRelease();
		//TestForReceivedData();
		//ScreenTouched();
		//wait_1s();
	}

}


