/*
 * Created by Krittin Srithong (Pong) 62070503402
 * Kittipol Neamprasertporn (Dome) 62070503404
 * and Thanasit Suwanposri (Men) 62070503414
 */



#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "sortedBinaryTree.h"
#include "analyzeMood.h"
#include "linkedListMood.h"
#include "modifyMood.h"


void searchByTitleUI()
{
    char input[64];
    char title[64];
    SONG_T *pResult = NULL;
    
    printf("What songs you want to search: ");
    fgets(input,sizeof(input),stdin);
    sscanf(input,"%[^\n]",title);
    
    pResult = searchByTitle(title);
    if (pResult == NULL)
    {
        printf("\nNo songs matched.\n\n");
    }
    else
    {
        printf("\nFound!\n\n");
        /* direct to display lyrics function (have not created yet)*/
    }
}

void freeSongsName(int songsCount, char **songsName)
{
    int i;
    for (i=0; i<songsCount; i++)
    {
        free(songsName[i]);
    }
    free(songsName);
}

void printMood(int moodPosition)
{
    FILE *pMoodlist = NULL;
    char read[READ];
    int i = 0;
    
    pMoodlist = fopen("Mood/moodList.txt", "r");
    if (pMoodlist == NULL)
    {
        printf("Error! - Can't open mood list file.\n");
        exit(0);
    }
    
    while (fgets(read, sizeof(read), pMoodlist) != NULL)
    {
        if (i == moodPosition)
        {
            printf("\t- %s",read);
        }
        i++;
    }
    fclose(pMoodlist);
}

void RealizeMood(SONG_T *pSong)
{
    int i, moodFound = 0;
    int moodCount = moodsItemCount();
    for (i=0; i<moodCount; i++)
    {
        if (pSong->songMood[i] == 1)
        {
            printMood(i);
            moodFound = 1;
        }
    }
    if (moodFound == 0)
    {
        printf(" - This song have no mood.\n");
    }
}

void selectSongUI(int songsCount, char **songsName)
{
    char stringInput[READ];
    char folder[64];
    int inputSongNumber;
    FILE * pLyrics = NULL;
    SONG_T *pResult = NULL;
    char decision[8];
    
    
    while(1)
    {
        printf("Enter song number: ");
        fgets(stringInput,sizeof(stringInput),stdin);
        sscanf(stringInput,"%d",&inputSongNumber);
        
        if((inputSongNumber > songsCount) || (inputSongNumber <= 0))
        {
            printf("You entered the invalid song number.\n");
        }
        else
        {
            inputSongNumber = inputSongNumber - 1;
            songsName[inputSongNumber][0] = toupper(songsName[inputSongNumber][0]);
            pResult = searchByTitle(songsName[inputSongNumber]);
            if (pResult == NULL)
            {
                printf("No songs found in database.\n");
                exit(1);
            }
            
            if (pResult->lowerCaseMark == 1)
            {
                sprintf(folder, "Lyrics/%s.txt",pResult->originalName);
                pLyrics = fopen(folder,"r");
                memset(stringInput, 0, sizeof(stringInput));

                printf("\n*************************************");
                printf("\nHere's a lyrics of '%s'.\n",pResult->originalName);
            }
            else
            {
                sprintf(folder,"Lyrics/%s.txt",pResult->songName);
                pLyrics = fopen(folder,"r");
                memset(stringInput, 0, sizeof(stringInput));

                printf("\n*************************************");
                printf("\nHere's a lyrics of '%s'.\n",pResult->songName);
            }
            
            printf("Mood(s) in this song:\n");

            RealizeMood(pResult);

            printf("*************************************\n");
            while(fgets(stringInput,sizeof(stringInput),pLyrics) != NULL)
            {
                printf("%s",stringInput);
            }
            printf("\n\n");
            fclose(pLyrics);

            memset(stringInput, 0, sizeof(stringInput));
            memset(decision, 0, sizeof(decision));

            printf("\nContinue looking other song? (Yes|No): ");
            fgets(stringInput, sizeof(stringInput), stdin);
            sscanf(stringInput, "%s",decision);
            if (strcasecmp(decision, "No") == 0)
            {
                printf("\nBack to Main Menu\n");
                break;
            }
        }
    }
    freeSongsName(songsCount,songsName);
}

