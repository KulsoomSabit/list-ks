//Kulsoom Sabit 
//coen12 
//An Amazing Sort of Assigment 

#include "list.h"
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>


//create a struct of nodes storing our data, node pointing to the next nodes and previous nodes
struct node {
   void ** data;
   struct node *next;
   struct node *prev;
};


//create a struct of list holding our counter, pointer pointing to the head of the list 
//and our comprison function 
struct list{
   int count;
   struct node *head; //dummy node 
   int (*compare)();
};


//function to create a list 
//allocating space for the size of the list and head node, setting our counter
//setting previous and next to the head so we can create a circular linked list 
//BIG O:O(n)
LIST *createList(int (*compare)()){
   LIST *lp = malloc(sizeof(LIST));
   assert (lp != NULL);
   lp->count = 0;
   lp->compare = compare;
   lp->head = malloc(sizeof(struct node));
   assert(lp->head != NULL); 
   lp->head->prev = lp->head;
   lp->head->next = lp->head;
   return lp; 
}


//function to remove the first piece of data in the linked list
//create a delete node (del) so we know what were trying to delete
//once deleted, rearrange the links to move over delete to the next ones on either side
//BIG O: O(1)
void *removeFirst(LIST *lp){
   assert(lp != NULL);
   struct node * del;
   del = lp -> head -> next;
   lp -> head -> next = del -> next;
   del -> next -> prev = lp -> head;
   void * f = del -> data;
   free(del);
   lp -> count--;
   return f;
}

//function to remove the last piece of data in a doubly linked list 
//again create a delet node now setting it to prev rather than next as were working with the back now
//freeing the deleted data and rearranging the links to point back to the starting head back into a circle 
//BIG O: O(1)
void *removeLast(LIST *lp){
   assert (lp != NULL);
   struct node * del;
   del = lp -> head -> prev;
   del -> prev -> next =lp-> head;
   lp -> head -> prev = del -> prev;
   void * f = del->data;
   free(del);
   lp -> count--;
   return f;
} 

//function to destroy the list and free up memory 
//BIG O: O(1)
void destroyList(LIST *lp){
   assert(lp != NULL);
   struct node * cur = lp->head->next;
   while (cur !=lp->head){
	struct node *pnext = cur -> next;
   	free(cur);
	cur = pnext;}
	free(lp->head);
	free(lp);
}

//funtion to count the number of items in our list and return it 
//BIG O: O(1)
int numItems(LIST *lp){
   assert(lp != NULL);
   return lp -> count;
}

//function to add an item to the beggining of our list
//create a new node that stores the value we want to add
//allocate space for the new node
//increment our counter and reassign the links so prev becomes head and next points 
//to the next of head 
//BIG O: O(n)
void addFirst(LIST *lp, void *item){
   assert(lp != NULL);
   assert (item != NULL);
   struct node *newnode = malloc(sizeof(struct node));
   assert(newnode != NULL);
   newnode->data = item;
   lp->count++;
   newnode->prev = lp->head;
   newnode->next = lp->head->next;
   lp-> head -> next -> prev = newnode;
   lp-> head -> next = newnode;
 
}


//function to add data to the end of the list
//create and allocate a new node
//increment counter
//add it in by assigning our newnode to the prev of head which is the end 
//reassign the links of the list including the newnode 
//BIG O: O(n)
void addLast(LIST *lp, void *item){
   assert(lp != NULL);
   assert(item != NULL);
   struct node * newnode = malloc(sizeof(struct node));
   assert(newnode != NULL);
   newnode -> data = item;
   lp->count++;
   newnode -> next = lp->head;
   newnode -> prev = lp->head->prev;
   lp -> head -> prev -> next = newnode;
   lp -> head -> prev = newnode;
 }

//function to remove the first element in the list 
//BIG O: O(1)
void *getFirst(LIST *lp){
   assert(lp != NULL);
   assert(lp->count-- > 0);
   return lp-> head -> next -> data;
}

//BIG O: O(1)
void *getLast(LIST *lp){
   assert (lp != NULL);
   return lp -> head -> prev -> data;
} 

//BIG O: O(n)
void *getItems(LIST *lp){
  assert(lp != NULL);
  void ** copy = malloc(sizeof(void*)*lp->count);
  assert(copy != NULL);
  struct node * curr = lp->head->next;
  int i;
  for(i = 0; i<lp->count; i++){
   copy[i] = curr -> next;}
  return copy;}   

//function to find a specific item in the list
//checks each element as it goes through lp and calls compare to check for a match 
//if its a match then reutrn the location 
//BIG O:O(n)
void *findItem(LIST *lp, void *item){
   assert(lp != NULL);
   assert(item != NULL);
   struct node * element = lp->head->next;
   while(element != lp->head){
 	if(lp->compare(element->data, item) == 0){
		return element->data;
	}
	element = element -> next;
	}
   return NULL;
}


//function to return and remove the first item in the list
//goes through lp with a cursor 
//checks each item calling compare
//reassigns the deleting nodes poointers and then frees the del node  
//BIG O: O(n)
void removeItem(LIST *lp, void *item){
   assert (lp != NULL);
   assert (item != NULL);
   int i;
   struct node * cur;
   struct node * del; 
   cur = lp->head;
   for ( i=0; i< lp->count; i++){
	int i = lp -> compare(item, cur -> next -> data);
	if ( i ==0){
         del=cur->next;
         del->next->prev = cur;
         cur->next = del->next;
         free(del);
         lp->count--;
         return;}
	cur = cur -> next;
	}
}

   	  
   
