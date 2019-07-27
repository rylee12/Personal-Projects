//-----------------------------------------------------------------------------
// Ryan Lee
// BST.h
// Header file for the BST ADT
//-----------------------------------------------------------------------------


#include <stdio.h>
#include <stdlib.h>
#ifndef _BST_H_INCLUDE_
#define _BST_H_INCLUDE_
#define TRUE 1
#define FALSE 0

// Exported reference type
// Tree node to store strings, space must be allocated for the strings
typedef struct BSTObj {
    char               *term;           /* string data in each block */
    struct BSTObj      *leftChild;      /* ptr to left child */
    struct BSTObj      *rightChild;     /* ptr to right child */
} BSTObj;

/*
 *  insert
 *  add a new node to the BST with the new_data values, space must be allocated in the BST node
 *  returns a BST with a node inserted that stores the string
 *  Preconditions: the new_data value != NULL and pBST != NULL
 *  Side effects: prints stderr
 *  Error conditions: new_data == NULL or pBST == NULL. In both cases, print stderr and end function.
 */
void insert(char *new_data,  BSTObj **pBST);

/*
 *  inorderTraverse
 *  print to OUT the inorder traversal
 *  returns FILE out with all the nodes from the tree printed in order
 *  Preconditions: FILE out exists and the tree is not empty
 *  Side effects: prints stderr
 *  Error conditions: out == NULL or the tree is empty. In both cases, print stderr and end function
 */
void inorderTraverse(FILE *out, BSTObj *T);

/*
 *  preorderTraverse
 *  print to OUT the preorder traversal
 *  returns FILE out with all the nodes from the tree printed pre order
 *  Preconditions: FILE out exists and the tree is not empty
 *  Side effects: prints stderr
 *  Error conditions: out == NULL or the tree is empty. In both cases, print stderr and end function
 */
void preorderTraverse(FILE *out, BSTObj *T);

/*
 *  postorderTraverse
 *  print to OUT the postorder traversal
 *  returns FILE out with the nodes from the tree printed post order
 *  Preconditions: FILE out exists and the tree contains nodes
 *  Side effects: prints stderr
 *  Error conditions: out == NULL or the tree is empty. In both cases, print stderr and end function
 */
void postorderTraverse(FILE *out, BSTObj *T);

/*
 *  inorderLeaves
 *  print the leaves of the tree in inorder to OUT
 *  returns FILE out with only the leaf nodes from the tree printed in order
 *  Preconditions: FILE out exists and the tree contains nodes
 *  Side effects: prints stderr
 *  Error conditions: out == NULL or the tree is empty. In both cases, print stderr and end function
 */
void inorderLeaves(FILE *out, BSTObj *T);

/*
 *  find
 *  searches the tree to find if a string stored in the tree matches term_to_find
 *  return TRUE if the item_to_find matches a string stored in the tree
 *  Preconditions: a tree with nodes inside it and term_to_find != NULL
 *  Side effects: prints stderr
 *  Error conditions: term_to_find == NULL or the tree is empty. In both cases, print stderr and return FALSE
 */
int  find(char *term_to_find, BSTObj *T);

/*
 *  treeHeight
 *  compute the height of the tree
 *  returns the height of the tree
 *  Preconditions: a tree with nodes inside it and height = 0 passed in
 *  Side effects: prints stderr
 *  Error conditions: if height is less than 0. Print stderr and return -1.
 *  Special Instructions: call height = 0 and the root of the tree
 */
int treeHeight(BSTObj *T, int height);

/*
 *  copyTree
 *  create and return a complete memory independent copy of the tree
 *  returns a copy of tree T
 *  Preconditions: a tree with nodes inside it
 *  Side effects: prints stderr
 *  Error conditions: the tree is empty. Print stderr and return NULL i.e. end function.
 */
BSTObj * copyTree(BSTObj *T);

/*
 *  makeEmpty
 *  remove all the nodes from the tree, deallocate space and reset Tree pointer
 *  returns a freed and NULLED tree, basically nothing
 *  Preconditions: a tree with nodes inside it
 *  Side effects: prints stderr
 *  Error conditions: pT == NULL or tree is empty. For both cases, print stderr and end function.
 */
void makeEmpty(BSTObj **pT);

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
int deleteItem(char *term_to_delete, BSTObj **pT);

#endif
