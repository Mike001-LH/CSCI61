#include <iostream>
#include <vector>

using namespace std;

bool binarySearchRecursive(const vector<int>& data, int valueToFind) {
    if (data.empty()) {// Base case: empty vector
        return false;
    }

    int mid = data.size() / 2;

    if (data[mid] == valueToFind) {//如果中间元素等于要找的值，返回true
        return true;
    } 
    else if (data[mid] > valueToFind) {//中间元素大于要找的值，说明在左半部分
        return binarySearchRecursive(vector<int>(data.begin(), data.begin() + mid), valueToFind);
    } 
    else {//中间元素小于要找的值，说明在右半部分
        return binarySearchRecursive(vector<int>(data.begin() + mid + 1, data.end()), valueToFind);
    }
}

int main() {
    
    vector<int> data = {1, 2, 4, 5, 9, 12, 18};
    int valueToFind = 13;

    bool found = binarySearchRecursive(data, valueToFind);//调用递归的二分搜索函数

    if (found) {
        cout << "Value " << valueToFind << " found." << endl;
    } else {
        cout << "Value " << valueToFind << " not found." << endl;
    }

    return 0;
}
