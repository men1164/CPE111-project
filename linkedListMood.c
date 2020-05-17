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

SONG_ITEM_T *listHead[MAXMOODS];    /* Head list, set as array to keep separate linked list each mood */
SONG_ITEM_T *listTail[MAXMOODS];    /* Tail list, set as array to keep separate linked list each mood */


/*
 * This function is for set all of head and tail to NULL.
 */
void initializeMoodArray()
{
    int i;
    
    for (i=0; i<MAXMOODS; i++)
    {
        listHead[i] = NULL;
        listTail[i] = NULL;
    }
}

/*
 * Argument
 *  - song      songs' structure to keep into an item in linked list.
 * This function use for check the songMood, if 1, put into a linked list
 * of that mood.
 */
void linkedListMood(SONG_T *song)
{
    int i;
    int moodCount;
    SONG_ITEM_T *songItem = NULL;

    

    moodCount = moodsItemCount();
    for (i=0; i<moodCount; i++)
    {
        if (song->songMood[i] == 1)
        {
            songItem = (SONG_ITEM_T *) calloc(1, sizeof(SONG_ITEM_T));
            songItem->song = song;
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

/*
 * Argument
 *  - moodPosition      to set the index of the array list.
 * This function will display the songs in that mood,
 * then ask user that they want to display lyrics or not.
 */
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


/*
 * Argument
 *  - moodPosition      to set the index of the array list.
 *  - songFoundInMood   to check error of input from user.
 * This function will let user input the number of song that user
 * want to display the lyrics.
 */
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
                    sprintf(folder, "Lyrics/%s",currentSong->song->fileName);
                    if (currentSong->song->lowerCaseMark == 1)
                    {
                        printf("\n***************************\n");
                        printf("Lyrics of '%s'\n",currentSong->song->originalName);
                    }
                    else
                    {
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
