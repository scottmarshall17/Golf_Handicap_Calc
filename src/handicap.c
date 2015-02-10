/**************************************************************************************************/

/*
 * File: handicap.c
 * Author: Scott Marshall
 * NetID: scottmarshall
 * Date: October 26, 2014
 * ECE 275
 * Description: This .c file contains the definitions of functions associated with the calculation of the golfer's handicap
 *
 */

/**************************************************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bool.h"
#include "score.h"
#include "fileio.h"
#include "handicap.h"

/*
** This function refreshes the scores that were counted in the previous revision.
** returns true if the functions completes successfully.
*/

bool flushCounted(ScoreList* list){
	Score* temp = NULL;

	temp = list->head;		//start at the head of the list
	while(temp != NULL){
		temp->counted = false;
		temp = temp->next;		//proceed to next item
	}

	return true;
}

/*
** findDifferentials() finds the ten lowest differentials in the list of the top 20
** most recent scores. returns true if the function completes successfully.
*/

bool findDifferentials(ScoreList* list){
	int count = 0;
	double min = 0;
	Score* temp = NULL;
	Score* minLoc = NULL;

	if(list == NULL || list->head == NULL){
		return false;
	}

	while(count < 10){		//find the ten lowest differentials
		temp = list->head;
		min = temp->hcpDifferential;	//start at the head of the list
		minLoc = temp;
		while(temp!= NULL && temp->counted == true){
			temp = temp->next;			//find first value not already counted
			min = temp->hcpDifferential;
			minLoc = temp;
		}
		while(temp != NULL){
			if(((temp->hcpDifferential) < min) && (temp->counted == false)){	//if a new minimum is found...
				min = temp->hcpDifferential;
				minLoc = temp;
			}
			temp = temp->next;
		}
		minLoc->counted = true;		//found one of the ten lowest differentials
		count++;
	}

	return true;
}

/*
** calcHCP() calculates the handicap index of the player based on the ten lowest
** differentials from the 20 most recent scores.
*/

double calcHCP(ScoreList* list){
	double index = 0;
	double sum = 0;
	Score* temp1 = NULL;

	temp1 = list->head;

	while(temp1 != NULL){
		if(temp1->counted == true){
			sum += temp1->hcpDifferential;		//sum the ten lowest differentials
		}
		temp1 = temp1->next;
	}

	index = sum/10;				//perform necessary calculations, average, multiply by constant, truncate
	index = index * 0.96;
	index = (double)(((int)(index*10)))/10;

	return index;
}

/*
** printCard() prints the finalized version of the handicap card that displays 
** pertinant information about the golfer.
*/

bool printCard(Info* stats, ScoreList* list, double hcpIndex, int numScores, char* fileName){
	Score* temp1 = NULL;
	int i = 0;
	int j = 0;
	FILE* outFile = NULL;

	outFile = fopen(fileName, "w");			//open file to write to

	if(outFile == NULL){
		printf("The output file could not be created!\n");
		return false;
	}

	if(hcpIndex > 36.4){		//maximum handicap value
		hcpIndex = 36.4;
	}
	else if(hcpIndex < -36.4){	//minimum handicap value
		hcpIndex = -36.4;
	}

	fprintf(outFile, "Name: %s\n", stats->name );		//print out formatted data to file
	fprintf(outFile, "Club: %s\n", stats->club);
	fprintf(outFile, "Club #: %-14s GHIN #: %s\n", stats->assignment, stats->id);
	if(hcpIndex >= 0){
		fprintf(outFile, "Scores Posted: %-7d USGA HCP Index: %.1lf\n", numScores, hcpIndex);
	}
	else{
		hcpIndex = hcpIndex * (-1);
		fprintf(outFile, "Scores Posted: %-7d USGA HCP Index: +%.1lf\n", numScores, hcpIndex);
	}
	fprintf(outFile, "Effective Date: %02d/%02d/%d\n", stats->month, stats->day, stats->year);
	fprintf(outFile, "       Score history: Most recent first *If Used\n");

	temp1 = list->head;

	while(i < 4){			//print the scores that were used in the calculation
		j = 0;
		while(j < 5){
			if(temp1->counted == true){
				fprintf(outFile, "%d*%c       ",temp1->adjGrossScore, temp1->scoreType[0]);
			}
			else{
				fprintf(outFile, "%d %c       ",temp1->adjGrossScore, temp1->scoreType[0]);
			}
			temp1 = temp1->next;
			j++;
		}
		fprintf(outFile, "\n");
		i++;
	}
	fclose(outFile);		//close the output file
	return true;
}

/*
** golferInit() initializes golfer with the information of "Scott Marshall"
*/

void golferInit(Info* golfer){
	golfer->day = 26;
	golfer->month = 10;			//initialize golfer data for printing
	golfer->year = 2014;
	strcpy(golfer->club, "ECE 275");
	strcpy(golfer->assignment, "Assignment X");
	strcpy(golfer->id, "scottmarshall");
	strcpy(golfer->name, "Scott Marshall");

	return;
}