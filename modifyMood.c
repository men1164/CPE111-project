/*
 * Created by Wagee Jr. Nanta Aree (Zor) 62070503445
 * modify mood and keywords
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "modifyMood.h"
#include "analyzeMood.h" /*include MAXMOODS define value*/

void modifyMood()
{
    char input[32];
    int ans = 0;
    
    while(1)
    {
        ans = 0;
        printf("======================================\n");
        printf("      What do you want to do?\n");
        printf("--------------------------------------\n");
        printf("        1 - add mood\n");
        printf("        2 - delete mood\n");
        printf("        3 - adjust keyword\n");
        printf("        4 - back to main menu\n");
        printf("  Ans: ");
        fgets(input, sizeof(input), stdin);
        sscanf(input, "%d", &ans);

        if(ans == 1)
        {
            printf("======================================\n");
            addMood();
        }
        else if(ans == 2)
        {
            printf("======================================\n");
            deleteMood();
        }
        else if(ans == 3)
        {
            printf("======================================\n");
            adjustKeyword();
        }
        else if(ans == 4)
        {
            printf("======================================\n");
            break;
        }
        else
        {
            printf("------------------------------\n");
            printf("|       Invalid Number       |\n");
            printf("------------------------------\n\n");
        }
    }
}


/* adding new mood to mood list
 *
*/
void addMood()
{
    char lines[32];
    char moodLists[MAXMOODS][32];     /* for keeping all mood list */
    char newMood[32];                 /* keep new mood from user input */
    char newMoodFile[40] = "Mood/";   /* for keeping file name of new mood */
    int countMood = 0;                /* keep the amount of mood list  */
    int i = 0;                        /* for start the loop */
    int checkExist = 1;               /* check if the mood that user input is already existes or not */
    long int length = 0;                   /* count length of new mood */
    
    FILE* pIn = NULL;     /* to read mood list */
    FILE* pOut = NULL;    /* to add mood list */
    FILE* pNew = NULL;    /* to build new mood file (for keeping keywords) */
    
    pIn = fopen("Mood/moodList.txt","r");
    pOut = fopen("Mood/moodList.txt","a");
    
    printf("\n");
    
    if((pIn == NULL) || (pOut == NULL))
    {
        printf(" Cannot open moodList\n");
        exit(0);
    }
     
    while(fgets(lines, sizeof(lines), pIn) != NULL)  /* count mood and keep in array */
    {
        sscanf(lines, "%s", moodLists[countMood]);
        countMood++;
    }
    
    if(countMood > MAXMOODS-1) /* in case mood is more than 10 */
    {
        printf("--------------------------------\n");
        printf("|   you cannot add more mood   |\n");
        printf("--------------------------------\n");
    }
    else
    {
        //printf("--------------------------------\n");
        printf("  -here's the existed mood-\n");
        printf("--------------------------------\n");
        for(i=0;i<countMood;i++)
        {
            printf("   %d. %s\n", i+1,moodLists[i]);
        }
        length = 0;
        memset(newMood, 0, sizeof(newMood));
        printf("What mood you want to add? ");
        fgets(lines, sizeof(lines), stdin);
        sscanf(lines, "%s", newMood);
        length = strlen(newMood);
         
        //printf("lenght = %d\n", length);
         
        if(length == 0)
        {
            printf("---------------------------------\n");
            printf("|   Please input something      |\n");
            printf("---------------------------------\n");
        }
        else
        {
            for(i=0;i<countMood;i++)
            {
                if(strcasecmp(moodLists[i],newMood) == 0) /* in case find the same word in moodlist */
                {
                    printf("------------------------------------\n");
                    printf("|   This mood is already existed   |\n");
                    printf("------------------------------------\n");
                    checkExist = 0;
                    break;
                }
            }
            if(checkExist == 1)
            {
                countMood++;
                sscanf(newMood, "%s", moodLists[countMood-1]);
                fprintf(pOut, "%s\n", moodLists[countMood-1]);  /* add mood in mood list */
                printf("---------------------------------\n");
                printf("|         -Mood updated-        |\n");
                printf("---------------------------------\n");
                for(i=0;i<countMood;i++)
                {
                    printf("   %d. %s\n", i+1,moodLists[i]);
                }

                strcat(newMood, ".txt");
                strcat(newMoodFile, newMood);
             
                /* create file for mood */
                pNew = fopen(newMoodFile, "w");
                if(pNew == NULL)
                {
                    printf(" Cannot create new mood file\n");
                    exit(1);
                }
                fclose(pNew);
            }
        }
    }
    fclose(pIn);
    fclose(pOut);
    printf("\n");
}


