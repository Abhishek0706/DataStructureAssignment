#include <bits/stdc++.h>
using namespace std;
/**
 * @brief struct for tree
 */
struct tree
{
    int data;
    tree *children;
    int index;
    int height;

    tree()
    {
        height = 1;
        index = -1;
    }

    void inserttree(tree t)
    {
        if (index == -1)
            children = new tree[100];
        index++;
        children[index] = t;
        height = max(height, t.height + 1);
    }
};

/**
 * @brief method returning the flag of preorder
 */
int preorder(tree t, ofstream &fout)
{
    int flag = 0;
    cout << t.data << " ";
    for (int i = t.index; i >= 0; i--)
    {
        flag = 1;
        fout << "\t" << t.data << " -- " << t.children[i].data << ";\n";
        preorder(t.children[i], fout);
    }
    return flag;
}

/**
 * @brief struct for binomial heap
 */
struct binomialheap
{
    int index;
    tree trees[100];

    binomialheap()
    {
        index = -1;
    }

    void insert(int x)
    {
        tree t;
        t.data = x;
        index++;
        trees[index] = t;
        while (trees[index].height >= trees[index - 1].height && index >= 1)
        {
            if (trees[index].data < trees[index - 1].data)
            {
                tree temp;
                temp = trees[index - 1];
                trees[index - 1] = trees[index];
                trees[index] = temp;
            }
            trees[index - 1].inserttree(trees[index]);
            index--;
        }
    }
};

int main()
{
    system("touch graph.dot");
    binomialheap bh;
    fstream fin("input.txt");
    int n;
    fin >> n;
    for (int i = 0; i < n; i++)
    {
        int x;
        char comma;
        fin >> x >> comma;
        bh.insert(x);
    }
    fin.close();
    ofstream fout("graph.dot");
    fout << "graph forest {\n";
    cout << "Order : Heap elements" << endl;
    for (int i = bh.index; i >= 0; i--)
    {
        cout << "    " << bh.index - i << " : ";
        if (preorder(bh.trees[i], fout) == 0)
        {
            fout << "\t" << bh.trees[i].data << ";\n";
        }
        cout << endl;
    }
    fout << "}";
    fout.close();
    
    system("dot -Tpng graph.dot > graph.png");
    system("dot -Tpdf graph.dot -o graph.pdf");
    return 0;
}
