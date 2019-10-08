#include <iostream>
#include <fstream>
#include <cstring>
#include <unordered_map>
#include <vector>
#include <list>
#include <queue>
#include <stack>

using namespace std;

/**
 * @brief graph class
 */
class Graph
{
public:
    vector<list<char>> vect;
    void addEdge(char v, char w);
    void DFS(char v);
    void BFS(char v);
    void print();
    bool isCyclic();
    bool isCyclicUtil(char v);
    void diameter();
    int diameterUtil(char v);
};
Graph *graph = new Graph();

/**
 * @brief method for adding edge in a graph with given vertices
 */
void Graph::addEdge(char v, char w)
{
    bool findv = false;
    bool findw = false;
    for (auto i = vect.begin(); i != vect.end(); i++)
    {
        if (i->front() == v)
        {
            findv = true;
            i->push_back(w);
        }
        if (i->front() == w)
        {
            findw = true;
            i->push_back(v);
        }
    }
    if (findv == false)
    {
        list<char> temp;
        temp.push_back(v);
        temp.push_back(w);
        vect.push_back(temp);
    }
    if (findw == false)
    {
        list<char> temp;
        temp.push_back(w);
        temp.push_back(v);
        vect.push_back(temp);
    }
}
/**
 * @brief method for printing bfs of the graph with initial vertex 
 */
void Graph::BFS(char v)
{

    unordered_map<char, bool> visited;
    for (auto i = vect.begin(); i != vect.end(); i++)
    {
        visited[i->front()] = false;
    }
    queue<char> q;

    if (visited.find(v) != visited.end())
    {
        q.push(v);
        visited[v] = true;
    }
    else
    {
        std::cout << "invalid vertex" << endl;
        return;
    }
    std::cout << "BFS is : ";
    while (!q.empty())
    {
        std::cout << q.front() << " ";
        for (auto i = vect.begin(); i != vect.end(); i++)
        {
            if (i->front() == q.front())
            {
                list<char> l = *i;
                auto j = l.begin();
                j++;
                for (j; j != l.end(); j++)
                {
                    if (visited[*j] == false)
                    {
                        q.push(*j);
                        visited[*j] = true;
                    }
                }
            }
        }
        q.pop();
    }
    std::cout << endl;
} /**
 * @brief method for printing the dfs of graph with given vertices
 */
void Graph::DFS(char v)
{
    unordered_map<char, bool> visited;
    for (auto i = vect.begin(); i != vect.end(); i++)
    {
        visited[i->front()] = false;
    }
    stack<char> s;
    if (visited.find(v) != visited.end())
    {
        s.push(v);
        visited[v] = true;
    }
    else
    {
        std::cout << "invalid vertex" << endl;
        return;
    }
    std::cout << "DFS is : ";
    std::cout << s.top() << " ";

    while (!s.empty())
    {
        bool find = false;

        for (auto i = vect.begin(); i != vect.end() && find == false; i++)
        {
            if (i->front() == s.top())
            {
                find = true;
                list<char> l = *i;

                auto j = l.begin();
                j++;
                for (j; j != l.end(); j++)
                {
                    if (visited[*j] == false)
                    {
                        s.push(*j);
                        std::cout << *j << " ";
                        visited[*j] = true;
                        break;
                    }
                }
                if (j == l.end())
                {
                    s.pop();
                }
            }
        }
    }
    std::cout << endl;
}
/**
 * @brief method for printing the graph in the form of adjacency list
 */
void Graph::print()
{
    vector<list<char>> v = graph->vect;
    for (auto i = v.begin(); i != v.end(); i++)
    {
        list<char> l = *i;
        for (auto j = l.begin(); j != l.end(); j++)
        {
            std::cout << *j << "-";
        }
        std::cout << endl;
    }
}
/**
 * @brief method detecting the graph has cycle or not starting with a given vertex
 */
