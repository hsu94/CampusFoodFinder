/*
 * profile.c
 *
 *  Created on: Mar 31, 2016
 *      Author: Kevin
 */


#include "profile.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void profile_init(profile *p){
	strcpy(p->name, "");
	p->gender = 0;
	p->age = 0;
	p->weight = 0;
	p->height = 0;
	p->bmi = 0;
	strcpy(p->goal, "");
	p->dis = 0;
	p->score = 0;
	p->rank = 0;
}

void set_name(profile *p, char *name){
	if (p == NULL)
		return;
	strcpy(p->name, name);
}

void set_gender(profile *p, int gender){
	if (p == NULL)
		return;
	p->gender = gender;
}

void set_age(profile *p, int age){
	if (p == NULL)
		return;
	p->age = age;
}

void set_weight(profile *p, float weight){
	if (p == NULL)
		return;
	p->weight = weight;
}

void set_height(profile *p, float height){
	if (p == NULL)
		return;
	p->height = height;
}

float calc_bmi(profile *p){

	p->bmi = p->weight / (p->height * p->height);
	return p->bmi;
}

void set_goal(profile *p, char goal[]){
	if (p == NULL)
		return;
	strcpy(p->goal, goal);
}

void set_dis(profile *p, float dis){
	if (p == NULL)
		return;
	p->dis = dis;
}

void update_score(profile *p){
	if (p == NULL)
		return;
	if (p->dis >= 0 && p->dis < 2){
		p->score = 20;
	}
	else if (p->dis >= 2 && p->dis < 4){
		p->score = 40;
	}
	else if (p->dis >= 4 && p->dis < 6){
		p->score = 60;
	}
	else if (p->dis >= 6 && p->dis < 8){
		p->score = 80;
	}
	else if (p->dis >= 8 && p->dis < 10){
		p->score = 100;
	}
	else if (p->dis >= 10 && p->dis < 12){
		p->score = 120;
	}
}

void set_rank(profile *p){
	if (p == NULL)
		return;
	if (p->score >= 0 && p->score <= 20){
		p->rank = 0;
	}
	else if (p->score > 20 && p->score <= 40){
		p->rank = 1;
	}
	else if (p->score > 40 && p->score <= 60){
		p->rank = 2;
	}
	else if (p->score > 60 && p->score <= 80){
		p->rank = 3;
	}
	else if (p->score > 80 && p->score <= 100){
		p->rank = 4;
	}
	else if (p->score > 100 && p->score <= 120){
		p->rank = 5;
	}

}
