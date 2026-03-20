/*
Question 3 (Merge Sort Variant – Count Inversions)

Given an integer array, write a function that returns the number of inversions in the array.

An inversion is a pair (i, j) such that:

i < j

arr[i] > arr[j]

Your solution must run in O(n log n) time.

Hint: modify Merge Sort.

int countInversions(int arr[], int n);

Example:

Input:  {8, 3, 6, 1}
Output: 5

Because the inversions are:

(8,3)
(8,6)
(8,1)
(3,1)
(6,1)
*/
#include <iostream>
using namespace std;

int mergeAndCount(int* data, int n1, int n2) {//n1和n2是两个subarray的长度，data是包含两个subarray的数组
    int* temp = new int[n1 + n2];
    int i = 0, j = 0, k = 0;//i是第一个subarray的索引，j是第二个subarray的索引，k是temp数组的索引
    int inversions = 0;

    //compare and merge from two halves
    while (i < n1 && j < n2) {
        if (data[i] <= data[n1 + j]) {//如果第一个subarray的当前元素小于等于第二个subarray的当前元素，说明没有逆序对，直接放到temp里
            temp[k++] = data[i++];
        } else {
            temp[k++] = data[n1 + j];
            j++;
            inversions += (n1 - i); // Count inversions
        }
    }
    // Copy remaining elements
    while (i < n1) {
        temp[k++] = data[i++];
    }
    while (j < n2) {
        temp[k++] = data[n1 + j];
        j++;
    }
    // Copy back the merged elements
    for (int i = 0; i < n1 + n2; i++) {
        data[i] = temp[i];
    }
    delete[] temp;
    return inversions;
}