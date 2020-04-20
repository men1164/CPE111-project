 Topic: Emotion-Based Song Recommender
 Group: Runtime Error
 
 Done:
 - Analyse the mood each songs
 - Songs and moods sample dataset
 - Linked List of Mood
 - Search songs by Mood (Display songs name only)
 - Sorted Binary Tree of Songs
 - Display All songs (using traversal)
 - Modify mood and keyword.
 

Doing:
- Search songs by title, user type the whole songs name (input exactly matched song name only)


To Do:
- Create the function for choose a songs to display lyrics from all the result list
- Some Detail error checking (ex.user input wrong choice)
- Thinking about particular matched in search songs by title.


QUESTION & ISSUE:
- How to do the particular searching songs by title using tree traversal? (Or you recommend to search directly from text file?)
- (ISSUE) When user type the correct whole song's name in search songs by title, the traversal found only one song, 'Crying Over You'. The other songs not found, don't know why. How can I fix this?
- (ISSUE) Can't free the tree when user finished modify mood for make the mood analysis again, got a core dumped. Don't know how to fix. When analysis again, song list wil be duplicate.
- (ISSUE) Don't know how to do with the songs that no moods (some songs in sample data can't analyse mood because found keywords of each mood less than 5 words)
