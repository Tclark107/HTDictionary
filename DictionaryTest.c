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
   /*char* v;
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

   delete(A,"not");
   delete(A,"what");

   printDictionary(stdout,A);
   printf("%d\n",size(A));
   
   makeEmpty(A);
   printDictionary(stdout,A);
   printf("%d\n",size(A));
   */

   Dictionary A = newDictionary();
   char* k;
   char* v;
   char* word1[] = {"one","two","three","four","five","six","seven"};
   char* word2[] = {"foo","bar","blah","galumph","happy","sad","blue"};
   int i;

   for(i=0; i<7; i++){
      insert(A, word1[i], word2[i]);
   }

   printDictionary(stdout, A);

   for(i=0; i<7; i++){
      k = word1[i];
      v = lookup(A, k);
      printf("key=\"%s\" %s\"%s\"\n", k, (v==NULL?"not found ":"value="), v);
   }

   // insert(A, "five", "glow"); // error: duplicate keys

   delete(A, "one");
   delete(A, "three");
   delete(A, "seven");

   printDictionary(stdout, A);

   for(i=0; i<7; i++){
      k = word1[i];
      v = lookup(A, k);
      printf("key=\"%s\" %s\"%s\"\n", k, (v==NULL?"not found ":"value="), v);
   }

   // delete(A, "one");  // error: key not found

   printf("%s\n", (isEmpty(A)?"true":"false"));
   printf("%d\n", size(A));
   makeEmpty(A);
   printf("%s\n", (isEmpty(A)?"true":"false"));

   freeDictionary(&A);

   return(EXIT_SUCCESS);


}

