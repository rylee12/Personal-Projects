/*
 * Ryan Lee
 * Title: Graph.c
 * Description: This file contains the functions and definitions needed to create and delete a graph. It also
 * can find the shortest path and distance from a source vertex to any other vertex. This graph file utilizes the
 * BFS search function.
 */

#include<stdio.h>
#include<stdlib.h>
#include"Graph.h"

#define WHITE 1
#define GRAY 2
#define BLACK 3

// private GraphObj type
typedef struct GraphObj{
        int order;
        int size;
        int source;
        int* color;
        int* parent;
        int* distance;
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
        G->source = NIL;
        G->color = calloc(n + 1, sizeof(int));
        G->parent = calloc(n + 1, sizeof(int));
        G->distance = calloc(n + 1, sizeof(int));
        // malloc(sizeof(List) * (n + 1));
        G->L = calloc(n + 1, sizeof(List));
        for (int i = 1; i <= n; i++){
          G->color[i] = WHITE;
          G->distance[i] = INF;
          G->parent[i] = NIL;
          G->L[i] = newList();
        }
        return G;
}

// freeGraph()
// frees the graph and deallocates memory
void freeGraph(Graph* pG){
        if (pG != NULL && *pG != NULL){
          free((*pG)->color);
          free((*pG)->parent);
          free((*pG)->distance);
          for (int i = 1; i <= (*pG)->order; i++){
                freeList(&(*pG)->L[i]);
          }
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

// getSource()
// returns the source i.e. "head" of the graph
// Preconditions: G != NULL
int getSource(Graph G){
        if (G == NULL){
          printf("Error: getSource() function called on NULL graph\n");
          exit(1);
        }
        return G->source;
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
          printf("Error: Graph index out of bounds\n");
          exit(1);
        }
        return G->parent[u];
}

// getDist()
// returns the distance from the source to u
// Preconditions: G != NULL and 1 <= u <= getOrder(G)
int getDist(Graph G, int u){
        if (G == NULL){
          printf("Error: getDist() function called on NULL graph\n");
          exit(1);
        }
        if (u < 1 || u > getOrder(G)){
          printf("Error: getDist() graph index out of bounds\n");
          exit(1);
        }
        return G->distance[u];
}

// getPath()
// returns the path from the source to u
// Preconditions: G != NULL, 1 <= u <= getOrder(G), and source is not NIL
void getPath(List L, Graph G, int u){
        if (G == NULL){
          printf("Error: getPath() function called on NULL graph\n");
          exit(1);
        }
        if (u < 1 || u > getOrder(G)){
          printf("Error: getPath() graph index out of bounds\n");
          exit(1);
        }
        if (getSource(G) == NIL){
          printf("Error: Source is NIL\n");
          exit(1);
        }
        if (u == getSource(G)){
          append(L, u);
        }
        else if (G->parent[u] == NIL){
          append(L, NIL);
        }
        else{
          //append(L, u);
          getPath(L, G, G->parent[u]);
          append(L, u);
        }
}

/*** Manipulation procedures ***/
// makeNULL()
// deletes all edges of G and restores it to its original (no edge) state i.e. a null graph
// Preconditions: G != NULL
void makeNull(Graph G){
        if (G == NULL){
          printf("Error: makeNull() function called on NULL graph\n");
          exit(1);
        }
        for (int i = 1; i <= G->order; i++){
          clear(G->L[i]);
        }
}

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

// BFS()
// Systematically explores the edges of G to discover every vertex that is reachable from s, computes the distance
// from s to all such reachable vertices, and produces a BFS tree with root s that contains all vertices reachable
// from s
// Preconditions: G != NULL and 1 <= s <= getOrder(G)
void BFS(Graph G, int s){
        if (G == NULL){
          printf("Error: BFS() function called on NULL graph\n");
          exit(1);
        }
        if (s < 1 || s > getOrder(G)){
          printf("Error: BFS() parameter s out of bounds\n");
          exit(1);
        }
        List L;
        int i, j;
        for (i = 1; i <= getOrder(G); i++){
          G->color[i] = WHITE;
          G->distance[i] = INF;
          G->parent[i] = NIL;
        }
        G->color[s] = GRAY;
        G->distance[s] = 0;
        G->parent[s] = NIL;
        // This line below is VERY IMPORTANT!!!
        G->source = s;
        // Queue. Treat the List as a Queue. First in, first out
        L = newList();
        append(L, s);
        while (length(L) > 0){
          i = front(L);
          deleteFront(L);

          if (length(G->L[i]) > 0){
                moveFront(G->L[i]);

                while (index(G->L[i]) != -1){
                  j = get(G->L[i]);

                  if (G->color[j] == WHITE){
                        G->color[j] = GRAY;
                        G->distance[j] = G->distance[i] + 1;
                        G->parent[j] = i;
                        append(L, j);
                  }
                  moveNext(G->L[i]);
                }
          }
          G->color[i] = BLACK;
        }
        freeList(&L);
}

/*** Other operations ***/
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

