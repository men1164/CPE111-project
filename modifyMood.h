/*
 * Created by Wagee Jr. Nanta Aree (Zor) 62070503445
 * modify mood and keywords
 */

#ifndef modifyMood_h
#define modifyMood_h

#define MAXKEYWORDS 40

/*
 * Main menu of modify mood
 */
void modifyMood();

/* adding new mood to mood list
 *
 */
void addMood();

/* delete mood from mood list
 *
 */
void deleteMood();

/* adjusting keyword in each mood
 *   - add keyword
 *   - delete keyword
 */
void adjustKeyword();

/* adding new keywords into selected mood
 *
 */
void addKeyword(char mood[]);

/* deleting keyword in selected mood
 *
 */
void deleteKeyword(char mood[]);

#endif /* modifyMood_h */
