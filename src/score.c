/**************************************************************************************************/

/*
 * File: score.c
 * Author: Scott Marshall
 * NetID: scottmarshall
 * Date: October 26, 2014
 * ECE 275
 * Description: This .c file includes the definitions of the functions necessary for the 
 *				doubly linked list data structure. This also includes functions for sorting the list.
 *
 */

/**************************************************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bool.h"
#include "score.h"

/*
** ScoreListInit() initializes the list of scores with size zero 
** and no initial data.
*/

void ScoreListInit(ScoreList* list){
	ScoreList* tempNode = NULL;


	if(list == NULL){
		printf("Unable to allocate memory for DList\n");
		return;
	}

	tempNode = list;

	tempNode->size = 0;		//initialize the list items
	tempNode->head = NULL;
	tempNode->tail = NULL;

	return;
}

/*
** ScoreListDestroy() destroys a list by freeing the memory that it 
** originally allocated. !WARNING! list must be stored on the heap 
** for this function to work properly.
*/

void ScoreListDestroy(ScoreList* list){
	Score* target = NULL;
	Score* temp = NULL;

	target = list->head;

	while(target != NULL){		//free the individual nodes in the list
		temp = target->next;
		free(target);
		target = temp;
	}

	free(list);

	return;
}

/*
** ScoreListInsertAfter() inserts a new node after the specified node in 
** a list. If the new node is placed after NULL, the new node will be placed
** at the head of the list.
*/

bool ScoreListInsertAfter(ScoreList* list, Score* currNode, Score* newNode){
	Score* temp = NULL;

	if((currNode == NULL) && (list->head == NULL)){		//if the list is empty
		list->head = newNode;
		list->tail = newNode;
		newNode->next = NULL;
		newNode->prev = NULL;
	}
	else if(currNode == NULL){			//insert the newNode at the head of the list
		temp = list->head;
		newNode->next = temp;
		newNode->prev = NULL;
		list->head = newNode;
	}
	else if(list->size == 1){		//one item in the list
		newNode->next = NULL;
		newNode->prev = list->head;
		list->head->next = newNode;
		list->tail = newNode;
	}
	else{
		temp = currNode->next;
		if(temp != NULL){				//insert after any node that's not the tail.
			newNode->next = temp;
			newNode->prev = currNode;
			currNode->next = newNode;
			temp->prev = newNode;
		}
		else{							//insert after the tail and modify the tail of the list
			newNode->next = temp;
			newNode->prev = currNode;
			currNode->next = newNode;
			list->tail = newNode;
		}
	}
	list->size += 1;	//increase the size of the list
	return true;
}

/*
** ScoreListInsertBefore() inserts a new node before the specified node in 
** a list. If the new node is placed before NULL, the new node will be placed
** at the head of the list.
*/

bool ScoreListInsertBefore(ScoreList* list, Score* currNode, Score* newNode){
	Score* temp = NULL;

	if((currNode == NULL) && (list->head == NULL)){ //insert the first item in the list
		list->head = newNode;
		list->tail = newNode;
		newNode->next = NULL;
		newNode->prev = NULL;
	}
	else if(currNode == NULL){			//insert the newNode at the head of the list
		temp = list->head;
		newNode->next = temp;
		newNode->prev = NULL;
		temp->prev = newNode;
		list->head = newNode;
	}
	else{
		temp = currNode->prev;
		if(temp != NULL){				//insert node before any other node that isn't the head
			newNode->next = currNode;
			newNode->prev = temp;
			temp->next = newNode;
			currNode->prev = newNode;
		}
		else{							//insert at the head and modify the head
			newNode->next = currNode;
			newNode->prev = temp;
			currNode->prev = newNode;
			list->head = newNode;
		}
	}
	list->size += 1;		//increase the size of the list
	return true;
}

/*
** ScoreListRemove() removes an item from the doubly linked list.
** If the node is NULL, the function will return false.
*/

