#include <iostream>
#include <stack>
#include <time.h>
using namespace std;

//binary search tree
stack <int> s;

/**
 * @brief class for bst node
 */
class bstNode {
public:
	int data;
	bstNode *left;
	bstNode *right;
};
/**
 * @brief method to make new bst node
 */
bstNode* newbstNode(int data)
{
	bstNode* node = new bstNode();
	node->data = data;
	node->left = NULL;
	node->right = NULL;

	return (node);
}
/**
 * @brief insert a bst node into bst
 */
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
/**
 * @brief print inorder of given bst 
 */
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
/**
 * @brief print the given stack
 */
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
/**
 * @brief make a stack opposite to given stack
 */
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

/**
 * @brief print path in a bst
 */
void bstPath(bstNode* node) {
	if (node == NULL) {
		return;
	}
	s.push(node->data);
	bstPath(node->left);
	if (node->left == NULL && node->right == NULL) {
		OppStack(s); //stack of a  leaf to root
		printf("\n");
	}
	bstPath(node->right);
	s.pop();

}
/**
 * @brief find height of a given node
 */
int nodeHeight(bstNode *n) {
	int a, b;
	if (n == NULL) {
		return -1;
	}
	else {
		a = nodeHeight(n->left);
		b = nodeHeight(n->right);
		if (a > b) {
			return a + 1;
		}
		else {
			return b + 1;
		}
	}
}
/**
 * @brief return balance factor of given bst node
 */
int bstgetBalance(bstNode *N)
{
	if (N == NULL)
		return 0;
	return nodeHeight(N->left) - nodeHeight(N->right);
}
/**
 * @brief return 1 if the given node is leaf otherwise 0
 */
int isBstLeaf(bstNode *n) {
	if (n->right == NULL && n->left == NULL) {
		return 1;
	}
	return 0;
}
/**
 * @brief print level wise intendent of bst
 */
void levelWiseBst(bstNode *node, int tab) {
	if (node == NULL) {
		return ;
	}
	for (int i = 0; i < tab; i++) {
		cout << "\t";

	}
	int a = bstgetBalance(node) ;
	if (a < 0) a *= (-1);
	if (isBstLeaf(node) == 1) {
		cout << node->data << endl;
	}
	else {
		cout << node->data << "[" << a << "]" << endl;
	}

	levelWiseBst(node->left, tab + 1);
	levelWiseBst(node->right, tab + 1);
}
// avl tree

/**
 * @brief class for avl node
 */
class avlNode
{
public:
	int data;
	avlNode *left;
	avlNode *right;
	int height;
};
/**
 * @brief return max of two number
 */
int max(int a, int b)
{
	return (a > b) ? a : b;
}
/**
 * @brief return height of avl node
 */
int height(avlNode *N)
{
	if (N == NULL)
		return 0;
	return N->height;
}
/**
 * @brief create new avl node
 */
avlNode* newavlNode(int data)
{
	avlNode* node = new avlNode();
	node->data = data;
	node->left = NULL;
	node->right = NULL;
	node->height = 1;

	return (node);
}
/**
 * @brief right rotation method in avl tree
 */
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
/**
 * @brief left rotation method in avl tree
 */
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
/**
 * @brief return balance factor of given avl node
 */
int getBalance(avlNode *N)
{
	if (N == NULL)
		return 0;
	return height(N->left) - height(N->right);
}
/**
 * @brief insert new node in given avl tree
 */
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

/**
 * @brief print inorder of given avl tree 
 */
void avlInOrder(avlNode *root)
{

	if (root != NULL)
	{

		avlInOrder(root->left);
		cout << root->data << " ";
		avlInOrder(root->right);
	}
}

/**
 * @brief create avl tree from given bst tree
 */
avlNode* createAVL(bstNode *b, avlNode *a) {
	if (b == NULL) {
		return a;
	}

	a = createAVL(b->left, a);
	a = avlInsert(a, b->data);
	a = createAVL(b->right, a);

	return a;

}
/**
 * @brief print all paths in given avl tree
 */
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
/**
 * @brief return 1 if given node is a leaf
 */
int isAvlLeaf(avlNode *n) {
	if (n->right == NULL && n->left == NULL) {
		return 1;
	}
	return 0;
}
/**
 * @brief print level wise indentent of given avl tree
 */
