// Ryan K Lee
// Title: List.c
// Description: This file contains the structure definitions and methods needed to create,
// manipulate, maintain, and delete a List ADT
//
// Note: The cursor is a pointer the client can use to navigate the List ADT.
// The index is the element the cursor is at, ranging from 0 to length - 1.

#include<stdio.h>
#include<stdlib.h>
#include "List.h" 

// structures
typedef struct NodeObj{
	int data;
	struct NodeObj* next;
	struct NodeObj* prev;
} NodeObj;

typedef NodeObj* Node;

typedef struct ListObj{
	Node front;
	Node back;
	Node cursor;
	int length;
	int index;
} ListObj;

Node newNode(int data){
	Node N = malloc(sizeof(NodeObj));
	N->data = data;
	N->next = NULL;
	N->prev = NULL;

	return(N);
}

void freeNode(Node* N){
	if (N != NULL && *N != NULL){
		free(*N);
		*N = NULL;
	}
}

// Constructors and Destructors
List newList(void){
	List L = malloc(sizeof(ListObj));
	L->front = L->back = NULL;
	L->cursor = NULL;
	L->length = 0;
	L->index = -1;

	return(L);
}

void freeList(List* pL){
	if (pL != NULL && *pL != NULL){
		clear(*pL);
	}
	free(*pL);
	*pL = NULL;
}

// Access functions
int length(List L){
	if (L == NULL){
		printf("Error: length() called on NULL List reference\n");
		exit(1);
	}
	return L->length;
}

int index(List L){
	if (L == NULL){
		printf("Error: index() called on NULL List reference\n");
		exit(1);
	}
	if (L->cursor == NULL){
		L->index = -1;
		return -1;
	}
	else{
		return L->index;
	}
}

int front(List L){
	if (L == NULL){
		printf("Error: front() called on NULL List reference\n");
		exit(1);
	}
	if (length(L) <= 0){
		printf("Error: front() called on empty list\n");
		exit(1);
	}
	return (L->front)->data;
}

int back(List L){
	if (L == NULL){
		printf("Error: back() called on NULL List reference\n");
		exit(1);
	}
	if (length(L) <= 0){
		printf("Error: back() called on empty list\n");
		exit(1);
	}
	return (L->back)->data;
}

int get(List L){
	if (L == NULL){
		printf("Error: get() called on NULL List reference\n");
		exit(1);
	}
	if (length(L) <= 0){
		printf("Error: get() called on empty list\n");
		exit(1);
	}
	if (index(L) < 0){
		printf("Error: get() called on undefined cursor\n");
		exit(1);
	}
	return (L->cursor)->data;
}

// returns 1 if equal, 0 if not equal
int equals(List A, List B){
	if (A == NULL || B == NULL){
		printf("Error: equals() called on NULL List reference\n");
		exit(1);
	}

	Node N = A->front;
	Node M = B->front;
	if (length(A) != length(B)){
		return 0;
	}
	else{
		while (N != NULL){
			if (N->data != M->data)
				return 0;
			N = N->next;
			M = M->next;
		}
		return 1;
	}

}

// Manipulation procedures
void clear(List L){
	if (L == NULL){
		printf("Error: clear() called on NULL List reference\n");
		exit(1);
	}
	// could use deleteFront or deleteBack
	while (length(L) > 0){
		Node N = L->front;
		L->front = (L->front)->next;
		N->next = NULL;
		freeNode(&N);
		L->length--;
	}
	L->cursor = NULL;
	L->length = 0;
	L->index = -1;
}

void moveFront(List L){
	if (L == NULL){
		printf("Error: moveFront() called on NULL List reference\n");
		exit(1);
	}
	if (length(L) > 0){
        L->cursor = L->front;
        L->index = 0;
    }
    else{
        return;
    }
}

void moveBack(List L){
	if (L == NULL){
		printf("Error: moveBack() called on NULL List reference\n");
		exit(1);
	}
	if (length(L) > 0){
        L->cursor = L->back;
        L->index = L->length - 1;
    }
    else{
        return;
    }
}

void movePrev(List L){
	if (L == NULL){
		printf("Error: movePrev() called on NULL List reference\n");
		exit(1);
	}
	if (L->cursor == NULL){
        return;
    }
    if (L->cursor == L->front){
        L->cursor = NULL;
        L->index = -1;
    }
    else{
        L->cursor = (L->cursor)->prev;
        L->index--;
    }
}

void moveNext(List L){
	if (L == NULL){
		printf("Error: moveNext() called on NULL List reference\n");
		exit(1);
	}
	if (L->cursor == NULL){
        return;
    }
    if (L->cursor == L->back){
        L->cursor = NULL;
        L->index = -1;
    }
    else{
        L->cursor = (L->cursor)->next;
        L->index++;
    }
}

void prepend(List L, int data){
	if (L == NULL){
		printf("Error: prepend() called on NULL List reference\n");
		exit(1);
	}
	Node N = newNode(data);
        
    if (length(L) == 0){
        L->front = L->back = N;
    }
    else{
        (L->front)->prev = N;
        N->next = L->front;
        L->front = N;
        if (index(L) >= 0){
            if (index(L) == length(L) - 1){
                L->index = -1;
            }
            else{
                L->index++;
            }
        }
    }
    L->length++;
}

