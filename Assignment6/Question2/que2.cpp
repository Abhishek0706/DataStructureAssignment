#include<bits/stdc++.h> 
using namespace std; 

struct Node 
{ 
	int data, degree; 
	Node *child, *sibling, *parent; 
}; 

Node* newNode(int key) 
{ 
	Node *temp = new Node; 
	temp->data = key; 
	temp->degree = 0; 
	temp->child = temp->parent = temp->sibling = NULL; 
	return temp; 
} 

// This function merge two Binomial Trees. 
Node* mergeBinomialTrees(Node *b1, Node *b2) 
{ 
	// Make sure b1 is smaller 
	if (b1->data > b2->data) 
		swap(b1, b2); 

	// We basically make larger valued tree 
	// a child of smaller valued tree 
	b2->parent = b1; 
	b2->sibling = b1->child; 
	b1->child = b2; 
	b1->degree++; 

	return b1; 
} 

// This function perform union operation on two 
// binomial heap i.e. l1 & l2 
list<Node*> unionBionomialHeap(list<Node*> l1, 
							list<Node*> l2) 
{ 
	// _new to another binomial heap which contain 
	// new heap after merging l1 & l2 
	list<Node*> _new; 
	list<Node*>::iterator it = l1.begin(); 
	list<Node*>::iterator ot = l2.begin(); 
	while (it!=l1.end() && ot!=l2.end()) 
	{ 
		// if D(l1) <= D(l2) 
		if((*it)->degree <= (*ot)->degree) 
		{ 
			_new.push_back(*it); 
			it++; 
		} 
		// if D(l1) > D(l2) 
		else
		{ 
			_new.push_back(*ot); 
			ot++; 
		} 
	} 

	// if there remains some elements in l1 
	// binomial heap 
	while (it != l1.end()) 
	{ 
		_new.push_back(*it); 
		it++; 
	} 

	// if there remains some elements in l2 
	// binomial heap 
	while (ot!=l2.end()) 
	{ 
		_new.push_back(*ot); 
		ot++; 
	} 
	return _new; 
} 

// adjust function rearranges the heap so that 
// heap is in increasing order of degree and 
// no two binomial trees have same degree in this heap 
list<Node*> adjust(list<Node*> _heap) 
{ 
	if (_heap.size() <= 1) 
		return _heap; 
	list<Node*> new_heap; 
	list<Node*>::iterator it1,it2,it3; 
	it1 = it2 = it3 = _heap.begin(); 

	if (_heap.size() == 2) 
	{ 
		it2 = it1; 
		it2++; 
		it3 = _heap.end(); 
	} 
	else
	{ 
		it2++; 
		it3=it2; 
		it3++; 
	} 
	while (it1 != _heap.end()) 
	{ 
		// if only one element remains to be processed 
		if (it2 == _heap.end()) 
			it1++; 

		// If D(it1) < D(it2) i.e. merging of Binomial 
		// Tree pointed by it1 & it2 is not possible 
		// then move next in heap 
		else if ((*it1)->degree < (*it2)->degree) 
		{ 
			it1++; 
			it2++; 
			if(it3!=_heap.end()) 
				it3++; 
		} 

		// if D(it1),D(it2) & D(it3) are same i.e. 
		// degree of three consecutive Binomial Tree are same 
		// in heap 
		else if (it3!=_heap.end() && 
				(*it1)->degree == (*it2)->degree && 
				(*it1)->degree == (*it3)->degree) 
		{ 
			it1++; 
			it2++; 
			it3++; 
		} 

		// if degree of two Binomial Tree are same in heap 
		else if ((*it1)->degree == (*it2)->degree) 
		{ 
			Node *temp; 
			*it1 = mergeBinomialTrees(*it1,*it2); 
			it2 = _heap.erase(it2); 
			if(it3 != _heap.end()) 
				it3++; 
		} 
	} 
	return _heap; 
} 

// inserting a Binomial Tree into binomial heap 
list<Node*> insertATreeInHeap(list<Node*> _heap, 
							Node *tree) 
{ 
	// creating a new heap i.e temp 
	list<Node*> temp; 

	// inserting Binomial Tree into heap 
	temp.push_back(tree); 

	// perform union operation to finally insert 
	// Binomial Tree in original heap 
	temp = unionBionomialHeap(_heap,temp); 

	return adjust(temp); 
} 


list<Node*> insert(list<Node*> _head, int key) 
{ 
	Node *temp = newNode(key); 
	return insertATreeInHeap(_head,temp); 
} 

void printTree(Node *h) 
{ 
	while (h) 
	{ 
		cout << h->data << " "; 
		printTree(h->child); 
		h = h->sibling; 
	} 
} 

// print function for binomial heap 
void printHeap(list<Node*> _heap) 
{ 
	list<Node*> ::iterator it; 
	it = _heap.begin(); 
	while (it != _heap.end()) 
	{ 
     	cout << "  " << (*it)->degree << "  	 :    ";
		printTree(*it); 
     	cout << endl;
		it++; 
	} 
}

void dot(ofstream &file,Node *h)
{
	if (h == NULL)
	{
		return;
	}
	else
	{
		Node* it = h->child;
		while(it != nullptr)
		{
			file <<  "\t" + to_string(h->data) + "->" + to_string(it->data) + ";\n";
			dot(file,it);
			it = it->sibling;
		}
	}
}

void writedot(list<Node*> _heap)
{
	ofstream file;
	file.open("heap.dot");

	file << "digraph g{\n";
	file << "\tgraph [ dpi = 900 ];\n";
	list<Node*> ::iterator it; 
	it = _heap.begin(); 
	while (it != _heap.end()) 
	{ 
     	if ((*it)->degree == 0)
     	{
     		file << "\t" + to_string((*it)->data) + ";\n";
     	} 
     	else
     	{
     		dot(file,*it); 
     	}
		it++; 
	}

	file << "}\n";
}

int main()
{
	list<Node*> _heap;
	cout << "Enter Number Of Elements To Insert : ";
	int n;
	cin >> n;
	cout << endl;
	for(int i = 0 ; i < n ; i++)
	{
		int temp;
		cin >> temp;
		_heap = insert(_heap,temp);
	}
	cout << "Order    :    Heap Elements" << endl;
	printHeap(_heap);

	writedot(_heap);

    system("dot -Tps heap.dot -o heap.pdf");
    return 0;
}