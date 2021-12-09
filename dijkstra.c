#include "node.h"
#include <stdio.h>
#include <stdlib.h>
#include "heap.h"
#include "dijkstra.h"

int * dijkstra(Node **matrix, int m, int n, int start, int *minPath, int *sizeOfArray, int* fastestTime){
    Node** pq = malloc(m*n*sizeof(Node *));
    int * size = malloc(sizeof(int));
    *size = 1;
    Node *first = matrix[start];
    pq[0] = first;
    first->minimum = first->time;

    //need to implement
    while(*size > 0){
        //need to implement
        Node * smallest = getMinimum(pq,size);
        smallest->status = 1;
        Node * up = smallest->up;
        Node * down = smallest->down;
        Node * left = smallest->left;
        Node * right = smallest->right;
        if(up != NULL && up->status != 1 && up->minimum > smallest->minimum + up->time){
            up->minimum = smallest->minimum + up->time;
            up->prev = smallest;
            //need to implement
            insertElement(pq, up, size);
        }
        if(down != NULL && down->status != 1 && down->minimum > smallest->minimum + down->time){
            down->minimum = smallest->minimum + down->time;
            down->prev = smallest;
            //need to implement
            insertElement(pq, down, size);
        }
        if(left != NULL && left->status != 1 && left->minimum > smallest->minimum + left->time){
            left->minimum = smallest->minimum + left->time;
            left->prev = smallest;
            //need to implement
            insertElement(pq, left, size);
        }
        if(right != NULL && right->status != 1 && right->minimum > smallest->minimum + right->time){
            right->minimum = smallest->minimum + right->time;
            right->prev = smallest;
            //need to implement
            insertElement(pq, right, size);
        }
    }
    Node * minimum = NULL;

    for(int i =0; i<n; i++){
        int new_i = (m-1)*n + i;
        if(minimum == NULL || matrix[new_i]->minimum < minimum->minimum){
            minimum = matrix[new_i];
        }
    }
    *fastestTime = minimum->minimum;
    if (minPath == NULL || minimum->minimum < *minPath){
        *minPath = minimum->minimum;
        int * return_ptr = createMinPath(minimum, sizeOfArray);
        return return_ptr;
    }
    return NULL;
}

int * createMinPath(Node* start,int *sizeOfArray){
    Node * ptr = start;

    int lengthOfPath = 0;
    while (ptr != NULL){
        lengthOfPath++;
        ptr = ptr->prev;
    }

    *sizeOfArray = lengthOfPath;
    int * pathPointer = malloc(sizeof(int) *lengthOfPath*2);
    ptr = start;
    
    int iterator = lengthOfPath *2;

    while (ptr != NULL){
        pathPointer[iterator - 1] = ptr->y;
        iterator--;
        pathPointer[iterator - 1] = ptr->x;
        iterator--;
        ptr = ptr->prev;
    }
    return pathPointer;
}