//---------------------------------------------------------------
// Ryan Lee
// BST.c
// 
//---------------------------------------------------------------

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "BST.h"

void deleteNode(BSTObj **pT);
void retrieveNode(char *term_to_delete, BSTObj **pT, BSTObj **prBST);
BSTObj *findLeftmost(BSTObj *pT);

/*
 * insert
 * add a new node to the BST with the new_data values, space must be allocated in the BST node
 * returns a BST with a node inserted that stores the string
 * Preconditions: the new_data value != NULL and pBST != NULL
 * Side effects: prints standard error
 * Error conditions: new_data == NULL or pBST == NULL. In both cases, print standard error and
 * end function.
 */
void insert(char *new_data, BSTObj **pBST){
        if (pBST == NULL){
          fprintf(stderr, "Error: ptr to ptr to root does not exist, null pointer not acceptable\n");
          return;
        }
        if (new_data == NULL){
          fprintf(stderr, "Error: the data to be stored does not exist, null value not acceptable\n");
          return;
        }
        if (*pBST == NULL){                                                     //the base case
          BSTObj *newNode = malloc(sizeof(BSTObj));                             //need to make sure you don't loop the malloc, or it will waste memory
          newNode->term = calloc(strlen(new_data) + 1, sizeof(char));           //allocates memory to the string
          strcpy(newNode->term, new_data);                                      //copies the string new_data into newNode->term
          newNode->leftChild = NULL;
          newNode->rightChild = NULL;
          *pBST = newNode;
          return;
        }
        if (strcmp(new_data, (*pBST)->term) <= 0){                              //If new_data is less than or equal to node->term, go left
          /*if ((*pBST)->leftChild == NULL){
                BSTObj *newNode = malloc(sizeof(BSTObj));
                newNode->term = calloc(strlen(new_data) + 1, sizeof(char));     //Junk code, but it's commented out
                strcpy(newNode->term, new_data);
                newNode->leftChild = NULL;
                newNode->rightChild = NULL;
                (*pBST)->leftChild = newNode;
                return;
          }*/
          insert(new_data, &((*pBST)->leftChild));
        }
        else{                                                                   //If new_data is greater than node->term, go right
          /*if ((*pBST)->rightChild == NULL){
                BSTObj *newNode = malloc(sizeof(BSTObj));                       //Junk code, but it's commented out
                newNode->term = calloc(strlen(new_data) + 1, sizeof(char));
                strcpy(newNode->term, new_data);
                newNode->leftChild = NULL;
                newNode->rightChild = NULL;
                (*pBST)->rightChild = newNode;
                return;
          }*/
          insert(new_data, &((*pBST)->rightChild));
        }
}

/*
 * inorderTraverse
 * print to OUT the inorder traversal
 * returns FILE out with all the nodes from the tree printed in order
 * Preconditions: FILE out exists and the tree is not empty
 * Side effects: prints standard error
 * Error conditions: out == NULL or tree is empty. In both cases, print stderr and end the function
 */
void inorderTraverse(FILE *out, BSTObj *T){
        if (out == NULL){
          fprintf(stderr, "Error: the file to print to does not exist\n");
          return;
        }
        if (T == NULL){
          fprintf(stderr, "Error: the tree is empty, nothing to print to\n");
          return;
        }
        //printf("first thing\n");
        if (T->leftChild != NULL)
          inorderTraverse(out, T->leftChild);
        fprintf(out, "%s ", T->term);
        if (T->rightChild != NULL)
          inorderTraverse(out, T->rightChild);
}

/*
 * preorderTraverse
 * print to OUT the preorder traversal
 * returns FILE out with the nodes from the tree printed pre order
 * Preconditions: FILE out exists and the tree contains nodes
 * Side effects: prints standard error
 * Error conditions: out == NULL or tree is empty. In both cases, print stderr and end the function
 */
