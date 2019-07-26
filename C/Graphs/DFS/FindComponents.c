/*
 * Ryan Lee
 * Title: FindComponents.c
 * Description: The program scans the input file and assembles a digraph from the result. It then prints out the
 * adjacency list representation of G and also prints out the strong components of G in topographical order.
 */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "Graph.h"

#define MAX_LEN 1000

int main(int argc, char* argv[]){
        int n, u, v, i, j = 0;
        int comp = 0;
        FILE *in, *out;
        //char line[MAX_LEN];
        List S = newList();
        List* A;
        Graph G, T;

        if (argc != 3){
          printf("Usage: %s <input file> <output file>\n", argv[0]);
          exit(1);
        }

        in = fopen(argv[1], "r");
        out = fopen(argv[2], "w");

        if (in == NULL){
          printf("Unable to open file %s for reading\n", argv[1]);
          exit(1);
        }
        if (out == NULL){
          printf("Unable to open file %s for writing\n", argv[2]);
          exit(1);
        }

        fscanf(in, "%d", &n);
        G = newGraph(n);

        while (fscanf(in, "%d %d", &u, &v) == 2){
          if (u == 0 && v == 0){
                break;
          }
          addArc(G, u, v);
        }

        fprintf(out, "Adjacency list representation of G:\n");
        printGraph(out, G);
        fprintf(out, "\n");

        for (i = 1; i <= n; i++){
          append(S, i);
        }
        DFS(G, S);
        T = transpose(G);
        DFS(T, S);

        for (i = 1; i <= n; i++){
          if (getParent(T, i) == NIL){
                comp++;
          }
        }

        A = calloc(comp + 1, sizeof(List));

        /*for (i = 1; i <= comp; i++){
          A[i] = newList();
        }*/

        // work by popping items off stack
        for (i = 1; i <= comp; i++){
          A[i] = newList();
          j = back(S);
          while (getParent(T, j) != NIL){
                prepend(A[i], j);
                deleteBack(S);
                j = back(S);
          }
          if (getParent(T, j) == NIL){
                prepend(A[i], j);
                deleteBack(S);
          }
        }

        fprintf(out, "G contains %d strongly connected components:\n", comp);
        for (i = 1; i <= comp; i++){
          fprintf(out, "Component %d: ", i);
          printList(out, A[i]);
          fprintf(out, "\n");
        }

        for (i = 1; i <= comp; i++){
          freeList(&A[i]);
        }
        free(A);
        freeList(&S);
        freeGraph(&G);
        freeGraph(&T);

        fclose(in);
        fclose(out);

        return(0);
}
