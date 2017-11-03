#include"ls.h"

int main(int argc, char* argv[])
{
    if (argc == 1)
    {
        dir_order(".");
    }
    else 
    {
        dir_order(argv[1]);
    }
    return 0;
}

