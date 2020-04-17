//
//  analyzeMood.c
//  project
//
//  Created by Thanasit Suwanposri on 29/3/2563 BE.
//  Copyright © 2563 Thanasit Suwanposri. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <sys/stat.h>

#include "analyzeMood.h"
#include "abstractHashTable.h"


char saveMood[32];
char keywordsString[MAXMOODS][KEYWORDSLEN];
static int moodCount = 0;


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
    char *lyricsArray, *token, *test;
    char toSearch[128];

    pSongList = fopen("Lyrics/songList.txt", "r");
    if (pSongList == NULL)
    {
        printf("Error! Can't read the songLists file.\n");
        exit(0);
    }
    
    combineKeywords();
    
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
//        printf("%lld\n",fileStatus.st_size);
        
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
        printf("***************");
        printf("\n%s\n",songName);
        printf("***************\n");
        while (fgets(lyricsArray, fileSize+1, pLyrics) != NULL)
        {
            token = strtok(lyricsArray, " ,.!?:;()&\n\r");
            while (token != NULL)
            {
                sprintf(toSearch, "|%s|", token);
                for (i=0; i<moodCount; i++)
                {
                    test = strstr(keywordsString[i], toSearch);
                    if (test != NULL) {
                        keywordsCount[i]++;
//                        printf("Mood #%d: %s with %s\n\n",i+1,token,test);
                    }
                }
                token = strtok(NULL, " ,.!?:;()&\n\r");
            }
        }
        
        for (i=0; i<moodCount; i++)
        {
            printf("\t%d:Found %d words\n", i+1, keywordsCount[i]);
        }
        
        moodAnalysis(keywordsCount, songName);
        fclose(pLyrics);
    }
    printf("\nItems in hashTable %d.\n",hashTableItemCount());
    fclose(pSongList);
}

void combineKeywords()
{
    FILE *pMoodlist = NULL;
    FILE *pEachMood = NULL;
    int i = 0;
    char read[READ];
    char mood[32], moodFile[64];
    char keywordsRead[KEYWORDSLEN];
    char keywords[32];
    
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
            sscanf(read, "%[^\n]", keywords);
            if (strlen(keywords) + strlen(keywordsRead) < KEYWORDSLEN)
            {
                strcat(keywordsRead, keywords);
                strcat(keywordsRead, "|");
            }
            else
            {
                printf("Warning! - Too many keywords -> %s.\n",mood);
                break;
            }
        }
        sprintf(keywordsString[i], "|%s",keywordsRead);
//        printf("%s\n\n",keywordsString[i]);
        i++;
        fclose(pEachMood);
    }
    moodCount = i;
    fclose(pMoodlist);
}

int moodsItemCount()
{
    return moodCount;
}

void moodAnalysis(int keywordsFound[], char songName[]) {
    
    int dummy = 0;
    int i;
    SONG_T *songsList = NULL;

    
    songsList = (SONG_T *) calloc(1, sizeof(SONG_T));
    strcpy(songsList->songName, songName);

    for (i=0; i<moodCount; i++)
    {
        if (keywordsFound[i] > 5)
        {
            findMoodPosition(i);
            strcpy(songsList->mood, saveMood);
            hashTableInsert(songsList->mood, songsList, &dummy);
            
//            if (colorMark == WHITE) {
//
//                colorMark = BLACK;
//            }
//            else {
//                /*already insert this song, plans to use hashLookup and put in pNext*/
//            }
        }
    }
}

void findMoodPosition(int position)
{
    FILE *pMoodlist = NULL;
    char read[READ];
    int i = 0;
    
    memset(saveMood, 0, sizeof(saveMood));
    
    pMoodlist = fopen("Mood/moodList.txt", "r");
    if (pMoodlist == NULL)
    {
        printf("Error! - Can't open list of mood files.\n");
        exit(6);
    }
    while (fgets(read, sizeof(read), pMoodlist) != NULL)
    {
        if (i == position)
        {
            sscanf(read, "%s", saveMood);
            break;
        }
        i++;
    }
    fclose(pMoodlist);
}
