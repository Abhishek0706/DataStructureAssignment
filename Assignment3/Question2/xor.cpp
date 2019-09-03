#include <iostream>
#include <string.h>
#include <time.h>

using namespace std;
int totalCount = 0;
class llNode {
public:

	int key;
	llNode* next;

};
llNode* root = NULL;

llNode* newNode(int key) {
	llNode* node = new llNode();

	node->key = key;
	node->next = NULL;
	return node;
}
void push(int key) {
	llNode* node = NULL;
	llNode* temp = NULL;

	if (root == NULL) {
		node = newNode(key);
		root = node;
	}
	else {


		llNode* node = newNode( key);
		temp = root;
		while (temp->next != NULL) {
			temp = temp->next;
		}
		temp->next = node;

	}
}
void pop() {
	llNode* temp = root;
	if (root == NULL) {
		return;
	}
	else {
		root = root->next;
		free(temp);
	}

}

void makeNext(int x) {
	llNode* temp = root;
	if (root == NULL) {
		return;
	}
	while (temp != NULL) {
		temp->key = temp->key ^ x;
		temp = temp->next;
	}
}
void printTriplet(int initial) {
	llNode* temp = root;
	if (root == NULL) {
		return;
	}
	int count = 0;
	while (temp != NULL) {
		count++;
		if (temp->key == 0) {
			for (int j = 1; j < count; j++) {
				cout << "(" << initial + 1 << "," << initial + j + 1 << "," << initial + count << ")" << endl;
				totalCount++;
			}

		}

		temp = temp->next;
	}

}
void printll() {
	llNode* temp = root;
	while (temp != NULL) {
		cout << temp->key << " ";
		temp = temp->next;
	}
	cout << endl;

}
int main() {
	clock_t start, end;
	double cpu_time_used;

	start = clock();

	int n;
	cin >> n;

	int a[n];
	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}
	if (n == 1) {
		cout << 0 << endl;
		return 0;
	}
	int x = a[0];
	push(x);
	for (int i = 1; i < n; i++) {
		x = x ^ a[i];
		push(x);

	}
	printTriplet(0);
	for (int i = 1; i < n; i++) {
		int x = root->key;
		pop();
		makeNext(x);
		printTriplet(i);

	}
	cout << "Total number of triplets are : " << totalCount << endl;

	end = clock();
	cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
	printf("cpu time used is %f\n", cpu_time_used);
	return 0;
}