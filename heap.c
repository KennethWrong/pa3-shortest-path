#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "node.h"
#include "heap.h"


void swap(int index1, int index2, Node **array){
    Node * tmp = array[index1];
    array[index1] = array[index2];
    array[index2] = tmp;
    return;
}

int getLeftChildIndex(int parentIndex){
    return 2 * parentIndex +1;
}

int getRightChildIndex(int parentIndex){
    return 2 *parentIndex +2;
}
int getParentIndex(int childIndex){
    return (childIndex -1)/2;
}

bool hasLeftChild(int index, int size){
    return getLeftChildIndex(index) < size;
}

bool hasRightChild(int index, int size){
    return getRightChildIndex(index) < size;
}

bool hasParent(int index){
    return getParentIndex(index) >= 0;
}

Node * leftChild(int index, Node **array){
    return array[getLeftChildIndex(index)];
}

Node *rightChild(int index, Node **array){
    return array[getRightChildIndex(index)];
}

Node *parent(int index, Node **array){
    return array[getParentIndex(index)];
}



Node * getMinimum(Node **array, int* size){
    Node * minNode = array[0];
    int deleted = minNode->minimum;
    array[0] = array[*size - 1];
    *size = *size - 1;
    heapifyDown(array, *size);
    // printf("After deleting element %d: ",deleted);
    // printHeap(array,*size);
    return minNode;
}

void insertElement(Node **array, Node * newElement, int * size){
    array[*size] = newElement;
    *size = *size + 1;
    heapifyUp(*size, array);
    // printf("After inserting new element %d: ",newElement->minimum);
    // printHeap(array,*size);
}
//something wrong with heapify up
void heapifyUp(int size, Node **array){
    int index = size -1;
    while(hasParent(index) && parent(index, array)->minimum > array[index]->minimum){
        // printf("\narray index minimum: %d\n",array[index]->minimum);
        // printf("\n%d\n",index);
        swap(getParentIndex(index),index, array);
        index = getParentIndex(index);
    }
}

void heapifyDown(Node **array, int size){
    int index = 0;
    while(hasLeftChild(index,size)){
        // printf("Curr Index:%d, hasRightChild: %d, %d < %d \n",index,hasRightChild(index,size),rightChild(index, array)->minimum,leftChild(index,array)->minimum);
        int smallerChildIndex = getLeftChildIndex(index);
        if(hasRightChild(index,size) && rightChild(index, array)->minimum < leftChild(index,array)->minimum){
            smallerChildIndex = getRightChildIndex(index);
        }
        // printf("Smaller Child: %d\n",smallerChildIndex);
        if(array[index]->minimum < array[smallerChildIndex]->minimum){
            break;
        }else{
            swap(index,smallerChildIndex,array);
        }
        index  = smallerChildIndex;
    }
}

void printHeap(Node **array, int size){
    printf("\n");
    for(int i =0; i < size; i++){
        printf("%d ",array[i]->minimum);
    }
    printf("\n");
}

