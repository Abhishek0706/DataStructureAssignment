#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int n;
int height;
int dataOutput = 1;

struct node
{
    int data;
    struct node *first;
    struct node *second;
    struct node *third;
    struct node *fourth;
};
int power(int a, int b)
{
    if (b == 0)
    {
        return 1;
    }
    int temp = a;
    for (int i = 1; i < b; i++)
    {
        a = a * temp;
    }
    return a;
}
struct node *newNode()
{

    struct node *node = (struct node *)malloc(sizeof(struct node));
    //-1 if it is not leaf
    node->data = -1;
    node->first = NULL;
    node->second = NULL;
    node->third = NULL;
    node->fourth = NULL;

    return (node);
}
int findlevel(int n)
{
    if (n == 1)
    {
        return 1;
    }
    int count = 2;
    while (n / 2 != 1)
    {
        n /= 2;
        count++;
    }
    return count;
}

struct node *nextLevel(struct node *input, int level, int r, int c, int data[n][n])
{
    //leaf

    if (level == 1)
    {
        input->data = data[r][c];
        input->first = NULL;
        input->second = NULL;
        input->third = NULL;
        input->fourth = NULL;
    }

    //not leaf
    else
    {
        int shift = height - level + 1;
        shift = n / power(2, shift);

        struct node *newNode1 = newNode();
        newNode1 = nextLevel(newNode1, level - 1, r, c, data);
        struct node *newNode2 = newNode();
        newNode2 = nextLevel(newNode2, level - 1, r, c + shift, data);
        struct node *newNode3 = newNode();
        newNode3 = nextLevel(newNode3, level - 1, r + shift, c, data);
        struct node *newNode4 = newNode();
        newNode4 = nextLevel(newNode4, level - 1, r + shift, c + shift, data);

        input->first = newNode1;
        input->second = newNode2;
        input->third = newNode3;
        input->fourth = newNode4;
    }
    return input;
}
int merge(struct node **input, int level)
{
    if (level == 1)
    {
        return (*input)->data;
    }

    else
    {
        int a = merge(&(*input)->first, level - 1);
        int b = merge(&(*input)->second, level - 1);
        int c = merge(&(*input)->third, level - 1);
        int d = merge(&(*input)->fourth, level - 1);

        if (a == 0 && b == 0 && c == 0 && d == 0)
        {
            (*input)->data = 0;
            return 0;
        }
        else if (a == 1 && b == 1 && c == 1 && d == 1)
        {
            (*input)->data = 1;
            return 1;
        }
        else
        {
            (*input)->data = -1;
            return -1;
        }
    }
}

void output(struct node *input, int arr[n][n], int level, int r, int c, int data[n][n])
{
    int diff;
    if (level == 1)
    {
        if (input->data == -2)
        {
            arr[r][c] = -2;
        }
        else
        {
            arr[r][c] = dataOutput++;
        }
    }

    else
    {

        int shift = height - level + 1;
        shift = n / power(2, shift);
        if (input->data == -1)
        {
            output(input->first, arr, level - 1, r, c, data);
            output(input->second, arr, level - 1, r, c + shift, data);
            output(input->third, arr, level - 1, r + shift, c, data);
            output(input->fourth, arr, level - 1, r + shift, c + shift, data);
        }
        else
        {
            output(input->first,
                   arr, level - 1, r, c, data);
            dataOutput--;
            output(input->second, arr, level - 1, r, c + shift, data);
            dataOutput--;
            output(input->third, arr, level - 1, r + shift, c, data);
            dataOutput--;
            output(input->fourth, arr, level - 1, r + shift, c + shift, data);
        }
    }
}

int next_pow_2(int n)
{
    if (!(n & (n - 1)))
        return n;
    else
    {
        int count = 0;
        while (n != 0)
        {
            n = n >> 1;
            count++;
        }
        return 1 << count;
    }
}
struct node *modifyTree(struct node *input)
{
    if (input->data == -1)
    {
        input->first = modifyTree(input->first);
        input->second = modifyTree(input->second);
        input->third = modifyTree(input->third);
        input->fourth = modifyTree(input->fourth);
    }
    else
    {
        input->first = NULL;
        input->second = NULL;
        input->third = NULL;
        input->fourth = NULL;
    }

    return input;
}
void printPostOrder(struct node *input, int level)
{
    if (input->data == -1)
    {
        printPostOrder(input->first, level + 1);
        printPostOrder(input->second, level + 1);
        printPostOrder(input->third, level + 1);
        printPostOrder(input->fourth, level + 1);
    }
    else
    {
        printf("(%d,%d,%d),", dataOutput, input->data, level);
        dataOutput++;
    }
}
int main()

{
    char *filename = "input1.txt";

    FILE *f = fopen(filename, "r");
    int temp;
    int count = 0;
    while (!feof(f))
    {
        fscanf(f, "%d ", &temp);

        count++;
    }
    f = fopen(filename, "r");
    count = sqrt(count);
    n = next_pow_2(count);
    int extra = n - count;

    int inputf[n][n];
    for (int i = 0 + extra; i < n; i++)
    {
        for (int j = 0; j < n - extra; j++)
        {
            fscanf(f, "%d ", &inputf[i][j]);
        }
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = n - extra; j < n; j++)
        {
            inputf[i][j] = 0;
        }
    }
    for (int i = 0; i < extra; i++)
    {
        for (int j = 0; j < n; j++)
        {
            inputf[i][j] = 0;
        }
    }
    printf("INPUT ARRAY IS:\n");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("%d\t", inputf[i][j]);
        }
        printf("\n");
        printf("\n");
    }
    printf("\n");

    struct node *head = newNode();

    height = findlevel(n);

    head = nextLevel(head, height, 0, 0, inputf);

    merge(&head, height);

    int result[n][n];

    output(head, result, height, 0, 0, inputf);
    printf("OUTPUT ARRAY IS:\n");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {

            printf("%d\t", result[i][j]);
            if (result[i][j] < 10)
            {
                printf(" ");
            }
        }
        printf("\n");
        printf("\n");
    }

    head = modifyTree(head);

    dataOutput = 1;
    printPostOrder(head, 0);

    return 0;
}