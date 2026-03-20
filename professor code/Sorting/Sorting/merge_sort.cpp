#include <iostream>
using namespace std;

// Merge function: Combines two sorted subarrays into one sorted array//n1和n2是两个subarray的长度，data是包含两个subarray的数组
void merge(int* data, int n1, int n2) {
    int* temp = new int[n1 + n2];  // Temp array for merging
    int i = 0, j = 0, k = 0;//i是第一个subarray的索引，j是第二个subarray的索引，k是temp数组的索引

    // Compare and merge from two halves
    while (i < n1 && j < n2) {//比较两半的当前元素，哪个更小就放到temp里
        if (data[i] <= data[n1 + j]) {
            temp[k++] = data[i++];//i++会先使用i的值，然后i自增1，所以会自动到下一个元素
        } else {
            temp[k++] = data[n1 + j];//data[n1 + j]是第二个subarray的当前元素，因为n1是第一个subarray的长度，所以n1 + j就是第二个subarray的索引
            j++;//到下一个元素
        }
    }

    // Copy any leftover elements
    while (i < n1) temp[k++] = data[i++];
    while (j < n2) temp[k++] = data[n1 + j++];

    // Copy back to original array
    for (int x = 0; x < n1 + n2; x++) {
        data[x] = temp[x];
    }

    delete[] temp;
}

// Recursive mergesort function (working on array + size)
void mergesort(int* data, int n) {//n是当前数组的长度，data是当前数组的指针
    if (n <= 1) return;  // Base case: already sorted

    int n1 = n / 2;
    int n2 = n - n1;

    // Recursive sort calls
    mergesort(data, n1);           // First half
    mergesort(data + n1, n2);       // Second half (data + n1 moves the pointer)

    // Merge both halves
    merge(data, n1, n2);
}

// Main function to test it
int main() {
    int data[] = {6, 3, 8, 5, 2, 7, 4, 1};
    int n = sizeof(data) / sizeof(data[0]);

    mergesort(data, n);

    cout << "Sorted array: ";
    for (int i = 0; i < n; i++) {
        cout << data[i] << " ";
    }
    cout << endl;

    return 0;
}
