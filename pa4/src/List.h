// List.h - header for List ADT
// Chris Griffis <chdgriff>
// pa4

#include <stdio.h>

#ifndef LIST_H_
#define LIST_H_

typedef struct ListObj* List;

// Constructors-Destructors ---------------------------------------------------
List newList(void);
void freeList(List*);

// Access functions -----------------------------------------------------------
int length(List);
int index(List);
int front(List);
int back(List);
int get(List);
int equals(List, List);

// Manipulation procedures ----------------------------------------------------
void clear(List);
void moveFront(List);
void moveBack(List);
void movePrev(List);
void moveNext(List);
void prepend(List, int);
void append(List, int);
void insertBefore(List, int);
void insertAfter(List, int);
void deleteFront(List);
void deleteBack(List);
void delete(List);

// Other operations -----------------------------------------------------------
void printList(FILE*, List);
List copyList(List);

#endif /* LIST_H_ */
