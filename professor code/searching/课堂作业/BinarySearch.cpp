/*
if (size == 0)
    found = false;
else{
    middle = index of the approximate midpoint of the array segment;
    if(target == a[middle])
        the target has been found at a[middle]
    else if (target < a[middle])
        search for the target left of the midpoint
    else if (target > a[middle])
        search for the target in right of the midpoint
}
*/
#include <iostream>
using namespace std;

bool binarySearch(int a[], int size, int target) {
    if (size == 0){
        return false;
    }
    else{
        int middle = size / 2;
        if (target == a[middle]) {
            return true;
        }
        else if (target < a[middle]) {
            return binarySearch(a, middle, target);
        }
        else {
            return binarySearch(a + middle + 1, size - middle - 1, target);//利用pointer arithmetic，a + middle + 1表示数组a中从middle + 1开始的元素的地址，也就是从右侧开始检索。
        }
    }
    
}

//比方说，一个数组 a 包含 10 个元素（1，2，3，4，5，6，7，8，9，10），size 是 10，target 是 5。第一次调用 binarySearch(a, 10, 5) 时，middle 会被计算为 5（10 / 2）。如果 a[5] 的值等于 target，那么函数会返回 true。如果 a[5] 的值大于 target，那么函数会递归调用 binarySearch(a, 5, 5)，在数组的前半部分继续搜索。如果 a[5] 的值小于 target，那么函数会递归调用 binarySearch(a + 6, 4, 5)，在数组的后半部分继续搜索。