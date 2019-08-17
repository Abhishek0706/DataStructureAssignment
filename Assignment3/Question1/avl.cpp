#include <iostream>
using namespace std;

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
void avlpreOrder(avlNode *root)  
{  
    if(root != NULL)  
    {  
        cout << root->key << " ";  
        avlpreOrder(root->left);  
        avlpreOrder(root->right);  
    }  
}

int main() {
	return 0;
}