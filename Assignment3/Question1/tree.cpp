#include <iostream>
#include <stack>
using namespace std;

//binary search tree
stack <int> s;

class bstNode {
public:
	int data;
	bstNode *left;
	bstNode *right;
};

bstNode* newbstNode(int data)
{
	bstNode* node = new bstNode();
	node->data = data;
	node->left = NULL;
	node->right = NULL;

	return (node);
}

bstNode* bstInsert(bstNode *node, int data) {
	if (node == NULL) {
		node = newbstNode(data);

	}
	else {
		if (node->data > data) {
			node->left = bstInsert(node->left, data);
		}
		else if (node->data < data) {
			node->right = bstInsert(node->right, data);
		}
	}
	return (node);
}

void bstInOrder(bstNode *root)
{
	if (root != NULL)
	{
		;
		bstInOrder(root->left);
		cout << root->data << " ";
		bstInOrder(root->right);
	}
}
void stackPrint(stack<int> s) {
	//input stact for root to 1 leaf
	if (s.empty()) {
		return;
	}
	int x = s.top();
	//print full stack
	stack <int> s1;
	while (!s.empty()) {
		int a =  s.top();
		s.pop();
		s1.push(a);
		cout << a << "->";

	}
	while (!s1.empty()) {
		int a = s1.top();
		s1.pop();
		s.push(a);
	}


	printf("NULL\n");

	s.pop();
	stackPrint(s);
	s.push(x);

}

void OppStack(stack<int> s) {
	if (s.empty()) {
		return;
	}

	stack <int> s1;
	while (!s.empty()) {
		int p = s.top();
		s.pop();
		s1.push(p);
	}

	stackPrint(s1);
}


void bstPath(bstNode* node) {
	if (node == NULL) {
		return;
	}
	s.push(node->data);
	bstPath(node->left);
	if (node->left == NULL && node->right == NULL) {
		OppStack(s);
		printf("\n");
	}
	bstPath(node->right);
	s.pop();

}

// avl tree


class avlNode
{
public:
	int data;
	avlNode *left;
	avlNode *right;
	int height;
};

int max(int a, int b)
{
	return (a > b) ? a : b;
}

int height(avlNode *N)
{
	if (N == NULL)
		return 0;
	return N->height;
}

avlNode* newavlNode(int data)
{
	avlNode* node = new avlNode();
	node->data = data;
	node->left = NULL;
	node->right = NULL;
	node->height = 1;

	return (node);
}

avlNode *rightRotate(avlNode *y)
{
	avlNode *x = y->left;
	avlNode *T2 = x->right;


	x->right = y;
	y->left = T2;


	y->height = max(height(y->left),
	                height(y->right)) + 1;
	x->height = max(height(x->left),
	                height(x->right)) + 1;


	return x;
}

avlNode *leftRotate(avlNode *x)
{
	avlNode *y = x->right;
	avlNode *T2 = y->left;


	y->left = x;
	x->right = T2;


	x->height = max(height(x->left),
	                height(x->right)) + 1;
	y->height = max(height(y->left),
	                height(y->right)) + 1;


	return y;
}

int getBalance(avlNode *N)
{
	if (N == NULL)
		return 0;
	return height(N->left) - height(N->right);
}

avlNode* avlInsert(avlNode* node, int data)
{

	if (node == NULL)
		return (newavlNode(data));

	if (data < node->data)
		node->left = avlInsert(node->left, data);
	else if (data > node->data)
		node->right = avlInsert(node->right, data);
	else
		return node;


	node->height = 1 + max(height(node->left),
	                       height(node->right));


	int balance = getBalance(node);


	if (balance > 1 && data < node->left->data)
		return rightRotate(node);

	if (balance < -1 && data > node->right->data)
		return leftRotate(node);

	if (balance > 1 && data > node->left->data)
	{
		node->left = leftRotate(node->left);
		return rightRotate(node);
	}

	if (balance < -1 && data < node->right->data)
	{
		node->right = rightRotate(node->right);
		return leftRotate(node);
	}

	return node;
}


void avlInOrder(avlNode *root)
{

	if (root != NULL)
	{

		avlInOrder(root->left);
		cout << root->data << " ";
		avlInOrder(root->right);
	}
}


avlNode* createAVL(bstNode *b, avlNode *a) {
	if (b == NULL) {
		return a;
	}

	a = createAVL(b->left, a);
	a = avlInsert(a, b->data);
	a = createAVL(b->right, a);

	return a;

}

void avlPath(avlNode* node) {
	if (node == NULL) {
		return;
	}
	s.push(node->data);
	avlPath(node->left);
	if (node->left == NULL && node->right == NULL) {
		OppStack(s);
		printf("\n");
	}
	avlPath(node->right);
	s.pop();

}

//red black tree
class rbNode
{
public:
	int data ;
	rbNode *parent;
	rbNode *left;
	rbNode *right;
	int color;//0 for red 1 for black

};
rbNode* rbHead = NULL;

rbNode* newrbNode(int data) {
	rbNode* node = new rbNode();
	node->data = data;
	node->parent = NULL;
	node->left = NULL;
	node->right = NULL;
	node->color = 0;

	return (node);

}

