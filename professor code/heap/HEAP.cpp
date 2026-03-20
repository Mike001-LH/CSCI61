#include <iostream>
using namespace std;

struct heap_node {
    int data;
    heap_node* left_field;
    heap_node* right_field;

    explicit heap_node(int val)
        : data(val), left_field(nullptr), right_field(nullptr) {}
};

bool mirror(const heap_node* a, const heap_node* b) {
    if (a == nullptr && b == nullptr) return true;
    if (a == nullptr || b == nullptr) return false;

    return mirror(a->left_field,  b->right_field) &&
           mirror(a->right_field, b->left_field);
}

void buildMaxHeap(int arr[], int n){
    // Start from the last non-leaf node and heapify all subtrees
    for (int i = n / 2 - 1; i >= 0; i--) {
        MaxHeapify(arr, n, i);
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

void buildMinHeap(int arr[], int n){
    // Start from the last non-leaf node and heapify all subtrees
    for (int i = n / 2 - 1; i >= 0; i--) {
        MinHeapify(arr, n, i);
    }
}
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
        swap(arr[i], arr[smallest]);

        // Recursively heapify the affected subtree
        MinHeapify(arr, n, smallest);
    }
}

int extractMax(int arr[], int& n){
    if (n <= 0) {
        return -1; // Heap is empty
    }
    int maxValue = arr[0]; // The maximum value is at the root of the max heap
    arr[0] = arr[n - 1]; // Move the last element to the root
    n--; // Reduce the size of the heap
    MaxHeapify(arr, n, 0); // Restore the max heap property
    return maxValue; // Return the extracted maximum value
}
void insertMax(int arr[], int& n, int value){
    arr[n] = value; // Insert the new value at the end of the heap
    n++; // Increase the size of the heap
    int i = n - 1; // Start from the last index
    while (i > 0) {
        int parent = (i - 1) / 2; // Calculate the parent index
        if (arr[i] > arr[parent]) { // If the new value is greater than its parent
            swap(arr[i], arr[parent]); // Swap with the parent
            i = parent; // Move up to the parent's index
        } else {
            break; // The max heap property is satisfied, stop heapifying up
        }
    }
}
int kthLargest(int arr[], int n, int k){
    if (k < 1 || k > n) {
        return -1;
    }
    buildMaxHeap(arr, n);
    for (int i = 0; i < k - 1; i++) {
        swap(arr[0], arr[n - 1]);
        n--;
        MaxHeapify(arr, n, 0);
    }
    return arr[0];
}
void mergeTwoMaxHeaps(int a[], int n, int b[], int m, int out[]){
    // Step 1: Copy elements of both heaps into the output array
    for (int i = 0; i < n; i++) {
        out[i] = a[i];
    }
    for (int j = 0; j < m; j++) {
        out[n + j] = b[j];
    }
    // Step 2: Build a max heap from the combined array
    buildMaxHeap(out, n + m);
}

void median(int arr[], int n){
    if (n <= 0) {
        cout << "No elements in the array." << endl;
        return;
    }
    if (n % 2 == 1) {
        cout << "Median: " << kthLargest(arr, n, n / 2 + 1) << endl; // Odd number of elements
    } else {
        int mid1 = kthLargest(arr, n, n / 2); // First middle element
        int mid2 = kthLargest(arr, n, n / 2 + 1); // Second middle element
        cout << "Median: " << (mid1 + mid2) / 2.0 << endl; // Average of the two middle elements
    }
}

struct Train { int arrival, departure; };
// --- Min-heap operations for departure times (array heap) ---
int extractMin(int heap[], int& size) {
    if (size <= 0) return -1;
    int minVal = heap[0];
    heap[0] = heap[size - 1];
    size--;
    MinHeapify(heap, size, 0);
    return minVal;
}

void insertMin(int heap[], int& size, int value) {
    heap[size] = value;
    size++;

    // heapify up
    int i = size - 1;
    while (i > 0) {
        int parent = (i - 1) / 2;
        if (heap[i] < heap[parent]) {
            swap(heap[i], heap[parent]);
            i = parent;
        } else {
            break;
        }
    }
}

// Find index of next train with smallest arrival among those not used (O(n^2), no sort needed)
int findNextTrainIndex(Train trains[], int n, bool used[]) {
    int best = -1;
    for (int i = 0; i < n; i++) {
        if (!used[i]) {
            if (best == -1 || trains[i].arrival < trains[best].arrival) {
                best = i;
            }
        }
    }
    return best;
}

int minPlatforms(Train trains[], int n) {
    if (n <= 0) return 0;

    // used[] marks which train has been processed (since we're not sorting)
    bool used[1000] = {false}; // adjust if your n can exceed 1000

    // min-heap for departure times
    int depHeap[1000];
    int depSize = 0;

    int maxPlatforms = 0;

    // Process trains in increasing arrival order
    for (int step = 0; step < n; step++) {
        int idx = findNextTrainIndex(trains, n, used);
        used[idx] = true;

        int arr = trains[idx].arrival;
        int dep = trains[idx].departure;

        // Free all platforms whose trains have departed (dep <= arr)
        while (depSize > 0 && depHeap[0] <= arr) {
            extractMin(depHeap, depSize);
        }

        // Occupy a platform with this train's departure
        insertMin(depHeap, depSize, dep);

        if (depSize > maxPlatforms) maxPlatforms = depSize;
    }

    return maxPlatforms;
}
