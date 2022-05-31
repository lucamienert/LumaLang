#include <iostream>
#include <string>

#include <luma.h>

int main(int argc, char **argv)
{
    if(argc < 2)
        exit(1);

    if(std::string(argv[1]) == "compile")
        compile(argv[1]);

    return 0;   
}
