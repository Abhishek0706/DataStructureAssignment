#include<iostream>
#include<bits/stdc++.h>
using namespace std;
void sol_print(int *arr,int n);
int is_save(int *arr,int n, int r, int c);
int helper(int *arr,int n, int c);
void solveNqueen(int n);
int total_no_sol=0;

/**
 * @brief main method for driving the programme
 */
int main()
{
    int n;
    cout<<"N:";
    cin>>n;
    solveNqueen(n);
    cout<<"Total number of combinations: "<<total_no_sol<<endl;
    cout << "Press any key to exit:";
    cin.ignore();
    cin.get();
    return 0;
}
/**
 * @brief print the solution for the given array 
 */
void sol_print(int *arr,int n)
{
    total_no_sol++;
    static int number_of_combinations = 1;
    cout<<"Combination "<<number_of_combinations++<<":\n";
    for (int i = 0; i <= n-1; i++)
    {
        for (int j = 0; j <= n-1; j++)
            {cout<<("%d ", *((arr+i*n) + j))<<" ";}
        cout<<("\n");
    }
    cout<<("\n");
}

/**
 * @brief find if the placement of next queen is safe 
 */
int is_save(int *arr,int n, int r, int c)
{
    int i;
    int j;
    for (i = 1; i <= c; i++)
    {
        if (*((arr+r*n) + i-1))
        {
            return 0;
        }
    }
    for (i=r+1, j=c+1; i>=1 && j>=1; i--, j--)
    {
        if (*((arr+i*n-n) + j-1))
        {
            return 0;
        }
    }

    for (i=r+1, j=c+1; j>=1 && i<n+1; i++, j--)
    {
        if (*((arr+i*n-n) + j-1))
        {
            return 0;
        }
    }
    return 1;
}

/**
 * @brief helper class for finding the queen is safe 
 */
int helper(int *arr,int n, int c)
{
    if (c == n)
    {
        sol_print((int*)arr,n);
        return 1;
    }
    int result = 0;
    for (int i = 0; i <= n-1; i++)
    {
        if ( is_save((int*)arr,n, i, c) )
        {
            *((arr+i*n) + c) = 1;
            result = helper((int*)arr,n, c + 1) || result;
            *((arr+i*n) + c) = 0;
        }
    }
    return result;
}
/**
 * @brief solving the n queen problem for all possible solutions
 */
void solveNqueen(int n)
{
    int arr[n][n];
    memset(arr, 0, sizeof(arr));
    helper((int*)arr,n, 0);
    return ;
}