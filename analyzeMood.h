//
//  analyzeMood.h
//  project
//
//  Created by Thanasit Suwanposri on 29/3/2563 BE.
//  Copyright © 2563 Thanasit Suwanposri. All rights reserved.
//

#ifndef analyzeMood_h
#define analyzeMood_h

#define READ 256
#define MAXMOODS 10
#define KEYWORDSLEN 512


typedef struct _songInfo
{
    char songName[32];
    char songFile[32];
    char mood[32];
    int songMood[MAXMOODS];
    struct _songInfo *left;
    struct _songInfo *right;
} SONG_T;

typedef struct _songItem
{
    SONG_T *song;
    struct _songItem *next;
} SONG_ITEM_T;

void initualizeMoodArray();
void keywordsAnalysis();
void combineKeywords();
int moodsItemCount();
void moodAnalysis(int keywordsFound[], char songName[]);
void linkedListMood(SONG_T *song);
void searchByMood(int moodPosition);
void findMoodPosition(int i);

#endif /* analyzeMood_h */
