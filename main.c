/*
 * Created by Krittin Srithong (Pong) 62070503402
 * Kittipol Neamprasertporn (Dome) 62070503404
 * Thanasit Suwanposri (Men) 62070503414
 * and Wagee Jr. Nanta Aree (Zor) 62070503445
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "sortedBinaryTree.h"
#include "analyzeMood.h"
#include "linkedListMood.h"
#include "modifyMood.h"


/* To free all songs name that allocate memory */
void freeSongsName(int songsCount, char **songsName)
{
    int i;
    for (i=0; i<songsCount; i++)
    {
        free(songsName[i]);
    }
    free(songsName);
}


/*
 * Argument
 *  - moodPosition      for display mood name if found the match position.
 *
 * This function use to display mood name that its position match to moodPosition.
 */
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

/*
 * Argument
 * - pSong      to get the data of songs for realize the mood.
 *
 * This function use for loop to realize any mood
 * in this song, then call the printMood() if found.
 */
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


/*
 * Argument
 *  - songCount     for checking error with the choice that user input.
 *  - **songName    to get all of the songs name for display.
 *
 * This function will let user input the song choice
 * to display the lyrics and mood in that song.
 * To display the mood, it will call RealizeMood() to get
 * the mood name.
 */
void selectSongUI(int songsCount, char **songsName)
{
    char stringInput[READ];
    char folder[64];
    int inputSongNumber = -1;
    FILE * pLyrics = NULL;
    SONG_T *pResult = NULL;
    char decision[8];
    
    
    while(1)
    {
        inputSongNumber = -1;
        printf("Enter song number: ");
        fgets(stringInput,sizeof(stringInput),stdin);
        sscanf(stringInput,"%d",&inputSongNumber);
        
        if((inputSongNumber > songsCount-1) || (inputSongNumber <= 0))
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
            
            sprintf(folder, "Lyrics/%s",pResult->fileName);
            pLyrics = fopen(folder,"r");
            memset(stringInput, 0, sizeof(stringInput));
            
            /* check if it have original lowercase title */
            if (pResult->lowerCaseMark == 1)
            {
                printf("\n*************************************");
                printf("\nHere's a lyrics of '%s'.\n",pResult->originalName);
            }
            else
            {
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
            
            while((strcasecmp(decision, "No") != 0)  && (strcasecmp(decision, "Yes") != 0))
            {
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
                else if(strcasecmp(decision, "Yes") != 0)
                {
                    printf("\nPlease input only 'yes' or 'no'\n");
                }
            }
            if(strcasecmp(decision, "No") == 0)
            {
                break;
            }
        }
    }
    freeSongsName(songsCount,songsName);
}


/* Use to display all the song lists directly
 * from the text file.
 * And allocate memory to keep all the songs' name.
 */
void displayAllSongsUI()
{
    char str[READ];
    char **songsName;
    char dummy[32];
    int i;
    FILE * pSongLists = NULL;
    int songsCount = 0;

    pSongLists = fopen("Lyrics/songList.txt","r");
    if (pSongLists == NULL)
    {
        printf("Eror! - Can't open the songList file.\n");
        exit(2);
    }
    songsCount = songsListCount();
    songsCount++; /* for [0] terminator */
    songsName = (char **) calloc(songsCount, sizeof(char*));
    
    for (i=0; i<songsCount; i++)
    {
        songsName[i] = (char *) calloc(READ, sizeof(char));
    }
    
    printf("\n*************************************");
    printf("\nHere are all songs list.\n");
    printf("*************************************\n");

    i = 0;
    while(fgets(str,sizeof(str),pSongLists) != NULL)
    {
        /* for checking the empty line */
        if (str[0] != '\n')
        {
            sscanf(str, "%s %[^\n]",dummy, songsName[i]);
            printf("%d : %s\n",i+1,songsName[i]);
            i++;
        }
    }
    printf("\n\n");
    fclose(pSongLists);
    selectSongUI(songsCount,songsName);
}

/*
 * Argument
 *  - songName[]    to receive the new song name.
 *  - fileName[]    to receive the text file name.
 * This function will let user input
 * lyrics of the songs, line by line.
 * Until user type 'done' to finished input.
 */
