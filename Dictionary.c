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
#define tableSize 101

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
   List hashTable[tableSize];
} DictionaryObj;


// newDictionary()
// Dictionary Constructor
Dictionary newDictionary(void) {
   Dictionary D = malloc(sizeof(DictionaryObj));
   assert(D!=NULL);
   D->numHashItems = 0;
   for(int i = 0; i < tableSize; ++i) D->hashTable[i] = newList();
   return D;
}

// freeDictionary()
// destructor for the Dictionary type
void freeDictionary(Dictionary* pD) {
   if(*pD != NULL && pD != NULL) {
      if(!isEmpty(*pD)) makeEmpty(*pD);
      //for(int i = 0; i < tableSize; i++) freeList(&pD->hashTable[i]);
      free(*pD);
      *pD = NULL;
   }
}

// freeList() 
// destructor for the List type
void freeList(List* pL) {
   if(*pL != NULL && pL != NULL) {
      //if(!isListEmpty(*pL)) makeListEmpty(*pL);
      free(*pL);
      *pL = NULL;
   }
}

//-----------------------------------------------------------------------------
// private functions
//-----------------------------------------------------------------------------

// rotate_left()
// rotate the bits in an unsigned int
unsigned int rotate_left(unsigned int value, int shift) {
   int sizeInBits = 8*sizeof(unsigned int);
   shift = shift & (sizeInBits - 1);
   if ( shift == 0 )
      return value;
   return (value << shift) | (value >> (sizeInBits - shift));
}

// pre_hash()
// turn a string into an unsigned int
unsigned int pre_hash(char* input) { 
   unsigned int result = 0xBAE86554;
   while (*input) { 
      result ^= *input++;
      result = rotate_left(result, 5);
   }
   return result;
}

// hash()
// turns a string into an int in the range 0 to m-1 
int hash(char* key){
   return pre_hash(key)%tableSize;
}

//-----------------------------------------------------------------------------
// public functions
//-----------------------------------------------------------------------------

// isEmpty()
// returns 1 (true) if S is empty, 0 (false) otherwise
// pre: none
int isEmpty(Dictionary D) {
   if(D==NULL) {
      fprintf(stderr,"Dictionary Error: calling isEmpty() on NULL Dictionary reference\n");
      exit(EXIT_FAILURE);
   }
   return(D->numHashItems == 0);
}

// size()
// returns the number of (key, value) pairs in D
// pre: none
int size(Dictionary D) {
   if(D==NULL) {
      fprintf(stderr,"Dictionary Error: calling size() on NULL Dictionary reference\n");
      exit(EXIT_FAILURE);
   }
   return D->numHashItems;
}

// lookup()
// returns the value v such that (k, v) is in D, or returns NULL if no 
// such value v exists.
// pre: none
char* lookup(Dictionary D, char* k) {   
   if(D==NULL) {
      fprintf(stderr,"Dictionary Error: calling lookup() on NULL Dictionary reference\n");
      exit(EXIT_FAILURE);
   }
   int slot = hash(k);
   Node N;
   for(N = D->hashTable[slot]->head; N!=NULL; N = N->next) {
      if(!strcmp(k,N->key)) {
         return N->value;
      }
   }
   return NULL; 
}

// insert()
// inserts new (key,value) pair into D
// pre: lookup(D, k)==NULL
void insert(Dictionary D, char* k, char* v) {
   if(D==NULL) {
      fprintf(stderr,"Dictionary Error: calling insert() on NULL Dictionary reference\n");
      exit(EXIT_FAILURE);
   }
   if(lookup(D,k)==NULL){
      int slot = hash(k);
      Node N = NewNode(k,v);
      if(D->hashTable[slot]->numListItems > 0) {
         N->next = D->hashTable[slot]->head;
         D->hashTable[slot]->head = N;
      } else {
         D->hashTable[slot]->head = N;
      }
      D->hashTable[slot]->numListItems++;
      D->numHashItems++; 
   } else {
      printf("cannot insert duplicate keys\n");
   }
}

// delete()
// deletes pair with the key k
// pre: lookup(D, k)!=NULL
void delete(Dictionary D, char* k) {
   if(D==NULL) {
      fprintf(stderr,"Dictionary Error: calling delete() on NULL Dictionary reference\n");
      exit(EXIT_FAILURE);
   }
   if(lookup(D,k)!=NULL){
      int slot = hash(k);
      Node N, P;
      P = NULL;

      for(N = D->hashTable[slot]->head; N!=NULL;
            P = N, N = N->next) {
         if(N->key == k) {
            if(P == NULL) {
               D->hashTable[slot]->head = N->next;
               break;
            } else {
               P->next = N->next;
               break;
            }
         }
      }    
      freeNode(&N);
      D->hashTable[slot]->numListItems--;
      D->numHashItems--;
   } else {
      printf("cannot delete non-existent key\n");
   }
}

// makeEmpty()
// re-sets D to the empty state.
// pre: none
void makeEmpty(Dictionary D) {
   if(D==NULL) {
      fprintf(stderr,"Dictionary Error: calling makeEmpty() on Dictionary reference\n");
      exit(EXIT_FAILURE);
   }
   if(D->numHashItems > 0) {
      Node N;
      for(int i = 0; i < tableSize; ++i) {
         if(D->hashTable[i]->numListItems>0) {
            while( D->hashTable[i]->numListItems>1 ) {
               N = D->hashTable[i]->head;
               D->hashTable[i]->head = D->hashTable[i]->head->next;
               freeNode(&N);
               D->hashTable[i]->numListItems--;
            }
            N = D->hashTable[i]->head;
            D->hashTable[i]->head = NULL;
            freeNode(&N);
            D->hashTable[i]->numListItems--;
         }
         freeList(&D->hashTable[i]);
      }
   }
   D->numHashItems = 0;
}

// printDictionary()
// pre: none
// prints a text representation of D to the file pointed to by out
void printDictionary(FILE* out, Dictionary D) {
   if(D==NULL) {
      fprintf(stderr,"Dictonary Error: calling printDictionary() on NULL Dictionary reference\n");
      exit(EXIT_FAILURE);
   }
   if(D->numHashItems>0) {
      Node N;
      for(int i = 0; i < tableSize; ++i) {
         for(N = D->hashTable[i]->head; N != NULL; N = N->next) {
            fprintf(out,"%s %s\n",N->key,N->value);
         }
      }
   }
}
