#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
    if (argc != 2)
    {
        const char* a = "a.out";
        printf("error");
        
        return 1;
    }
    else
    {
        int n = atoi(argv[1]);
        printf("%d\n",n);
        return 0;
    }
}
