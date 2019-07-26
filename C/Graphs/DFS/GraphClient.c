/*
 * Ryan Lee
 * Title: GraphClient.c
 * Description: Test client for the Graph ADT
 */

#include<stdio.h>
#include<stdlib.h>
#include"Graph.h"

int main(int argc, char* argv[]){
        int i, d = 0;
        int n = 8;
        List A = newList();
        Graph G, T, C;

        G = newGraph(n);

        /*addArc(G, 1, 2);
        //addArc(G, 1, 3);
        addArc(G, 1, 6);
        //addArc(G, 1, 8);
        addArc(G, 2, 4);
        addArc(G, 2, 5);
        //addArc(G, 2, 7);
        //addArc(G, 2, 8);
        //addArc(G, 3, 2);
        addArc(G, 4, 7);
        addArc(G, 4, 9);
        addArc(G, 5, 8);
        addArc(G, 6, 9);
        addArc(G, 7, 8);*/

        addArc(G, 1, 2);
        addArc(G, 2, 3);
        addArc(G, 2, 5);
        addArc(G, 2, 6);
        addArc(G, 3, 4);
        addArc(G, 3, 7);
        addArc(G, 4, 3);
        addArc(G, 4, 8);
        addArc(G, 5, 1);
        addArc(G, 5, 6);
        addArc(G, 6, 7);
        addArc(G, 7, 6);
        addArc(G, 7, 8);
        addArc(G, 8, 8);

        printGraph(stdout, G);
        printf("\n");
        printf("copy graph\n");
        C = copyGraph(G);
        printGraph(stdout, C);
        printf("\n");

        for (int i = 1; i <= n; i++){
          append(A, i);
        }
        //T = transpose(G);
        DFS(G, A);
        printf("pass\n");
        printList(stdout, A);
        printf("\n");

        T = transpose(G);
        printf("pass2\n");
        DFS(T, A);

        printList(stdout, A);
        printf("\n");

        T = transpose(G);
        printf("pass2\n");
        DFS(T, A);

        printList(stdout, A);
        printf("\n");

        //Free Objects
        freeList(&A);
        freeGraph(&G);
        freeGraph(&T);

        return(0);
}
