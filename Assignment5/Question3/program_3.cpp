#include <fstream>
#include <string>
#include <iostream>
#include <bits/stdc++.h>
using namespace std;
struct adjoint_list_node
{
	int weight;
	int destination;
	struct adjoint_list_node *next;
};
struct adjoint_list
{
	struct adjoint_list_node *head;
};
struct Graph
{
	int V;
	struct adjoint_list *array;
};
struct adjoint_list_node *newadjoint_list_node(int destination, int weight)
{
	struct adjoint_list_node *new_node = (struct adjoint_list_node *)malloc(sizeof(struct adjoint_list_node));
	new_node->destination = destination;
	new_node->weight = weight;
	new_node->next = NULL;
	return new_node;
}
struct Graph *create_graph(int V)
{
	struct Graph *graph = (struct Graph *)malloc(sizeof(struct Graph));
	graph->V = V;
	graph->array = (struct adjoint_list *)malloc(V * sizeof(struct adjoint_list));
	for (int i = V; i > 0; i--)
	{
		graph->array[i - 1].head = NULL;
	}
	return graph;
}
void append_edge(struct Graph *graph, int src, int destination, int weight)
{
	struct adjoint_list_node *new_node = newadjoint_list_node(destination, weight);
	new_node->next = graph->array[src].head;
	graph->array[src].head = new_node;
	new_node = newadjoint_list_node(src, weight);
	new_node->next = graph->array[destination].head;
	graph->array[destination].head = new_node;
}
struct fibonacci_heap_node
{
	int v;
	int key;
};
struct fibonacci_heap
{
	int size;
	int capacity;
	int *pos;
	struct fibonacci_heap_node **array;
};
struct fibonacci_heap_node *new_fibonacci_heap_node(int v, int key)
{
	struct fibonacci_heap_node *fibonacci_heap_node = (struct fibonacci_heap_node *)malloc(sizeof(struct fibonacci_heap_node));
	fibonacci_heap_node->v = v;
	fibonacci_heap_node->key = key;
	return fibonacci_heap_node;
}
struct fibonacci_heap *createfibonacci_heap(int capacity)
{
	struct fibonacci_heap *fibonacci_heap = (struct fibonacci_heap *)malloc(sizeof(struct fibonacci_heap));
	fibonacci_heap->pos = (int *)malloc(capacity * sizeof(int));
	fibonacci_heap->size = 0;
	fibonacci_heap->capacity = capacity;
	fibonacci_heap->array = (struct fibonacci_heap_node **)malloc(capacity * sizeof(struct fibonacci_heap_node *));
	return fibonacci_heap;
}
void swap_fibonacci_heap_node(struct fibonacci_heap_node **a, struct fibonacci_heap_node **b)
{
	struct fibonacci_heap_node *t = *a;
	*a = *b;
	*b = t;
}
void fibonacci_heapify(struct fibonacci_heap *fibonacci_heap, int idx)
{
	int smallest, previous, next;
	smallest = idx;
	previous = 2 * idx + 1;
	next = 2 * idx + 2;
	if (previous < fibonacci_heap->size && fibonacci_heap->array[previous]->key < fibonacci_heap->array[smallest]->key)
	{
		smallest = previous;
	}
	if (next < fibonacci_heap->size && fibonacci_heap->array[next]->key < fibonacci_heap->array[smallest]->key)
	{
		smallest = next;
	}
	if (smallest != idx)
	{
		fibonacci_heap_node *smallestNode = fibonacci_heap->array[smallest];
		fibonacci_heap_node *idxNode = fibonacci_heap->array[idx];
		fibonacci_heap->pos[smallestNode->v] = idx;
		fibonacci_heap->pos[idxNode->v] = smallest;
		swap_fibonacci_heap_node(&fibonacci_heap->array[idx], &fibonacci_heap->array[smallest]);
		fibonacci_heapify(fibonacci_heap, smallest);
	}
}
int isEmpty(struct fibonacci_heap *fibonacci_heap)
{
	return fibonacci_heap->size == 0;
}
struct fibonacci_heap_node *extractMin(struct fibonacci_heap *fibonacci_heap)
{
	if (isEmpty(fibonacci_heap))
	{
		return NULL;
	}
	struct fibonacci_heap_node *root = fibonacci_heap->array[0];
	struct fibonacci_heap_node *lastNode = fibonacci_heap->array[fibonacci_heap->size - 1];
	fibonacci_heap->array[0] = lastNode;
	fibonacci_heap->pos[root->v] = fibonacci_heap->size - 1;
	fibonacci_heap->pos[lastNode->v] = 0;
	--fibonacci_heap->size;
	fibonacci_heapify(fibonacci_heap, 0);
	return root;
}
void decrease_key(struct fibonacci_heap *fibonacci_heap, int v, int key)
{
	int i = fibonacci_heap->pos[v];
	fibonacci_heap->array[i]->key = key;
	while (fibonacci_heap->array[i]->key < fibonacci_heap->array[(i - 1) / 2]->key && i)
	{
		fibonacci_heap->pos[fibonacci_heap->array[i]->v] = (i - 1) / 2;
		fibonacci_heap->pos[fibonacci_heap->array[(i - 1) / 2]->v] = i;
		swap_fibonacci_heap_node(&fibonacci_heap->array[i], &fibonacci_heap->array[(i - 1) / 2]);
		i = (i - 1) / 2;
	}
}
bool is_in_fibonacci_heap(struct fibonacci_heap *fibonacci_heap, int v)
{
	if (fibonacci_heap->pos[v] < fibonacci_heap->size)
		return true;
	return false;
}
void display_array(int arr[], int n, string *arr_node, int *arr_weight)
{
	ofstream file_output;
	file_output.open("newick.py");
	file_output << "from ete3 import Tree\n";
	file_output << "l=[\n";
	int sum = 0;
	for (int i = 1; i < n; ++i)
	{
		if (arr[i] < i)
		{
			printf("%c     %c", (char)(arr[i] + 65), (char)(i + 65));
			file_output << "    (\"" << (char)(arr[i] + 65) << "\",";
			file_output << "\"" << (char)(i + 65) << "\""
						<< ",";
			for (int j = 0; i < n; j++)
			{
				if (arr_node[j] == to_string((char)(arr[i] + 65)) + to_string((char)(i + 65)))
				{
					cout << "     " << arr_weight[j] << " \n";
					sum += arr_weight[j];
					file_output << (arr_weight[j]) << "),\n";
					break;
				}
			}
		}
		else
		{
			printf("%c     %c", (char)(i + 65), (char)(arr[i] + 65));
			file_output << "    (\"" << (char)(arr[i] + 65) << "\",";
			file_output << "\"" << (char)(i + 65) << "\""
						<< ",";
			for (int j = 0; i < n; j++)
			{
				if (arr_node[j] == to_string((char)(i + 65)) + to_string((char)(arr[i] + 65)))
				{
					cout << "     " << arr_weight[j] << " \n";
					sum += arr_weight[j];
					file_output << (arr_weight[j]) << "),\n";
					break;
				}
			}
		}
	}

	cout << "sum : " << sum << endl;
	file_output << "]\n";
	file_output << "t = Tree.from_parent_child_table(l)\n";
	file_output << "s=t.write()\n";
	file_output << "tree=Tree(s)\n";
	file_output << "tree.show()\n";
	file_output.close();
}
void prim_mst(struct Graph *graph, string *arr_node, int *arr_weight)
{
	int V = graph->V;
	int parent[V];
	int key[V];
	struct fibonacci_heap *fibonacci_heap = createfibonacci_heap(V);
	for (int v = 1; v < V; ++v)
	{
		parent[v] = -1;
		key[v] = INT_MAX;
		fibonacci_heap->array[v] = new_fibonacci_heap_node(v, key[v]);
		fibonacci_heap->pos[v] = v;
	}
	key[0] = 0;
	fibonacci_heap->array[0] = new_fibonacci_heap_node(0, key[0]);
	fibonacci_heap->pos[0] = 0;
	fibonacci_heap->size = V;
	while (!isEmpty(fibonacci_heap))
	{
		struct fibonacci_heap_node *fibonacci_heap_node = extractMin(fibonacci_heap);
		int u = fibonacci_heap_node->v;
		struct adjoint_list_node *drag_p = graph->array[u].head;
		while (drag_p != NULL)
		{
			int v = drag_p->destination;
			if (is_in_fibonacci_heap(fibonacci_heap, v) && drag_p->weight < key[v])
			{
				key[v] = drag_p->weight;
				parent[v] = u;
				decrease_key(fibonacci_heap, v, key[v]);
			}
			drag_p = drag_p->next;
		}
	}
	display_array(parent, V, arr_node, arr_weight);
}
int main()
{
	int V = 6;
	int E = 8;
	struct Graph *graph = create_graph(V);
	char *buffer = (char *)malloc(3000);
	char *record, *line;
	FILE *fstream = fopen("file.csv", "r");
	if (fstream == NULL)
	{
		printf("\n file opening failed ");
	}
	cout << "Node1 Node2 Weight\n";
	string arr_node[E];
	int arr_weight[E];
	for (int i = 0; i < E; i++)
	{
		line = fgets(buffer, 3000, fstream);
		record = strtok(line, ",");
		if ((int)(*(record + 0)) < (int)(*(record + 2)))
		{
			arr_node[i] = to_string(*(record + 0)) + to_string(*(record + 2));
		}
		else
		{
			arr_node[i] = to_string(*(record + 2)) + to_string(*(record + 0));
		}
		arr_weight[i] = *(record + 4) - 48;
		append_edge(graph, (int)(*(record + 0)) - 65, (int)(*(record + 2)) - 65, *(record + 4) - 48);
	}
	prim_mst(graph, arr_node, arr_weight);
	return 0;
}
