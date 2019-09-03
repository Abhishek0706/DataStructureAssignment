#include <stdlib.h>
#include <stdio.h>
#include <bits/stdc++.h>
using namespace std;

/**
 * @brief find the length of the subarray
 */
int findLength(int arr[],
                    int N,
                    int n)
{

    unordered_map<int, int> h;
    int sum = 0, max = 0;

    for (int i = 0; i < N; i++)
    {

        sum += arr[i];

        if (sum == n)
            max = i + 1;

        if (h.find(sum) == h.end())
            h[sum] = i;

        if (h.find(sum - n) != h.end())
        {

            if (max < (i - h[sum - n]))
                max = i - h[sum - n];
        }
    }

    return max;
}
/**
 * @brief main method for driving the code
 */
int main()
{
	cout <<"N = ";
	int N;
	cin>>N;
	int arr[N];
	for(int i=0;i<N;i++){
		cin>>arr[i];
	}
	cout<<"n = ";
	int n;
	cin>>n;
	cout<<findLength(arr,N,n)<<endl;

    return 0;
}