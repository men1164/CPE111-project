/*
 * Created by Thanasit Suwanposri (Men) 62070503414
 *
 * This file is use for lyrics analysis.
 */



#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <sys/stat.h>

#include "analyzeMood.h"
#include "sortedBinaryTree.h"
#include "linkedListMood.h"

char keywordsString[MAXMOODS][KEYWORDSLEN];     /* for combining all keywords each mmod */
static int moodsCount = 0;                      /* count of all moods */
static int songsCount;                          /* count of all songs */
int songsNoMood;                                /* count of song that have no mood */

/*
 * This function use for separate the lyrics into word by word,
 * then add delimeter to each word ('|')
 * and compare with keywordsString in each mood.
 */
void keywordsAnalysis()
{
    FILE *pSongList = NULL;
    FILE *pLyrics = NULL;
    char read[READ];
    char songName[32], songDirectory[64], fileName[32];
    int keywordsCount[MAXMOODS] = {0};
    int i;
    int statResult, fileSize;
    struct stat fileStatus;     /* stat structure for get the file size to allocate */
    char *lyricsArray, *token;
    char toSearch[128];

    initualizeMoodArray(); /* set the linked list of mood array to NULL */
    
    pSongList = fopen("Lyrics/songList.txt", "r");
    if (pSongList == NULL)
    {
        printf("Error! Can't read the songLists file.\n");
        exit(0);
    }
    
    combineKeywords();
    songsCount = 0;
    songsNoMood = 0;
    while (fgets(read, sizeof(read), pSongList) != NULL)
    {
        if (read[0] != '\n')
        {
            memset(keywordsCount, 0, sizeof(keywordsCount));
            sscanf(read, "%s %[^\n]",fileName,songName);
            sprintf(songDirectory, "Lyrics/%s", fileName);
            
            statResult = stat(songDirectory, &fileStatus);
            if (statResult != 0)
            {
                printf("Warning! - Can't find the lyrics file for '%s'.\n", songName);
                /*skip the the file*/
            }
            else
            {
                fileSize = (int) fileStatus.st_size;
                lyricsArray = (char *) calloc(fileSize+1, sizeof(char));
                if (lyricsArray == NULL)
                {
                    printf("Dynamically allocate lyricsArray failed.\n");
                    exit(1);
                }
                
                pLyrics = fopen(songDirectory, "r");
                if (pLyrics == NULL)
                {
                    printf("Error! - Can't read the lyrics file -> '%s'.\n", songName);
                    exit(2);
                }
                
                while (fgets(lyricsArray, fileSize+1, pLyrics) != NULL)
                {
                    token = strtok(lyricsArray, " ,.!?:;()&\n\r");
                    while (token != NULL)
                    {
                        sprintf(toSearch, "|%s|", token);
                        for (i=0; i<moodsCount; i++)
                        {
                            if (strstr(keywordsString[i], toSearch) != NULL)
                            {
                                keywordsCount[i]++;
                            }
                        }
                        token = strtok(NULL, " ,.!?:;()&\n\r");
                    }
                }
                moodAnalysis(keywordsCount, songName, fileName);
                fclose(pLyrics);
                songsCount++;
            }
        }
    }
    printf("\n\t%d out of %d Songs have no mood.\n",songsNoMood,songsCount);
    fclose(pSongList);
}

/*
 * Argument
 *  - keywordsFound     to check the count keywords found in each mood.
 *  - songName          for keep into SONG_T structure
 *  - fileName          for keep the file name of the song to structure.
 * Check if found keywords more than 4 words each mood, set the mood for that song
 * Store song info into binary tree and mood to linked list
 */
void moodAnalysis(int keywordsFound[], char songName[], char fileName[])
{
    int i;
    SONG_T *song = NULL;
    int moodFound = 0;

    song = (SONG_T *) calloc(1, sizeof(SONG_T));
    strcpy(song->fileName, fileName);
    
    if (islower(songName[0]) != 0)
    {
        song->lowerCaseMark = 1;
        strcpy(song->originalName, songName);
        songName[0] = toupper(songName[0]);
        strcpy(song->songName, songName);
    }
    else
    {
        strcpy(song->songName, songName);
        song->lowerCaseMark = 0;
    }
    
    for (i=0; i<moodsCount; i++)
    {
        if (keywordsFound[i] > 4)
        {
            moodFound = 1;
            song->songMood[i] = 1;
        }
    }
    
    if (moodFound == 0)
    {
        printf("NO MOOD FOUND - %s\n", songName);
        songsNoMood++;
    }
    checkRoot(song);
    linkedListMood(song);
}

/* Use to combine all keywords for comparing with lyrics
 * and use '|' as a delimeter to separate each keywords
 */
void combineKeywords()
{
    FILE *pMoodlist = NULL;
    FILE *pEachMood = NULL;
    int i = 0;
    char read[READ];
    char mood[32], moodFile[64];
    char keywordsRead[KEYWORDSLEN];
    char newKeywords[32];
    
    pMoodlist = fopen("Mood/moodList.txt", "r");
    if (pMoodlist == NULL)
    {
        printf("Error! - Can't open list of mood files.\n");
        exit(4);
    }
    
    while (fgets(read, sizeof(read), pMoodlist) != NULL)
    {
        memset(keywordsRead, 0, sizeof(keywordsRead));
        sscanf(read, "%s", mood);
        sprintf(moodFile, "Mood/%s.txt", mood);
        
        pEachMood = fopen(moodFile, "r");
        if (pEachMood == NULL)
        {
            printf("Error! Can't open the mood files -> %s.\n",mood);
            exit(5);
        }
        
        while (fgets(read, sizeof(read), pEachMood) != NULL)
        {
            sscanf(read, "%[^\n]", newKeywords);
            if (strlen(newKeywords) + strlen(keywordsRead) < KEYWORDSLEN)
            {
                strcat(keywordsRead, newKeywords);
                strcat(keywordsRead, "|");
            }
            else
            {
                printf("Warning! - Too many keywords in mood -> %s.\n",mood);
                break;
            }
        }
        sprintf(keywordsString[i], "|%s",keywordsRead); /*add the front delimeter*/
        i++;
        fclose(pEachMood);
    }
    moodsCount = i;
    fclose(pMoodlist);
}

int moodsItemCount()
{
    return moodsCount;
}

int songsListCount()
{
    return songsCount;
}
