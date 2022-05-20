#include <iostream>

#include <luma.h>

int main(int argc, char **argv)
{
    if(argc < 2)
        exit(1);

    compile(argv[1]);

    return 0;   
}