void preorderTraverse(FILE *out, BSTObj *T){
        if (out == NULL){
          fprintf(stderr, "Error: the file to print to does not exist\n");
          return;
        }
        if (T == NULL){
          fprintf(stderr, "Error: the tree is empty, nothing to print to\n");
          return;
        }
        fprintf(out, "%s ", T->term);
        if (T->leftChild != NULL)
          preorderTraverse(out, T->leftChild);
        if (T->rightChild != NULL)
          preorderTraverse(out, T->rightChild);
}

/*
 * postorderTraverse
 * print to OUT the postorder traversal
 * returns FILE out with the nodes from the tree printed post order
 * Preconditions: FILE out exists and the tree contains nodes
 * Side effects: prints standard error
 * Error conditions: out == NULL or tree is empty. In both cases, print stderr and end the function
 */
void postorderTraverse(FILE *out, BSTObj *T){
        if (out == NULL){
          fprintf(stderr, "Error: the file to print to does not exist\n");
          return;
        }
        if (T == NULL){
          fprintf(stderr, "Error: the tree is empty, nothing to print to\n");
          return;
        }
        if (T->leftChild != NULL)
          postorderTraverse(out, T->leftChild);
        if (T->rightChild != NULL)
          postorderTraverse(out, T->rightChild);
        fprintf(out, "%s ", T->term);
}

/*
 * inorderLeaves
 * prints only the leaves of the tree in order to OUT
 * returns FILE out with only the leaf nodes from the tree printed in order
 * Preconditions: FILE out exists and the tree contains nodes
 * Side effects: prints standard error
 * Error conditions: out == NULL or tree is empty. In both cases, print stderr and end the function
 */
void inorderLeaves(FILE *out, BSTObj *T){
        if (out == NULL){
          fprintf(stderr, "Error: the file to print to does not exist\n");
          return;
        }
        if (T == NULL){
          fprintf(stderr, "Error: the tree is empty, nothing to print\n");
          return;
        }
        if (T->leftChild != NULL)
          inorderLeaves(out, T->leftChild);
        if (T->leftChild == NULL && T->rightChild == NULL)                              //Checks if the BST node is a leaf or not
          fprintf(out, T->term);
        if (T->rightChild != NULL)
          inorderLeaves(out, T->rightChild);
}

/*
 * find
 * searches the tree to find if a string stored in the tree matches term_to_find
 * returns TRUE if the term_to_find matches a string stored in the tree
 * Preconditions: a tree with nodes inside it and term_to_find != NULL
 * Side effects: prints standard error
 * Error conditions: term_to_find == NULL or the tree is empty. In both cases, print
 * standard error and return FALSE.
 */
int find(char *term_to_find, BSTObj *T){
        if (term_to_find == NULL){
          fprintf(stderr, "Error: the data does not exist in the tree\n");
          return FALSE;
        }
        if (T == NULL){
          fprintf(stderr, "Error: the tree is empty, the data does not exist in this tree\n");
          return FALSE;
        }
        if (strcmp(term_to_find, T->term) == 0)                                         //If the term_to_find matches a string stored in the tree
          return TRUE;
        if (strcmp(term_to_find, T->term) <= 0)                                         //If the term_to_find value is less than or equal to T->term, go left
          return find(term_to_find, T->leftChild);
        else                                                                            //If the term_to_find value is greater than T->term, go right
          return find(term_to_find, T->rightChild);
}

/*
 * treeHeight
 * computes the height of the tree
 * returns the height of the tree
 * Preconditions: a tree with nodes inside it and the integer 1 is passed into the height parameter
 * Side effects: prints stderr
 * Error conditions: the height is less than 0. Print stderr and return -1.
 */
int treeHeight(BSTObj *T, int height){
        if (height < 0){
          fprintf(stderr, "Error: height should not be less than 0\n");
          return -1;
        }
        if (T == NULL)
          return height;
        if (T->leftChild == NULL && T->rightChild == NULL)                              //Checks for if only the root is there or if it reaches a leaf node
          return height + 1;
        int l = treeHeight(T->leftChild, height + 1);
        int r = treeHeight(T->rightChild, height + 1);
        if (l > r)                                                                      //Compares the 2 variables, only returns the greatest one
          return l;
        else                                                                            //If both are equal, it returns r b/c it doesn't matter, both are equal
          return r;
}

