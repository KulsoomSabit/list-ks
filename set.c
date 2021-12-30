//Kulsoom Sabit
//coen12
//An Amazing Sort of Assigment

#include "set.h"
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "list.h"

struct set{
   int length;
   int count;
   int (*compare)();
   void ** data; 
   void ** list;
   unsigned (*hash)();
};

typedef struct set SET;

//function to create a set and allocating data to our list 
//setting our counter, hash, and compare to  be used later 
//BIG O: O(1)
SET *createSet(int maxElts, int (*compare)(), unsigned (*hash)()){
   SET *sp = malloc(sizeof(SET));
   assert(sp!=NULL);
   sp->count = 0;
   sp->length = maxElts;  
   sp->data = malloc(sizeof(LIST*) * maxElts);
   int i;
   for (i = 0; i < sp->length; i++){
	sp->data[i] = createlist(compare);}
   sp->compare = compare;
   sp->hash = hash;
   return sp;}

//function to search for a specific value 
//set locn to our hash table 
//calls finditem and passes our data and the elements 
//BIG O: O(1)
static int search(SET *sp, char *elt, bool *found){
   assert (sp != NULL);
   assert (elt != NULL);
   unsigned locn = (*sp->hash)(elt) % sp->length;
   *found = false;
   void * data = findItem(sp->data[locn], elt);
   if(data != NULL){
	*found = true;}
   return locn;}

//funtion to count the number of items in our list and return it
//BIG O: O(1)
int numElements(SET *sp){
   assert(sp != NULL);
   return sp->count; 
}

//function to assign and add an element 
//big O: O(1)
void addElement(SET *sp, void *elt){
   assert(sp != NULL);
   assert(elt != NULL);
   bool found;
   int locn;
   locn = search(sp, elt, &found);
   if(!found){
   addLast(sp->data[locn], elt);}
   sp->count++;
 }  

//function to destroy the list and free up memory
//BIG O: O(n)
void destroySet(SET *sp){
   int i;
   assert(sp != NULL);
   for(i=0; i < sp->length; i++){
        destroyList(sp->data[i]);}
   free(sp->data);
   free(sp);}


//function to return and remove an element in the list
//goes through the size of sp and calls search to  find the element 
//once its found then remove item is called to remove it 
//reassigns the deleting nodes poointers and then frees the del node
//BIG O: O(n)
void removeElement(SET *sp, void *elt){
   assert(sp->length > 0);
   bool found;
   int locn;
   locn = search(sp, elt, &found);
   assert(found);
   removeItem(sp->data[locn], elt);
   sp->count--;
 }


//function to allocate and return a list of items 
//calls getitems to put the elements into the array we make
//BIG O: O(n^2)
void *getElements(SET *sp){
   assert(sp != NULL);
   void ** elements = malloc(sizeof(void *) *sp->count);
   assert(elements != NULL);
   int k = 0;
   int s = 0;
   while( k < sp-> count && s < sp -> length){
	void *index = getItems(sp->list[s]);
	memcpy(elements + k, index, sizeof(void*) * numItems(sp->list[s]));
	k += numItems(sp -> list[s]);
	s++;}
   return elements;}


//function to find an element in sp
//search is called to find the element
//once its true that its found then the location of the element is returned
//BIG O: O(n)
void *findElement(SET *sp, void *elt){
   assert(sp != NULL);
   assert(elt != NULL);
   int locn;
   bool found;
   locn = search(sp, elt, &found);
   if (found == true){
        return sp->data[locn];}
   return NULL;
}
