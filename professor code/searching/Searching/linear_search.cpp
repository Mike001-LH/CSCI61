#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    vector<int> v = {4, 1, 3, 2, 5};

    int valueToFind = 4;

    auto result = find(v.begin(), v.end(), valueToFind);//用auto是因为find函数返回的是一个迭代器，指向找到的元素的位置，如果没有找到则指向v.end()，所以result的类型是vector<int>::iterator

    if (result != v.end())
        cout << "Value " << valueToFind << " found." << endl;//如果result不等于v.end()，说明找到了valueToFind，输出找到的消息
    else
        cout << "Value " << valueToFind << " not found." << endl;//如果result等于v.end()，说明没有找到valueToFind，输出没有找到的消息

    return 0;
}