/*
 * copyTree
 * creates a complete memory independent copy of the tree
 * returns a copy of tree T
 * Preconditions: a tree with nodes inside it
 * Side effects: prints standard error
 * Error conditions: the tree is empty. If the tree is empty, print stderr and end function.
 */
BSTObj * copyTree(BSTObj *T){
        if (T == NULL){
          fprintf(stderr, "Error: the tree is empty, nothing to copy\n");
          return NULL;
        }
        BSTObj *newTree = malloc(sizeof(BSTObj));
        //newTree->term = T->term;                                                      //Junk code commented out
        newTree->term = calloc(strlen(T->term) + 1, sizeof(char));
        strcpy(newTree->term, T->term);
        if (T->leftChild != NULL)
          newTree->leftChild = copyTree(T->leftChild);
        if (T->rightChild != NULL)
          newTree->rightChild = copyTree(T->rightChild);
        return newTree;
}

/*
 * makeEmpty
 * removes all the nodes from the tree, deallocates the space and resets tree pointer
 * returns a freed and NULLED tree, basically nothing
 * Preconditions: a tree with nodes inside it
 * Side effects: prints standard error
 * Error conditions: pT == NULL or the tree is empty. For both cases, print standard error and end function.
 */
void makeEmpty(BSTObj **pT){
        if (pT == NULL){
          fprintf(stderr, "Error: Cannot pass in a null pointer, ptr to ptr to root does not exist\n");
          return;
        }
        if (*pT == NULL){
          fprintf(stderr, "The tree is empty, nothing to free\n");
          return;
        }
        if ((*pT)->leftChild != NULL)
          makeEmpty(&((*pT)->leftChild));
        if ((*pT)->rightChild != NULL)
          makeEmpty(&((*pT)->rightChild));
        free((*pT)->term);                                                              //Need to free the memory allocated to the string
        free(*pT);                                                                      //Frees memory allocated to the BST node
        *pT = NULL;                                                                     //Must do *pT = NULL before pT = NULL, or errors
        pT = NULL;
}

/*
 * deleteItem
 * deletes a single node from the tree and deallocates the space, using helper functions
 * returns 1 if it successfully deletes the node and a 0 if it fails to do so
 * Preconditions: a tree with nodes inside it, the node to be deleted is inside the tree, and the term != NULL
 * Side effects: prints standard error
 * Error conditions: pT == NULL, term_to_delete == NULL, the tree is empty, or the node to be deleted is not inside the tree.
 * In all cases, print standard error and return a 0 to indicate FALSE.
 * Special Note: True = 1, False = 0 as defined in the BST.h file given to us.
 */
