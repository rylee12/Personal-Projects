/*
 * Ryan Lee
 * Title: Graph.c
 * Description: This file contains the code needed to create and delete a graph. It utilizes the Depth First Search (DFS)
 * function.
 */

#include<stdio.h>
#include<stdlib.h>
#include"Graph.h"

#define WHITE 1
#define GRAY 2
#define BLACK 3

void Visit(Graph G, List S, int* time, int x);

// private GraphObj type
typedef struct GraphObj{
        int order;
        int size;
        int* color;
        int* parent;
        int* discover;
        int* finish;
        List* L;
} GraphObj;

/*** Constructors-Destructors ***/
// newGraph()
// creates and returns a Graph pointing to a new GraphObj of size n and no edges using adjacency lists
// Preconditions: there is memory available to allocate
Graph newGraph(int n){
        Graph G = malloc(sizeof(GraphObj));
        G->order = n;
        G->size = 0;

        G->color = calloc(n + 1, sizeof(int));
        G->parent = calloc(n + 1, sizeof(int));
        G->discover = calloc(n + 1, sizeof(int));
        G->finish = calloc(n + 1, sizeof(int));
        // malloc(sizeof(List) * (n + 1));
        G->L = calloc(n + 1, sizeof(List));
        for (int i = 1; i <= n; i++){
          G->color[i] = WHITE;
          G->parent[i] = NIL;
          G->discover[i] = UNDEF;
          G->finish[i] = UNDEF;
          G->L[i] = newList();
        }
        return G;
}

// freeGraph()
// frees the graph and deallocates memory
void freeGraph(Graph* pG){
        if (pG != NULL && *pG != NULL){
          for (int i = 1; i <= (*pG)->order; i++){
                freeList(&(*pG)->L[i]);
          }
          free((*pG)->color);
          free((*pG)->parent);
          free((*pG)->discover);
          free((*pG)->finish);
          free((*pG)->L);

          free(*pG);
          *pG = NULL;
        }
}

/*** Access functions ***/
// getOrder()
// returns the number of vertices in the graph
// Preconditions: G != NULL
int getOrder(Graph G){
        if (G == NULL){
          printf("Error: getOrder() function called on NULL graph\n");
          exit(1);
        }
        return G->order;
}

// getSize()
// returns the size of the graph i.e. number of edges
// Preconditions: G != NULL
int getSize(Graph G){
        if (G == NULL){
          printf("Error: getSize() function called on NULL graph\n");
          exit(1);
        }
        return G->size;
}

// getParent()
// returns parent of u in the graph
// Preconditions: G != NULL and 1 <= u <= getOrder(G)
int getParent(Graph G, int u){
        if (G == NULL){
          printf("Error: getParent() function called on NULL graph\n");
          exit(1);
        }
        if (u < 1 || u > getOrder(G)){
          printf("Error: getParent() graph index out of bounds\n");
          exit(1);
        }
        return G->parent[u];
}

// getDiscover()
// returns the discover time of u in the graph
// Preconditions: G != NULL and 1 <= u <= getOrder(G)
int getDiscover(Graph G, int u){
        if (G == NULL){
          printf("Error: getDiscover() function called on NULL graph\n");
          exit(1);
        }
        if (u < 1 || u > getOrder(G)){
          printf("Error: getDiscover() graph index out of bounds\n");
          exit(1);
        }
        return G->discover[u];
}

// getFinish()
// returns the finish time of u in the graph
// Preconditions: G != NULL and 1 <= u <= getOrder(G)
int getFinish(Graph G, int u){
        if (G == NULL){
          printf("Error: getFinish() function called on NULL graph\n");
          exit(1);
        }
        if (u < 1 || u > getOrder(G)){
          printf("Error: getFinish() graph index out of bounds\n");
          exit(1);
        }
        return G->finish[u];
}

/*** Manipulation procedures ***/
// addEdge()
// inserts a new edge joining u to v and v to u. Maintains the lists in sorted order by increasing labels
// Preconditions: G != NULL, 1 <= u <= getOrder(G), 1 <= v <= getOrder(G)
void addEdge(Graph G, int u, int v){
        if (G == NULL){
          printf("Error: addEdge() function called on NULL graph\n");
          exit(1);
        }
        if (u < 1 || u > getOrder(G)){
          printf("Error: addEdge() graph index out of bounds\n");
          exit(1);
        }
        if (v < 1 || v > getOrder(G)){
          printf("Error: addEdge() graph index out of bounds\n");
          exit(1);
        }
        moveFront(G->L[v]);
        moveFront(G->L[u]);
        while (index(G->L[v]) != -1 && u > get(G->L[v])){
          moveNext(G->L[v]);
        }
        while (index(G->L[u]) != -1 && v > get(G->L[u])){
          moveNext(G->L[u]);
        }

        if (index(G->L[v]) == -1){
          append(G->L[v], u);
        }
        else{
          insertBefore(G->L[v], u);
        }

        if (index(G->L[u]) == -1){
          append(G->L[u], v);
        }
        else{
          insertBefore(G->L[u], v);
        }
        //append(G->L[u], v);
        G->size++;
}

