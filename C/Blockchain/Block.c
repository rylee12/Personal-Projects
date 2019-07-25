/*
 * Ryan Lee
 * Title: Block.c
 * Description:
 */

#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<string.h>
#include "Block.h"

/*
 * BlockObj
 * Creates and defines a structure called BlockObj
 * returns nothing, it just defines a structure
 * Preconditions: none
 * Side effects: none
 * Error conditions: none
 */
typedef struct BlockObj{
        int ID;
        char *data;
        long prevHash;
} BlockObj;

/*
 * newBlock
 * Constructor; creates a new Block object and allocates memory to it and initializes the field values
 * returns a block
 * Preconditions: memory is available to allocate
 * Side effects: prints standard error
 * Error conditions: Memory allocation fails or the data is NULL
 */
Block newBlock (char *data, int id, long hash){
        Block B = malloc(sizeof(BlockObj));
        if (B == NULL){
          fprintf(stderr, "Error: memory allocation failed\n");
          return;
        }
        if (data == NULL){
          fprintf(stderr, "the data is NULL, there is no data\n");
          B->data = "";
          B->ID = id;
          B->prevHash = hash;
          return B;
        }
        else{
          B->data = data;
          B->ID = id;
          B->prevHash = hash;
          return B;
        }
}

/*
 * freeBlock
 * Destructor; frees the block
 * returns a freed block
 * Preconditions: there is a block to be freed i.e. B != NULL
 * Side effects: prints standard error
 * Error conditions: The block is NULL
 */
void freeBlock (Block B){
        if (B == NULL){
          fprintf(stderr, "Error: Cannot free a nulled block\n");
          return;
        }
        free(B);
}

/*
 * data
 * returns the block's data
 * returns data of the block
 * Preconditions: there is data to return
 * Side effects: none
 * Error conditions: none
 */
char* data(Block B){
        return B->data;
}

/*
 * previousHash
 * returns the block's prevHash, or previous hash, value
 * returns previous hash value of the block
 * Preconditions: there is a previous hash value
 * Side effects: none
 * Error conditions: none
 */
long previousHash(Block B){
        return B->prevHash;
}

/*
 * hash
 * calculates the hash value of the block, which will be the prevHash value of the next block
 * returns the hash value of the block
 * Preconditions: the field values are initialized
 * Side effects: none
 * Error conditions: none
 */
long hash(Block B){
        long x = 0;
        for (int i = 0; i < strlen(B->data); i++){
          x = x + (int)(B->data)[i];
        }
        x = x + B->ID;
        x = x + B->prevHash;
        return x;
}

/*
 * printBlock
 * Prints the id and data of the block in the format ID:data
 * returns a printed message
 * Preconditions: there is a block with the ID and data values initialized
 * Side effects: prints standard error
 * Error conditions: the block is NULL
 */
void printBlock(FILE *out, Block B){
        if (B == NULL){
          fprintf(stderr, "Error: Calling printBlock() on a Null Block\n");
          return;
        }
        fprintf(out, "%d:%s", B->ID, B->data);
        fprintf(out, "\n");
}
