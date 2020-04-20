/*
* Created by Thanasit Suwanposri (Men) 62070503414
* and Krittin Srithong (Pong) 62070503402
*
*
* Based on Lab 6 code.
* This fle use for create a sorted binary tree to store the songs.
*/

#ifndef sortedBinaryTree_h
#define sortedBinaryTree_h

#include "analyzeMood.h"

void checkRoot(SONG_T *song);
void insertNode(SONG_T *pCurrent, SONG_T *pNew);
SONG_T *searchByTitle(char searchSong[]);
SONG_T *recursiveSearch(SONG_T *pCurrent, char searchSong[]);
void printAll();
void recursivePrint(SONG_T *pCurrent);
void freeTree();
void recursiveFree(SONG_T *pCurrent);


#endif /* sortedBinaryTree_h */
