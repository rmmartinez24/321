#include <stdio.h>

void main()
{

    fork();
        printf("Process child 1");
        printf("\n");

    fork();
        printf("Process chidl 2");
        printf("\n");

    exit(0);

}