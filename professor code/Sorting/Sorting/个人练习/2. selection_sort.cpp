/*
Question 2 (Selection Sort Variant – Minimum Swap Count)

You are given an integer array. Sort it in ascending order using Selection Sort.

Return the number of times an actual swap happens.

Do not count the iteration if the minimum element is already in the correct position.

int selectionSwapCount(int arr[], int n);

Example:

Input:  {4, 2, 3, 1}
Output: 2

Explanation:

Pass 1: swap 4 and 1

Pass 2: swap 2 and 2? No actual swap needed

Pass 3: swap 3 and 2
*/
#include <iostream>
using namespace std;
int selectionSwapCount(int arr[], int n) {
    int swapCount = 0;
    for (int i = 0; i < n; i++) {
        int minIdx = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIdx]) {
                minIdx = j;
            }
        }
        if (minIdx != i) {
            swap(arr[i], arr[minIdx]);
            swapCount++;
        }
    }
    return swapCount;
}
