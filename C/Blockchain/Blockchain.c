/*
 * Ryan Lee
 * Title: Blockchain.c
 * Description:
 */

#include<stdlib.h>
#include<stdio.h>
#include<assert.h>
#include<string.h>
#include "Blockchain.h"

/*
 * BlockChainObj
 * Creates and defines a structure called BlockchainObj with int size and an array of Block, up to 100 blocks
 * returns nothing
 * Preconditions: none
 * Side effects: none
 * Error conditions: none
 */
typedef struct BlockchainObj{
        Block blocks[100];
        int size;
} BlockchainObj;

/*
 * newBlockchain
 * Constructor; constructs a blockchain, initializes field values and allocates memory to the blockchain
 * returns a blockchain
 * Preconditions: memory is available to allocate
 * Side effects: prints standard error
 * Error conditions: memory allocation fails
 */
Blockchain newBlockchain(){
        Blockchain blockchain = malloc(sizeof(BlockchainObj));
        if (blockchain == NULL){
          fprintf(stderr, "Error: malloc failed\n");
          return;
        }
        blockchain->size = 0;
        return blockchain;
}

/*
 * freeBlockchain
 * Destructor; frees the blocks in the blockchain, then frees the blockchain itself
 * returns a freed blockchain
 * Preconditions: there is a blockchain with blocks to free
 * Side effects: prints standard error
 * Error conditions: blockchain is NULL
 */
void freeBlockchain(Blockchain B){
        if (B == NULL){
          fprintf(stderr, "Error: Cannot free a Blockchain that is NULL\n");
          return;
        }
        for (int i = 0; i < B->size; i++){
          free((B->blocks)[i]);
        }
        free(B);
}

/*
 * append
 * Appends a block inside the blockchain and returns the size of the blockchain
 * returns either the size of the blockchain or 0 if it fails
 * Preconditons: there is a blockchain to append a block to
 * Side effects: prints standard error
 * Error conditions: blockchain is NULL
 */
int append(Blockchain B, char *data){
        if (B == NULL){
          fprintf(stderr, "Error: The Blockchain is NULL, cannot append a block to it\n");
          return;
        }
        if (B->size < 100){
          ++(B->size);
          int iD = B->size - 1;
          long x;
          //printf("InsideTest #1 condition B->size\n");
          if ((B->size)-1 <= 0){
          		//printf("InsideTest #2 condition x=0\n");
                x = 0;
          }
          else{
          		//printf("InsideTest #3 x = hash()\n");
                x = hash((B->blocks)[B->size - 2]);}
          		//printf("InsideTest #4 create blockz\n");
         	 	Block blockz = newBlock(data, iD, x);
          		//printf("InsideTest #5 blockz put into array\n");
          		B->blocks[B->size-1] = blockz;
          		//printf("InsideTest #6 return the size\n");
          		return ((B->size));
        }
        else
          return 0;
}

/*
 * size
 * Function that returns the size of the blockchain
 * returns the size of blockchain
 * Preconditions: there is a blockchain
 * Side effects: none
 * Error conditions: none
 */
int size(Blockchain B){
        return B->size;
}

/*
 * get
 * Finds the block at index idx and returns that block
 * returns the block at the index position idx
 * Preconditions: there is a blockchain to get the block from and idx does not exceed the blockchain size
 * Side effects: prints standard error
 * Error conditions: blockchain is NULL or idx exceeds the blockchain size
 */
Block get(Blockchain B, int idx){
        if (B == NULL){
          fprintf(stderr, "Error: The Blockchain is NULLED, it holds no blocks\n");
          return;
        }
        if (idx < B->size){
          return ((B->blocks)[idx]);
        }
        else{
          fprintf(stderr, "Error: No blocks at this position in the blockchain\n");
          return;
        }
}

/*
 * valid
 * Validates the blockchain by checking and comparing prevHash and hash values
 * returns a 1 if valid or a 0 if not valid
 * Preconditions: there is a blockchain
 * Side effects: none
 * Error conditions: none
 */int valid(Blockchain B){
        long x;
        for (int i = 0; i < B->size-1; i++){
          x = hash((B->blocks)[i]);
          if (previousHash((B->blocks)[i+1]) != x)
                return 0;
        }
        return 1;
}

/*
 * removeLast
 * Removes the last block from the blockchain and decreases the size of the blockchain
 * returns a blockchain with the last block removed
 * Preconditions: there is a blockchain
 * Side effects: none
 * Error conditions: none
 */
void removeLast(Blockchain B){
        int i = B->size - 1;
        free((B->blocks)[i]);
        B->size = B->size - 1;
}

/*
 * printBlockchain
 * Prints out the entire contents of the blockchain
 * returns printed messages of all the blocks in the Blockchain
 * Preconditions: there is a blockchain
 * Side effects: prints standard error
 * Error conditions: blockchain is NULL
 */
void printBlockchain(FILE *out, Blockchain B){
        if (B == NULL){
          fprintf(stderr, "Error: The blockchain is NULLED, unable to print from a NULLED blockchain\n");
          return;
        }
        for (int i = 0; i < B->size; i++){
                printBlock(out, (B->blocks)[i]);
        }
}
