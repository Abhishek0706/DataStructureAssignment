#include <iostream>
#include <unordered_map>
using namespace std;

unordered_map<int, int> poly1;
unordered_map<int, int> poly2;
unordered_map<int, int> addition;
unordered_map<int, int> multiplication;

void add(int max)
{
    for (int i = 0; i <= max; i++)
    {
        bool find = false;
        if (poly1.find(i) != poly1.end())
        {
            addition[i] = poly1.at(i);
            find = true;
        }
        if (poly2.find(i) != poly2.end())
        {
            if (find == true)
            {
                addition[i] = addition.at(i) + poly2.at(i);
            }
            else
            {
                addition[i] = poly2.at(i);
            }
        }
    }
    cout << "addition is:" << endl;
    cout << "coef\t"
         << "pwr\t" << endl;
    for (int i = 0; i <= max; i++)
    {
        if (addition.find(i) != addition.end())
        {
            cout << addition.at(i) << "\t" << i << endl;
        }
    }
}
void mul(int n, int m)
{
    cout << "multiplication is :" << endl;
    cout << "coef\t"
         << "pwr\t" << endl;
    int nm = n + m;

    for (int k = 0; k <= nm; k++)
    {
        int summation = 0;
        for (int i = 0; i <= k; i++)
        {
            if ((poly1.find(i) != poly1.end()) && (poly2.find(k - i) != poly2.end()))
            {
                summation += (poly1.at(i) * poly2.at(k - i));
            }
        }
        if (summation != 0)
        {
            multiplication[k] = summation;
        }
    }
    for (int i = 0; i <= nm; i++)
    {
        if (multiplication.find(i) != multiplication.end())
        {
            cout << multiplication.at(i) << "\t" << i << endl;
        }
    }
}

int main()
{
    int max1 = 0;
    int max2 = 0;
    int max = 0;
    int N1;
    cout << "Number of terms in expression :";
    cin >> N1;

    for (int i = 0; i < N1; i++)
    {
        int coef;
        int pwr;
        cin >> coef;
        cin >> pwr;
        poly1[pwr] = coef;

        if (pwr > max1)
        {
            max1 = pwr;
        }
    }

    int N2;
    cout << "Number of terms in expression :";
    cin >> N2;

    for (int i = 0; i < N2; i++)
    {
        int coef;
        int pwr;
        cin >> coef;
        cin >> pwr;
        poly2[pwr] = coef;

        if (pwr > max2)
        {
            max2 = pwr;
        }
    }

    if (max1 >= max2)
    {
        max = max1;
    }
    else
    {
        max = max2;
    }

    while (1 == 1)
    {
        int input;
        cout << "Enter 1 to add or 2 to multiply" << endl;
        cin >> input;
        if (input == 1)
        {
            add(max);
        }
        else if (input == 2)
        {
            mul(max1, max2);
        }
        else
        {
            cout << "invalid operation" << endl;
        }
    }
    return 0;
}