bool ScoreListRemove(ScoreList* list, Score* currNode){
	Score* temp1 = NULL;
	Score* temp2 = NULL;

	if(currNode == NULL){
		return false;
	}
	else{
		if((currNode->next == NULL) && (currNode->prev == NULL)){			//if the list only has one item: item is both head and tail
			list->head = NULL;
			list->tail = NULL;
			free(currNode);
		}
		if(currNode->next == NULL){			//remove the tail of the list
			temp1 = currNode->prev;
			temp1->next = NULL;
			free(currNode);
			list->tail = temp1;
		}
		else if(currNode->prev == NULL){	//remove the head of the list
			temp1 = currNode->next;
			temp1->prev = NULL;
			list->head = temp1;
			free(currNode);
		}
		else{								//remove any item within the list
			temp1 = currNode->prev;
			temp2 = currNode->next;
			temp1->next = temp2;
			temp2->prev = temp1;
			free(currNode);
		}
	}
	list->size -= 1;		//decrease the size of the list.
	return true;
}

/*
** ScoreCreate() creates a score node that contains information
** pertaining to the golfer's score. This includes variables such as
** the score type, the date, the score, the differential, and the 
** course difficulty among other things.
*/

Score* ScoreCreate(bool counted, char* scoreType, unsigned short month,
				   unsigned int year, unsigned short adjGrossScore, double courseRating,
				   unsigned short slopeRating, double hcpDifferential, int filenum){

					   Score* node = NULL;

					   node = (Score*)malloc(sizeof(Score));			//allocate the memory to create a DListNode

					   if(node == NULL){							//check to see if the memory has been allocated
						   printf("New node failed to initialize");
						   return NULL;
					   }

					   node->counted = counted;
					   strcpy(node->scoreType, scoreType);
					   //printf("%s\n", scoreType); //debugging purposes
					   node->month = month;
					   node->year = year;
					   node->adjGrossScore = adjGrossScore;
					   node->courseRating = courseRating;
					   node->slopeRating = slopeRating;
					   node->hcpDifferential = hcpDifferential;
					   node->filenum = filenum;
					   node->next = NULL;
					   node->prev = NULL;


					   return node;
}

/*
** DuplicateList() copies a list to a new list essentially separating 
** the same data into two identical lists.
*/

bool DuplicateList(ScoreList* duplicateList, ScoreList* firstList){
	Score* temp1 = NULL;
	Score* temp2 = NULL;
	Score* temp2tail = NULL;

	if(firstList == NULL){
		printf("The list you tried to duplicate doesn't exist\n");
		return false;
	}
	if(duplicateList == NULL){
		printf("You need to allocate the list to allow duplication\n");
		return false;
	}

	temp1 = firstList->head;

	while(temp1 != NULL){		//iterate through the list
		temp2 = (Score*)malloc(sizeof(Score));

		if(temp2 == NULL){
			printf("Failed to allocate memory to duplicate list\n");
			return false;
		}
		temp2->adjGrossScore = temp1->adjGrossScore;
		temp2->counted = temp1->counted;
		temp2->courseRating = temp1->courseRating;
		temp2->hcpDifferential = temp1->hcpDifferential;	//duplicate the data in the node
		temp2->month = temp1->month;
		strcpy(temp2->scoreType, temp1->scoreType);
		temp2->slopeRating = temp1->slopeRating;
		temp2->year = temp1->year;
		temp2->filenum = temp1->filenum;

		if(duplicateList->head == NULL){
			ScoreListInsertAfter(duplicateList, NULL, temp2);
		}
		else{
			ScoreListInsertAfter(duplicateList, temp2tail, temp2);
		}
		temp2tail = temp2;
		temp1 = temp1->next;

	}

	return true;
}

/*
** ScoreListCat() concatenates a list at the end of another list. This function
** returns a pointer to the combined lists. Data is not duplicated.
*/

