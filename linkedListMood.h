/*
 * Created by Kittipol Neamprasertporn (Dome) 62070503404
 *
 *
 * Based on Lab 3 code.
 * This file use linked list to store and searching songs by mood.
 */


#ifndef linkedListMood_h
#define linkedListMood_h

#include "analyzeMood.h"

void initualizeMoodArray();
void linkedListMood(SONG_T *song);
void searchByMood(int moodPosition);

#endif /* linkedListMood_h */
