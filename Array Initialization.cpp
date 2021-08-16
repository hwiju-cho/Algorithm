#include<bits/stdc++.h>

using namespace std;
int main()
{
    int arr1[21];
    int arr2[21][21];

    // initialize array

    // 1. memset - not recommended
    memset(arr1, 0, sizeof(arr1));
    memset(arr2, 0, sizeof(arr2));

    // 2. for
    for (int i=0; i < 21; i++)
    {
        arr1[i] = 0;
    }
    for (int i=0; i<21;i++)
    {
        for (int j=0; j<21; j++)
        {
            arr2[i][j] = 0;
        }
    }

    // 3. fill - recommended!
    fill(arr1,arr1+21,0);
    for (int i = 0; i<21;i++)
    {
        fill(arr2[i],arr2[i]+21,0);
    }
}