/**
*\file list.h
*\brief Modelisation of a chained list
*\version 1.0
*\author Antoine GENOT
*\date 01 march 2015
*/

#ifndef LIST_H
#define LIST_H
typedef struct nodeList{
	char * file;
	char * function;
	int line;
	void * address;
	struct nodeList * next;
}nodeList;

typedef struct{
	nodeList * first;
	nodeList * current;
	nodeList * last;
}list;

nodeList * newNodeList(char *f, char *fn, int l, void *a, nodeList *n);

/******** GROUPE 1 **********/
void printList(list * l);

void initList(list * l);
int empty(list * l);
int first(list * l);
int last(list * l);
int outOfList(list * l);

void setOnFirst(list * l);
void setOnLast(list * l);
void next(list * l);
void * getCurrentAddress(list * l);

/******** GROUPE 2 **********/
int countElement(list * l);
int insertFirst(list * l, char * f, char * fn, int ln, void * a);
int insertLast(list * l, char * f, char * fn, int ln, void * a);
int insertAfterCurrent(list * l, char * f, char * fn, int ln, void * a);
int insertSort(list * l, char * f, char * fn, int ln, void * a);

/******** GROUPE 3 **********/
int find(list * l, void * a);
int deleteFirst(list * l);
int deleteLast(list * l);
int deleteCurrent(list * l);
void deleteValue(list * l, void * a);

#endif //LIST_H