void levelWiseAvl(avlNode *node, int tab) {
	if (node == NULL) {
		return ;
	}
	for (int i = 0; i < tab; i++) {
		cout << "\t";

	}
	int a = getBalance(node);
	if (a < 0) a = a * (-1);
	if (isAvlLeaf(node) == 1) {
		cout << node->data << endl;
	}
	else {
		cout << node->data << "[" << a << "]" << endl;
	}

	levelWiseAvl(node->left, tab + 1);
	levelWiseAvl(node->right, tab + 1);
}

/**
 * @brief class for red black node
 */
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
/**
 * @brief create new node of red black tree
 */
rbNode* newrbNode(int data) {
	rbNode* node = new rbNode();
	node->data = data;
	node->parent = NULL;
	node->left = NULL;
	node->right = NULL;
	node->color = 0;

	return (node);

}
/**
 * @brief left rotate method for red black tree
 */
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
/**
 * @brief right rotate method for red black tree
 */
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
/**
 * @brief making rotation in red black tree after inserting new node
 */
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
/**
 * @brief insert new node in given red black tree
 */
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
/**
 * @brief print inOrder of given red black tree
 */
void rbInOrder(rbNode *root)
{

	if (root != NULL)
	{

		rbInOrder(root->left);
		cout << root->data << " ";
		rbInOrder(root->right);
	}
}
/**
 * @brief print all paths in given red black tree
 */
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
/**
 * @brief return height of given red black node
 */
int rbNodeHeight(rbNode *n) {
	int a, b;
	if (n == NULL) {
		return -1;
	}
	else {
		a = rbNodeHeight(n->left);
		b = rbNodeHeight(n->right);
		if (a > b) {
			return a + 1;
		}
		else {
			return b + 1;
		}
	}
}
/**
 * @brief return balance factor of given red black node
 */
int RbgetBalance(rbNode *N)
{
	if (N == NULL)
		return 0;
	return rbNodeHeight(N->left) - rbNodeHeight(N->right);
}
/**
 * @brief return 1 if given node is leaf
 */
int isRbLeaf(rbNode *n) {
	if (n->right == NULL && n->left == NULL) {
		return 1;
	}
	return 0;
}
/**
 * @brief print level wise indentent of given red black tree
 */
void levelWiseRb(rbNode *node, int tab) {
	if (node == NULL) {
		return ;
	}
	for (int i = 0; i < tab; i++) {
		cout << "\t";

	}
	char c;
	int a = RbgetBalance(node);
	if (a < 0) {
		a = a * (-1);
	}
	if (node->color == 0) {
		c = 'r';
	}
	else {
		c = 'b';
	}
	if (isRbLeaf(node) == 1) {
		cout << node->data << "[" << c << "]" << endl;
	}
	else {
		cout << node->data << "[" << a << "]" << "[" << c << "]" << endl;
	}

	levelWiseRb(node->left, tab + 1);
	levelWiseRb(node->right, tab + 1);
}
/**
 * @brief main method for executing the programme
 */
int main() {

	clock_t start, end;
	double cpu_time_used;

	start = clock();

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
			// printf("\t1. insert in BST\n");
			// printf("\t2. insert in red-black Tree\n");
			// cin >> task2;

			// if (task2 == 1) {
			// 	cin >> data;
			// 	bstHead = bstInsert(bstHead, data);

			// }
			// else if (task2 == 2) {
			// 	cin >> data;
			// 	rbInsert(data);
			// }
			// else {
			// 	cout << "give a valid input\n";
			// }
			cin >> data;
			bstHead = bstInsert(bstHead, data);
			rbInsert(data);


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
				cout << "give a valid input\n";
			}

		}
		else if (task == 5) {
			printf("\t1. level-wise indentation of BST\n");
			printf("\t2. level-wise indentation of AVL Tree\n");
			printf("\t3. level-wise indentation of red-black tree\n");
			cin >> task2;
			if (task2 == 1) {
				levelWiseBst(bstHead, 0);
			}
			else if (task2 == 2) {
				levelWiseAvl(avlHead, 0);
			}
			else if (task2 == 3) {
				levelWiseRb(rbHead, 0);
			}
			else {
				cout << "give a valid input" << endl;
			}

		}
		else if (task == 6) {
			break;
		}
		else {
			printf("Enter a valid input\n");
		}
	}


	end = clock();
	cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
	printf("cpu time used is %f\n", cpu_time_used);
	return 0;
}