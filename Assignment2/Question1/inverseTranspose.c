#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int n = 5;
int a = 2, b = 1;
/**
 *@brief find size of given array
 *@param char* input
 *@return size
 */
int getsize(char *input)
{
    int size = strlen(input);
    return size;
}
/**
 *@brief create J for given n,a,b
 *@param int input[1000]
 *@param int size
 *@return void
 */
void createInputJ(int inputJ[1000], int size)
{
    for (int i = 0; i < size; i++)
    {
        inputJ[i] = (a * i + b) % n;
    }
}
/**
 *@brief decrypt the code
 *@param char* output
 *@param char* input
 *@param int inputJ[1000]
 *@param int size
 *@return void
 */
void createOutput(char *output, char *input, int inputJ[1000], int size)
{
    int patch = -n;
    for (int i = 0; i < size; i++)
    {
        if (i % n == 0)
        {
            patch += n;
        }
        output[i] = input[inputJ[i] + patch];
        if (output[i] == '*')
        {
            output[i] = '\0';
        }
    }
    output[size] = '\0';

    FILE *stream = fopen("decryptOutput.txt", "w");
    fprintf(stream, "%s\n", output);
}
/**
 *@brief main method of program
 */
int main(int argc, char const *argv[])
{
    clock_t start, end;
    double cpu_time_used;

    start = clock();

    if (argc != 5)
    {
        printf("error: number of args should be 4\n");
        return 1;
    }
    else
    {
        n = atoi(argv[1]);
        a = atoi(argv[2]);
        b = atoi(argv[3]);
        const char* filename = argv[4];
        char input[1000] = "";
        int outputI[1000];
        int inputJ[1000];
        char output[1000];

        FILE *stream = fopen(filename, "r");

        char temp[1000];
        while (fgets(temp, 1000, stream))
        {
            strcat(input, temp);
        }

        int size = getsize(input);

        createInputJ(inputJ, size);

        createOutput(output, input, inputJ, size);

        printf("DONE!\n");
        end = clock();
        cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
        printf("cpu time used is %f\n", cpu_time_used);
        return 0;
    }
}