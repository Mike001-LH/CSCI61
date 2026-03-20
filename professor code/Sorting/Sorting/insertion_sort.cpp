#include <iostream>

using namespace std;

void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

void insertionSort(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;//当前元素的前一个元素的索引

        cout << "Inserting " << key << ":" << endl;
        
        while (j >= 0 && arr[j] > key) {//如果前一个元素大于当前元素
            cout << "Shifting " << arr[j] << " (index " << j << ") to index " << j + 1 << endl;
            arr[j + 1] = arr[j];//将前一个元素向右移动
            
            printArray(arr, n);
            j--;//继续比较下一个前一个元素
            
            cin.get(); 
        }

        arr[j + 1] = key;//将当前元素放到正确的位置

        cout << "Placed " << key << " at index " << j + 1 << endl;
        
        printArray(arr, n);
        cout << endl;
        
        cin.get(); 
    }
}

int main() {
    int arr[] = {12, 11, 13, 5, 6};
    int n = sizeof(arr) / sizeof(arr[0]);

    cout << "Original array: ";
    printArray(arr, n);
    cout << endl;

    insertionSort(arr, n);

    cout << "Sorted array: ";
    printArray(arr, n);

    return 0;
}
/*
初始数组：
Original array: 12 11 13 5 6

Inserting 11:                           第1轮 (i = 1, key = 11)
Shifting 12 (index 0) to index 1
12 12 13 5 6

Placed 11 at index 0              //j = -1, loop ends, place key at index 0
11 12 13 5 6

Inserting 13:                           第2轮 (i = 2, key = 13)
Placed 13 at index 2
11 12 13 5 6

Inserting 5:                            第3轮 (i = 3, key = 5)
Shifting 13 (index 2) to index 3
11 12 13 13 6

Shifting 12 (index 1) to index 2
11 12 12 13 6

Shifting 11 (index 0) to index 1
11 11 12 13 6

Placed 5 at index 0
5 11 12 13 6

Inserting 6:                            第4轮 (i = 4, key = 6)
Shifting 13 (index 3) to index 4
5 11 12 13 13

Shifting 12 (index 2) to index 3
5 11 12 12 13

Shifting 11 (index 1) to index 2
5 11 11 12 13

Placed 6 at index 1
5 6 11 12 13
*/

void insertionSortsimple(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;

        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}