void append(List L, int data){
	if (L == NULL){
		printf("Error: append() called on NULL List reference\n");
		exit(1);
	}

	Node N = newNode(data);

    if (length(L) == 0){
        L->front = L->back = N;
    }
    else{
        (L->back)->next = N;
        N->prev = L->back;
        L->back = N;
    }
    L->length++;
}

void insertBefore(List L, int data){
	if (L == NULL){
		printf("Error: insertBefore() called on NULL List reference\n");
		exit(1);
	}
	if (length(L) <= 0){
		printf("Error: insertBefore() called on empty list\n");
		exit(1);
	}
	if (index(L) < 0){
		printf("Error: insertBefore() called on undefined cursor\n");
		exit(1);
	}

	Node N = newNode(data);

    if (L->cursor == L->front){
        N->next = L->front;
        (L->front)->prev = N;
        L->front = N;
    }
    else{
        N->next = L->cursor;
        N->prev = (L->cursor)->prev;
        ((L->cursor)->prev)->next = N;
        (L->cursor)->prev = N;
    }
    L->length++;
    L->index++;
}

void insertAfter(List L, int data){
	if (L == NULL){
		printf("Error: insertAfter() called on NULL List reference\n");
		exit(1);
	}
	if (length(L) <= 0){
		printf("Error: insertAfter() called on empty list\n");
		exit(1);
	}
	if (index(L) < 0){
		printf("Error: insertAfter() called on undefined cursor\n");
		exit(1);
	}

	Node N = newNode(data);

    // could find out using index and compare to length?
    if (L->cursor == L->back){
        N->prev = L->back;
        (L->back)->next = N;
        L->back = N;
    }
    else{
        N->prev = L->cursor;
        N->next = (L->cursor)->next;
        ((L->cursor)->next)->prev = N;
        (L->cursor)->next = N;
    }
    L->length++;
}

void insertOrder(List L, int data){
	if (L == NULL){
		printf("Error: insertOrder() called on NULL List reference\n");
		exit(1);
	}
	Node M;
	moveFront(L);
	while (index(L) >= 0){
		M = L->cursor;
		if (data <= M->data)
			break;
		moveNext(L);
	}
	if (index(L) == -1)
		append(L, data);
	else
		insertBefore(L, data);
	L->length++;
}

void deleteFront(List L){
	if (L == NULL){
		printf("Error: deleteFront() called on NULL List reference\n");
		exit(1);
	}
	if (length(L) <= 0){
		printf("Error: deleteFront() called on empty list\n");
		exit(1);
	}
	Node N = L->front;
    if (length(L) > 1){
        (N->next)->prev = NULL;
        L->front = (L->front)->next;
        N->next = NULL;
        if (index(L) <= 0){
            L->index = -1;
        }
        else{
            L->index--;
        }
    }
    else{
        L->front = L->back = NULL;
        L->index = -1;
    }
    L->length--;
    freeNode(&N);
}

void deleteBack(List L){
	if (L == NULL){
		printf("Error: deleteBack() called on NULL List reference\n");
		exit(1);
	}
	if (length(L) <= 0){
		printf("Error: deleteBack() called on empty list\n");
		exit(1);
	}
	Node N = L->back;
    if (length(L) > 1){
        (N->prev)->next = NULL;
        L->back = (L->back)->prev;
        N->prev = NULL;
        if (index(L) == length(L) - 1){
            L->index = -1;
        }
    }
    else{
        L->back = L->front = NULL;
        L->index = -1;
    }
    L->length--;
    freeNode(&N);
}

void delete(List L){
	if (L == NULL){
		printf("Error: delete() called on NULL List reference\n");
		exit(1);
	}
	if (length(L) <= 0){
		printf("Error: delete() called on empty list\n");
		exit(1);
	}
	if (index(L) < 0){
		printf("Error: delete() called on undefined cursor\n");
		exit(1);
	}
	Node N = NULL;

    if (L->cursor == L->front){
        N = L->front;
        L->front = (L->front)->next;
        (L->front)->prev = NULL;
        N->next = NULL;
        L->cursor = NULL;
        L->index = -1;
    }
    else if (L->cursor == L->back){
        N = L->back;
        L->back = (L->back)->prev;
        (L->back)->next = NULL;
        N->prev = NULL;
        L->cursor = NULL;
        L->index = -1;
    }
    else{
        N = L->cursor;
        (N->prev)->next = N->next;
        (N->next)->prev = N->prev;
        N->next = NULL;
        N->prev = NULL;
        L->cursor = NULL;
        L->index = -1;
    }
    freeNode(&N);
    N = NULL;
    L->length--;
}

// Miscellaneous
void printList(FILE* out, List L){
	if (out == NULL){
		printf("Error: printList() out file does not exist\n");
		exit(1);
	}
	if (L == NULL){
		printf("Error: printList() called on NULL List reference\n");
		exit(1);
	}
	Node N;
    for (N = L->front; N != NULL; N = N->next){
        fprintf(out, "%d ", N->data);
    }
    //fprintf(out, "\n");
}

List copyList(List L){
	if (L == NULL){
		printf("Error: copyList() called on NULL List reference\n");
		exit(1);
	}
	List copy = newList();
    Node N, M;

    if (length(L) > 0){
        N = L->front;
        M = newNode(N->data);
        copy->front = M;
        copy->length++;
        N = N->next;

        while (N != NULL){
            M->next = newNode(N->data);
            (M->next)->prev = M;
            M = M->next;
            copy->length++;
            N = N->next;
        }
    }
    return copy;
}