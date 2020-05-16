/*
* Created by Thanasit Suwanposri (Men) 62070503414
* and Krittin Srithong (Pong) 62070503402
*
*
* Based on Lab 6 code.
* This file use for create a sorted binary tree to store the songs.
*/

#ifndef sortedBinaryTree_h
#define sortedBinaryTree_h

#include "analyzeMood.h"

/*
 * This function use for set the rootSong if it NULL.
 * For the first node, otherwise it will call insertNode().
 */
void checkRoot(SONG_T *song);

/*
 * This function will insert the new node
 * into left or right child.
 * Working as a recursive function.
 */
void insertNode(SONG_T *pCurrent, SONG_T *pNew);

/*
 * This function use for send rootNode to search the
 * songs in the tree.
 * Return the pResult if found the data, otherwise return NULL.
 */
SONG_T *searchByTitle(char searchSong[]);

/*
 * This function work as a recursive function
 * to search any song name. If match, return pResult, otherwise return NULL.
 */
SONG_T *recursiveSearch(SONG_T *pCurrent, char searchSong[]);

/*
 * This function is use for free the tree,
 * send rootSong to recursive function
 */
void freeTree();

/*
 * This function work as recursive
 * to free the tree.
 */
void recursiveFree(SONG_T *pCurrent);


#endif /* sortedBinaryTree_h */
