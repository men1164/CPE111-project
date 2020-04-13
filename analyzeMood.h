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

typedef struct _songInfo {
    char songName[32];
    char mood[32];
    struct _songInfo *pNext;    /*next mood*/
} SONG_T;

void keywordsAnalysis();
int combineKeywords();
void moodAnalysis(int keywordsFound[], char songName[], int moodCount);
void findMoodPosition(int i);

#endif /* analyzeMood_h */
