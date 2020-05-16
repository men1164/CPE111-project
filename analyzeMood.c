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
static int moodsCount = 0;
static int songsCount;
int songsNoMood ;

/* This function use for separate the lyrics into word by word and compare with keywords in each mood */
void keywordsAnalysis()
{
    FILE *pSongList = NULL;
    FILE *pLyrics = NULL;
    char read[READ];
    char songName[32], fileName[64];
    int keywordsCount[MAXMOODS] = {0};
    int i;
    int statResult, fileSize;
    struct stat fileStatus;
    char *lyricsArray, *token;
    char toSearch[128];

    initualizeMoodArray();
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
        memset(keywordsCount, 0, sizeof(keywordsCount));
        sscanf(read, "%[^\n]",songName);
        sprintf(fileName, "Lyrics/%s.txt", songName);
        
        statResult = stat(fileName, &fileStatus);
        if (statResult != 0)
        {
            printf("Error! - Can't stat the lyrics file size -> '%s'.\n", songName);
            exit(1);
        }

        fileSize = (int) fileStatus.st_size;
        lyricsArray = (char *) calloc(fileSize+1, sizeof(char));
        if (lyricsArray == NULL)
        {
            printf("Dynamically allocate lyricsArray failed.\n");
            exit(2);
        }
        
        pLyrics = fopen(fileName, "r");
        if (pLyrics == NULL)
        {
            printf("Error! - Can't open the lyrics file -> '%s'.\n", songName);
            exit(3);
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

        moodAnalysis(keywordsCount, songName);
        fclose(pLyrics);
        songsCount++;
    }
    printf("\n\t%d out of %d Songs have no mood.\n",songsNoMood,songsCount);
    fclose(pSongList);
}

/* Check if found keywords more than 4 words each mood, set the mood for that song
 * Store song info into binary tree and mood to linked list
 */
void moodAnalysis(int keywordsFound[], char songName[]) {
    
    int i;
    SONG_T *song = NULL;
    int moodFound = 0;

    song = (SONG_T *) calloc(1, sizeof(SONG_T));
    
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
