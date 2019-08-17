#include <iostream>
#include <stdio.h>
using namespace std;


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

int main() {

	rbInsert(45);
	cout<<rbHead->data<<endl;
	cout<<rbHead->color<<endl;
	return 0;
}