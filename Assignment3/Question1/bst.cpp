#include <iostream>
using namespace std;

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

void bstPrint(bstNode *node) {
	if (node == NULL) {
		return;
	}
	else {
		bstPrint(node->left);
		cout << node->data << " ";
		bstPrint(node->right);
	}
}
void bstpreOrder(bstNode *root)  
{  
    if(root != NULL)  
    {  
        cout << root->key << " ";  
        bstpreOrder(root->left);  
        bstpreOrder(root->right);  
    }  
}
int main(){
	return 0;
}