void addLyrics(char songName[], char fileName[])
{
    FILE* pLyrics = NULL;
    char lyrics[READ];
    char read[READ];
    char songDirectory[32];
    
    printf("\n*************************************");
    printf("\nHow to input the lyrics.\n");
    printf("\t1. Input lyrics line by line or copy/paste them from google.\n");
    printf("\t2. Hit return, then type 'done' for finished input lyrics.\n");
    printf("*************************************\n\n");
    
    sprintf(songDirectory,"Lyrics/%s",fileName);
    pLyrics = fopen(songDirectory,"w");
    if (pLyrics == NULL)
    {
        printf("Error! - Can't write the new file into Lyrics directory.\n");
        exit(2);
    }
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

/* This function will open the songsList.txt as append mode
 * to let user add a new song name.
 * Then call the addLyrics function.
 */
void addNewSong()
{
    FILE* pSongList = NULL;
    char newSongName[32];
    char stringInput[64];
    char newFileName[32];
    char fileName[32];
    int i;
    
    pSongList = fopen("Lyrics/songList.txt","a");
    if(pSongList == NULL)
    {
        printf("Error! - Can't open the songList file.\n");
        exit(3);
    }
    
    printf("Enter new song name: ");
    fgets(stringInput,sizeof(stringInput),stdin);
    sscanf(stringInput,"%[^\n]",newSongName);

    memset(stringInput, 0, sizeof(stringInput));
    printf("Enter the file name to hold '%s' lyrics (no spacebar or any special characters): ",newSongName);
    fgets(stringInput, sizeof(stringInput), stdin);
    sscanf(stringInput, "%s",newFileName);
    
    for (i=0; i<strlen(newFileName); i++)
    {
        if (isupper(newFileName[i]) != 0)
        {
            newFileName[i] = tolower(newFileName[i]);
        }
    }
    
    sprintf(fileName, "%s.txt",newFileName);
    fprintf(pSongList,"%s %s\n",fileName,newSongName);
    fclose(pSongList);
    
    addLyrics(newSongName,fileName);
}


/* displayMoodUI function is use as
 * user interface for display the mood,
 * then ask user to search songs by moods or not.
 *
 * If want, it will call searchByMood() in linkedListMood.c
 * to display any songs that exists in that mood.
 */
void displayMoodUI()
{
    FILE *pMoodlist = NULL;
    char read[READ];
    char decision[8];
    int i = 1;
    int moodChoice = -1;
    int countMood = 0;
    pMoodlist = fopen("Mood/moodList.txt", "r");
    if (pMoodlist == NULL)
    {
        printf("Error! - Can't read the mood list file.\n");
        exit(4);
    }
    
    printf("\n***** Mood List *****\n");
    while (fgets(read, sizeof(read), pMoodlist) != NULL)
    {
        printf("%d: %s\n",i,read);
        i++;
        countMood++;
    }
    
    while((strcasecmp(decision, "No") != 0)  && (strcasecmp(decision, "Yes") != 0))
    {
        memset(read, 0, sizeof(read));
        memset(decision, 0, sizeof(decision));
        printf("Do you want to search songs by mood? (yes|no): ");
        fgets(read, sizeof(read), stdin);
        sscanf(read, "%s",decision);
        if (strcasecmp(decision, "yes") == 0)
        {
            while((moodChoice > countMood) || (moodChoice < 1))
            {
                memset(read, 0, sizeof(read));
                printf("Enter the number of mood that you want : ");
                fgets(read, sizeof(read), stdin);
                sscanf(read, "%d",&moodChoice);
                if((moodChoice > countMood) || (moodChoice < 1))
                {
                    printf("\n");
                    printf("Please input valid mood.\n");
                    printf("\n");
                }
                else
                {
                   printf("\n");
                   searchByMood(moodChoice-1);
                   printf("\n");
                }
            }
        }
        else if(strcasecmp(decision, "no") != 0)
        {
            printf("\nplease input only 'yes' or 'no'\n\n");
        }
        else
        {
            printf("\nBack to Main Menu\n");
            break;
        }
    }
    fclose(pMoodlist);
}


/* Main function
 *
 * Using for main menu interface and let
 * user select what function user want to do.
 */
int main(int argc, const char * argv[])
{
    char input[10];
    int choice;
    
    /* call this function to analyze the song */
    keywordsAnalysis();
    
    printf("\n\n************************************************************\n\n");
    printf("Welcome to Emotion-based Song Recommender!!\n\n");
    printf("************************************************************\n\n");
    
    while (1)
    {
        choice = -1;
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
    /* free everything before close the program */
    freeTree();
    initializeMoodArray();
    printf("Goodbye!\n");
    return 0;
}
