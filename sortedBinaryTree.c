/*
 * Created by Thanasit Suwanposri (Men) 62070503414
 * and Krittin Srithong (Pong) 62070503402
 *
 *
 * Based on Lab 6 code.
 * This file use for create a sorted binary tree to store the songs.
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "sortedBinaryTree.h"

SONG_T *rootSong = NULL;    /* root songs of the tree */

/*
 * This function use for set the rootSong if it NULL.
 * For the first node, otherwise it will call insertNode().
 */
void checkRoot(SONG_T *song)
{
    if (rootSong == NULL)
    {
        rootSong = song;
    }
    else
    {
        insertNode(rootSong, song);
    }
}

/*
 * This function will insert the new node
 * into left or right child.
 * Working as a recursive function.
 */
void insertNode(SONG_T *pCurrent, SONG_T *pNew)
{
     if (strcmp(pNew->songName, pCurrent->songName) < 0)
     {
         if (pCurrent->left == NULL)
         {
             pCurrent->left = pNew;
         }
         else
         {
             insertNode(pCurrent->left, pNew);
         }
     }
     else
     {
         if (pCurrent->right == NULL)
         {
             pCurrent->right = pNew;
         }
         else
         {
             insertNode(pCurrent->right, pNew);
         }
     }
}


/*
 * This function use for send rootNode to search the
 * songs in the tree.
 * Return the pResult if found the data, otherwise return NULL.
 */
SONG_T *searchByTitle(char searchSong[])
{
    SONG_T *pResult = NULL;
    
    pResult = recursiveSearch(rootSong, searchSong);
    
    return pResult;
}

/*
 * This function work as a recursive function
 * to search any song name. If match, return pResult, otherwise return NULL.
 */
SONG_T *recursiveSearch(SONG_T *pCurrent, char searchSong[])
{
    SONG_T *pResult = NULL;
    
    if (pCurrent != NULL)
    {
        if (strcasecmp(searchSong, pCurrent->songName) == 0)
        {
            pResult = pCurrent;
        }
        else if (strcasecmp(searchSong, pCurrent->songName) < 0)
        {
            pResult = recursiveSearch(pCurrent->left, searchSong);
        }
        else
        {
            pResult = recursiveSearch(pCurrent->right, searchSong);
        }
    }
    return pResult;
}

/*
 * This function is use for free the tree,
 * send rootSong to recursive function
 */
void freeTree()
{
    recursiveFree(rootSong);
    rootSong = NULL;
}

/*
 * This function work as recursive
 * to free the tree.
 */
void recursiveFree(SONG_T *pCurrent)
{
    if (pCurrent->left != NULL)
    {
        recursiveFree(pCurrent->left);
    }
    if (pCurrent->right != NULL)
    {
        recursiveFree(pCurrent->right);
    }
    free(pCurrent);
}
