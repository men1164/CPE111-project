/*
 * Created by Thanasit Suwanposri (Men) 62070503414
 *
 * This file is use for lyrics analysis.
 */

#ifndef analyzeMood_h
#define analyzeMood_h

#define READ 512
#define MAXMOODS 10
#define KEYWORDSLEN 512


typedef struct _songInfo
{
    char songName[32];
    char originalName[32];
    int lowerCaseMark;
    int songMood[MAXMOODS];
    struct _songInfo *left;
    struct _songInfo *right;
} SONG_T;

typedef struct _songItem
{
    SONG_T *song;
    struct _songItem *next;
} SONG_ITEM_T;

void keywordsAnalysis();
void combineKeywords();
int moodsItemCount();
void moodAnalysis(int keywordsFound[], char songName[]);
int songsListCount();

#endif /* analyzeMood_h */
