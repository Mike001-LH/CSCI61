#include <iostream>
#include <map>

using namespace std;

int main()
{
    multimap<int, int> demo;

    demo.insert(pair<int, int>(1, 10));
    demo.insert(pair<int, int>(2, 20));
    demo.insert(pair<int, int>(2, 10));

    multimap<int, int>::iterator iter;
    int index = 2;//我们定义了一个整数变量index，并将其赋值为2，表示我们要在demo这个multimap中查找键值为2的元素。

    iter = demo.find(index);//返回一个指向demo中第一个键值为index的元素的迭代器，如果找不到该键值，则返回demo.end()。因为demo是一个multimap，可能存在多个键值为2的元素，所以find()函数会返回第一个匹配的元素。

    if (iter == demo.end())
        cout << "Not found";
    else
        cout << iter->first << " " << iter->second;//输出: 2 20，说明我们找到了一个键值为2的元素，并且它的值是20。注意，因为demo中有两个键值为2的元素（一个是2:20，另一个是2:10），find()函数只返回第一个匹配的元素，所以我们得到的是2:20这个键值对，而不是2:10。

    return 0;
}