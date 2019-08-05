#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int n = 5;
int a = 3, b = 2;
void getnab()
{
    printf("Enter n\n");
    scanf("%d", &n);
    printf("Enter a\n");
    scanf("%d", &a);
    printf("Enter b\n");
    scanf("%d", &b);
}
int getsize(char *input)
{
    int size = strlen(input);
    return size;
}

void createInputJ(int inputJ[1000], int size)
{
    for (int i = 0; i < size; i++)
    {
        inputJ[i] = (a * i + b) % n;
    }
}

void createOutput(char *output, char *input, int inputJ[1000], int size)
{
    int patch = -n;
    for (int i = 0; i < size; i++)
    {
        if (i % n == 0)
        {
            patch += n;
        }
        output[inputJ[i] + patch] = input[i];
        if (output[inputJ[i] + patch] == '*')
        {
            output[inputJ[i] + patch] = '\0';
        }
    }
    output[size] = '\0';

    FILE *stream = fopen("decryptOutput.txt", "w");
    fprintf(stream, "%s\n", output);
}

int main(int argc, char const *argv[])
{

    if (argc != 4)
    {
        printf("error: number of args should be 3");
        return 1;
    }
    else
    {
        n = atoi(argv[1]);
        a = atoi(argv[2]);
        b = atoi(argv[3]);
        char input[1000] = "";
        int outputI[1000];
        int inputJ[1000];
        char output[1000];

        FILE *stream = fopen("output.txt", "r");

        char temp[1000];
        while (fgets(temp, 1000, stream))
        {
            strcat(input, temp);
        }

        int size = getsize(input);

        createInputJ(inputJ, size);

        createOutput(output, input, inputJ, size);

        printf("DONE!\n");

        return 0;
    }
}