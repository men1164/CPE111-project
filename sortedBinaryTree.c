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

SONG_T *rootSong = NULL;

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

SONG_T *searchByTitle(char searchSong[])
{
    SONG_T *pResult = NULL;
    
    pResult = recursiveSearch(rootSong, searchSong);
    
    return pResult;
}

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

void freeTree()
{
    recursiveFree(rootSong);
    rootSong = NULL;
}

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
