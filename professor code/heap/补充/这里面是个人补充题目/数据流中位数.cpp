/*
题目： 读入一串数字（流式），每读入一个数字就输出当前中位数。
要求： 用两个 heap：

max-heap 存较小一半

min-heap 存较大一半
保持 size 差不超过 1。

输入：第一行 m，接着 m 行每行一个数

输出：每行一个中位数（若偶数个，输出两个中间值的平均值，保留 1 位小数）
*/
#include <iostream>
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
void minHeapPush(int arr[], int& size, int value){
    arr[size] = value;
    size++;
    buildMinHeap(arr, size);//重新堆化
}
void maxHeapPush(int arr[], int& size, int value){
    arr[size] = value;
    size++;
    buildMaxHeap(arr, size);//重新堆化
}
int minHeapPop(int arr[], int& size){
    int minValue = arr[0];//堆顶元素是最小值
    arr[0] = arr[size - 1];//用最后一个元素覆盖堆顶,因为最后一个元素在堆中没有特定位置
    size--;
    MinHeapify(arr, size, 0);//重新堆化
    return minValue;
}
int maxHeapPop(int arr[], int& size){
    int maxValue = arr[0];//堆顶元素是最大值
    arr[0] = arr[size - 1];//用最后一个元素覆盖堆顶,因为最后一个元素在堆中没有特定位置
    size--;
    MaxHeapify(arr, size, 0);//重新堆化
    return maxValue;
}

int main() {
    int m;//数字个数
    cin >> m;//读入数字个数
    int* minHeap = new int[m];//存较大一半
    int* maxHeap = new int[m];//存较小一半
    int minHeapSize = 0;
    int maxHeapSize = 0;

    for (int i = 0; i < m; i++) {
        int num;//读入数字
        cin >> num;

        // 插入新数字
        if (maxHeapSize == 0 || num <= maxHeap[0]) {//如果maxHeap为空，或者num小于等于maxHeap堆顶元素
            maxHeapPush(maxHeap, maxHeapSize, num);
        } else {
            minHeapPush(minHeap, minHeapSize, num);
        }

        // 平衡两个堆的大小
        if (maxHeapSize > minHeapSize + 1) {//如果maxHeap比minHeap大超过1
            int value = maxHeapPop(maxHeap, maxHeapSize);//从maxHeap弹出堆顶元素
            minHeapPush(minHeap, minHeapSize, value);//推入minHeap
        } else if (minHeapSize > maxHeapSize) {//如果minHeap比maxHeap大
            int value = minHeapPop(minHeap, minHeapSize);//从minHeap弹出堆顶元素
            maxHeapPush(maxHeap, maxHeapSize, value);//推入maxHeap
        }

        // 输出当前中位数
        if ((maxHeapSize + minHeapSize) % 2 == 1) {//总数为奇数
            cout << maxHeap[0] << endl;
        } else {
            double median = (maxHeap[0] + minHeap[0]) / 2.0;
            cout.setf(ios::fixed);
            cout.precision(1);
            cout << median << endl;
        }
    }

    delete[] minHeap;
    delete[] maxHeap;
    return 0;
}