ScoreList* ScoreListCat(ScoreList* firstList, ScoreList* lastList){
	ScoreList* newList = NULL;
	ScoreList* firstTemp = NULL;
	ScoreList* lastTemp = NULL;

	if(firstList == NULL && lastList == NULL){
		return NULL;
	}

	if(firstList == NULL || firstList->head == NULL){
		newList = (ScoreList*)malloc(sizeof(ScoreList));
		if(newList == NULL){
			printf("Unable to allocate memory for the list\n");
			return NULL;
		}
		ScoreListInit(newList);			//initialize the list and duplicate the first part
		DuplicateList(newList, lastList);	
		return newList;
	}
	if(lastList == NULL || lastList->head == NULL){
		newList = (ScoreList*)malloc(sizeof(ScoreList));
		if(newList == NULL){
			printf("Unable to allocate memory for the list\n");
			return NULL;
		}
		ScoreListInit(newList);			//initialize the list and duplicate the first part
		DuplicateList(newList, firstList);
		return newList;
	}

	newList = (ScoreList*)malloc(sizeof(ScoreList));
	firstTemp = (ScoreList*)malloc(sizeof(ScoreList));		//allocate memory for the new list
	lastTemp = (ScoreList*)malloc(sizeof(ScoreList));

	if(newList == NULL || firstTemp == NULL || lastTemp == NULL){
		printf("Failed to concatenate lists due to lack of memory\n");
		return NULL;
	}
	ScoreListInit(newList);
	ScoreListInit(firstTemp);		//initialize the lists
	ScoreListInit(lastTemp);
	DuplicateList(firstTemp, firstList);
	DuplicateList(lastTemp, lastList);

	newList->head = firstTemp->head;		//move pointers for head and tail
	newList->tail = lastTemp->tail;
	newList->size = (firstTemp->size) + (lastTemp->size);		//modify final list size

	firstTemp->tail->next = lastTemp->head;
	lastTemp->head->prev = firstTemp->tail;

	free(firstTemp);		//free the temporary list pointers
	free(lastTemp);

	return newList;
}

/*
** swapNode() swaps the data within two specified nodes. 
*/

void swapNode(Score* node1, Score* node2){
	bool countedTemp;
	char scoreTypeTemp[3];
	unsigned short monthTemp;
	unsigned int yearTemp;
	unsigned short adjGrossScoreTemp;
	double courseRatingTemp;
	unsigned short slopeRatingTemp;
	double hcpDifferentialTemp;
	int filenumTemp;

	//store the values in node 1 into temporary values
	countedTemp = node1->counted;
	strcpy(scoreTypeTemp, node1->scoreType);
	monthTemp = node1->month;
	yearTemp = node1->year;
	adjGrossScoreTemp = node1->adjGrossScore;
	courseRatingTemp = node1->courseRating;
	slopeRatingTemp = node1->slopeRating;
	hcpDifferentialTemp = node1->hcpDifferential;
	filenumTemp = node1->filenum;

	//store the values from node 2 into node 1
	node1->counted = node2->counted;
	strcpy(node1->scoreType, node2->scoreType);
	node1->month = node2->month;
	node1->year = node2->year;
	node1->adjGrossScore = node2->adjGrossScore;
	node1->courseRating = node2->courseRating;
	node1->slopeRating = node2->slopeRating;
	node1->hcpDifferential = node2->hcpDifferential;
	node1->filenum = node2->filenum;


	//store the data originally in node 1 into node 2
	node2->counted = countedTemp;
	strcpy(node2->scoreType, scoreTypeTemp);
	node2->month = monthTemp;
	node2->year = yearTemp;
	node2->adjGrossScore = adjGrossScoreTemp;
	node2->courseRating = courseRatingTemp;
	node2->slopeRating = slopeRatingTemp;
	node2->hcpDifferential = hcpDifferentialTemp;
	node2->filenum = filenumTemp;

	return;
}

/*
** ScoreListPartitionRecent() separates the list into two parts for the quicksort function.
** The most recent items are placed at the beginning of the list.
*/

Score* ScoreListPartitionRecent(Score* start, Score* end){
	Score* wall = NULL;
	Score* pivot = NULL;
	Score* currNode = NULL;
	int month = 0;
	int year = 0;
	//long x = (end->endCount) - (end->startCount);	//value to be compared

	wall = start;		//quicksort "wall"
	pivot = end;		//pivot point is the end node
	currNode = start;	//current node to be compared to pivot node

	if(start == end){	//if pivot is itself
		return start;
	}

	while((currNode != end) && (currNode != NULL)){			//iterate through the list
		month = currNode->month;
		year = currNode->year;
		if(year > end->year){		//place more trendy items at the front
			swapNode(currNode, wall);	//swap node with the node next to the wall
			wall = wall->next;			//move "wall" over one step to include new value
		}
		else if(year == end->year){
			if(end->month <= month){
				swapNode(currNode, wall);	//swap node with the node next to the wall
				wall = wall->next;			//move "wall" over one step to include new value
			}
		}
		currNode = currNode->next;		//iterate
	}
	swapNode(wall, pivot);		//finally, swap the pivot with the wall so that the pivot node is in the right location
	return wall;
}

