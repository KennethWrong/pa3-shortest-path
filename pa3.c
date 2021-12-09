#include <stdio.h>
#include <stdlib.h>
#include "graph_helper.h"

int main(int argc, char *argv[])
{
    int res = read_file(argv[1],argv[2],argv[3],argv[4]);
    if(res == 1){
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
