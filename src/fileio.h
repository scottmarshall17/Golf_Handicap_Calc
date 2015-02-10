/**************************************************************************************************/

/*
 * File: fileio.h
 * Author: Scott Marshall
 * NetID: scottmarshall
 * Date: October 26, 2014
 * ECE 275
 * Description: This .c file includes the declarations of functions used to read score data from the specified input files.
 *
 */

/**************************************************************************************************/


#ifndef FILEIO_H
#define FILEIO_H

/*
** readRevisionFile() reads data from the revisionScores input file
** and places the data in a specified doubly linked list.
*/
bool readRevisionFile(ScoreList* list, char* filename );

/*
** readRecentFile() reads data from the newScores input file
** and places the data in a specified doubly linked list.
*/

bool readRecentFile(ScoreList* list, char* filename);

#endif