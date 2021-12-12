# Makefile for Project Group RuntimeError

ifeq ($(OSTYPE),WINDOWS)
	EXECEXT =.exe
	COMP	=__MINGCC__
	PLATFORM	=mingw
else
	EXECEXT =
	COMP	=__GCC__
	PLATFORM	=linux
endif

EXECUTABLES= main$(EXECEXT)

all : $(EXECUTABLES)

main.o :	main.c analyzeMood.h sortedBinaryTree.h linkedListMood.h
	gcc -c main.c

analyzeMood.o : analyzeMood.c analyzeMood.h sortedBinaryTree.h linkedListMood.h
	gcc -c analyzeMood.c

sortedBinaryTree.o :	sortedBinaryTree.c sortedBinaryTree.h analyzeMood.h
	gcc -c sortedBinaryTree.c

linkedListMood.o :	linkedListMood.c linkedListMood.h analyzeMood.h
	gcc -c linkedListMood.c

modifyMood.o :	modifyMood.c modifyMood.h analyzeMood.h
	gcc -c modifyMood.c

main$(EXECEXT) : main.o analyzeMood.o sortedBinaryTree.o linkedListMood.o modifyMood.o
	gcc -o main$(EXECEXT) main.o analyzeMood.o sortedBinaryTree.o linkedListMood.o modifyMood.o

clean	: 
	-rm *.o
	-rm $(EXECUTABLES) 
