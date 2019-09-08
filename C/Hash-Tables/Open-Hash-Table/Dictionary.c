//--------------------------------------------------------------------
// Ryan Lee
// Dictionary.c
// Contains the code needed to create and delete an open hash table
//--------------------------------------------------------------------

#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<stdbool.h>
#include "Dictionary.h"

/*
 * rotate_left()
 * rotate the bits in an unsigned int
 * returns a rotated unsigned int
 * Preconditions: none
 * Side effects: none
 * Error conditions: none
 */
unsigned int rotate_left(unsigned int value, int shift) {
        int sizeInBits = 8*sizeof(unsigned int);
        shift = shift & (sizeInBits - 1);
        if ( shift == 0 )
          return value;
        return (value << shift) | (value >> (sizeInBits - shift));
}

/*
 * pre_hash()
 * turn a string into an unsigned int
 * returns an unsigned int
 * Preconditions: input != NULL
 * Side effects: none
 * Error conditions: input == NULL
 */
unsigned int pre_hash(char* input) {
        unsigned int result = 0xBAE86554;
        while (*input) {
          result ^= *input++;
          result = rotate_left(result, 5);
        }
        return result;
}

/*
 * hash()
 * turns a string into an int in the range 0 to tableSize-1
 * returns an int between the range of 0 to tableSize-1
 * Preconditions: tableSize is significantly large enough i.e. tableSize >= 1
 * Side effects: none
 * Error conditions: tableSize is too small i.e. tableSize <= 1
 * Special Note: tableSize is set by the client
 */
int hash(char* key, int tableSize){
        return pre_hash(key)%tableSize;
}

/*
 * newHashTable
 * creates a new hash table and allocates memory to it
 * returns a hash table object H
 * Preconditions: there is available memory to allocate to the hash table
 * Side effects: prints stderr
 * Error conditions: H == NULL/there is no memory available to allocate.
 * Print stderr and return NULL.
 */
HashTableObj *newHashTable(int size) {
        // error checking code omitted
        // we explicitly allocate space for the fixed size element in HashTableObj,
        // the size element plus the space for the variable size array
        HashTableObj *H = (HashTableObj *) malloc(sizeof(HashTableObj) + sizeof(bucketListObj)*size);   //creates a new hash table and allocates memory
        if (H == NULL){                                                                                 //checks if memory allocation failed
          fprintf(stderr, "Error: memory allocation failed\n");
          return NULL;
        }
        H->size = size;
        return H;                                                                                       //returns the new hash table H
}

/*
 * insert
 * inserts a bucket with string str at the hash index at the head of the list
 * returns a hash table with the bucket object stored at the appropriate hash index
 * Preconditions: H != NULL, str != NULL, and there is available memory to allocate to the bucket
 * Side effects: prints stderr
 * Error conditions: H == NULL, str == NULL, or B == NULL. In each case, print stderr
 * and end the function.
 */
void insert(HashTableObj *H, char *str){
        if (H == NULL){
          fprintf(stderr, "Error: no table available to insert\n");
          return;
        }
        if (str == NULL){
          fprintf(stderr, "Error: null string ptr invalid\n");
          return;
        }
        bucketListObj *B = (bucketListObj*) malloc(sizeof(bucketListObj) + sizeof(strlen(str)) + 1);    //creating a new bucket and allocating memory to it
        if (B == NULL){                                                                 //checks if memory allocation failed
          fprintf(stderr, "Error: memory allocation for bucket failed\n");
          return;
        }
        B->next = NULL;
        strcpy(B->item, str);
        int i = hash(str, H->size);                                                     //calculates where bucket B should go
        if (H->bucket[i] == NULL){                                                      //checks if the linked list at that index is empty or not
          H->bucket[i] = B;
        }
        else{
          bucketListObj *temp = H->bucket[i];
          H->bucket[i] = B;
          B->next = temp;
        }
}

/*
 * deleteHashTable
 * deletes the entire hash table and deallocates the memory
 * returns a freed and deallocated hash table H
 * Preconditions: H != NULL
 * Side effects: prints stderr
 * Error conditions: H == NULL. Print stderr and end the function.
 */
void deleteHashTable(HashTableObj *H){
        if (H == NULL){
          fprintf(stderr, "Error: no table available to delete\n");
          return;
        }
        for (int i = 0; i < H->size; i++){                              //loops through the entire hash table
          if (H->bucket[i] != NULL){                                    //checks if the bucket at the index is empty or not
                bucketListObj *temp = H->bucket[i];
                bucketListObj *current = temp;
                while (temp->next != NULL){                             //checks for more than one element in the linked list
                        current = temp;
                        temp = temp->next;
                        free(current);
                }
                free(temp);
          }
        }
        free(H);                                                        //frees the hash table H
        H = NULL;
}

