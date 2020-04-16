//-----------------------------------------------------------------------------
// DictionaryTest.c
// Test module for the Dictionary ADT
//
// Tristan Clark
//-----------------------------------------------------------------------------

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"Dictionary.h"

#define MAX_LEN 180

int main(int argc, char* argv[]){
   char* v;
   Dictionary A = newDictionary();
   printf("%d\n",size(A));
   printf("%d\n",isEmpty(A));
   insert(A,"some","thing");
   v = lookup(A, "some");
   printf("key=\"%s\" %s\"%s\"\n", "some", (v==NULL?"not found ":"value="), v);
   printf("%d\n",size(A));
   printf("%d\n",isEmpty(A));
   insert(A,"what","now");
   insert(A,"does","this");
   insert(A,"work", "?");

   printDictionary(stdout,A);
   printf("%d\n",size(A));

}

