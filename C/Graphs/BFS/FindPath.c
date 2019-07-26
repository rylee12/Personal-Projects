/*
 * Ryan Lee
 * Title: FindPath.c
 * Description: The FindPath program takes the input file, scans it, and then prints out the resulting graph.
 * It also prints out the shortest path and distance from the source vertex to another vertex.
 */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "Graph.h"

// Test's 2 and 3.
int main(int argc, char * argv[]){
        FILE *in, *out;
        int n, u, v = 0;
        List L = newList();
        Graph G;

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
          addEdge(G, u, v);
        }

        printGraph(out, G);

        while (fscanf(in, "%d %d", &u, &v) == 2){
          if (u == 0 && v == 0){
                break;
          }
          BFS(G, u);
          getPath(L, G, v);
          if (getDist(G, v) == -1){
                fprintf(out, "\nThe distance from %d to %d is infinity\n", u, v);
                fprintf(out, "No %d-%d path exists\n", u, v);
          }
          else{
                fprintf(out, "The distance from %d to %d is %d\n", u, v, getDist(G, v));
                fprintf(out, "A shortest %d-%d path is: ", u, v);
                printList(out, L);
                fprintf(out, "\n");
          }
          clear(L);
        }

        freeList(&L);
        freeGraph(&G);

        fclose(in);
        fclose(out);
}