void displayAllSongsUI()
{
    char stringInput[128];
    char str[READ];
    char **songsName;
    int stringLenght = 64;
    int i;
    FILE * pSongLists = NULL;
    int songsCount = 0;

    pSongLists = fopen("Lyrics/songList.txt","r");
    songsCount = songsListCount();
    songsName = (char **) calloc(songsCount, sizeof(char*));
    
    for (i=0; i<songsCount; i++)
    {
        songsName[i] = (char *) calloc(stringLenght, sizeof(char));
    }
    
    printf("\n*************************************");
    printf("\nHere are all songs list.\n");
    printf("*************************************\n");

    i = 0;
    while(fgets(str,sizeof(stringInput),pSongLists) != NULL)
    {
        sscanf(str, "%[^\n]", songsName[i]);
        printf("%d : %s",i+1,str);
        i++;
    }
    printf("\n\n");
    fclose(pSongLists);
    selectSongUI(songsCount,songsName);
}

void addLyrics(char songName[])
{
    FILE* pLyrics = NULL;
    char lyrics[READ];
    char read[READ];
    char filename[32];
    
    printf("\n*************************************");
    printf("\nHow to input the lyrics.\n");
    printf("\t1. Input lyrics line by line or paste them from google.\n");
    printf("\t2. Hit return, then type 'done' for finished input lyrics.\n");
    printf("*************************************\n\n");
    
    sprintf(filename,"Lyrics/%s.txt",songName);
    pLyrics = fopen(filename,"w");
    printf("Enter lyrics (done to stop): ");
    while(fgets(read,sizeof(read),stdin) != NULL)
    {
        sscanf(read,"%[^\n]",lyrics);
        if(strcasecmp(lyrics,"done") == 0)
        {
            break;
        }
        fprintf(pLyrics,"%s\n",lyrics);
    }
    fclose(pLyrics);
}

void addNewSong()
{
    FILE* pSongList = NULL;
    char newSongName[32];
    char stringInput[64];
    
    pSongList = fopen("Lyrics/songList.txt","a");
    if(pSongList == NULL)
    {
        printf("Error! - Can't open the songList file.\n");
        exit(2);
    }
    
    printf("Enter new song name: ");
    fgets(stringInput,sizeof(stringInput),stdin);
    sscanf(stringInput,"%[^\n]",newSongName);
    
    fprintf(pSongList,"%s\n",newSongName);
    fclose(pSongList);
    
    addLyrics(newSongName);
}

void displayMoodUI()
{
    FILE *pMoodlist = NULL;
    char read[READ];
    char decision[8];
    int i = 1;
    int moodChoice;
    
    pMoodlist = fopen("Mood/moodList.txt", "r");
    if (pMoodlist == NULL)
    {
        printf("Error! - Can't read the mood list file.\n");
        exit(3);
    }
    
    printf("\n***** Mood List *****\n");
    while (fgets(read, sizeof(read), pMoodlist) != NULL)
    {
        printf("%d: %s\n",i,read);
        i++;
    }
    memset(read, 0, sizeof(read));
    
    printf("Do you want to search songs by mood? (yes|no): ");
    fgets(read, sizeof(read), stdin);
    sscanf(read, "%s",decision);
    if (strcasecmp(decision, "yes") == 0)
    {
        memset(read, 0, sizeof(read));
        printf("Enter the number of mood that you want : ");
        fgets(read, sizeof(read), stdin);
        sscanf(read, "%d",&moodChoice);
        printf("\n");
        searchByMood(moodChoice-1);
        printf("\n");
    }
    else
    {
        printf("\nBack to Main Menu\n");
    }
    fclose(pMoodlist);
}

int main(int argc, const char * argv[])
{
    char input[10];
    int choice;
    
    /* call the function to analyze the song */
    keywordsAnalysis();
    
    printf("\n\n************************************************************\n\n");
    printf("Welcome to Emotion-based Song Recommender!!\n\n");
    printf("************************************************************\n\n");
    
    while (1)
    {
        printf("|Main Menu|\n");
        printf("\t1) Display all songs and lyrics.\n");
        printf("\t2) Display all moods and Search songs by mood.\n");
        printf("\t3) Add a new songs.\n");
        printf("\t4) Modify Mood.\n");
        printf("\t5) Exit the program.\n");

        printf("What do you want to do? : ");
        fgets(input, sizeof(input), stdin);
        sscanf(input, "%d", &choice);

        if (choice == 1)
        {
            displayAllSongsUI();
        }
        else if (choice == 2)
        {
            displayMoodUI();
        }
        else if (choice == 3)
        {
//            searchByTitleUI();
            addNewSong();

            /*reset after added a new song*/
            freeTree();
            keywordsAnalysis();
//            printAll();
        }
        else if (choice == 4)
        {
            modifyMood();
            
            /*reset after modify*/
            freeTree();
            keywordsAnalysis();
        }
        else if (choice == 5)
        {
            break;
        }
        else
        {
            printf("Please enter only number 1 to 5 !\n");
        }
    }
    printf("Goodbye!\n");
    return 0;
}