/*
 * member
 * checks the hash table to find if the string str is inside the hash table
 * returns true if the string str is in the hash table and false if it fails to find it
 * Preconditions: H != NULL, str != NULL, and the string str is in the hash table
 * Side effects: prints stderr
 * Error conditions: H == NULL, str == NULL, or the string str is not in the hash table.
 * In each case, print stderr and return false.
 */
bool member(HashTableObj *H, char *str){
        if (H == NULL){
          fprintf(stderr, "Error: no table available to search\n");
          return false;
        }
        if (str == NULL){
          fprintf(stderr, "Error: null string ptr invalid\n");
          return false;
        }
        for (int i = 0; i < H->size; i++){                                      //loops through the entire array
          if (H->bucket[i] != NULL){
                bucketListObj *temp = H->bucket[i];
                while (temp->next != NULL){                                     //checks for more than one element in the hash table
                  if (strcmp(str, temp->item) == 0)
                        return true;
                  temp = temp->next;
                }
                if (strcmp(str, temp->item) == 0)                               //this either checks the first element or last element depending on how many items
                        return true;                                            //are in the linked list
          }
        }
        return false;
}

/*
 * delete
 * deletes the bucket with the specific string from the hash table
 * returns true if it deletes the bucket with the string str or false if it fails to do so
 * Preconditions: H != NULL, str != NULL, the bucket with string str is inside the hash table
 * Side effects: prints stderr
 * Error conditions: H == NULL, str == NULL, the bucket is empty/the string str is not inside the hash table.
 * In each case, print stderr and return false
 */
bool delete(HashTableObj *H, char *str){
        if (H == NULL){
          fprintf(stderr, "Error: no table exists to delete the string from\n");
          return false;
        }
        if (str == NULL){
          fprintf(stderr, "Error: null string ptr invalid\n");
          return false;
        }
        int i = hash(str, H->size);                                             //finds the index the string str should be at using the hash function
        bucketListObj *current = H->bucket[i];
        bucketListObj *temp = current;

        if (current == NULL){                                                   //checks if the bucket linked list is empty or not
          fprintf(stderr, "Error: the bucket is empty, nothing inside\n");
          return false;
        }
        if (current->next == NULL){                                             //checks if there is only one element in the linked list
          if (strcmp(str, current->item) == 0){                                 //checks if the string current->item is the string str
                free(current);
                current = NULL;
                return true;
          }
          else
                return false;
        }
        else{                                                                   //more than one element in the linked list
          if (strcmp(str, current->item) == 0){                                 //checks the first element
                H->bucket[i] = current->next;
                free(temp);
                temp = NULL;
                return true;
          }
          else{                                                                 //goes through the other elements
                current = current->next;
                while (current->next != NULL){
                  if (strcmp(str, current->item) == 0){
                        temp->next = current->next;
                        free(current);
                        current = NULL;
                        return true;
                  }
                  temp = current;
                  current = current->next;
                }
                if (strcmp(str, current->item) == 0){                           //last item; necessary to avoid null pointer error
                  temp->next = NULL;
                  free(current);
                  current = NULL;
                  return true;
                }
                else{
                  fprintf(stderr, "Error: the string str is not in the hash table\n");
                  return false;                                 //the bucket with str is not in the hash table
                }
          }
        }
}

/*
 * printHashTable
 * loops through the entire hash table and prints out the contents of it
 * returns a text of strings of the hash table contents to the FILE out
 * Preconditions: FILE out != NULL and the hash table exists
 * Side effects: prints stderr
 * Error conditions: FILE out == NULL or H == NULL. In both cases, print stderr
 * and end the function.
 */
void printHashTable(FILE *out, HashTableObj *H){
        if (out == NULL){
          fprintf(stderr, "Error: the FILE to print to does not exist\n");
          return;
        }
        if (H == NULL){
          fprintf(stderr, "Error: the hash table does not exist\n");
          return;
        }
        for (int i = 0; i < H->size; i++){                              //loops through the entire hash table array
          fprintf(out, "bucket %d\n", i);
          if (H->bucket[i] != NULL){                                    //checks if the bucket list in each index is empty or not
                bucketListObj *temp = H->bucket[i];
                while (temp->next != NULL){                             //checks for more than one element in the linked list
                  fprintf(out, "        bucket list item = %s\n", temp->item);
                  temp = temp->next;
                }
                fprintf(out, "  bucket list item = %s\n", temp->item);
          }
        }
}
