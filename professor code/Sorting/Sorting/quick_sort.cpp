#include <iostream>
#include <vector>
using namespace std;

//这个的作用是将数组分成两部分，左边是小于等于pivot的元素，右边是大于pivot的元素，并返回pivot的最终索引，pivot选择是第一个元素
int partition(vector<int>& arr, int low, int high) {//low和high是当前subarray的边界索引，arr是当前数组的引用
    int p = arr[low];  // Pivot is the first element
    int tbi = low + 1; // Start after pivot
    int tsi = high;    // Start from end

    while (true) {
        while (tbi <= tsi && arr[tbi] <= p) {//如果左边界index和右边界index没有交叉，并且左边界的元素小于等于pivot
            tbi++;//左边界向右移动，直到找到一个大于pivot的元素或者左边界和右边界交叉
        }
        while (arr[tsi] > p) {//如果右边界的元素大于pivot
            tsi--;//右边界向左移动，直到找到一个小于等于pivot的元素或者左边界和右边界交叉
        }
        if (tbi < tsi) {//如果左边界index小于右边界index，说明还没有交叉，此时上方的两个while循环结束后，左边界的元素大于pivot，右边界的元素小于等于pivot，可以交换它们
            swap(arr[tbi], arr[tsi]);
        } 
        else {//如果左边界index大于等于右边界index，说明已经交叉了，停止循环
            break;
        }
    }
    swap(arr[low], arr[tsi]);  // Place pivot in final position//交叉以后，右边界的元素小于等于pivot，左边界的元素大于pivot，所以将pivot和右边界的元素交换，这样pivot就放在了正确的位置上
    return tsi;                 // Final pivot index           //返回pivot的最终索引，这个索引将被用来划分数组，左边是小于等于pivot的元素，右边是大于pivot的元素
}

void quicksort(vector<int>& arr, int low, int high) {
    if (low >= high) return;  // Base case: 1 element or empty array

    int pivotIndex = partition(arr, low, high);
    quicksort(arr, low, pivotIndex - 1);   // Left half     //递归调用quicksort对左半部分进行排序
    quicksort(arr, pivotIndex + 1, high);  // Right half    //递归调用quicksort对右半部分进行排序
}

int main() {
    vector<int> arr = {5,3,8,1,4,6,2,7};
    quicksort(arr, 0, arr.size() - 1);
    for (int x : arr) {
        cout << x << " ";
    }
    cout << endl;
    return 0;
}

/*
quick sort example:
Initial array: [5, 3, 8, 1, 4, 6, 2, 7]
1. First call: quicksort(arr, 0, 7)
   - Partition around pivot 5:
   tbi moves right to 8, then stops at 2
*/