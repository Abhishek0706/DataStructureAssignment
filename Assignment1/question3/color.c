#include <stdio.h>
#include <time.h>

int arr[953][1268];/*!<a temperory array*/
int red[953][1268];/*!<2D array for input red.dat file*/
int blue[953][1268];/*!<2D array for input blue.dat file*/
int green[953][1268];/*!<2D array for input green.dat file*/
int _red[953][1268];/*!<2D array for output red.dat file*/
int _blue[953][1268];/*!<2D array for output blue.dat file*/
int _green[953][1268];/*!<2D array for output green.dat file*/


/**
*@brief method to open a file
*@param filepath
*/
void openFile(char filename[100]) {
	FILE *file;
	file = fopen(filename, "r");
	if (!file) {
		printf("error opening the  file" );
	}

	for (int i = 0; i < 953; i++) {
		for (int j = 0; j < 1268; j++) {
			fscanf(file, "%d", &arr[i][j]);
			fscanf(file, ",");

		}

	}

	fclose(file);
}
/**
*@brief print input and out pixel value in the form of rgb
*@param x cord
*@param y cord
*/

void printPixel(int x, int y) {
	if(x>=953||y>=1268){
		printf("print the valid pixel\n");
		return;
	}

	printf("input rgb values are %d,%d,%d\n", red[x][y], green[x][y], blue[x][y]);
	printf("output rgb values are %d,%d,%d\n", _red[x][y], _green[x][y], _blue[x][y]);


}
/**
*@brief find which color is dominating
*@param red
*@param green
*@param blue
*@return r if red
*@return g if green
*@return b if blue
*/
char max(int a, int b, int c) {
	char ch = 'n';
	if (a == b && b == c) {

		return ch;
	}
	int m = a;
	if (b > m) {
		m = b;
	}
	if (c > m) {
		m = c;
	}

	if (m == a) {
		ch = 'r';
	}
	if (m == b) {
		ch = 'g';
	}
	if (m == c) {
		ch = 'b';
	}
	return ch;
}
/**
*@brief save the matrix to output file
*@param filepath
*@param output matrix
*/
void saveFile(char filename[100], int mat[953][1268]) {
	FILE *f = fopen(filename, "w");
	for (int i = 0; i < 953; i++) {
		for (int j = 0; j < 1268; j++) {
			fprintf(f, "%d", mat[i][j]);
			fprintf(f, ",");
		}
		fprintf(f, "\n");
	}
}
/**
*@brief remove red from where red is dominating
*@detail it compares the value of r,g,b and if r is max the make r=0
*/
void removeRed() {
	for (int i = 0; i < 953; i++) {
		for (int j = 0; j < 1268; j++) {
			char m = max(red[i][j], green[i][j], blue[i][j]);
			_red[i][j] = red[i][j];
			_green[i][j] = green[i][j];
			_blue[i][j] = blue[i][j];
			if (m == 'r') {
				_red[i][j] = 0;
			}
		}
	}
	saveFile("output/red.dat", _red);
	saveFile("output/blue.dat", _blue);
	saveFile("output/green.dat", _green);
	printf("red shades are removed\n");

}
/**
*@brief remove green from where green is dominating
*@detail it compares the value of r,g,b and if g is max the make g=0
*/
void removeGreen() {
	for (int i = 0; i < 953; i++) {
		for (int j = 0; j < 1268; j++) {
			char m = max(red[i][j], green[i][j], blue[i][j]);
			_red[i][j] = red[i][j];
			_green[i][j] = green[i][j];
			_blue[i][j] = blue[i][j];
			if (m == 'g') {
				_green[i][j] = 0;
			}
		}
	}
	saveFile("output/red.dat", _red);
	saveFile("output/blue.dat", _blue);
	saveFile("output/green.dat", _green);
	printf("green shades are removed\n");

}
/**
*@brief remove red from where blue is dominating
*@detail it compares the value of r,g,b and if b is max the make b=0
*/
void removeBlue() {
	for (int i = 0; i < 953; i++) {
		for (int j = 0; j < 1268; j++) {
			char m = max(red[i][j], green[i][j], blue[i][j]);
			_red[i][j] = red[i][j];
			_green[i][j] = green[i][j];
			_blue[i][j] = blue[i][j];
			if (m == 'g') {
				_green[i][j] = 0;
			}
		}
	}
	saveFile("output/red.dat", _red);
	saveFile("output/blue.dat", _blue);
	saveFile("output/green.dat", _green);
	printf("blue shades are removed\n");

}
/**
*@brief remove green and blue where red is dominating
*@detail it compares the value of r,g,b and if r is max the make g=b=0
*/
void onlyRed() {
	for (int i = 0; i < 953; i++) {
		for (int j = 0; j < 1268; j++) {
			char m = max(red[i][j], green[i][j], blue[i][j]);
			_red[i][j] = red[i][j];
			_green[i][j] = green[i][j];
			_blue[i][j] = blue[i][j];
			if (m == 'r') {
				_green[i][j] = 0;
				_blue[i][j] = 0;
			}
		}
	}
	saveFile("output/red.dat", _red);
	saveFile("output/blue.dat", _blue);
	saveFile("output/green.dat", _green);
	printf("red shades are preserved\n");

}
/**
*@brief remove red and blue where green is dominating
*@detail it compares the value of r,g,b and if g is max the make r=b=0
*/
void onlyGreen() {
	for (int i = 0; i < 953; i++) {
		for (int j = 0; j < 1268; j++) {
			char m = max(red[i][j], green[i][j], blue[i][j]);
			_red[i][j] = red[i][j];
			_green[i][j] = green[i][j];
			_blue[i][j] = blue[i][j];
			if (m == 'g') {
				_red[i][j] = 0;
				_blue[i][j] = 0;
			}
		}
	}
	saveFile("output/red.dat", _red);
	saveFile("output/blue.dat", _blue);
	saveFile("output/green.dat", _green);
	printf("green shades are preserved\n");

}
/**
*@brief remove red and green where blue is dominating
*@detail it compares the value of r,g,b and if b is max the make r=g=0
*/
void onlyBlue() {
	for (int i = 0; i < 953; i++) {
		for (int j = 0; j < 1268; j++) {
			char m = max(red[i][j], green[i][j], blue[i][j]);
			_red[i][j] = red[i][j];
			_green[i][j] = green[i][j];
			_blue[i][j] = blue[i][j];
			if (m == 'b') {
				_green[i][j] = 0;
				_red[i][j] = 0;
			}
		}
	}
	saveFile("output/red.dat", _red);
	saveFile("output/blue.dat", _blue);
	saveFile("output/green.dat", _green);
	printf("blue shades are preserved\n");

}
/**
*@brief main method for executing programme
*/
int main() {
	clock_t start, end;
	double cpu_time_used;

	start = clock();


	openFile("input/blue.dat");
	for (int i = 0; i < 953; i++) {
		for (int j = 0; j < 1268; j++) {
			blue[i][j] = arr[i][j];
		}
	}
	openFile("input/green.dat");
	for (int i = 0; i < 953; i++) {
		for (int j = 0; j < 1268; j++) {
			green[i][j] = arr[i][j];
		}
	}
	openFile("input/red.dat");
	for (int i = 0; i < 953; i++) {
		for (int j = 0; j < 1268; j++) {
			red[i][j] = arr[i][j];
		}
	}


	int input;
	while (1) {
		printf("Enter index of operation to perform\n1. remove red\n2. remove green\n3. remove blue\n4. red only\n5. green only\n6. blue only\n7. next\n");
		scanf("%d", &input);
		if (input == 1) {
			removeRed();
		}
		else if (input == 2) {
			removeGreen();
		}
		else if (input == 3) {
			removeBlue();
		}
		else if (input == 4) {
			onlyRed();
		}
		else if (input == 5) {
			onlyGreen();
		}
		else if (input == 6) {
			onlyBlue();
		}
		else if (input == 7) {
			break;
		}
		else {
			printf("enter a valid operation\n");
		}
	}
	int x, y;
	while (1) {
		printf("1. know difference in input and output\n2. exit\n");
		scanf("%d", &input);
		if (input == 1) {
			printf("enter value of x and y cord in form of x y\n");
			scanf("%d", &x);
			scanf("%d", &y);
			printPixel(x, y);

		}
		if (input == 2) {
			break;
		}
	}

	end = clock();
	cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
	printf("cpu time used is %f\n", cpu_time_used );

	return 0;
}