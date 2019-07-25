// Ryan K Lee
// Title: ListClient.c
// Description: Client/test file for the List ADT

#include<stdio.h>
#include<stdlib.h>
#include"List.h"

int main(int argc, char* argv[]){
   
   List A = newList();
   List B = newList();
   List C = newList();
   List D = NULL;
   int i;

   for (i = 1; i <= 20; i++){
      append(A, i);
      prepend(B, i);
   }

   for (i = 1; i <= 30; i = i + 3){
   	  append(C, i);
   }

   printList(stdout,A); 
   printf("\n");
   printList(stdout,B); 
   printf("\n");
   printList(stdout, C);
   printf("\n");

   for(moveFront(A); index(A)>=0; moveNext(A)){
      printf("%d ", get(A));
   }
   printf("\n");

   for(moveBack(B); index(B)>=0; movePrev(B)){
      printf("%d ", get(B));
   }
   printf("\n");

   D = copyList(A);
   printf("%s\n", equals(A,B)?"true":"false");
   printf("%s\n", equals(B,D)?"true":"false");
   printf("%s\n", equals(D,A)?"true":"false");

   moveFront(A);
   for(i = 0; i < 5; i++) moveNext(A);  // at index 5
   insertBefore(A, -1);            		// at index 6
   for(i = 0; i < 9; i++) moveNext(A);  // at index 15
   insertAfter(A, -2);
   for(i = 0; i < 5; i++) movePrev(A);  // at index 10
   delete(A);
   printList(stdout,A);
   printf("\n");
   printf("%d\n", length(A));
   clear(A);
   printf("%d\n", length(A));

   insertOrder(C, 0);
   insertOrder(C, 100);
   insertOrder(C, 14);
   printList(stdout, C);
   printf("\n");
   printf("%d\n", length(C));

   freeList(&A);
   freeList(&B);
   freeList(&C);
   freeList(&D);

   return(0);
}

/*
Output of this program:
1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20
20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1
0 3 6 9 12 15 18 21 24 27 30
1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20
1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20
false
false
true
1 2 3 4 5 -1 6 7 8 9 11 12 13 14 15 -2 16 17 18 19 20
21
0
*/