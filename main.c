/*************************************
 *
 * USER INTERFACE ONLY
 *
 ************************************/



#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "analyzeMood.h"
#include "abstractHashTable.h"

#define BUCKET_COUNT 1003

/* Based on code by Sally Goldin from [hashTester.c]
 * Used with permission.
 *
 * Robust hash function that uses bitwise operations to
 * modify string values. Adapted from Kyle Loudon,
 * "Mastering Algorithms with C"
 */
unsigned int bitwiseOpHash(char* key)
{
    unsigned int result = 0;
    unsigned int tmp = 0;
    int size = hashTableSize();
    int i = 0;
    for (i = 0; i < strlen(key); i++)
    {
        /* shift up four bits then add in next char */
        result = (result << 4) + key[i];
        if (tmp == (result & 0xf0000000))  /* if high bit is set */
        {
            /* XOR result with down shifted tmp */
            result = result ^ (tmp >> 24);
            /* then XOR with tmp itself */
            result = result ^ tmp;
        }
    }
    result = result % size;   /* make it fit in the table size */
    return result;
}

void modifyUI()
{

}

void searchViaMoodUI()
{
    char key[4] = "sad"; /*for testing*/
    SONG_T **found = NULL;
    char read[READ];
    FILE *pMoodlist = NULL;
    int i;
    int count;
    
//    pMoodlist = fopen("Mood/moodList.txt", "r");
//    if (pMoodlist == NULL) {
//        printf("Error! - Can't open the mood list file for searching.\n");
//        exit(0);
//    }
//
//    printf("\nPlease choose the mood that you want.\n");
//
//    while (fgets(read, sizeof(read), pMoodlist) != NULL)
//    {
//
//    }

    found = hashTableMultiLookup(key, &count);
    if (found != NULL)
    {
        for (i=0; i<count; i++) {
            printf("Songs: %s\n\n",found[i]->songName);
        }
    }
    free(found);
}

void displayMoodUI()
{

}

void displaySongsUI()
{

}

int main(int argc, const char * argv[])
{

    char input[10];
    int choice;
    int hashInitReturn;

    hashInitReturn = hashTableInit(BUCKET_COUNT, &bitwiseOpHash);
    if (hashInitReturn == 0)
    {
        printf("Error! - Can't create the hash table.\n");
    }
    else
    {
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
            printf("\t3) Search songs via emotion.\n");
            printf("\t4) Modify Emotion.\n");
            printf("\t5) Exit the program,\n");

            printf("What do you want to do? : ");
            fgets(input, sizeof(input), stdin);
            sscanf(input, "%d", &choice);

            if (choice == 1)
            {
                displaySongsUI();
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
                modifyUI();
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
    }
    return 0;
}
