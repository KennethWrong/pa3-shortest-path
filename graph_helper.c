#include <stdio.h>
#include <stdlib.h>
#include <math.h> 
#include "node.h"
#include "dijkstra.h"

int read_file(char* infile,char*tfile, char *ffile, char *pfile);
Node * create_node(int weight);
void link_nodes(Node ** matrix, int m, int n);
void reverseChanges(Node **matrix, int size);
int writeTwoDimensionalGrid(char *writeFile, Node **matrix, int m, int n);
int writeFastestTime(char *writeFile, int * fastestTimes, int n);
int writeFastestPath(char *writeFile, int sizeOfArray, int *array, int min_weight);
void freeMatrix(Node**matrix, int size);

int MAX_SIZE = 999999999; 

int read_file(char* infile, char*tfile, char *ffile, char *pfile)
{
    FILE *read_ptr;
    read_ptr = fopen(infile, "rb");

    if(read_ptr == NULL)
    {
        return 1;
    }

    fseek(read_ptr,0,SEEK_END);
    int size_of_file = ftell(read_ptr);
    fseek(read_ptr,0,SEEK_SET);

    int * curr_int = malloc(sizeof(int));
    if(curr_int == NULL)
    {
        return 1;
    }
    int m,n;

    fread(curr_int,sizeof(short) ,1,read_ptr);
    m = *curr_int;
    fread(curr_int,sizeof(short) ,1,read_ptr);
    n = *curr_int;
    Node** matrix = malloc(n * m * sizeof(Node *));
    if(matrix == NULL)
    {
        free(curr_int);
        return 1;
    }
    int i = 0;

    while (fread(curr_int,sizeof(short) ,1,read_ptr))
    {
        Node *new_node = create_node(*curr_int);
        if(new_node == NULL)
        {
            freeMatrix(matrix, i);
            free(curr_int);
            return 1;
        }
    
        matrix[i] = new_node;
        i++;
    }

    free(curr_int);
    fclose(read_ptr);

    int * minPath = malloc(sizeof(int));
    if(minPath == NULL)
    {
        freeMatrix(matrix, m*n);
        return 1;
    }
    *minPath = MAX_SIZE;
    int *sizeOfArray = malloc(sizeof(int));
    if(sizeOfArray == NULL)
    {
        free(minPath);
        freeMatrix(matrix, m*n);
        return 1;
    }
    int *fastestTimes = malloc(sizeof(int)*n);
    if(fastestTimes == NULL)
    {
        free(sizeOfArray);
        free(minPath);
        freeMatrix(matrix, m*n);
        return 1;
    }
    *sizeOfArray = -1;
    int *return_array = NULL;

    int *fastestTime = malloc(sizeof(int));
    if(fastestTime == NULL)
    {
        free(fastestTimes);
        free(sizeOfArray);
        free(minPath);
        freeMatrix(matrix, m*n);
        return 1;
    }

    link_nodes(matrix,m,n);
    for(int i=0; i<n;i++){
        int *result = dijkstra(matrix,m,n,i, minPath, sizeOfArray, fastestTime);
        if(result != NULL){
            if(return_array != NULL){
                free(return_array);
            }
            return_array = result;
        }
        fastestTimes[i] = *fastestTime;
        reverseChanges(matrix,m*n);
    }

    int r1 = writeFastestPath(pfile,*sizeOfArray, return_array, *minPath);
    int r2 = writeFastestTime(ffile, fastestTimes,n);
    int r3 = writeTwoDimensionalGrid(tfile, matrix, m, n);

    if(r1 || r2 || r3){
        free(minPath);
        free(sizeOfArray);
        free(fastestTimes);
        free(fastestTime);
        free(return_array);
        freeMatrix(matrix, m*n);
        return 1;
    }
    

    free(minPath);
    free(sizeOfArray);
    free(fastestTimes);
    free(fastestTime);
    freeMatrix(matrix, m*n);
    //free matrix and free nodes

    return 0;
}

Node * create_node(int weight){
    Node *new_node = malloc(sizeof(Node));
    new_node->time = weight;
    new_node->minimum = MAX_SIZE;
    new_node->up = NULL;
    new_node->prev = NULL;
    new_node->status = -1;
    new_node->down = NULL;
    new_node->left = NULL;
    new_node->right = NULL;

    return new_node;
}

void reverseChanges(Node **matrix, int size){
    for(int i =0; i <size; i++){
        matrix[i]->minimum = MAX_SIZE;
        matrix[i]->prev = NULL;
        matrix[i]->status = -1;
    }
}


void link_nodes(Node ** matrix, int m, int n){
    // m is row, n is column 5,4
    int i;
    int new_i;

    for(int r = 0; r < m; r++){
        for(int c = 0; c < n; c++){
            //up
            int i = r *n + c;
            matrix[i]->x = r;
            matrix[i]->y = c;
            if(r - 1 >= 0){
                new_i = (r-1)*n + c;
                matrix[i]->up = matrix[new_i];
            }
            //down
            if(r+1 < m){
                new_i = (r+1)*n + c;
                matrix[i]->down = matrix[new_i];
            }
            //left
            if(c-1 >= 0){
                new_i = (r)*n + c - 1;
                matrix[i]->left = matrix[new_i];
            }
            //right
            if(c+1 < n){
                new_i = (r)*n + c + 1;
                matrix[i]->right = matrix[new_i];
            }
        }
    }
    return;
}

//4_5.t
int writeTwoDimensionalGrid(char *writeFile, Node **matrix, int m, int n){
    FILE *fp;
    fp = fopen( writeFile , "w" );
    if(fp == NULL){
        return 1;
    }

    fprintf(fp,"%hd %hd\n",(short) m,(short)n );
    for (int r = 0; r < m*n; r ++){
        if(r%n == 0 && r != 0){
            fprintf(fp,"\n");
        }
        fprintf(fp,"%hd",(short)matrix[r]->time);
        if(r%n != n -1){
            fprintf(fp," ");
        }
    }
    fclose(fp);
    return 0;
}

int writeFastestTime(char *writeFile, int * fastestTimes, int n){
    //4_5.f
    FILE *fp;
    short n_short = (short)n; 
    fp = fopen( writeFile , "wb" );
    if(fp == NULL){
        return 1;
    }


    fwrite(&n_short,sizeof(short),1,fp);
    for(int i =0; i<n;i++){
        fwrite(&fastestTimes[i],sizeof(int),1,fp);
    }
    fclose(fp);
    return 0;

}

int writeFastestPath(char *writeFile, int sizeOfArray, int *array, int min_weight){
    //4_5.p
    FILE *fp;
    fp = fopen( writeFile , "wb" );
    if(fp == NULL){
        return 1;
    }
    int i = 0;
    short x1;
    short x2;

    fwrite(&min_weight,sizeof(int),1,fp);
    fwrite(&sizeOfArray,sizeof(int),1,fp);

    while(i <= sizeOfArray*2 -1){
        x1 = (short)array[i];
        x2 = (short)array[i+1];
        fwrite( &x1, sizeof(short), 1, fp );
        fwrite( &x2, sizeof(short), 1, fp );
        i += 2;
    }
    fclose(fp);
    return 0;
}

void freeMatrix(Node**matrix, int size){
    for(int i=0; i<size; i++){
        free(matrix[i]);
    }
    free(matrix);
}