int deleteItem(char *term_to_delete, BSTObj **pT){
        if (pT == NULL){
          fprintf(stderr, "Error: null pointer invalid\n");
          return 0;
        }
        if (term_to_delete == NULL){
          fprintf(stderr, "Error: null pointer for the term unacceptable\n");
          return 0;
        }
        if (*pT == NULL){
          fprintf(stderr, "Error: the tree is empty\n");
          return 0;
        }
        BSTObj *parent = NULL;
        BSTObj *current = *pT;
        BSTObj *temp = *pT;
        retrieveNode(term_to_delete, &current, &parent);
        //printf("retrieve node 0 = %s\n", current->term);
        if (current == NULL){                                           //checks if the term to be deleted is in the BST or not
          fprintf(stderr, "Error: node is not in the BST\n");
          return 0;
        }
        if (current->leftChild == NULL && current->rightChild == NULL){                         //no child case (need to deal with root)
          //printf("first case\n");
          if (strcmp((*pT)->term, current->term) != 0){                         //checks if it is only the root
                if (strcmp(term_to_delete, (parent->leftChild)->term) == 0)
                        parent->leftChild = NULL;
                else
                        parent->rightChild = NULL;
          }
          deleteNode(&current);
          return 1;
        }

        else if (current->leftChild == NULL || current->rightChild == NULL){                    //one child case
          //printf("second case\n");
          if (current->leftChild != NULL && current->rightChild == NULL){                       //if the one child is the left child
                if (strcmp(term_to_delete, (parent->leftChild)->term) == 0){
                        parent->leftChild = current->leftChild;
                }
                else
                        parent->rightChild = current->leftChild;
                deleteNode(&current);
                return 1;
          }
          else{                                                                                 //if the one child is the right child
                if (strcmp(term_to_delete, (parent->leftChild)->term) == 0){
                        parent->leftChild = current->rightChild;
                }
                else{
                        parent->rightChild = current->rightChild;
                }
                deleteNode(&current);
                return 1;
          }
        }

        else{                                                                                   //two children
          if (current->leftChild != NULL && current->rightChild != NULL){
                //printf("third case\n");
                temp = findLeftmost(current->rightChild);
                BSTObj *hello = malloc(sizeof(BSTObj));
                hello->term = calloc(strlen(temp->term) + 1, sizeof(char));
                strcpy(hello->term, temp->term);
                deleteItem(temp->term, pT);
                strcpy(current->term, hello->term);
                deleteNode(&hello);
                return 1;
          }
        }
}

/*
 * deleteNode
 * deletes the node and term
 * returns a freed node and term and deallocates both the term and node
 * Preconditions: there is a node to be freed
 * Side effects: none
 * Error conditions: pT == NULL. This should be caught in the main function
 * as this function is meant to be a helper function, not a function on its own.
 */
void deleteNode(BSTObj **pT){
        free((*pT)->term);
        free(*pT);
        *pT = NULL;
        pT = NULL;
        return;
}

/*
 * retrieveNode
 * retrieves the firt node it finds in the BST with term to_be_deleted, sets *pT to that node and *prBST as *pT's parent
 * returns pT as the node with term_to_delete stored and prBST as its parent node or both nodes as NULL if it can't find the term
 * Preconditions: pT and prBST != NULL and the term_to_delete is in the BST
 * Side effects: none
 * Error conditions: pT or prBST == NULL and the term_to_delete is not in the BST. pT or prBST == NULL should be caught in the main
 * function, but they don't rlly matter as the pointers passed in are not **ptrs. As for term_to_delete, it sets both *pT and *prBST
 * to NULL so the main function can check to see if pT is NULL to determine if term_to_delete is in the BST or not.
 */
void retrieveNode(char *term_to_delete, BSTObj **pT, BSTObj **prBST){
        if (*pT == NULL){
          //*pT = NULL;
          return;
        }
        if (strcmp(term_to_delete, (*pT)->term) == 0){
          //printf("found the node\n");
          return;
        }
        if (strcmp(term_to_delete, (*pT)->term) < 0){
          *prBST = *pT;
          *pT = (*pT)->leftChild;
          //printf("left retrieve\n");
          retrieveNode(term_to_delete, pT, prBST);
        }
        else{
          *prBST = *pT;
          *pT = (*pT)->rightChild;
          //printf("right retrieve\n");
          retrieveNode(term_to_delete, pT, prBST);
        }
}

/*
 * findLeftmost
 * finds the leftmost node of the BST node
 * returns the leftmost node or the right child of pT
 * Preconditions: pT != NULL and pT->rightChild != NULL
 * Side effects: none
 * Error conditions: pT == NULL or pT->rightChild == NULL. This is resolved in the main function.
 * Special note: This helper function is meant for deleteItem. As such, it is meant to be called
 * like i.e.: findLeftmost(pT->rightChild).
 */
BSTObj *findLeftmost(BSTObj *pT){
        //if (pT->leftChild != NULL)                            //Personal Notes: Probably can't do recursively b/c it doesn't set pT == node I want
        //  findLeftmost(pT->leftChild);
        //printf("the leftmost string = %s\n", pT->term);
        while (pT->leftChild != NULL)
          pT = pT->leftChild;
        return pT;
}
