#include <iostream>
#include <vector>
#include <algorithm> // For binary_search

using namespace std;

int main() {
    
    vector<int> data = {1, 2, 4, 5, 9, 12, 18};
    
    int valueToFind = 5;

    bool found = binary_search(data.begin(), data.end(), valueToFind);//调用STL的二分搜索函数，传入数据的开始迭代器、结束迭代器和要找的值

    if (found) {
        cout << "Value " << valueToFind << " found." << endl;
    } else {
        cout << "Value " << valueToFind << " not found." << endl;
    }

    return 0;
}