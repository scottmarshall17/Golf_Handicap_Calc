/**************************************************************************************************/

/*
 * File: fileio.c
 * Author: Scott Marshall
 * NetID: scottmarshall
 * Date: October 26, 2014
 * ECE 275
 * Description: This .c file includes the definitions of functions used to read score data from the specified input files.
 *
 */

/**************************************************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bool.h"
#include "score.h"
#include "fileio.h"

/*
** readRevisionFile() reads data from the revisionScores input file
** and places the data in a specified doubly linked list.
*/

bool readRevisionFile(ScoreList* list, char* filename ){
	Score* temp = NULL;
	Score* lastNode = NULL;
	char buffer[300] = "";
	char firstChar = ' ';
	bool counted = false;
	char scoreType[3] = "";
	unsigned short month = 0;
	unsigned int year = 0;
	unsigned short adjGrossScore = 0;
	double courseRating = 0.00;
	unsigned short slopeRating = 0;
	double hcpDifferential = 0.00;
	FILE* inFile = NULL;

	inFile = fopen(filename, "r");		//open file for reading

	if(NULL == inFile){				//check for any possible errors in the file or the list
		printf("The file %s could not be found\n", filename);
		return false;
	}
	if(NULL == list){
		printf("The list doesn't exist!\n");
		return false;
	}


	while(!feof(inFile)){
		strcpy(buffer, "");			//flush the buffer
		fgets(buffer, 295, inFile);		//get a line up until a newline character and store it in the buffer
		if((strcmp(buffer, "") != 0) && (strcmp(buffer, "\n") != 0) && (strlen(buffer) > 14)){	//check for valid input
			sscanf(buffer, "%c\t%s\t%hu/%u\t%hu\t%lf/%hu\t%lf", &firstChar, scoreType, &month, &year, &adjGrossScore, &courseRating, &slopeRating, &hcpDifferential);

			if(firstChar == '*'){	//test to see if the data was counted initially
				counted = true;
			}
			else{
				counted = false;
			}

			if(year >= 15){			//no year before 2000 can be valid
				continue;
			}

			temp = ScoreCreate(counted, scoreType, month, year, adjGrossScore, courseRating, slopeRating, hcpDifferential, 1);	//create a score
			
			if(list->head == NULL){		//insert at the head of the list
				ScoreListInsertAfter(list, NULL, temp);
			}
			else{
				ScoreListInsertAfter(list, lastNode, temp);		//insert after the last most recent data
			}
			lastNode = temp;
		}
	}
	fclose(inFile);			//close the input file
	return true;
}

/*
** readRecentFile() reads data from the newScores input file
** and places the data in a specified doubly linked list.
*/

bool readRecentFile(ScoreList* list, char* filename){
	Score* temp = NULL;
	Score* lastNode = NULL;
	char buffer[300] = "";
	char scoreType[3] = "";
	unsigned short month = 0;
	unsigned int year = 0;
	unsigned short adjGrossScore = 0;
	double courseRating = 0.00;
	unsigned short slopeRating = 0;
	double hcpDifferential = 0.00;
	FILE* inFile = NULL;

	inFile = fopen(filename, "r");	//open the input file for reading

	if(NULL == inFile){			//check for errors in the file or the list
		printf("The file %s could not be found\n", filename);
		return false;
	}
	if(NULL == list){
		printf("The list doesn't exist!\n");
		return false;
	}


	
	while(!feof(inFile)){
		strcpy(buffer, "");			//flush the buffer with an empty string
		fgets(buffer, 295, inFile);		//store a line from the file into the buffer
		if((strcmp(buffer, "") != 0) && (strcmp(buffer, "\n") != 0) && (strlen(buffer) > 14)){
			sscanf(buffer, "%s\t%hu/%u\t%hu\t%lf/%hu\t%lf", scoreType, &month, &year, &adjGrossScore, &courseRating, &slopeRating, &hcpDifferential);
			if(year >= 15){		//anything before the year 2000 is invalid
				continue;
			}

			temp = ScoreCreate(false, scoreType, month, year, adjGrossScore, courseRating, slopeRating, hcpDifferential, 2);	//create a node in the list 
			
			//place the score into the list in order of most recent
			if(list->head == NULL){
				ScoreListInsertAfter(list, NULL, temp);
			}
			else{
				ScoreListInsertAfter(list, lastNode, temp);
			}
			lastNode = temp;
		}
	}
	fclose(inFile);			//close the input file
	return true;
}