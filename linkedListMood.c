/*
 * Created by Kittipol Neamprasertporn (Dome) 62070503404
 * and Thanasit Suwanposri (Men) 62070503414
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
    int i = 1;
    char read[READ];
    char decision[8];

    printf("\nHere are the song lists in this mood\n");
    
    if (currentSong == NULL)
    {
        printf("\n\t**** No songs found in this mood. ****\n\n");
    }
    else
    {
        while (currentSong != NULL)
        {
            if (currentSong->song->lowerCaseMark == 1)
            {
                printf("%d : %s\n", i, currentSong->song->originalName);
            }
            else
            {
                printf("%d : %s\n", i, currentSong->song->songName);
            }
            i++;
            currentSong = currentSong->next;
        }
    }
    
    printf("\nDo you want to choose the songs to display the lyrics? (Yes|No): ");
    fgets(read, sizeof(read), stdin);
    sscanf(read, "%s",decision);
    if (strcasecmp("Yes", decision) == 0)
    {
        selectSongFromMood(moodPosition,i);
    }
    else
    {
        printf("\nBack to Main Menu.\n");
    }
    
}

void selectSongFromMood(int moodPosition, int songFoundInMood)
{
    SONG_ITEM_T *currentSong = listHead[moodPosition];
    char read[READ];
    int choice;
    int i = 1;
    char folder[64];
    FILE *pSong = NULL;
    
    while (1)
    {
        choice = 0;
        printf("Input the number of songs you want to display lyrics (-1 to exit): ");
        fgets(read, sizeof(read), stdin);
        sscanf(read, "%d",&choice);
        
        if (choice < 0)
        {
            printf("\nBack to Main Menu.\n");
            break;
        }
        
        if ((choice == 0) || (choice > songFoundInMood-1))
        {
            printf("Invalid Choice, please try again.\n");
        }
        else
        {
            while (currentSong != NULL)
            {
                if (i == choice)
                {
                    if (currentSong->song->lowerCaseMark == 1)
                    {
                        sprintf(folder, "Lyrics/%s.txt",currentSong->song->originalName);
                        printf("\n***************************\n");
                        printf("Lyrics of '%s'\n",currentSong->song->originalName);
                    }
                    else
                    {
                        sprintf(folder, "Lyrics/%s.txt",currentSong->song->songName);
                        printf("\n***************************\n");
                        printf("Lyrics of '%s'\n",currentSong->song->songName);
                    }
                    break;
                }
                i++;
                currentSong = currentSong->next;
            }
            
            pSong = fopen(folder, "r");
            if (pSong == NULL)
            {
                printf("Error! - Can't found the song file.\n");
                exit(0);
            }
            memset(read, 0, sizeof(read));
            
            printf("***************************\n");
            while (fgets(read, sizeof(read), pSong) != NULL)
            {
                printf("%s",read);
            }
            printf("\n\n");
        }
    }
}
