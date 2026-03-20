#include <iostream>
#include <map>

using namespace std;

int main() {

    int index;

    cout << "Enter key to search: ";
    cin >> index;

    map<int, int> demo;

    // Insert elements
    demo.insert(make_pair(1, 20));
    demo.insert(pair<int, int>(2, 10));

    // Search for key
    auto iter = demo.find(index);//find()-- Returns an iterator tothe element with key value 'g’inthe map if found, else returnsthe iterator to end.
    //find()函数在map中查找键值为index的元素，如果找到，返回一个指向该元素的迭代器；如果没有找到，返回一个指向map末尾之后位置的迭代器（demo.end()）。我们将这个迭代器存储在变量iter中，以便后续检查是否找到了键值index。

    if (iter == demo.end())
        cout << "Key not present";
    else
        cout << "Key-value pair present: "
             << iter->first << " " << iter->second;

    return 0;
}
/*
Enter key to search: 2
Key-value pair present:2 10
Enter key to search: 3
Key not present
*/