/*
** quicksortRecent() quickly sorts the list by date. The most
** recent scores are placed at the head of the list.
*/

void quicksortRecent(Score* head, Score* tail){
	Score* tempNode = NULL;
	if((head != tail) && (tail != NULL) && (head != NULL) && (head->prev != tail)){
		tempNode = ScoreListPartitionRecent(head, tail);		//partition the list into two halves
		if(tempNode->prev != NULL){
			quicksortRecent(head, tempNode->prev);		//quicksort the first half
		}
		if(tempNode->next != NULL){
			quicksortRecent(tempNode->next, tail);		//quicksort the second half
		}
	}
	return;
}

/*
** This function creates a list of the top twenty most
** recent scores found in the input files.
*/

ScoreList* mostRecent(ScoreList* list){
	ScoreList* newList = NULL;
	Score* temp1 = NULL;
	Score* temp2 = NULL;
	Score* previous = NULL;
	int i = 0;

	newList = (ScoreList*)malloc(sizeof(ScoreList));		//allocate memory for a new list

	if(newList == NULL){
		printf("The most recent list could not be created\n");
		return NULL;
	}

	ScoreListInit(newList);			//initialize the list


	temp1 = list->head;

	for(i = 0; i < 20; i++){
		if(0 == i){
			temp2 = (Score*)malloc(sizeof(Score));		//allocate a node for new data
			if(temp2 == NULL){
				return NULL;
			}
			temp2->filenum = temp1->filenum;
			temp2->adjGrossScore = temp1->adjGrossScore;
			temp2->counted = temp1->counted;
			temp2->courseRating = temp1->courseRating;
			temp2->hcpDifferential = temp1->hcpDifferential;
			temp2->month = temp1->month;
			strcpy(temp2->scoreType, temp1->scoreType);
			temp2->slopeRating = temp1->slopeRating;
			temp2->year = temp1->year;

			ScoreListInsertAfter(newList, NULL, temp2);			//add the data after the next most recent list item
		}
		else{			//insert a node not at the head of the list
			temp2 = (Score*)malloc(sizeof(Score));
			if(temp2 == NULL){
				return NULL;
			}
			temp2->filenum = temp1->filenum;
			temp2->adjGrossScore = temp1->adjGrossScore;
			temp2->counted = temp1->counted;
			temp2->courseRating = temp1->courseRating;
			temp2->hcpDifferential = temp1->hcpDifferential;
			temp2->month = temp1->month;
			strcpy(temp2->scoreType, temp1->scoreType);
			temp2->slopeRating = temp1->slopeRating;
			temp2->year = temp1->year;

			ScoreListInsertAfter(newList, newList->tail, temp2);
		}
		previous = temp1;
		temp1 = temp1->next;
	}

	return newList;
}

/*
** insertionSort() sorts the list by most recent, while taking into
** account the order of which the data was read in. Data from 
** argv[2] get priority of data from argv[1].
*/

bool insertionSort(ScoreList* list){
	Score* temp1 = NULL;
	Score* temp2 = NULL;

	if((list == NULL) || (list->head == NULL)){
		return true;
	}

	temp1 = list->head->next;	//start at the second item in the list

	while(temp1 != NULL){
		temp2 = temp1;
		while((temp2 != NULL) && (temp2->year > temp2->prev->year)){	//sort by most recent year
			swapNode(temp2, temp2->prev);
			temp2 = temp2->prev;
		}
		while((temp2 != NULL) && (temp2->prev != NULL) && (temp2->month > temp2->prev->month)){		//sort by most recent month
			swapNode(temp2, temp2->prev);
			temp2 = temp2->prev;
		}
		while((temp2 != NULL) && (temp2->prev != NULL) && (temp2->month == temp2->prev->month) && (temp2->filenum > temp2->prev->filenum)){		//sort by file number
			swapNode(temp2, temp2->prev);
			temp2 = temp2->prev;
		}
		temp1 = temp1->next;
	}


	return true;
}