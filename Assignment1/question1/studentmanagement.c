#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int next_roll = 101;/*!<gives next roll number*/
struct Node* start = NULL;/*!<start node of double circular linked kist*/
struct QNode* head = NULL;/*!<head node for queue*/
/**
*@brief queue node class
*/
struct QNode {
	int roll;/*!< roll number */
	struct QNode* next; /*!< pointer to next node*/
};
/**
*@brief queue method for pushing data into it
*@param data to push
*@return void
*/
void push(int key) {
	if ((head) == NULL) {
		struct QNode* new_node = (struct QNode*)malloc(sizeof(struct QNode));
		new_node->roll = key;
		new_node->next = NULL;
		head = new_node;
		return;
	}
	struct QNode* temp = head;
	struct QNode* new_node = (struct QNode*)malloc(sizeof(struct QNode));
	new_node->roll = key;
	while (temp->next != NULL) {
		temp = temp->next;
	}
	temp->next = new_node;
	new_node->next = NULL;
}
/**
*@brief queue mothod for poping data from it
*@return return the data which was pushed first
*/
int pop() {
	int ret = (head)->roll;
	struct QNode* temp = head;
	(head) = (head)->next;
	free(temp);
	return ret;
}
/**
*@brief Node for double circular linked list
*/
struct Node {
	int rollno; /*!<roll number*/
	char* name;/*!<name*/
	char* dob;/*!<date of birth*/
	char* address;/*!<address*/
	char* phone;/*!<phone number*/
	struct Node* next;/*!<pointer to next node*/
	struct Node* prev;/*!<pointer to previous node*/
};
/**
*@return size of double circular linked list
*/
int size() {

	if (start == NULL) {
		return 0;
	}
	int s = 1;
	struct Node* temp = start;
	while (temp->next != start) {
		temp = temp->next;
		s++;
	}
	return s;
}
/**
*@brief insert in double circular linked list
*@param name
*@param dob
*@param address
*@param phone
*/
void insert(char* name, char* dob, char* address, char* phone) {
	int rollno;
	struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));

	new_node->name = name;
	new_node->dob = dob;
	new_node->address = address;
	new_node->phone = phone;

	if (head == NULL) {
		rollno = next_roll;
		next_roll++;

	}
	else {
		rollno = pop();

	}
	new_node->rollno = rollno;

	if (start == NULL)
	{

		new_node->next =  new_node;
		new_node->prev = new_node;
		start = new_node;
		return;
	}

	struct Node* temp = start->next;

	while (temp->rollno != rollno + 1 && temp != start) {
		temp = temp->next;
	}
	if (temp != start) {
		new_node->next = temp;
		temp->prev->next = new_node;
		new_node->prev = temp->prev;
		temp->prev = new_node;
		temp = NULL;
		return;

	}
	new_node->next = (start);
	(start)->prev->next = new_node;
	new_node->prev = (start)->prev;
	(start)->prev = new_node;

	if (temp->rollno == rollno + 1) {
		start = new_node;
	}

	temp = NULL;
}
/**
*@brief delete student from doubly cicular linked list
*@param roll number
*/

void deleteStudent(int rollno) {
	if (start == NULL) {
		printf("student with roll no %d not found \n", rollno);
		return;
	}
	struct Node* temp = (start);
	if (temp->rollno == rollno) {
		temp->prev->next = temp->next;
		temp->next->prev = temp->prev;
		start = (start)->next;
		free(temp);
		push(rollno);
		return;

	}
	temp = temp->next;
	while (temp != (start) && temp->rollno != rollno) {

		temp = temp->next;

	}
	if (temp == (start)) {
		printf("student with roll no %d not found \n", rollno);
		return;
	}
	temp->prev->next = temp->next;
	temp->next->prev = temp->prev;
	temp->next = NULL;
	temp->prev = NULL;
	free(temp);
	push(rollno);
	return;
}
/**
*@brief print full data of all students
*/

/**
*@brief print dname dob and roll number of all students
*/

void print() {
	struct Node* temp = (start);
	while (temp->next != start) {
		printf("roll no = %d name = %s dob = %s \n", temp->rollno, temp->name, temp->dob);
		temp = temp->next;
	}
	printf("roll no = %d name = %s dob = %s \n\n", temp->rollno, temp->name, temp->dob);

	temp = NULL;
}