// addArc()
// inserts a new directed edge from u to v
// Preconditions: G != NULL, 1 <= u <= getOrder(G), 1 <= v <= getOrder(G)
void addArc(Graph G, int u, int v){
        if (G == NULL){
          printf("Error: addArc() function called on NULL graph\n");
          exit(1);
        }
        if (u < 1 || u > getOrder(G)){
          printf("Error: addArc() graph index out of bounds\n");
          exit(1);
        }
        if (v < 1 || v > getOrder(G)){
          printf("Error: addArc() graph index out of bounds\n");
          exit(1);
        }
        moveFront(G->L[u]);
        while (index(G->L[u]) != -1 && v > get(G->L[u])){
          moveNext(G->L[u]);
        }
        if (index(G->L[u]) == -1){
          append(G->L[u], v);
        }
        else{
          insertBefore(G->L[u], v);
        }
        G->size++;
}

// DFS()
// performs the depth search first algorithm on G
// Preconditions: G != NULL and length(S) == getOrder(G)
// Note: 2nd or 4th option. 1st is bad, 3rd not applicable to several other compilers.
// Answer: Do 2nd option for experience. 4th is probably Visit(time)
void DFS(Graph G, List S){
        if (G == NULL){
          printf("Error: DFS() function called on NULL graph\n");
          exit(1);
        }
        if (length(S) != getOrder(G)){
          printf("Error: List size != Graph size\n");
          exit(1);
        }
        int i, time;
        for (i = 1; i <= getOrder(G); i++){
          G->color[i] = WHITE;
          G->parent[i] = NIL;
          //Discover and finish?
        }
        time = 0;
        moveFront(S);
        // Use S instead of G->L[x]
        while (index(S) != -1){
          i = get(S);
          if (G->color[i] == WHITE){
                Visit(G, S, &time, i);
          }
          moveNext(S);
        }

        i = length(S)/2;
        while (i > 0){
          deleteBack(S);
          i--;
        }
}

// Private Helper function
// Visit()
// Recursive helper function that visits each vertex, discovers it, and then finishes it after its done
// Note: Preconditions should be checked in the DFS function.
// Note: time does not have the ampersand in front because we are reusing the same parameter, not passing it in
// Thus, &time causes a segfault error
void Visit(Graph G, List S, int* time, int x){
        G->discover[x] = ++(*time);
        G->color[x] = GRAY;
        int y;

        moveFront(G->L[x]);
        while (index(G->L[x]) != -1){
          y = get(G->L[x]);
          if (G->color[y] == WHITE){
                G->parent[y] = x;
                Visit(G, S, time, y);
          }
          moveNext(G->L[x]);
        }

        G->color[x] = BLACK;
        G->finish[x] = ++(*time);
        prepend(S, x);
}

/*** Other operations ***/
// transpose()
// returns a reference to a new graph that is a transpose of graph G i.e. reverses the arcs of G
// Preconditions: G != NULL
Graph transpose(Graph G){
        if (G == NULL){
          printf("Error: transpose() function called on NULL graph\n");
          exit(1);
        }
        int i, j, x;
        j = getOrder(G);
        Graph T = newGraph(j);
        //printf("extra help plz\n");
        //printf("help\n");
        for (i = 1; i <= getOrder(G); i++){
          moveFront(G->L[i]);
          while (index(G->L[i]) != -1){
                x = get(G->L[i]);
                addArc(T, x, i);
                moveNext(G->L[i]);
          }
        }
        return T;
}

// copyGraph()
// returns a reference to a new graph that is a copy of graph G
// Preconditions: G != NULL
Graph copyGraph(Graph G){
        if (G == NULL){
          printf("Error: copyGraph() function called on NULL graph\n");
          exit(1);
        }
        List A;
        Graph copy = newGraph(getOrder(G));
        for (int i = 1; i <= getOrder(G); i++){
          A = copyList(G->L[i]);
          copy->L[i] = A;
        }
        return copy;
}

// printGraph()
// prints the adjacency list representation of G to the file pointed to by out
// Preconditions: out != NULL and G != NULL
void printGraph(FILE* out, Graph G){
        if (G == NULL){
          printf("Error: printGraph() function called on NULL graph\n");
          exit(1);
        }
        if (out == NULL){
          printf("Error: printing to a NULL file\n");
          exit(1);
        }
        for (int i = 1; i <= getOrder(G); i++){
          fprintf(out, "%d: ", i);
          printList(out, G->L[i]);
          fprintf(out, "\n");
        }
}

