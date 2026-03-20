#include <iostream>
using namespace std;

void heapify(int arr[], int n, int i);
void buildMaxHeap(int arr[], int n);
void buildMinHeap(int arr[], int n);

int main() {
    // Input array
    int arr[] = {1, 3, 5, 4, 6, 13, 10, 9, 8, 15, 17};
    int n = sizeof(arr) / sizeof(arr[0]);// Calculate the number of elements in the array

    // Build a max heap from the array
    buildMaxHeap(arr, n);

    // Print the elements of the max heap
    cout << "Max Heap Elements: ";
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;

    // Build a min heap from the array (optional)
    buildMinHeap(arr, n);

    // Print the elements of the min heap
    cout << "Min Heap Elements: ";
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;

    return 0;
}
/*
array: [17, 15, 13, 9, 6, 5, 10, 4, 8, 3, 1]
index:  0   1   2  3  4  5   6  7  8  9  10

树形表示:
           17 (i=0)
          /  \
        15    13 (i=1,2)
       /  \   / \
      9   6  5  10 (i=3,4,5,6)
     / \ / \
    4  8 3  1 (i=7,8,9,10)
*/
void buildMaxHeap(int arr[], int n) {
    // Start from the last non-leaf node and heapify all subtrees
    for (int i = n / 2 - 1; i >= 0; i--) {
        MaxHeapify(arr, n, i);
    }
}

void MaxHeapify(int arr[], int n, int i) {
    int largest = i;        // Initialize largest as root
    int left = 2 * i + 1;   // Left child index
    int right = 2 * i + 2;  // Right child index

    // If the left child is larger than the root
    if (left < n && arr[left] > arr[largest])
        largest = left;//如果左子节点比根节点大，就把largest指向左子节点

    // If the right child is larger than the largest so far
    if (right < n && arr[right] > arr[largest])
        largest = right;//如果右子节点比当前最大的还大，就把largest指向右子节点

    // If the largest is not the root
    if (largest != i) {//如果上面的比较中，largest发生了变化，说明需要交换
        swap(arr[i], arr[largest]);

        // Recursively heapify the affected sub-tree
        MaxHeapify(arr, n, largest);
    }
}

void buildMinHeap(int arr[], int n) {
    // Start from the last non-leaf node and heapify all subtrees
    for (int i = n / 2 - 1; i >= 0; i--) {
        // Min-heapify logic can be implemented here if needed
        MinHeapify(arr, n, i);
    }
}

void MinHeapify(int arr[], int n, int i) {
    int smallest = i;       // Initialize smallest as root
    int left = 2 * i + 1;   // Left child index
    int right = 2 * i + 2;  // Right child index

    // If the left child is smaller than the root
    if (left < n && arr[left] < arr[smallest])
        smallest = left;
    
    // If the right child is smaller than the smallest so far
    if (right < n && arr[right] < arr[smallest])
        smallest = right;

    // If the smallest is not the root
    if (smallest != i) {
        swap(arr[i], arr[smallest]);

        // Recursively heapify the affected sub-tree
        MinHeapify(arr, n, smallest);
    }
}