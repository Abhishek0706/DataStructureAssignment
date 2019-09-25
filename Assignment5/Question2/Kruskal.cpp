#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

// A = {};
// while E si not empty do{
// 	take an edge (u,v) that is shortest in E and delete it from E;
// 	if u and v are in 	different component then add (u,v) to A;

// }

// 1. Sort all the edges in non-decreasing order of their weight.
// 2. Pick the smallest edge. Check if it forms a cycle with the spanning tree formed
// so far. If cycle is not formed, include this edge. Else, discard it.
// 3. Repeat step#2 until there are (V-1) edges in the spanning tree.

// Part 1

class Edge
{
public:
	char src, dest;
	int weight;
	Edge *next = NULL;

	Edge()
	{
	}

	Edge(char s, char d, int w)
	{
		src = s;
		dest = d;
		weight = w;
	}
};
Edge *head = NULL;

class Vertex
{
public:
	char name;
	char parent;

	Vertex()
	{
	}
	Vertex(char a)
	{
		name = a;
		parent = a;
	}
};
Vertex **array = NULL;
int size = 1;
int capacity = 0;

void insertVertex(char c)
{
	//allot
	bool present = false;
	for (int i = 0; i < capacity; i++)
	{
		if (array[i]->name == c)
		{
			present = true;
		}
	}
	if (present == true)
	{
		return;
	}
	else
	{
		Vertex *temp = new Vertex(c);
		array[capacity] = temp;
		// cout<<"Vertex "<<c<<" inserted"<<endl;
		// cout<<array[capacity]->name<<endl;
		capacity++;
		if (size <= capacity)
		{
			array = (Vertex **)realloc(array, (2 * size) * sizeof(Vertex *));
			size = size * 2;
		}
	}
}

void insertEdge(char src, char dest, int weight)
{
	Edge *temp = new Edge(src, dest, weight);
	Edge *current;
	if (head == NULL || head->weight >= temp->weight)
	{
		temp->next = head;
		head = temp;
	}
	else
	{
		current = head;
		while (current->next != NULL && current->next->weight < temp->weight)
		{
			current = current->next;
		}
		temp->next = current->next;
		current->next = temp;
	}
}

void readData()
{

	ifstream myfile;
	myfile.open("input.csv");
	char s[1], d[1];
	int w;
	int count = 2;
	while (myfile.good())
	{
		string line;
		if (count == 2)
		{
			getline(myfile, line, ',');
			strcpy(s, line.c_str());
			insertVertex(s[0]);
			count--;
		}
		else if (count == 1)
		{
			getline(myfile, line, ',');
			strcpy(d, line.c_str());
			insertVertex(d[0]);
			count--;
		}
		else
		{
			getline(myfile, line);
			w = atoi(line.c_str());

			insertEdge(s[0], d[0], w);
			// cout<<s[0]<<" "<<d[0]<<" "<<w<<endl;
			count = 2;
		}
	}
	myfile.close();
}

char find(char c)
{
	int index = 0;
	while (array[index]->name != c)
	{
		index++;
	}
	if (array[index]->parent == array[index]->name)
	{
		return array[index]->name;
	}
	else
	{
		return find(array[index]->parent);
	}
}

void _union(char s, char d)
{
	if (find(s) == find(d))
	{
		return;
	}
	int index = 0;
	char f = find(s);
	while (array[index]->name != f)
	{
		index++;
	}
	array[index]->parent = find(d);
}

void join()
{
	int sum = 0;
	;
	fstream file;
	file.open("graph.dot");
	file << "graph{" << endl;

	//find karo same ho to join mat karna aur same ni ho to union kar dena
	Edge *temp = head;
	while (temp != NULL)
	{
		if (find(temp->src) != find(temp->dest))
		{
			_union(temp->src, temp->dest);
			sum += temp->weight;
			cout << temp->src << " \t" << temp->dest << " \t" << temp->weight << endl;
			file << temp->src << " -- " << temp->dest << "[label=\"" << temp->weight << "\",weight=\"" << temp->weight << "\"];" << endl;
		}

		temp = temp->next;
	}
	file << "}" << endl;
	file.close();
	cout << "sum :" << sum << endl;
}

int main()
{
	system("touch graph.dot");
	array = (Vertex **)malloc(1 * sizeof(Vertex *));
	readData();
	cout << "Node1\tNode2\tWeight" << endl;
	join();

	system("dot -Tpng graph.dot > graph.png");
	system("dot -Tpdf graph.dot -o graph.pdf");

	// insert('A','B',4);
	// insert('A','C',4);
	// insert('B','C',2);
	// insert('C','D',3);

	// cout << head->src << " " << head->dest << " " << head->weight << endl;

	// insertVertex('A');
	// insertVertex('A');
	// cout<<array[1]->parent<<endl;

	// cout<<find('D');

	return 0;
}