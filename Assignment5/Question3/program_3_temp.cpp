#include <bits/stdc++.h> 
using namespace std; 
#define Ver 6
int minKey(int key[], bool mstSet[])  
{   
    int min = INT_MAX, min_index;  
  
    for (int v = 0; v < Ver; v++)  
        if (mstSet[v] == false && key[v] < min)  
            min = key[v], min_index = v;  
  
    return min_index;  
}  
void printMST(int parent[], int graph[Ver][Ver])  
{  
    cout<<"Node1 Node2 Weight\n";  
    for (int i = 1; i < Ver; i++)  
    {
        cout<<(char)(parent[i]+65)<<"     "<<(char)(i+65)<<"     "<<graph[i][parent[i]]<<" \n";  

    }
    ofstream file_output;
    file_output.open ("newick.py");
    file_output << "from ete3 import Tree\n";
    file_output << "l=[\n";
    for (int i = 1; i < Ver; i++)  
    {
        file_output<<"    (\""<<(char)(parent[i]+65)<<"\",";
        file_output<<"\""<<(char)(i+65)<<"\",";
        file_output<<graph[i][parent[i]]<<"),\n";
    }
    file_output<<"]\n";
    file_output<<"t = Tree.from_parent_child_table(l)\n";
    file_output<<"s=t.write()\n";
    file_output<<"tree=Tree(s)\n";
    file_output<<"tree.show()\n";
    file_output.close();
}  
void primMST(int graph[Ver][Ver])  
{  
    int parent[Ver];  
    int key[Ver];  
    bool mstSet[Ver];  
    for (int i = 0; i < Ver; i++)  
        key[i] = INT_MAX, mstSet[i] = false;  
    key[0] = 0;  
    parent[0] = -1; 
    for (int count = 0; count < Ver - 1; count++) 
    {  
        int u = minKey(key, mstSet);  
        mstSet[u] = true;  
        for (int v = 0; v < Ver; v++)   
            if (graph[u][v] && mstSet[v] == false && graph[u][v] < key[v])  
                parent[v] = u, key[v] = graph[u][v];  
    }  
    printMST(parent, graph);  
}  
int main()  
{  
    int V = Ver;
    int E = 8; 
    int graph[Ver][Ver];
    for(int i=0;i<Ver;i++)
    {
        for(int j=0;j<Ver;j++)
        {
            graph[i][j]=0;
        }
    }
    char *buffer = (char*)malloc(3000);
    char *record, *line;
    FILE *fstream = fopen("file.csv", "r");
    if (fstream == NULL)
    {
        printf("\n file opening failed ");
    }
    cout<<"Node1 Node2 Weight\n";  
    for (int i = 0; i < E; i++)
    {
        line = fgets(buffer, 3000, fstream);
        record = strtok(line, ",");
        cout<<*(record+0)<<"     ";       
        cout<<*(record+2)<<"     "; 
        cout<<*(record+4)-48<<"\n"; 
        graph[(int)(*(record+0)-65)][(int)(*(record+2)-65)]=*(record+4)-48;
        graph[(int)(*(record+2)-65)][(int)(*(record+0)-65)]=*(record+4)-48;
    }
    primMST(graph);  
    return 0;  
}  