/*
 * Ryan Lee
 * Title: GraphClient.c
 * Description: This is a test client meant to test the Graph ADT
 */

#include<stdio.h>
#include<stdlib.h>
#include"Graph.h"

int main(int argc, char* argv[]){
        int i, d = 0;
        int n = 30;
        List A = newList();
        Graph G = NULL;

        G = newGraph(n);

        addEdge(G, 1, 2);
        addEdge(G, 1, 3);
        addEdge(G, 1, 6);
        addEdge(G, 1, 8);
        addEdge(G, 2, 4);
        addEdge(G, 2, 5);
        addEdge(G, 2, 7);
        addEdge(G, 2, 8);
        addEdge(G, 3, 2);
        addEdge(G, 4, 7);
        addEdge(G, 4, 9);
        addEdge(G, 5, 8);
        addEdge(G, 6, 9);
        addEdge(G, 7, 8);

        printGraph(stdout, G);

        BFS(G, 2);
        getPath(A, G, 8);
        printf("getPath = ");
        printList(stdout, A);
        printf("\n");

        //Free Objects
        freeList(&A);
        freeGraph(&G);

        return(0);
}
