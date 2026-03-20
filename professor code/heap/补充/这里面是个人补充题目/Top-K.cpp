/*
题目： 给定 n 个整数和 k，输出最大的 k 个数（按从大到小）。
要求： 用最小堆，时间复杂度 O(n log k)，不能排序整个数组。

输入：n k，下一行 n 个整数

输出：k 个数（从大到小）
*/
#include <iostream>
#include <queue>
using namespace std;

void MinHeapify(int arr[], int n, int i){
    int smallest = i;       // Initialize smallest as root
    int left = 2 * i + 1;   // Left child index
    int right = 2 * i + 2;  // Right child index

    // If the left child is smaller than the root
    if (left < n && arr[left] < arr[smallest]) {
        smallest = left;
    }

    // If the right child is smaller than smallest so far
    if (right < n && arr[right] < arr[smallest]) {
        smallest = right;
    }

    // If smallest is not root
    if (smallest != i) {
        swap(arr[i], arr[smallest]);//swap是c++标准库中的一个函数，用于交换两个变量的值

        // Recursively heapify the affected subtree
        MinHeapify(arr, n, smallest);
    }
}
void buildMinHeap(int arr[], int n){
    // Start from the last non-leaf node and heapify all subtrees
    for (int i = n / 2 - 1; i >= 0; i--) {
        MinHeapify(arr, n, i);
    }
}
void MaxHeapify(int arr[], int n, int i){
    int largest = i;        // Initialize largest as root
    int left = 2 * i + 1;   // Left child index
    int right = 2 * i + 2;  // Right child index

    // If the left child is larger than the root
    if (left < n && arr[left] > arr[largest]) {
        largest = left;
    }

    // If the right child is larger than largest so far
    if (right < n && arr[right] > arr[largest]) {
        largest = right;
    }

    // If largest is not root
    if (largest != i) {
        swap(arr[i], arr[largest]);//swap是c++标准库中的一个函数，用于交换两个变量的值

        // Recursively heapify the affected subtree
        MaxHeapify(arr, n, largest);
    }
}
void buildMaxHeap(int arr[], int n){
    // Start from the last non-leaf node and heapify all subtrees
    for (int i = n / 2 - 1; i >= 0; i--) {
        MaxHeapify(arr, n, i);
    }
}   
void buildMaxHeap(int arr[], int n){
    // Start from the last non-leaf node and heapify all subtrees
    for (int i = n / 2 - 1; i >= 0; i--) {
        MaxHeapify(arr, n, i);
    }
}
int KthLargest(int arr[], int n, int k){
    if (k < 1 || k > n) {//如果 k 不合法，返回 -1
        return -1; // Invalid k
    }
    buildMaxHeap(arr, n);//先 build max heap，arr 变成一个最大堆，堆顶元素是数组中最大的元素
    // 删除堆顶 k-1 次，每次删除后堆顶元素就是当前最大的元素，所以我们需要删除 k-1 次，最后一次删除后堆顶就是第 k 大的元素
    for (int i = 0; i < k - 1; i++) {
         swap(arr[0], arr[n - 1]);//把堆顶元素和当前堆的最后一个元素交换
         n--;//堆的大小减1，相当于删除了原来的堆顶元素
         MaxHeapify(arr, n, 0);//重新堆化，堆的大小减1
    }
    return arr[0];//返回当前堆顶元素，即第 k 大的元素
}
//用priority_queue实现的topKFinder，时间复杂度是O(n log k)，空间复杂度是O(k)
int KthLargestWithQueue(int arr[], int n, int k) {
    if (k < 1 || k > n) {
        return -1;
    }
    priority_queue<int> temp;
    for (int i = 0; i < n; i++) {
        temp.push(arr[i]);
    }
    for (int i = 0; i < k - 1; i++) {
        temp.pop();
    }
    return temp.top();
}
void topKFinder(int arr[], int n, int k){//n是整数数量，也就是数组长度，k是要找的最大元素个数
    int* minHeap = new int[k];//
    // 初始化最小堆，前 k 个元素
    for (int i = 0; i < k; i++) {//先把前k个元素放进最小堆
        minHeap[i] = arr[i];
    }
    buildMinHeap(minHeap, k);//构建最小堆

    //遍历剩余的 n - k 个元素
    for (int i = k; i < n; i++) {
        if (arr[i] > minHeap[0]) {//如果当前元素大于堆顶元素
            minHeap[0] = arr[i];//用当前元素替换堆顶元素
            MinHeapify(minHeap, k, 0);//重新堆化
        }
    }
    // 现在 minHeap 中存储的就是最大的 k 个数
    // 但是由于我们是用最小堆存储的，所以需要排序后输出（从大到小）
    //先复制到result数组，再进行排序
    int* result = new int[k];
    for (int i = 0; i < k; i++) {
        result[i] = minHeap[i];
    }
    //对result进行堆排序
    for (int i = k - 1; i >= 0; i--) {
        swap(result[0], result[i]);//把堆顶元素和最后一个元素交换
        MinHeapify(result, i, 0);//重新堆化，堆大小减1，如此以来就可以得到一个从小到大的排序
    }
    // 从大到小输出（反向遍历排序后的数组）
    for (int i = k - 1; i >= 0; i--) {
        cout << result[i];
        if (i > 0) cout << " ";
    }
    cout << endl;
    
    // 释放动态内存
    delete[] minHeap;
    delete[] result;
}
void addToMaxHeap(int arr[], int& n, int value) {
    arr[n] = value;
    n++;
    // // heapify up
    // int i = n - 1;
    // while (i > 0) {
    //     int parent = (i - 1) / 2;
    //     if (arr[i] > arr[parent]) {
    //         swap(arr[i], arr[parent]);
    //         i = parent;
    //     } else {
    //         break;
    //     }
    // }

    // heapify down
    buildMaxHeap(arr, n);
    
}