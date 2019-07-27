//---------------------------------------------------------------------
// Ryan Lee
// BSTClient.c
// Test client for Binary Search Tree ADT
//---------------------------------------------------------------------

#include "stdio.h"
#include "BST.h"
#include<unistd.h>

int main(int argc, char* argv[]){

        BSTObj  *T;
        BSTObj *nT;
        BSTObj *K;

        T = NULL;
        nT = NULL;
        K = NULL;

        printf("Testing all the null cases first\n");
        insert(NULL, &T);
        insert("cat", NULL);
        inorderTraverse(NULL, T);
        inorderTraverse(stdout, NULL);
        preorderTraverse(NULL, T);
        preorderTraverse(stdout, NULL);
        postorderTraverse(NULL, T);
        postorderTraverse(stdout, NULL);
        inorderLeaves(NULL, T);
        inorderLeaves(stdout, NULL);
        printf("Still testing, moving onto the find function\n");
        find(NULL, T);
        find("cat", NULL);
        copyTree(NULL);
        makeEmpty(NULL);
        makeEmpty(&T);

        printf("inserting a lot of nodes to build a tree \n");
        insert("cat", &T);
        insert("rat", &T);
        insert("bat", &T);
        insert("crow", &T);
        insert("dog", &T);
        insert("dan", &T);
        insert("dtsh", &T);
        insert("fox", &T);
        insert("aaz", &T);
        insert("zoo", &T);

        printf("inorder traverse == \n");
        inorderTraverse(stdout, T);
        printf("\n== after traverse ==\n ");

        printf("preorder traverse == \n");
        preorderTraverse(stdout, T);
        printf("\n== after traverse ==\n ");

        printf("postorder traverse == \n");
        postorderTraverse(stdout, T);
        printf("\n== after traverse ==\n");

        printf("inorder leaves == \n");
        inorderLeaves(stdout, T);
        printf("\n== after leaves ==\n");

        printf("Testing the treeHeight functions, should test for height == NULL?\n");
        printf("treeHeight\n");
        int i = treeHeight(T, 0);
        printf("%d\n", i);
        printf("%d\n", treeHeight(nT, 0));

        printf("Testing the find functions\n");
        printf("result = %d\n", find("crow", T));
        printf("result = %d\n", find(NULL, T));
        printf("result = %d\n", find("Mumbai", T));

        printf("Copying T into nT\n");
        nT = copyTree(T);
        inorderTraverse(stdout, nT);

        makeEmpty(&nT);
        printf("\nPrinting nT tree, should return nothing\n");
        inorderTraverse(stdout, nT);
        printf("Printed, please check\n");
        //makeEmpty(&T);

        /*printf("first insertion to make it root\n");
        insert("cat", &K);
        preorderTraverse(stdout, K);
        printf("\nsame word\n");
        insert("cat", &K);
        printf("find the cat\n");
        printf("result = %d\n", find("cat", K));*/

        insert("hello", &K);
        preorderTraverse(stdout, K);
        //printf("error delete = %d\n", deleteItem("Baghdad", &K));
        deleteItem("Baghdad", &K);
        inorderTraverse(stdout, K);
        printf("\n after inorder \n");
        printf("\nnull node = %d\n", deleteItem("hello", NULL));
        printf("null term = %d\n", deleteItem(NULL, &K));
        printf("empty list = %d\n", deleteItem("hello", &nT));
        printf("deleting root from K = %d\n", deleteItem("hello", &K));
        printf("printing K\n");
        inorderTraverse(stdout, K);

        /*inorderTraverse(stdout, T);
        printf("error dlete = %d\n", deleteItem("Bangladesh", &T));
        inorderTraverse(stdout, T);
        printf("\ndelete the root\n");
        printf("root delete (two children) = %d\n", deleteItem("cat", &T));
        inorderTraverse(stdout, T);
        printf("delete aaz i.e. no children at the left subtree\n");
        printf("first delete (no children) = %d\n", deleteItem("aaz", &T));
        inorderTraverse(stdout, T);
        //dtsh should not be in list, but fox should still be in list
        printf("second stuff\n");
        printf("second delete (one child right) = %d\n", deleteItem("dtsh", &T));
        inorderTraverse(stdout, T);
        //dog should not be in list, but dan and fox should
        printf("third delete (two children) = %d\n", deleteItem("dog", &T));
        sleep(2);
        inorderTraverse(stdout, T);
        sleep(1);
        printf("\n\nerror delete = %d\n", deleteItem("Mumbai", &T));*/

        //inorderTraverse(stdout, T);
        printf("error delete = %d\n", deleteItem("hello", &T));

        makeEmpty(&T);

  return 0;
}