bool Graph::isCyclicUtil(char v)
{
    bool cycle = false;
    unordered_map<char, bool> visited;
    for (auto i = vect.begin(); i != vect.end(); i++)
    {
        visited[i->front()] = false;
    }
    stack<char> s;

    s.push(v);
    visited[v] = true;

    while (!s.empty())
    {
        bool find = false;

        for (auto i = vect.begin(); i != vect.end() && find == false; i++)
        {
            if (i->front() == s.top())
            {
                find = true;
                list<char> l = *i;

                auto j = l.begin();
                j++;
                for (j; j != l.end(); j++)
                {
                    if (visited[*j] == false)
                    {
                        s.push(*j);

                        for (auto ii = vect.begin(); ii != vect.end(); ii++)
                        {
                            if (ii->front() == *j)
                            {
                                list<char> ll = *ii;
                                int count = 0;
                                auto jj = ll.begin();
                                jj++;
                                for (jj; jj != ll.end(); jj++)
                                {
                                    if (visited[*jj] == true)
                                    {
                                        count++;
                                    }
                                }
                                if (count > 1)
                                {
                                    cycle = true;
                                }
                            }
                        }
                        visited[*j] = true;
                        break;
                    }
                }
                if (j == l.end())
                {
                    s.pop();
                }
            }
        }
    }
    return cycle;
}
/**
 * @brief nethod detecting the graph has cycle or not
 */
bool Graph::isCyclic()
{
    int V = vect.size();
    for (int i = 0; i < V; i++)
    {
        list<char> l = vect[i];
        if (isCyclicUtil(l.front()))
            return true;
    }
    return false;
}
/**
 * @brief method returning the length of longest path in graph with a given vertex
 */
int Graph::diameterUtil(char v)
{
    int length = 0;
    unordered_map<char, bool> visited;
    unordered_map<char, int> rank;
    for (auto i = vect.begin(); i != vect.end(); i++)
    {
        visited[i->front()] = false;
        rank[i->front()] = 0;
    }
    queue<char> q;

    q.push(v);
    visited[v] = true;
    rank[v] = 0;

    while (!q.empty())
    {

        for (auto i = vect.begin(); i != vect.end(); i++)
        {

            if (i->front() == q.front())
            {
                list<char> l = *i;
                auto j = l.begin();
                j++;
                for (j; j != l.end(); j++)
                {
                    if (visited[*j] == false)
                    {

                        q.push(*j);
                        visited[*j] = true;
                        rank[*j] = rank[(*i).front()] + 1;
                        if (rank[*j] > length)
                        {
                            length = rank[*j];
                        }
                        // cout << i->front() << " " << *j << endl;
                    }
                }
            }
        }
        q.pop();
    }

    // cout << length;
    return length;
}
/**
 * @brief method returning the diameter of the graph
 */
void Graph::diameter()
{
    int max = 0;
    for (int i = 0; i < vect.size(); i++)
    {
        int length = diameterUtil((vect[i]).front());
        if (length > max)
        {
            max = length;
        }
    }
    cout << "\ndiameter is : " << max << endl;
}
/**
 * @brief method for reading the data from input file
 */
void readData()
{
    ifstream myfile;
    myfile.open("input.txt");
    while (myfile.good())
    {
        string line;
        if (!getline(myfile, line, ' ') || line.empty())
            break;
        char v = line[0];
        if (!getline(myfile, line) || line.empty())
            break;
        char w = line[0];
        graph->addEdge(v, w);
    }
}
/**
 * @brief method for running the menu for the programme
 */
void runprogramme()
{
    while (true)
    {
        std::cout << "1. insert edge" << endl;
        std::cout << "2. BFS transversal" << endl;
        std::cout << "3. DFS transversal" << endl;
        std::cout << "4. cycle finding in graph" << endl;
        std::cout << "5. Calculate diameter of graph" << endl;

        int input;
        std::cin >> input;
        if (input == 1)
        {
            char v;
            char w;
            cin >> v;
            cin >> w;
            graph->addEdge(v, w);
        }
        else if (input == 2)
        {
            std::cout << "starting vertex : ";
            char v;
            std::cin >> v;
            graph->BFS(v);
        }
        else if (input == 3)
        {
            std::cout << "starting vertex : ";
            char v;
            std::cin >> v;
            graph->DFS(v);
        }
        else if (input == 4)
        {
            if (graph->isCyclic() == true)
            {
                cout << "Yes" << endl;
            }
            else
            {
                cout << "NO" << endl;
            }
        }
        else if (input == 5)
        {
            graph->diameter();
        }
        else
        {
            std::cout << "invalid input" << endl;
        }
    }
}

int main()
{
    readData();
    runprogramme();
    return 0;
}