/* delete mood from mood list
 *
 */
void deleteMood()
{
    char lines[32];
    char moodLists[MAXMOODS][32];   /* for keeping all mood list */
    char ans[10] = "cat";           /* keep answer if user really want to delete */
    int countMood = 0;              /* keep the amount of mood list  */
    int i = 0;                      /* for start the loop */
    int deleteNum = 0;              /* keep what user want to delete */
    
    FILE* pIn = NULL;             /* to read mood list */
    FILE* pOut = NULL;            /* to rewrite mood list */
    
    pIn = fopen("Mood/moodList.txt","r");
    
    printf("\n");
    
    if(pIn == NULL )
    {
        printf("----------------------------------\n");
        printf("|      Cannot open moodList      |\n");
        printf("----------------------------------\n");
        exit(2);
    }
    
    while(fgets(lines, sizeof(lines), pIn) != NULL)
    {
        sscanf(lines, "%s", moodLists[countMood]);
        countMood++;
    }
        
    printf("   -here's the existed mood-\n");
    printf("----------------------------------\n");
    for(i=0;i<countMood;i++)
    {
        printf("   %d. %s\n", i+1,moodLists[i]);
    }

    while((deleteNum < 1) || (deleteNum > countMood))
    {
        printf("What mood you want to delete? (type the number)");
        fgets(lines, sizeof(lines), stdin);
        sscanf(lines, "%d", &deleteNum);
        
        if((deleteNum < 1) || (deleteNum > countMood)) /* make sure user type existed number */
        {
            printf("-----------------------------------\n");
            printf("|   please input existed number   |\n");
            printf("-----------------------------------\n");
        }
    }
    
    while((strcasecmp(ans,"no") != 0) && (strcasecmp(ans,"yes") != 0))  /* make sure user want to delete */
    {
        printf("Are you sure deleting '%s' Mood(Yes/No)  : ", moodLists[deleteNum-1]);
        fgets(lines, sizeof(lines), stdin);
        sscanf(lines, "%s", ans);
        
        if((strcasecmp(ans,"yes") != 0) && (strcasecmp(ans,"no") != 0))  /* incase user types neither yes nor no */
        {
            printf("-----------------------------------\n");
            printf("| please input 'yes' or 'no' only |\n");
            printf("-----------------------------------\n");
        }
        else if(strcasecmp(ans,"no") == 0)  /* incase user types no */
        {
            printf("---------------------------------\n");
            printf("| No Change -- Delete cancelled |\n");
            printf("---------------------------------\n\n");
        }
        else if(strcasecmp(ans,"yes") == 0)  /* incase user types yes */
        {
            pOut = fopen("Mood/moodList.txt","w");
            if(pIn == NULL )
            {
                printf(" Cannot open moodList\n");
                exit(3);
            }
            
            for(i=0; i<countMood; i++)
            {
                if(i == deleteNum-1)
                {
                    i++;
                }
                if(i<countMood)
                {
                    fprintf(pOut,"%s\n",  moodLists[i]);
                }
            }
            fclose(pOut);
            printf("----------------------\n");
            printf("|    Mood deleted    |\n");
            printf("----------------------\n\n");
        }
    }
    fclose(pIn);
}


/* adjusting keyword in each mood
 *   - add keyword
 *   - delete keyword
 */
