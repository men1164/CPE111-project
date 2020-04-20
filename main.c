/*
 * Created by Krittin Srithong (Pong) 62070503402
 * and Kittipol Neamprasertporn (Dome) 62070503404
 *
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
        exit(0);
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
        printf("\t1) Display all songs.\n");
        printf("\t2) Display all moods and Search songs by mood.\n");
        printf("\t3) Search songs by title.\n");
        printf("\t4) Modify Mood.\n");
        printf("\t5) Exit the program.\n");

        printf("What do you want to do? : ");
        fgets(input, sizeof(input), stdin);
        sscanf(input, "%d", &choice);

        if (choice == 1)
        {
            printAll();
        }
        else if (choice == 2)
        {
            displayMoodUI();
        }
        else if (choice == 3)
        {
            searchByTitleUI();
        }
        else if (choice == 4)
        {
            modifyMood();
            
            /* issue: got core dumped when called freeTree();
             */
            
            //freeTree();
            
            /* issue: can't free tree. When analysis again, the song list will be duplicate */
            keywordsAnalysis(); /*reset after modify*/
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
