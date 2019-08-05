#include <stdio.h>
#include <stdlib.h>
#include <time.h>
/**
*@brief node for queue
*/

struct QNode {

	int data; /*!<integer data of node*/
	struct QNode* next; /*!<pointer to next node*/
	struct QNode* prev;/*!<pointer to previous node*/
};
/**
*@brief queue class
*/
struct Queue
{
	struct QNode *front , *rear;/*!<front and rear pointer of the queue*/
	int capacity;/*!<capacity of queue*/
	int size;/*!<size of queue*/
};

/**
*@brief method to create queue
*@return pointer to created queue
*/
struct Queue* createQueue()
{
	struct Queue* q = (struct Queue*)malloc(sizeof(struct Queue));
	q->rear  = NULL;
	q->front = NULL;
	q->size = 0;
	q->capacity = 1;
	return q;

}
/**
*@brief insert data at front of the queue
*@param Queue* pointer to that queue
*@param key data to be inseted
*/
void insertFront(struct Queue* q, int key) {
	if (q->size == q->capacity) {
		q->capacity *= 2;
	}

	if (q->size == 0) {
		struct QNode* temp = (struct QNode*)malloc(sizeof(struct QNode));
		temp->data = key;
		temp->next = NULL;
		temp->prev = NULL;
		q->rear  = temp;
		q->front = temp;
		(q->size)++;
		return;
	}

	struct QNode* temp = (struct QNode*)malloc(sizeof(struct QNode));
	temp->data = key;
	temp->prev = q->front;
	temp->next = NULL;
	q->front->next = temp;
	q->front = temp;
	(q->size)++;

}
/**
*@brief insert data at end of the queue
*@param Queue* pointer to that queue
*@param key data to be inseted
*/
void insertLast(struct Queue* q, int key) {
	if (q->size == q->capacity) {
		q->capacity *= 2;
	}

	if (q->size == 0) {
		struct QNode* temp = (struct QNode*)malloc(sizeof(struct QNode));
		temp->data = key;
		temp->next = NULL;
		temp->prev = NULL;
		q->rear  = temp;
		q->front = temp;
		(q->size)++;
		return;
	}

	struct QNode* temp = (struct QNode*)malloc(sizeof(struct QNode));
	temp->data = key;
	temp->next = q->rear;
	temp->prev = NULL;
	q->rear->prev = temp;
	q->rear  = temp;
	(q->size)++;

}
/**
*@brief delete data from the front of the queue
*@param Queue* pointer to the queue
*/
void deleteFront(struct Queue* q) {
	if (q == NULL) {
		printf("queue is empty" );
		return;
	}

	struct QNode* temp = q->front;
	q->front = temp->prev;
	temp->prev->next = NULL;
	temp->prev = NULL;
	free(temp);
	(q->size)--;
	if (2 * (q->size) == q->capacity) {
		q->capacity /= 2;
	}


}
/**
*@brief delete data from the end of the queue
*@param Queue* pointer to the queue
*/
void deleteLast(struct Queue* q) {
	if (q == NULL) {
		printf("queue is empty" );
		return;
	}
	struct QNode* temp = q->rear;
	q->rear = temp->next;
	temp->next->prev = NULL;
	temp->next = NULL;
	free(temp);
	(q->size)--;
	if (2 * (q->size) == q->capacity) {
		q->capacity /= 2;
	}

}
/**
*@brief print the list with its capacity
*/

void printList(struct Queue* q) {
	if (q == NULL) {
		printf("queue is empty" );
		return;
	}
	struct QNode* temp = q->rear;
	printf("the queue is ");
	while (temp != NULL) {
		printf(" %d ", temp->data);
		temp = temp->next;
	}
	printf("capacity is %d", q->capacity);
	printf("\n");
	free(temp);
}
/**
*@brief main method to execute the programme
*/
int main() {

	clock_t start, end;
	double cpu_time_used;

	start = clock();


	struct Queue* myque = createQueue();
	while (1) {
		int n;
		int data;
		printf("enter index of operation to perform\n1. insertFront\n2. insertLast\n3. deleteFront\n4. deleteLast\n5. printList\n6. exit\n");
		scanf("%d", &n);
		if (n == 1) {
			printf("insert integer data\n");
			scanf("%d", &data);
			insertFront(myque, data);
		}
		else if (n == 2) {
			printf("insert integer data\n");
			scanf("%d", &data);
			insertLast(myque, data);
		}
		else if (n == 3) {
			deleteFront(myque);

		}
		else if (n == 4) {
			deleteLast(myque);

		}
		else if (n == 5) {
			printList(myque);
		}
		else if (n == 6) {
			break;
		}
		else {
			printf("enter a valid input\n");
		}
	}
	end = clock();
	cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
	printf("cpu time used is %f\n",cpu_time_used );


	return 0;

}