#include <iostream>
using namespace std;
/*
Given BuildHeap(), an in-place sorting algorithm is easily constructed :

1. Maximum element is at A[0].
2. Discard by swapping with element at A[n-1]
    1. Decrement heap_size[A]
    2. A[n-1] now contains correct value
3. Restore heap property by calling Heapify()
4. Repeat, aleays swapping A[0] with A[n-1].
*/

// 交换两个元素
void swap(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}

// Heapify函数：维护堆性质
void heapify(int arr[], int n, int i) {
    int largest = i;           // 假设根节点最大
    int left = 2 * i + 1;      // 左子节点索引
    int right = 2 * i + 2;     // 右子节点索引
    
    // 如果左子节点存在且大于根节点
    if (left < n && arr[left] > arr[largest])
        largest = left;
    
    // 如果右子节点存在且大于当前最大值
    if (right < n && arr[right] > arr[largest])
        largest = right;
    
    // 如果最大值不是根节点
    if (largest != i) {
        swap(arr[i], arr[largest]);
        
        // 递归heapify受影响的子树
        heapify(arr, n, largest);
    }
}

// 建立最大堆
void buildMaxHeap(int arr[], int n) {
    // 从最后一个非叶子节点开始，向上heapify所有子树
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(arr, n, i);
    }
}

// 堆排序主函数
void heapsort(int arr[], int n) {
    // 步骤1：建立最大堆
    buildMaxHeap(arr, n);
    
    // 步骤2-4：重复提取最大值并恢复堆
    for (int i = n - 1; i >= 1; i--) {
        // 步骤2：交换A[0]和A[i]，将最大元素放到正确位置
        swap(arr[0], arr[i]);
        
        // 步骤3：恢复堆性质（堆大小减1）
        heapify(arr, i, 0);
    }
}

int main() {
    int arr[] = {1, 3, 5, 4, 6, 13, 10, 9, 8, 15, 17};
    int n = sizeof(arr) / sizeof(arr[0]);
    
    cout << "原数组: ";
    for (int i = 0; i < n; i++)
        cout << arr[i] << " ";
    cout << endl;
    
    heapsort(arr, n);
    /*
    过程如下：
    1. 建立最大堆
       初始数组: [1, 3, 5, 4, 6, 13, 10, 9, 8, 15, 17]
       最大堆:   [17, 15, 13, 9, 6, 5, 10, 4, 8, 3, 1]
    2. 交换并heapify
         交换17和1: [1, 15, 13, 9, 6, 5, 10, 4, 8, 3, 17]
         heapify后: [15, 9, 13, 8, 6, 5, 10, 4, 1, 3, 17]
         交换15和3: [3, 9, 13, 8, 6, 5, 10, 4, 1, 15, 17]
         heapify后: [13, 9, 10, 8, 6, 5, 3, 4, 1, 15, 17]
         ...
    最终排序结果: [1, 3, 4, 5, 6, 8, 9, 10, 13, 15, 17]
    因为每次都是交换A[0]和A[n-1]，所以最大元素总是被放到数组末尾，最终实现排序。
    */
    
    cout << "排序后: ";
    for (int i = 0; i < n; i++)
        cout << arr[i] << " ";
    cout << endl;
    
    return 0;
}


// ## 算法解释

// **Heapsort的核心思想：**
// 1. **建堆阶段**：把无序数组变成最大堆（根节点最大）
// 2. **排序阶段**：重复执行
//    - 把堆顶（最大元素）与堆尾交换
//    - 堆大小减1（排除已排好的元素）
//    - 对新堆顶执行heapify恢复堆性质

// **为什么总是交换 A[0] 和 A[n-1]？**
// - A[0] 是最大堆的根，存储当前堆中最大的元素
// - A[n-1] 是当前堆的最后位置
// - 交换后，最大元素就放到了它最终应该在的位置（数组末尾）

// **时间复杂度：** O(n log n)  
// **空间复杂度：** O(1) - 原地排序

// 运行结果：
// ```
// 原数组: 1 3 5 4 6 13 10 9 8 15 17 
// 排序后: 1 3 4 5 6 8 9 10 13 15 17