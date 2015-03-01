/**
*\file list.c
*\brief Modelisation of a chained list
*\version 1.0
*\author Antoine GENOT
*\date 01 march 2015
*/

#include <stdio.h>
#include <stdlib.h>
#include "list.h"

nodeList * newNodeList(char *f, char *fn, int l, void *a, nodeList *n){
	nodeList * nouv = (nodeList*) malloc(sizeof(nodeList));
	if(nouv == NULL) return NULL;
	nouv->file = f;
	nouv->function = fn;
	nouv->line = l;
	nouv->address = a;
	nouv->next = n;
	return nouv;
}

/****************************/
/******** GROUPE 1 **********/
/****************************/
void printList(list * l){
	nodeList * tamp = l->current;
	printf("***** List : ");
	setOnFirst(l);
	while(l->current != NULL){
		printf("%d ",getCurrentAddress(l));
		next(l);
	}
	//REMETTRE CURRENT COMME AU DEPART
	l->current = tamp;
	printf("\n");
}

void initList(list * l){ l->first = l->current = l->last = NULL; }
int empty(list * l){ return l->first == NULL; }
int first(list * l){ return l->first == l->current; }
int last(list * l){ return l->last == l->current; }
int outOfList(list * l){ return l->current == NULL; }

void setOnFirst(list * l){ l->current = l->first; }
void setOnLast(list * l){ l->current = l->last; }
void next(list * l){ l->current = l->current->next; }
void * getCurrentAddress(list * l){ return l->current->address; }

/****************************/
/******** GROUPE 2 **********/
/****************************/
int countElement(list * l){
	nodeList * tamp;
	int counter = 0;
	if (empty(l)){
		return counter;
	}//if
	tamp = l->current;
	setOnFirst(l);
	while(!outOfList(l)){
		counter++;
		next(l);
	}
	l->current = tamp;
	return counter;
}

int insertFirst(list * l, char * f, char * fn, int ln, void * a){
	nodeList * nouv;
	nouv = newNodeList(f, fn, ln, a, l->first);
	if(nouv == NULL)
		return 0;
	if(empty(l))
		l->last = l->current = nouv;
	l->first = nouv;
	return 1;
}

int insertLast(list * l, char * f, char * fn, int ln, void * a){
	nodeList * nouv;
	nouv = newNodeList(f, fn, ln, a, NULL);
	if(nouv == NULL)
		return 0;
	if(empty(l))
		l->first = l->current = nouv;
	l->last->next = nouv;
	l->last = nouv;
	return 1;
}
int insertAfterCurrent(list * l, char * f, char * fn, int ln, void * a){
	nodeList * nouv;
	nouv = newNodeList(f, fn, ln, a, l->current->next);
	if(nouv == NULL)
		return 0;
	if(empty(l)) {
		l->first = l->current = l->last = nouv;
		return 1;
	}
	if(l->first == l->last) l->last = nouv;
	l->current->next = nouv;
	return 1;
}

int insertSort(list * l, char * f, char * fn, int ln, void * a){
	if(empty(l)){
		insertFirst(l, f, fn, ln, a);
		return 1;
	}
	if(l->first == l->last){
		if(l->current->line < ln){
			return insertAfterCurrent(l, f, fn, ln, a);
		}
		return insertFirst(l, f, fn, ln, a);
	}
	setOnFirst(l);
	if(l->current->line > ln) return insertFirst(l, f, fn, ln, a);
	if(l->last->line < ln) return insertLast(l, f, fn, ln, a);
	while(l->current->next != NULL){
		if(l->current->next->line >= ln) return insertAfterCurrent(l, f, fn, ln, a);
		next(l);
	}
}

/****************************/
/******** GROUPE 3 **********/
/****************************/
int find(list * l, void * a){
	if (empty(l)){
		return 0;
	}//if
	setOnFirst(l);
	while(!outOfList(l)){
		if(l->current->address == a) return 1;
		next(l);
	}
	return 0;
}

int deleteFirst(list * l){
	nodeList * tamp;
	if(empty(l)) return -1;
	if(l->first == l->last){
		free(l->first);
		initList(l);
		return 0;
	}
	tamp = l->first;
	if(first(l)) next(l);
	l->first = l->first->next;
	free(tamp);
	return 1;
}

int deleteLast(list * l){
	nodeList * tamp;
	if(empty(l)) return -1;
	if(l->first == l->last){
		free(l->last);
		initList(l);
		return 0;
	}
	tamp = l->last;
	if(last(l)) setOnFirst(l);
	while(l->current->next != l->last) next(l);
	l->current->next = NULL;
	l->last = l->current;
	free(tamp);
	return 1;
}

int deleteCurrent(list * l){
	nodeList * tamp;
	if(empty(l)) return 0;
	if(first(l)){ deleteFirst(l); return 1; }
	if(last(l)){ deleteLast(l); return 1; }
	tamp = l->current;
	setOnFirst(l);
	while(l->current->next != tamp) next(l);
	l->current->next = tamp->next;
	next(l);
	free(tamp);
	return 1;
}

void deleteValue(list * l, void * a){
	if(find(l,a)){
		if(!deleteCurrent(l)) printf("Pb in function deleteCurrent");
	}
}
