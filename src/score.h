/**************************************************************************************************/

/*
 * File: score.h
 * Author: Scott Marshall
 * NetID: scottmarshall
 * Date: October 26, 2014
 * ECE 275
 * Description: This .c file includes the declarations of the functions necessary for the 
 *				doubly linked list data structure. This also includes functions for sorting the list.
 *
 */

/**************************************************************************************************/


#ifndef SCORE_H
#define SCORE_H

typedef struct Score_struct {
	bool counted;
	char scoreType[3];
	unsigned short month;
	unsigned int year;
	unsigned short adjGrossScore;
	double courseRating;
	unsigned short slopeRating;
	double hcpDifferential;
	int filenum;
	struct Score_struct *next;
	struct Score_struct *prev;
} Score;

typedef struct ScoreList_struct{
	int size;
	struct Score_struct *head;
	struct Score_struct *tail;
} ScoreList;

/*
** ScoreListInit() initializes the list of scores with size zero 
** and no initial data.
*/

void ScoreListInit(ScoreList* list);

/*
** ScoreListDestroy() destroys a list by freeing the memory that it 
** originally allocated. !WARNING! list must be stored on the heap 
** for this function to work properly.
*/

void ScoreListDestroy(ScoreList* list);

/*
** ScoreListInsertAfter() inserts a new node after the specified node in 
** a list. If the new node is placed after NULL, the new node will be placed
** at the head of the list.
*/

bool ScoreListInsertAfter(ScoreList* list, Score* currNode, Score* newNode);

/*
** ScoreListInsertBefore() inserts a new node before the specified node in 
** a list. If the new node is placed before NULL, the new node will be placed
** at the head of the list.
*/

bool ScoreListInsertBefore(ScoreList* list, Score* currNode, Score* newNode);

/*
** ScoreListRemove() removes an item from the doubly linked list.
** If the node is NULL, the function will return false.
*/

bool ScoreListRemove(ScoreList* list, Score* currNode);

/*
** ScoreCreate() creates a score node that contains information
** pertaining to the golfer's score. This includes variables such as
** the score type, the date, the score, the differential, and the 
** course difficulty among other things.
*/

Score* ScoreCreate(bool counted, char* scoreType, unsigned short month,
				   unsigned int year, unsigned short adjGrossScore, double courseRating,
				   unsigned short slopeRating, double hcpDifferential, int filenum);

/*
** DuplicateList() copies a list to a new list essentially separating 
** the same data into two identical lists.
*/

bool DuplicateList(ScoreList* duplicateList, ScoreList* firstList);

/*
** ScoreListCat() concatenates a list at the end of another list. This function
** returns a pointer to the combined lists. Data is not duplicated.
*/

ScoreList* ScoreListCat(ScoreList* firstList, ScoreList* lastList);

/*
** swapNode() swaps the data within two specified nodes. 
*/

void swapNode(Score* node1, Score* node2);

/*
** ScoreListPartitionRecent() separates the list into two parts for the quicksort function.
** The most recent items are placed at the beginning of the list.
*/

Score* ScoreListPartitionRecent(Score* start, Score* end);

/*
** quicksortRecent() quickly sorts the list by date. The most
** recent scores are placed at the head of the list.
*/

void quicksortRecent(Score* head, Score* tail);

/*
** This function creates a list of the top twenty most
** recent scores found in the input files.
*/

ScoreList* mostRecent(ScoreList* list);

/*
** insertionSort() sorts the list by most recent, while taking into
** account the order of which the data was read in. Data from 
** argv[2] get priority of data from argv[1].
*/

bool insertionSort(ScoreList* list);

#endif