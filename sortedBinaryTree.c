//
//  sortedBinaryTree.c
//  project2
//
//  Created by Thanasit Suwanposri on 17/4/2563 BE.
//  Copyright © 2563 Thanasit Suwanposri. All rights reserved.
//

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

/* Based on code by Sally Goldin from [simpleBinaryTree.c]
 * Used with permission.
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

SONG_T *searchByTitle(SONG_T *pCurrent, char searchSong[])
{
    SONG_T *pResult = NULL;
    
    if (pCurrent != NULL)
    {
        if (strcasecmp(pCurrent->songName, searchSong) == 0)
        {
            pResult = pCurrent;
        }
        else if (strcasecmp(pCurrent->songName, searchSong) < 0)
        {
            pResult = searchByTitle(pCurrent->left, searchSong);
        }
        else
        {
            pResult = searchByTitle(pCurrent->right, searchSong);
        }
    }
    return pResult;
}

void printAll()
{
    recursivePrint(rootSong);
}

void recursivePrint(SONG_T *pCurrent)
{
    if (pCurrent->left != NULL)
    {
        recursivePrint(pCurrent->left);
    }
    printf("%s\n",pCurrent->songName);
    if (pCurrent->right != NULL)
    {
        recursivePrint(pCurrent->right);
    }
}
