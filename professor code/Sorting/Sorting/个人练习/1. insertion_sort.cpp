/*
Question 1 (Insertion Sort Variant – Cost Counting)

You are given an integer array. Sort it in ascending order using Insertion Sort.

However, every time an element is shifted one position to the right, count it as 1 move.

Write a function that returns the total number of shifts performed during the sort.

If the array is already sorted, return 0.

Your solution must use the logic of insertion sort.

int insertionShiftCount(int arr[], int n);

Example:

Input:  {8, 3, 6, 1, 7, 2}
Output: 10
*/

#include <iostream>
using namespace std;

int insertionShiftCount(int arr[], int n) {
    int shiftCount = 0;
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;

        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j]; // Shift element to the right
            shiftCount++; // Count the shift
            j--;
        }
    }
    return shiftCount;
}