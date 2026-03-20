#include <iostream>
#include <map>

using namespace std;

int main()
{
    multimap<int, int> demo;

    demo.insert(pair<int, int>(1, 10));
    demo.insert(pair<int, int>(2, 20));
    demo.insert(pair<int, int>(2, 10));

    auto range = demo.equal_range(2);//equal_range()函数在multimap中查找键值为2的元素，并返回一个pair类型的对象，其中first成员是一个指向第一个键值为2的元素的迭代器，second成员是一个指向最后一个键值为2的元素之后位置的迭代器。我们将这个pair对象存储在变量range中，以便后续遍历所有键值为2的元素。

    for (auto itr = range.first; itr != range.second; ++itr)//遍历2的所有元素。我们使用一个迭代器itr来遍历从range.first到range.second之间的所有元素。range.first是指向第一个键值为2的元素的迭代器，range.second是指向最后一个键值为2的元素之后位置的迭代器。通过++itr，我们可以逐个访问这些元素，直到itr等于range.second为止。
    {
        cout << itr->first << " " << itr->second << endl;
    }
    /*输出：
    2 20
    2 10
    */

    return 0;
}