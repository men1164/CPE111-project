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


/*
 * This structure is use for keep songs' info.
 * And keeping the left and right child songs' node
 * for binary tree data structure.
 */
typedef struct _songInfo
{
    char songName[32];          /* for keeping the song title */
    char originalName[32];      /* for keeping the original title in case of if starts with lower case */
    int lowerCaseMark;          /* for mark that this song is starting with lower or upper case, 0 if not, otherwise 1.*/
    char fileName[32];          /* for keep the file name of each song */
    int songMood[MAXMOODS];     /* array integer for mark that the songs match in any mood, 1 if match. */
    struct _songInfo *left;     /* left child */
    struct _songInfo *right;    /* right child */
} SONG_T;


/*
 * This structure is use for keep any songs in each mood,
 * using linked list.
 */
typedef struct _songItem
{
    SONG_T *song;               /* structure of song */
    struct _songItem *next;     /* next list of song */
} SONG_ITEM_T;


/*
 * This function use for separate the lyrics into word by word,
 * then add delimeter to each word ('|')
 * and compare with keywordsString in each mood.
 */
void keywordsAnalysis();

/*
 * Argument
 *  - keywordsFound     to check the count keywords found in each mood.
 *  - songName          for keep into SONG_T structure
 *  - fileName          for keep the file name of the song to structure.
 * Check if found keywords more than 4 words each mood, set the mood for that song
 * Store song info into binary tree and mood to linked list
 */
void moodAnalysis(int keywordsFound[], char songName[], char fileName[]);

/* Use to combine all keywords for comparing with lyrics
 * and use '|' as a delimeter to separate each keywords
 */
void combineKeywords();

/* return mood count */
int moodsItemCount();

/* return song count */
int songsListCount();

#endif /* analyzeMood_h */
