#include <iostream>
#include <list>

using namespace std;


int main()
{
    // 1. how to declare
    list<int> L1 = {1,2}; 
    list<int> L2;

    // 2. add element
    list<int> L3 = {1,2};
    L3.push_back(3); // 1 2 3
    L3.push_front(0); // 0 1 2 3

    list<int>::iterator t = L3.begin(); // point to 0
    L3.push_front(-1);
    L3.insert(t,10); // 6 10 0 1 2 3
      
    // 3. delete element
    list<int> L4 = {1,2,3,4};
    list<int>::iterator t1 = L4.begin();
    t1 = L4.erase(t1); // delete 1 and return iterator for next element
    
    // 4. Access to element
    list<int> L5 = {1,2,3,4};
    
    for (auto i : L5) cout << i << ' ';
    cout << '\n';
    
    for (list<int>::iterator it = L5.begin(); it != L5.end(); it++)
        cout << *it <<' ';
    cout << '\n';

    // 5. sort
    list<int> L6 = {5,1,2,3,4};
    L6.sort();
    for (auto i : L6) cout << i << ' ';
    cout << '\n';

    // 6.size
    list<int> L7 = {1,2,3};
    cout << L7.size() <<'\n';

}
