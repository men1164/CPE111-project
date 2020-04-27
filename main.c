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

int readSongName()
{
    char stringInput[128];
    char str[READ];

    int line = 1;

    FILE * pSongLists = NULL;

    pSongLists = fopen("Lyrics/songList.txt","r");
    while(fgets(str,sizeof(stringInput),pSongLists) != NULL)
    {
        printf("%d : %s",line,str);
        line++;
    }
    printf("\n\n");
    fclose(pSongLists);
    
    return line;
}

void displaySongUI()
{
    char stringInput[READ];
    char folder[64];
    int inputSongNumber;
    int songCount;
    int returnCount;
    FILE * pSongLists = NULL;
    FILE * pLyrics = NULL;
    char song[64];
    
    
    while(1)
    {
        returnCount = readSongName();
        returnCount--;
        printf("Enter song number (negative number to stop): ");
        fgets(stringInput,sizeof(stringInput),stdin);
        sscanf(stringInput,"%d",&inputSongNumber);
        
        if((inputSongNumber > returnCount) || (inputSongNumber == 0))
        {
            printf("You entered the invalid song number.\n");
        }
        else if (inputSongNumber < 0)
        {
            break;
        }
        else
        {
            memset(stringInput, 0, sizeof(stringInput));
            pSongLists = fopen("Lyrics/songList.txt","r");
            songCount = 1;
            while(fgets(stringInput,sizeof(stringInput),pSongLists) != NULL)
            {
                if(songCount == inputSongNumber)
                {
                    sscanf(stringInput,"%[^\n]",song);
                    break;
                }
                songCount++;
            }
            fclose(pSongLists);
            
            sprintf(folder,"Lyrics/%s.txt",song);
            pLyrics = fopen(folder,"r");
            memset(stringInput, 0, sizeof(stringInput));
            
            printf("\n*************************************");
            printf("\nHere's a lyrics of '%s'.\n",song);
            printf("*************************************\n");
            while(fgets(stringInput,sizeof(stringInput),pLyrics) != NULL)
            {
                printf("%s",stringInput);
            }
            printf("\n\n");
            fclose(pLyrics);
        }
    }
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
    printf("\t2. Hit return, then type 'done' for finished input lytics.\n");
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
        printf("Error! - File cannot open.\n");
        exit(0);
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
        exit(1);
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
        
        searchByMood(moodChoice-1);
    }
    else
    {
        printf("\nBack to Main Menu\n");
    }
}

int main(int argc, const char * argv[])
{
    char input[10];
    int choice;
    
    /*call the function to analyze the song and create hash table*/
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
            displaySongUI();
        }
        else if (choice == 2)
        {
            displayMoodUI();
        }
        else if (choice == 3)
        {
            addNewSong();
            
            /*reset after added a new song*/
            freeTree();
            keywordsAnalysis();
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
