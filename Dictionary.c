//------------------------------------------------------------------------------
// Dictionary.c
// My Hash Table implementation of a Dictionary.
//
// Tristan Clark
//------------------------------------------------------------------------------

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>
#include"Dictionary.h"
#define TABLE_SIZE 101

//-----------------------------------------------------------------------------
// Constructors
//-----------------------------------------------------------------------------

typedef struct NodeObj{
   char* key;
   char* value;
   struct NodeObj* next;
} NodeObj;

typedef NodeObj* Node;

// Node Constructor
Node NewNode(char* key, char* value) {
   Node N = malloc(sizeof(NodeObj));
   assert(N!=NULL);
   N->key = key;
   N->value = value;
   N->next = NULL;
   return(N);
}

void freeNode(Node* p) {
   if(*p != NULL && p != NULL) {
      free(*p);
      *p = NULL; 
   }
}

typedef struct ListObj {
   int numListItems;
   Node head;
} ListObj;

// make List a type pointer to ListObj
typedef struct ListObj* List;

// newList()
// List Constructor
List newList() {
   List L = malloc(sizeof(ListObj));
   assert(L!=NULL);
   L->numListItems = 0;
   L->head = NULL;
   return L;
}

typedef struct DictionaryObj {
   int numHashItems;
   List hashTable[TABLE_SIZE];
} DictionaryObj;


// newDictionary()
// Dictionary Constructor
Dictionary newDictionary(void) {
   Dictionary D = malloc(sizeof(DictionaryObj));
   assert(D!=NULL);
   D->numHashItems = 0;
   for(int i = 0; i < TABLE_SIZE; ++i) D->hashTable[i] = newList();
   return D;
}

// freeList() 
// destructor for the List type
/*void freeList(List* pL) {
   if(*pL != NULL && pL != NULL) {
      if(!isEmpty(*pL)) makeEmpty(*pL);
      free(*pL);
      *pL = NULL;
   }
}*/
