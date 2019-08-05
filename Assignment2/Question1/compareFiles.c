#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
/**
 *@brief compare input and decrypted text
 */
int main()
{
    clock_t start, end;
    double cpu_time_used;

    start = clock();
    char input[1000] = "";
    char decryptOutput[1000] = "";
    char temp[1000];
    FILE *f1 = fopen("input.txt", "r");
    while (fgets(temp, 1000, f1))
    {
        strcat(input, temp);
    }
    FILE *f2 = fopen("decryptOutput.txt", "r");
    while (fgets(temp, 1000, f2))
    {
        strcat(decryptOutput, temp);
    }

    if (strcmp(input, decryptOutput) == 0)
    {
        printf("same\n");
    }
    else
    {
        printf("not same\n");
    }
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("cpu time used is %f\n", cpu_time_used);

    return 0;
}