/**
*@brief modify data of student with a given roll number
*/
void modify() {
	int rollno;
	char name[100], dob[100], address[100], phone[100];
	printf("enter roll number\n");
	scanf("%d", &rollno);
	printf("enter name\n");
	scanf("%s", name);
	printf("enter dob\n");
	scanf("%s", dob);
	printf("enter address\n");
	scanf("%s", address);
	printf("enter phone\n");
	scanf("%s", phone);
	if (start == NULL) {
		printf("not found");
		return;
	}
	struct Node* temp = start->next;
	while (temp != start && temp->rollno != rollno) {
		temp = temp->next;
	}
	if (temp->rollno == rollno) {
		strcpy(temp->name , name);
		strcpy(temp->dob, dob);
		strcpy(temp->address , address);
		strcpy(temp->phone , phone);

	}
	else {
		printf("error\n");
	}
	temp = NULL;
}
/**
*@param line
*@param num
*@return nth word from given line
*/
char* getfield(char* line, int num) {
	char* tok;
	for (tok = strtok(line, "\";\"");
	        tok && *tok;
	        tok = strtok(NULL, "\";\""))
	{
		if (!--num)
			return tok;
	}
	return NULL;
}
/**
*@brief method to insert nth student from the given student data file
*@param student number from the data
*/
void insertStudent(int std_no) {
	FILE* stream = fopen("StudentData.csv", "r");
	std_no++;
	char line[2048];
	while (std_no--)
	{
		fgets(line, 2048, stream);
	}
	insert(getfield(strdup(line), 2), getfield(strdup(line), 3), getfield(strdup(line), 4), getfield(strdup(line), 5));

}
/**
*@brief method to sort data by name
*/
void sortByName() {


	struct Node* currX = start;
	struct Node* currY = start;
	struct Node* prevY;
	struct Node* prevX;
	struct Node* nextX;
	struct Node* nextY;
	struct Node* temp1;
	struct Node* temp2;

	int s = size();
	for (int i = 0; i < s; i++) {
		currY = currX->next;;
		for (int j = i + 1; j < s; j++) {
			if (strcmp(currX->name, currY->name) > 0) {
				//swapping nodes
				prevX = currX->prev;
				nextX = currX->next;
				prevY = currY->prev;
				nextY = currY->next;
				prevX->next = currY;
				nextX->prev = currY;
				prevY->next = currX;
				nextY->prev = currX;
				temp1 = currX->next;
				temp2 = currX->prev;
				currX->next = currY->next;
				currX->prev = currY->prev;
				currY->next = temp1;
				currY->prev = temp2;

				temp1 = currX;
				currX = currY;
				currY = temp1;

				if (currX == start) {
					start = currY;
				}
				if (currY == start) {
					start  = currX;
				}

			}
			currY = currY->next;
		}
		currX = currX->next;

	}
	nextX = NULL;
	nextY = NULL;
	prevY = NULL;
	prevX = NULL;
	currX = NULL;
	currY = NULL;
	temp1 = NULL;
	temp2 = NULL;

}
/**
*@brief search in double circular linked list
*/
void search() {
	int rollno;
	printf("enter roll number to search\n");
	scanf("%d", &rollno);
	if (start == NULL) {
		printf("not found");

	}
	if (rollno == start->rollno) {
		printf("roll no = %d name = %s dob = %s \n", start->rollno, start->name, start->dob);

	}
	struct Node* temp = start->next;
	while (temp != start) {
		if (temp->rollno == rollno) {
			printf("roll no = %d name = %s dob = %s \n", temp->rollno, temp->name, temp->dob);
			break;
		}

		temp = temp->next;
	}
	if (temp == start) {
		printf("not found\n");
	}
	temp = NULL;


}

int main() {

	clock_t start, end;
	double cpu_time_used;

	start = clock();

	while (1) {
		int input;
		int n;
		char name[100];
		char dob[20];
		char address[100];
		char phone[12];
		printf("\nEnter the index of operation to perform :\ninsert -> 1\ndelete -> 2\nsearch -> 3\nmodify -> 4\nprint -> 5\nsort -> 6\nexit -> 0\n");
		scanf("%d", &input);
		if (input == 1) {
			printf("enter row number to insert\n");
			scanf("%d", &n);
			n--;
			insertStudent(n);

		}
		else if (input == 2) {
			printf("enter roll number to delete\n");
			int n;
			scanf("%d", &n);
			deleteStudent(n);

		}
		else if (input == 3) {

			search();

		}
		else if (input == 4) {
			modify();
		}
		else if (input == 5) {
			print();
		}
		else if (input == 6) {
			sortByName();
		}

		else if (input == 0) {
			exit(0);
			break;
		}
		else {
			printf("\nPlease enter a valid entry\n\n");
		}
	}

	end = clock();
	cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
	printf("cpu time used is %f\n", cpu_time_used );

	return 0;
}