void adjustKeyword()
{
    char input[32];
    char moodLists[MAXMOODS][32];    /* for keeping all mood list */
    int ans = 0;                     /* keep answer if user really want to add or delete keyword */
    int countMood = 0;               /* keep the amount of mood list  */
    int choosenMoodNum = -12;        /* keep mood user choose  */
    FILE* pIn = NULL;                /* to read mood list */
    
    pIn = fopen("Mood/moodList.txt","r");
    
    if(pIn == NULL)
    {
        printf("----------------------------------\n");
        printf("|      Cannot open moodList      |\n");
        printf("----------------------------------\n");
        exit(4);
    }
    printf("\n");
    printf("   -here's the existed mood-\n");
    printf("--------------------------------\n");
    while(fgets(input, sizeof(input), pIn) != NULL)
    {
        sscanf(input, "%s", moodLists[countMood]);
        printf("   %d. %s\n",countMood+1, moodLists[countMood]);
        countMood++;
    }
        
    while((choosenMoodNum < 1) || (choosenMoodNum > countMood))  /* make sure user type exist mood */
    {
        printf("what mood that you want to adjust keywords? (type the number) ");
        fgets(input, sizeof(input), stdin);
        sscanf(input, "%d", &choosenMoodNum);
        
        if((choosenMoodNum < 1) || (choosenMoodNum > countMood))
        {
            printf("-----------------------------------\n");
            printf("|   please input existed number   |\n");
            printf("-----------------------------------\n");
        }
    }
    
    while( (ans<1) || (ans>2) )  /* keep asking til user types existed number */
    {
        ans = 0;
        printf("\n---------------------------------------\n");
        printf("  what you want to do with '%s' Mood?\n", moodLists[choosenMoodNum-1]);
        printf("---------------------------------------\n");
        printf("     1.add keywords\n");
        printf("     2.delete keywords\n");
        printf("ans: ");
        fgets(input, sizeof(input), stdin);
        sscanf(input, "%d", &ans);
        
        if( (ans<1) || (ans>2) )
        {
            printf("-------------------------------------\n");
            printf("|    please input existed number    |\n");
            printf("-------------------------------------\n");
        }
    }
        
    if(ans == 1)   /* incase user want to add keywords */
    {
        printf("-------------------------------------\n");
        addKeyword(moodLists[choosenMoodNum-1]);
    }
    else if(ans == 2)    /* incase user want to delete keywords */
    {
        printf("-------------------------------------\n");
        deleteKeyword(moodLists[choosenMoodNum-1]);
    }
}


/* adding new keywords into selected mood
 *
*/
void addKeyword(char mood[])
{
    char input[64];
    char fileName[64] = "Mood/";   /* keep file name */
    char keyword[64];              /* keep exist keyword */
    char newKeyword[64];           /* keep new keyword */
    int countKeywords = 0;         /* count keywords */
    long int length = -2;          /* keep length of keyword */
    int check = 1;                 /* check if keyword is already existed or not */
    FILE* pIn = NULL;              /* to read keyword's mood list */
    FILE* pOut = NULL;             /* to add keyword's mood list */
    
    strcat(mood, ".txt");
    strcat(fileName, mood);
    
    while((length != 0) && (countKeywords<MAXKEYWORDS))
    {
        countKeywords = 0;
        check =1;
        pIn = fopen(fileName,"r");
        if(pIn == NULL)
        {
            printf("-----------------------------------\n");
            printf("|   Cannot open keyword of mood   |\n");
            printf("-----------------------------------\n");
            exit(5);
        }
        
        pOut = fopen(fileName,"a");
        if(pOut == NULL)
        {
            printf("-----------------------------------\n");
            printf("|   Cannot open keyword of mood   |\n");
            printf("-----------------------------------\n");
            exit(6);
        }
            
        memset(newKeyword,0,sizeof(newKeyword));
        printf("what keyword you want to add? (ENTER to stop) ");
        fgets(input, sizeof(input), stdin);
        sscanf(input, "%s", newKeyword);
        length = 0;
        length = strlen(newKeyword);
        
        while(fgets(input,sizeof(input),pIn) != NULL)
        {
            countKeywords++;
            sscanf(input, "%s", keyword);
            if(strcasecmp(newKeyword,keyword) == 0)   /* incase keyword is already existed in keyword's file */
            {
                check = 0;
                printf("----------------------------------------\n");
                printf("|  - this keyword is already existed.  |\n");
                printf("----------------------------------------\n");
            }
        }
        fclose(pIn);
        
        if(countKeywords >= MAXKEYWORDS)  /* incase keywords are more than 40 */
        {
            printf("--------------------------\n");
            printf("|  - Too many keywords.  |\n");
            printf("--------------------------\n");
        }
        else if(check == 1 && length!=0)   /* incase the keyword can be added */
        {
            fprintf(pOut,"%s\n", newKeyword);
            printf("------------------------\n");
            printf("|  -keyword is added.  |\n");
            printf("------------------------\n");
        }
        fclose(pOut);
    }
    printf("--------------------\n");
    printf("|     - DONE -     |\n");
    printf("--------------------\n");
}

