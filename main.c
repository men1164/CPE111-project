/*************************************
 *
 * USER INTERFACE ONLY
 *
 ************************************/



#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "sortedBinaryTree.h"
#include "analyzeMood.h"
#include "linkedListMood.h"

void modifyUI()
{

}

void searchViaMoodUI()
{
    FILE *pMoodlist = NULL;
    char read[READ];
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
    
    printf("What mood do you want? : ");
    fgets(read, sizeof(read), stdin);
    sscanf(read, "%d",&moodChoice);
    moodChoice = moodChoice - 1;
    
    searchByMood(moodChoice);
}

void displayMoodUI()
{

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
        printf("\t2) Display all moods.\n");
        printf("\t3) Search songs by mood.\n");
        printf("\t4) Search songs by title.\n");
        printf("\t5) Modify Mood.\n");
        printf("\t6) Exit the program,\n");

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
            searchViaMoodUI();
        }
        else if (choice == 4)
        {
            
        }
        else if (choice == 5)
        {
            modifyUI();
        }
        else if (choice == 6)
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
