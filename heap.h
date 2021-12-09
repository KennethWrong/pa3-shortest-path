#include <stdbool.h>
void swap(int index1, int index2, Node **array);
int getLeftChildIndex(int parentIndex);
int getRightChildIndex(int parentIndex);
int getParentIndex(int childIndex);
bool hasLeftChild(int index, int size);
bool hasRightChild(int index, int size);
bool hasParent(int index);
Node * leftChild(int index, Node **array);
Node *rightChild(int index, Node **array);
Node *parent(int index, Node **array);
Node * getMinimum(Node **array, int* size);
void insertElement(Node **array, Node * newElement, int * size);
void heapifyUp(int size, Node **array);
void heapifyDown(Node **array, int size);
void printHeap(Node ** array,int size);