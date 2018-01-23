/*
 * distance.c
 *
 *  Created on: 2016-02-24
 *      Author: steven
 */

#include "distance.h"
extern double RESDIS;

double dist2res(int RES){
	char * resloc;
	char localRL[50];
	char localCL[50];

	//char localrn [50];

	OpenSD();
	printf("open done\n");
	init_GPS();
	printf("GPS initialized\n");
	//strncpy(localrn, resname,6);
	//localrn[6] = '\0';

	if(RES == 1){
		resloc = ReadFromSD("RESLOC.txt","FORTIM");
	}else if(RES == 2){
		resloc = ReadFromSD("RESLOC.txt","KASTAR");
	}else if(RES == 3){
		resloc = ReadFromSD("RESLOC.txt","AGOCAF");
	}else if(RES == 4){
		resloc = ReadFromSD("RESLOC.txt","REBCAF");
	}
	printf("%s\n",resloc);

	strncpy(localRL, resloc,20);
	localRL[20] = '\0';
	printf("%s\n",localRL);

	char *curloc = getGPSData(GPSCOORD);
	strncpy(localCL, curloc, 20);
	localCL[20] = '\0';
	printf("%s\n",localCL);


	double distance = (double) getDistance(localCL,localRL);
	printf("the distance is %f\n");
	RESDIS = distance;
	printf("RESDIS IS %f\n",RESDIS);
	return distance;

}