void leftrotate(rbNode *p)
{
	if (p->right == NULL)
		return ;
	else
	{
		rbNode *y = p->right;
		if (y->left != NULL)
		{
			p->right = y->left;
			y->left->parent = p;
		}
		else
			p->right = NULL;
		if (p->parent != NULL)
			y->parent = p->parent;
		if (p->parent == NULL)
			rbHead = y;
		else
		{
			if (p == p->parent->left)
				p->parent->left = y;
			else
				p->parent->right = y;
		}
		y->left = p;
		p->parent = y;
	}
}
void rightrotate(rbNode *p)
{
	if (p->left == NULL)
		return ;
	else
	{
		rbNode *y = p->left;
		if (y->right != NULL)
		{
			p->left = y->right;
			y->right->parent = p;
		}
		else
			p->left = NULL;
		if (p->parent != NULL)
			y->parent = p->parent;
		if (p->parent == NULL)
			rbHead = y;
		else
		{
			if (p == p->parent->left)
				p->parent->left = y;
			else
				p->parent->right = y;
		}
		y->right = p;
		p->parent = y;
	}
}

void insertfix(rbNode* t) {
	if (rbHead == t) {
		t->color = 1;
		return;
	}
	rbNode* u;
	while (t->parent != NULL && t->parent->color == 0) {
		rbNode* g = t->parent->parent;
		if (g->left == t->parent) {
			if (g->right != NULL) {
				u = g->right;
				if (u->color == 0) {
					t->parent->color = 1;
					u->color = 1;
					g->color = 0;
					t = g;

				}
			}
			else {
				if (t->parent->right = t) {
					t = t->parent;
					leftrotate(t);
				}
				t->parent->color = 1;
				g->color = 0;
				rightrotate(g);
			}
		}
		else {
			if (g->left != NULL)
			{
				u = g->left;
				if (u->color == 0)
				{
					t->parent->color = 1;
					u->color = 1;
					g->color = 0;
					t = g;
				}
			}
			else
			{
				if (t->parent->left == t)
				{
					t = t->parent;
					rightrotate(t);
				}
				t->parent->color = 1;
				g->color = 0;
				leftrotate(g);
			}
		}
		rbHead->color = 1;

	}

}

void rbInsert(int data) {

	rbNode* p;
	rbNode* q;
	rbNode* t = newrbNode(data);
	p = rbHead;
	q = NULL;
	if (rbHead == NULL)
	{
		rbHead = t;
		t->parent = NULL;
	}
	else
	{
		while (p != NULL)
		{
			q = p;
			if (p->data < t->data)
				p = p->right;
			else
				p = p->left;
		}
		t->parent = q;
		if (q->data < t->data)
			q->right = t;
		else
			q->left = t;
	}
	insertfix(t);

}
void rbInOrder(rbNode *root)
{

	if (root != NULL)
	{

		rbInOrder(root->left);
		cout << root->data << " ";
		rbInOrder(root->right);
	}
}

void rbPath(rbNode* node) {
	if (node == NULL) {
		return;
	}
	s.push(node->data);
	rbPath(node->left);
	if (node->left == NULL && node->right == NULL) {
		OppStack(s);
		printf("\n");
	}
	rbPath(node->right);
	s.pop();

}


int main() {

	bstNode* bstHead = NULL;
	avlNode* avlHead = NULL;

	int task, task2, data;
	while (1) {
		printf("1. To insert a node in the BST and in the red-black tree.\n");
		printf("2. To create AVL tree from the inorder traversal of the BST.\n");
		printf("3. To print the inorder traversal of the BST/AVL/red-black tree.\n");
		printf("4. To display all the paths in the BST/AVL tree/red-black tree.\n");
		printf("5. To print the BST/AVL tree/red-black Tree in the terminal using level-wise indentation.\n");
		printf("6. Exit. \n");

		cin >> task;

		if (task == 1) {
			printf("\t1. insert in BST\n");
			printf("\t2. insert in red-black Tree\n");
			cin >> task2;

			if (task2 == 1) {
				cin >> data;
				bstHead = bstInsert(bstHead, data);

			}
			else if (task2 == 2) {
				cin >> data;
				rbInsert(data);
			}
			else {
				cout << "give a valid input\n";
			}


		}
		else if (task == 2) {
			avlHead = createAVL(bstHead, avlHead);

		}
		else if (task == 3) {
			printf("\t1. inorder of BST\n");
			printf("\t2. inorder of AVL Tree\n");
			printf("\t3. inorder of red-black tree\n");
			cin >> task2;
			if (task2 == 1) {
				bstInOrder(bstHead);
				printf("\n");
			}
			else if (task2 == 2) {
				avlInOrder(avlHead);
				printf("\n");

			}
			else if (task2 == 3) {
				rbInOrder(rbHead);
				cout << "\n";

			}
			else {
				cout << "give a valid input\n";
			}

		}
		else if (task == 4) {
			printf("\t1. paths of BST\n");
			printf("\t2. paths of AVL Tree\n");
			printf("\t3. paths of red-black tree\n");
			cin >> task2;
			if (task2 == 1) {
				bstPath(bstHead);
			}
			else if (task2 == 2) {
				avlPath(avlHead);
			}
			else if (task2 == 3) {
				rbPath(rbHead);

			}
			else {
				cout<<"give a valid input\n";
			}

		}
		else if (task == 5) {
			printf("\t1. level-wise indentation of BST\n");
			printf("\t2. level-wise indentation of AVL Tree\n");
			printf("\t3. level-wise indentation of red-black tree\n");
			cin >> task2;
			if (task2 == 1) {

			}
			else if (task2 == 2) {

			}
			else if (task2 == 3) {

			}
			else {

			}

		}
		else if (task == 6) {
			break;
		}
		else {
			printf("Enter a valid input\n");
		}
	}


	return 0;
}