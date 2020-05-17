/*
 * Created by Kittipol Neamprasertporn (Dome) 62070503404
 * and Thanasit Suwanposri (Men) 62070503414
 *
 *
 * Based on Lab 3 code.
 * This file use linked list to store and searching songs by mood.
 */


#ifndef linkedListMood_h
#define linkedListMood_h

#include "analyzeMood.h"


/*
 * This function is for set all of head and tail to NULL.
 */
void initializeMoodArray();

/*
 * Argument
 *  - song      songs' structure to keep into an item in linked list.
 * This function use for check the songMood, if 1, put into a linked list
 * of that mood.
 */
void linkedListMood(SONG_T *song);

/*
 * Argument
 *  - moodPosition      to set the index of the array list.
 * This function will display the songs in that mood,
 * then ask user that they want to display lyrics or not.
 */
void searchByMood(int moodPosition);

/*
 * Argument
 *  - moodPosition      to set the index of the array list.
 *  - songFoundInMood   to check error of input from user.
 * This function will let user input the number of song that user
 * want to display the lyrics.
 */
void selectSongFromMood(int moodPosition, int songFoundInMood);

#endif /* linkedListMood_h */
