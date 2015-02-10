/**************************************************************************************************/

/*
 * File: main.c
 * Author: Scott Marshall
 * NetID: scottmarshall
 * Date: October 26, 2014
 * ECE 275
 * Description:	This program takes golf score data from two separate text files and calculates a 
 *				golfer's handicap based on the 10 lowest recorded score differentials.
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



int main(int argc, char* argv[]){
	ScoreList* revisionScores = NULL;
	ScoreList* recentScores = NULL;
	ScoreList* fullList = NULL;
	ScoreList* topTwenty = NULL;
	Info golfer;
	double hcpIndex = 0;

	if(argc != 4){		//Check to see if the correct number of command line arguments is available.
		printf("Usage: ./handicapper <revisionFile> <recentFile> <outFile>\n");
		return -1;
	}

	revisionScores = (ScoreList*)malloc(sizeof(ScoreList));			//initialize the lists of the scores lists to hold scores
	recentScores = (ScoreList*)malloc(sizeof(ScoreList));

	if(revisionScores == NULL || recentScores == NULL){				//safety check if memory allocated correctly
		printf("Unable to allocate memory for lists in main.c\n");
		return -1;
	}
	ScoreListInit(revisionScores);		//initialize the scores lists with proper numbers.
	ScoreListInit(recentScores);

	if(readRevisionFile(revisionScores, argv[1])){		//read in data from first file. returns true if no issues.
		if(readRecentFile(recentScores, argv[2])){

			fullList = ScoreListCat(revisionScores, recentScores);		//create the combined list for sorting
			if(fullList == NULL || fullList->size < 20){	//if the list contains less than 20 items, return -1
				printf("You don't have enough score data to calculate a handicap!\n");
				return -1;
			}

			if(insertionSort(fullList)){	//sort the list with the most recent scores first
				topTwenty = mostRecent(fullList);				//create a list that holds the top 20 most recent scores.
				flushCounted(topTwenty);			//initialize all items as uncounted
				findDifferentials(topTwenty);		//find the lowest differentials

				hcpIndex = calcHCP(topTwenty);		//calculate the HCP index based on the lowest 10 differentials

				golferInit(&golfer);			//initialize the golfer to be printed "Scott Marshall" in this case

				printCard(&golfer, topTwenty, hcpIndex, fullList->size, argv[3]);	//prints the card to the specified output file

				ScoreListDestroy(recentScores);			//free all of the memory that was allocated for the program
				ScoreListDestroy(revisionScores);
				ScoreListDestroy(fullList);
				ScoreListDestroy(topTwenty);
			}
			else{
				printf("There was an error reading the file\n");		//throw error
				return -1;
			}
		}
		else{
			printf("There was an error reading the file\n");		//throw error
			return -1;
		}
	}
	else{
		printf("There was an error reading the file\n");		//throw error
		return -1;
	}

	return 0;
}