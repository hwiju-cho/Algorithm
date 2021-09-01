#include<iostream>
#include<vector>

using namespace std;

void func(vector<int> v);
bool cmp1 (vector<int> v1, vector<int> v2, int idx);
bool cmp2 (vector<int>& v1, vector<int>& v2, int idx);

int main()
{
    // 1. how to declare
    vector<int> v1;   
    vector<int> v2 = {1,2,3};
    vector<int> v3[10];
    vector<int> v4[] = {{1,2},{3,4}};
    vector<vector<int>> v5;
    vector<int> v6(5); //initialinze 5 elements with 0
    vector<int> v7(10,3); // initialize 10 elements with 3
    vector<int> v8(v7); // copy v7

    // 2. add value
    vector<int> v9;
    
    v9.push_back(10);
    vector<int>::iterator it = v9.begin();
    it = v9.insert(it,2);
    it = v9.insert(it+2,3);

    // 3. delete value
    vector<int> v10(20,5);

    v10.pop_back();
    v10.erase(v10.begin()+10); // delete idx=10
    v10.erase(v10.begin(), v10.begin()+5); // delete where  0 <= idx <5  
    v10.clear(); // delete all elements

    // 4. size
    vector<int> v11(10,5);
    cout << v11.size() <<"\n"; // num of element
    cout << v11.capacity() <<"\n"; // physical size

    // 5. get value
    vector<int> v12 = {1,2,3,4};
    
    cout << v12[2]<<"\n";
    cout << v12.front() <<"\n";
    cout << v12.back() <<"\n";

    for (int i=0;i<v12.size();i++)  cout <<v12[i]<<" ";
    cout <<"\n";

    for (auto i = v12.begin(); i!= v12.end(); i++) cout << *i <<" ";

    // 6. else
    vector<int> v(100);
    func(v);
    cout << v[10]; // 0
}

void func(vector<int> v)
{
    v[10] = 7;
}

// O(N)
bool cmp1 (vector<int> v1, vector<int> v2, int idx)
{
    return v1[idx] > v2[idx];
}

//O(1)
bool cmp2 (vector<int>& v1, vector<int>& v2, int idx)
{
    return v1[idx] > v2[idx];
}
