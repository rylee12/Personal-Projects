/*
 * Ryan Lee
 * Title: Graph.h
 * Description: This file contains the function and structure definitions for the Graph ADT
 */

#include<stdio.h>
#include<stdlib.h>
#include "List.h"
#ifndef GRAPH_H
#define GRAPH_H

#define INF -1
#define NIL -2

/*** Exported type ***/
typedef struct GraphObj* Graph;

/*** Constructors-Destructors ***/
Graph newGraph(int n);

void freeGraph(Graph* pG);

/*** Access functions ***/
int getOrder(Graph G);

int getSize(Graph G);

int getSource(Graph G);

int getParent(Graph G, int u);

int getDist(Graph G, int u);

void getPath(List L, Graph G, int u);

/*** Manipulation procedures ***/
void makeNull(Graph G);

void addEdge(Graph G, int u, int v);

void addArc(Graph G, int u, int v);

void BFS(Graph G, int s);

/*** Other operations ***/
void printGraph(FILE* out, Graph G);

#endif
