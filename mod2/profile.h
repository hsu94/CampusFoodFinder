/*
 * profile.h
 *
 *  Created on: Mar 31, 2016
 *      Author: Kevin
 */

#ifndef PROFILE_H_
#define PROFILE_H_

#define XRES 800
#define YRES 480

typedef struct
{
	char *name;
	int gender;
	int age;
	float weight;		//weight in KG
	float height;		//height in METER
	float bmi;
	char goal[50];
	float dis;
	int rank;
	int score;

} profile;

// initialize the profile
void profile_init(profile *p);
// set the name of the user
void set_name(profile *p, char *name);
// set the gender of the zero (0 is female and 1 is male)
void set_gender(profile *p, int gender);
// set the age of the user
void set_age(profile *p, int age);
// set the weight of the user
void set_weight(profile *p, float weight);
// set the height of the user
void set_height(profile *p, float height);
// calculate the bmi of the user
float calc_bmi(profile *p);
// set user's "goal"
void set_goal(profile *p, char goal[]);
// update user's distance ran
void set_dis(profile *p, float dis);
// update user's score
void update_score(profile *p);
// set user's rank
void set_rank(profile *p);

#endif /* PROFILE_H_ */
