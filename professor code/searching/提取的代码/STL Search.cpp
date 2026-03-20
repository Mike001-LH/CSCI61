#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {

    vector<int> v = {4, 1, 3, 2, 5};

    int valueToFind = 4;

    auto result = find(v.begin(), v.end(), valueToFind);//find()函数接受三个参数：第一个参数是要搜索的范围的起始迭代器，第二个参数是要搜索的范围的结束迭代器，第三个参数是要搜索的值。它返回一个指向找到的元素的迭代器，如果没有找到该元素，则返回end(v)。//这里用auto是因为find()函数返回的是一个迭代器类型，使用auto可以让编译器自动推断出正确的类型，避免了手动指定迭代器类型的麻烦。

    if (result != end(v))//如果result不等于end(v)，说明我们找到了valueToFind这个值在vector v中的位置。因为end(v)表示vector v的末尾，如果result等于end(v)，说明我们没有找到valueToFind这个值。
        cout << "Value " << valueToFind << " found." << endl;
    else
        cout << "Value " << valueToFind << " not found." << endl;

    return 0;
}