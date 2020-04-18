//
//  sortedBinaryTree.h
//  project2
//
//  Created by Thanasit Suwanposri on 17/4/2563 BE.
//  Copyright © 2563 Thanasit Suwanposri. All rights reserved.
//

#ifndef sortedBinaryTree_h
#define sortedBinaryTree_h

#include "analyzeMood.h"

void insertNode(SONG_T *pCurrent, SONG_T *pNew);
SONG_T *searchByTitle(SONG_T *pCurrent, char searchSong[]);
void recursivePrint(SONG_T *pCurrent);
void checkRoot(SONG_T *song);
void printAll();


#endif /* sortedBinaryTree_h */
