/*
 * Created by Kittipol Neamprasertporn (Dome) 62070503404
 *
 *
 * Based on Lab 3 code.
 * This file use linked list to store and searching songs by mood.
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "linkedListMood.h"

SONG_ITEM_T *listHead[MAXMOODS];
SONG_ITEM_T *listTail[MAXMOODS];

void initualizeMoodArray()
{
    int i;
    
    for (i=0; i<MAXMOODS; i++)
    {
        listHead[i] = NULL;
        listTail[i] = NULL;
    }
}

void linkedListMood(SONG_T *song)
{
    int i;
    int moodCount;
    SONG_ITEM_T *songItem = NULL;

    songItem = (SONG_ITEM_T *) calloc(1, sizeof(SONG_ITEM_T));
    songItem->song = song;

    moodCount = moodsItemCount();
    for (i=0; i<moodCount; i++)
    {
        if (songItem->song->songMood[i] == 1)
        {
            if (listHead[i] == NULL)
            {
                listHead[i] = listTail[i] = songItem;
            }
            else
            {
                listTail[i]->next = songItem;
                listTail[i] = songItem;
            }
        }
    }
}

void searchByMood(int moodPosition)
{
    SONG_ITEM_T *currentSong = listHead[moodPosition];

    if (currentSong == NULL)
    {
        printf("\n\t**** No songs found in this mood. ****\n\n");
    }
    else
    {
        while (currentSong != NULL)
        {
            printf("%s\n",currentSong->song->songName);
            currentSong = currentSong->next;
        }
    }
}
