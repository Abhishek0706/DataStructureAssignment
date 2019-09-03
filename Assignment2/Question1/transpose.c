#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int n = 5;
int a = 3, b = 2;

/**
 *@brief return size of given input array
 *@param char *input
 *@return size
 */
int getsize(char *input)
{
	int size = strlen(input);
	return size;
}
/**
 *@brief create J for given a,n,b
 *@param int outputJ[1000]
 *@param int size
 *@return void
 */
void createOutputJ(int outputJ[1000], int size)
{
	for (int i = 0; i < size; i++)
	{
		outputJ[i] = ((a * i) + b) % n;
	}
}
/**
 *@brief create output array with encryption
 *@param char *input
 *@param char *output
 *@param int outputJ[1000]
 *@param int size
 *return void
 */
void createOutput(char *input, char *output, int outputJ[1000], int size)
{
	int patch = -n;
	for (int i = 0; i < size; i++)
	{
		if (i % n == 0)
		{
			patch = patch + n;
		}
		output[i] = input[outputJ[i] + patch];
	}
	output[size] = '\0';

	FILE *stream = fopen("output.txt", "w");
	fprintf(stream, "%s\n", output);
}
/**
 *@brief make string size multiple of n by adding extra char
 *@param char *input
 *@return void
 */
void extend(char *input)
{

	int size = getsize(input);
	const char *end = "\0";
	strcpy(&input[size - 1], end);
	size = getsize(input);
	int extra = (n - (size % n)) % n;

	char add[] = "*";
	for (int i = 0; i < extra; i++)
	{
		strcat(input, add);
	}
}
/**
 * @brief find decryption key for given encryption key
 * @param int n
 * @param int a
 * @param int b
 */

void decKey(int n, int a, int b)
{
	int _a = 0;
	int _b = 0;

	while ((1 - (a * _a)) % n != 0)
	{
		_a++;
	}
	while ((_a * b + _b) % n != 0)
	{
		_b++;
	}
	printf("decryption key is n=%d, a'=%d, b'= %d\n", n, _a, _b);
}
/**
 * @brief find gcd of two number
 * @param int n1
 * @param int n2
 * @return int gcd
 */
int gcd(int n1, int n2)
{
	int g;
	for (int i = 1; i <= n1 && i <= n2; ++i)
	{
		if (n1 % i == 0 && n2 % i == 0)
			g = i;
	}
	return g;
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
		const char *filename = argv[4];

		if(gcd(n,a)!=1){
			printf("n and a must be coprime\n");
			return 1;
		}
		char input[1000] = "";

		FILE *stream = fopen(filename, "r");

		char temp[1000];
		while (fgets(temp, 1000, stream))
		{
			strcat(input, temp);
		}

		int outputJ[1000];
		char output[1000];

		extend(input);

		int size = getsize(input);

		createOutputJ(outputJ, size);

		createOutput(input, output, outputJ, size);

		printf("DONE!\n");
		decKey(n, a, b);

		end = clock();
		cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
		printf("cpu time used is %f\n", cpu_time_used);

		return 0;
	}
}