/**************************************************************************************************/

/*
 * File: handicap.h
 * Author: Scott Marshall
 * NetID: scottmarshall
 * Date: October 26, 2014
 * ECE 275
 * Description: This .c file contains the declarations of functions and struct associated with the calculation of the golfer's handicap
 *
 */

/**************************************************************************************************/


#ifndef HANDICAP_H
#define HANDICAP_H

typedef struct Info_struct {
	int day;
	int month;
	int year;
	char name[30];
	char id[30];
	char assignment[30];
	char club[30];
	int numScores;
	double hcpIndex;
} Info;

/*
** This function refreshes the scores that were counted in the previous revision.
** returns true if the functions completes successfully.
*/

bool flushCounted(ScoreList* list);

/*
** findDifferentials() finds the ten lowest differentials in the list of the top 20
** most recent scores. returns true if the function completes successfully.
*/

bool findDifferentials(ScoreList* list);

/*
** calcHCP() calculates the handicap index of the player based on the ten lowest
** differentials from the 20 most recent scores.
*/

double calcHCP(ScoreList* list);

/*
** printCard() prints the finalized version of the handicap card that displays 
** pertinant information about the golfer.
*/

bool printCard(Info* stats, ScoreList* list, double hcpIndex, int numScores, char* fileName);

/*
** golferInit() initializes golfer with the information of "Scott Marshall"
*/

void golferInit(Info* golfer);
	
#endif