/* deleting keyword in selected mood
 *
*/
void deleteKeyword(char mood[])
{
    char lines[64];
    char moodName[64];                   /* keep mood */
    char fileName[64] = "Mood/";         /* keep file name */
    char keywordList[MAXKEYWORDS][64];   /* for keeping all keyword list */
    int countKeyword = 0;                /* count keywords */
    int i = 0;                           /* for starting loops */
    int deleteNum = 1;                   /* keep what user want to delete */
    FILE* pIn = NULL;
    FILE* pOut = NULL;
    
    strcpy(moodName, mood);
    strcat(mood, ".txt");
    strcat(fileName, mood);
    
    pIn = fopen(fileName, "r");
    if(pIn == NULL)
    {
        printf("----------------------------------\n");
        printf("|   Cannot open keyword of mood  |\n");
        printf("----------------------------------\n");
        exit(5);
    }
    while(fgets(lines,sizeof(lines),pIn) != NULL)  /* count keyword and keep in array */
    {
        sscanf(lines, "%s", keywordList[countKeyword]);
        countKeyword++;
    }
    fclose(pIn);
    
    while(countKeyword>0)   /* keep delete until user type negative number  and  there's keyword */
    {
        countKeyword = 0;
        pIn = fopen(fileName, "r");
        if(pIn == NULL)
        {
            printf("-----------------------------------\n");
            printf("|   Cannot open keyword of mood   |\n");
            printf("-----------------------------------\n");
            exit(5);
        }
        while(fgets(lines,sizeof(lines),pIn) != NULL)    /* count keyword and keep in array */
        {
            sscanf(lines, "%s", keywordList[countKeyword]);
            countKeyword++;
        }
        fclose(pIn);

        deleteNum = 0;
        printf("here's all keywords for '%s' Mood\n", moodName);
        for(i=0; i<countKeyword; i++)
        {
            printf("   %d. %s\n", i+1, keywordList[i]);
        }
            
        printf("what word you want to delete (type down the number || type negative numder to stop): ");
        fgets(lines, sizeof(lines), stdin);
        sscanf(lines, "%d", &deleteNum);
        
        if(deleteNum < 0)
        {
            printf("--------------\n");
            printf("|   -DONE-   |\n");
            printf("--------------\n");
            break;
        }
        
        if(deleteNum > countKeyword  || deleteNum < 1) /* incase user input non-existed number */
        {
            printf("-----------------------------------\n");
            printf("|   please input existed number   |\n");
            printf("-----------------------------------\n");
        }
        else if((deleteNum > 0) || (deleteNum <= countKeyword) ) /* delete keyword user input */
        {
            pOut = fopen(fileName, "w");
            if(pOut == NULL)
            {
                printf("----------------------------------\n");
                printf("|   Cannot open keyword of mood  |\n");
                printf("----------------------------------\n");
                exit(6);
            }
            for(i=0; i<countKeyword; i++)  /* rewrite keywords into file exceppt the one user choose */
            {
                if(i == deleteNum-1)
                {
                    i++;
                }
                if(i < countKeyword)
                {
                    fprintf(pOut,"%s\n", keywordList[i]);
                }
            }
            fclose(pOut);
        }
        if((deleteNum > 0) && (countKeyword == 1)) /* incase there's no keyword left */
        {
            countKeyword = 0;
        }
    }
    if(countKeyword == 0)
    {
        printf("---------------------------------------\n");
        printf("|   there's no keyword in this mood   |\n");
        printf("---------------------------------------\n");
    }
    printf("\n");
}
