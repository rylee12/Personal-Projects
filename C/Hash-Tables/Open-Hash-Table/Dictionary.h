//-----------------------------------------------------------------------------
// Dictionary.h
// Header file for the HashTable ADT
// Array implmentation with  bucket heads that point to linked list of items
// that hash to this bucket
//
// Note that the hash table size is decided by the client and passed to
// the new function that creates the hash table.
//
//-----------------------------------------------------------------------------

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#ifndef _DICTIONARY_H_INCLUDE_
#define _DICTIONARY_H_INCLUDE_


typedef struct bucketListObj  *bucketList;

typedef struct bucketListObj {
    bucketList  next;
    char        item[];
} bucketListObj;


// this item will be dynamically allocated newHash,
// must manage the index to stay in allocated array range
typedef struct HashTableObj {
    int         size;           // MUST COME FIRST!!!
    bucketList bucket[];
} HashTableObj;

/*
 * newHashTable
 * creates a new hash table and allocates memory to it
 * returns a hash table object H
 * Preconditions: there is available memory to allocate to the hash table
 * Side effects: prints stderr
 * Error conditions: H == NULL/there is no memory available to allocate.
 * Print stderr and return NULL.
 */
HashTableObj    *newHashTable(int size);

/*
 * deleteHashTable
 * deletes the entire hash table and deallocates the memory
 * returns a freed and deallocated hash table H
 * Preconditions: H != NULL
 * Side effects: prints stderr
 * Error conditions: H == NULL. Print stderr and end the function.
 */
void            deleteHashTable(HashTableObj * H);

/*
 * member
 * checks the hash table to find if the string str is inside the hash table
 * returns true if the string str is in the hash table and false if it fails to find it
 * Preconditions: H != NULL, str != NULL, and the string str is in the hash table
 * Side effects: prints stderr
 * Error conditions: H == NULL, str == NULL, or the string str is not in the hash table.
 * In each case, print stderr and return false.
 */
bool            member(HashTableObj *H, char *str);

/*
 * insert
 * inserts a bucket with string str at the hash index at the head of the list
 * returns a hash table with the bucket object stored at the appropriate hash index
 * Preconditions: H != NULL, str != NULL, and there is available memory to allocate to the bucket
 * Side effects: prints stderr
 * Error conditions: H == NULL, str == NULL, or B == NULL. In each case, print stderr
 * and end the function.
 */
void            insert(HashTableObj *H, char *str);

/*
 * delete
 * deletes the bucket with the specific string from the hash table
 * returns true if it deletes the bucket with the string str or false if it fails to do so
 * Preconditions: H != NULL, str != NULL, the bucket with string str is inside the hash table
 * Side effects: prints stderr
 * Error conditions: H == NULL, str == NULL, the bucket is empty/the string str is not inside the hash table.
 * In each case, print stderr and return false
 */
bool            delete(HashTableObj *H, char *str);

/*
 * printHashTable
 * loops through the entire hash table and prints out the contents of it
 * returns a text of strings of the hash table contents to the FILE out
 * Preconditions: FILE out != NULL and the hash table exists
 * Side effects: prints stderr
 * Error conditions: FILE out == NULL or H == NULL. In both cases, print stderr
 * and end the function.
 */
void            printHashTable(FILE *out, HashTableObj *H);

#endif
