/*
2.[10 points] You are given an array of sorted integers. Find the N closest (difference is minimum) numbers to a given integer X. Assume X is always given in the array. 

For example:

CASE_1: Input: N = 4, X = 35
               arr[] = {12, 16, 22, 30, 35, 39, 42, 45, 48, 50, 53, 55, 56}
               Output: 30 39 42 45

CASE_2: Input: N = 3, X = 16 
               arr[] = {12, 16, 22, 30, 35, 39, 42, 45, 48, 50, 53, 55, 56}
               Output: 12 22 30

*/
#include <iostream>
using namespace std;

void findClosestElements(int arr[], int size, int N, int X) {//N is the number of closest elements, X is the target element
    int left = 0, right = size - 1;

    // Find the index of X in the array
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] == X) {
            left = mid - 1;
            right = mid + 1;
            break;
        }
        else if (arr[mid] < X) {//if x is on the right of mid
            left = mid + 1;
        }
        else {//if x is on the left of mid
            right = mid - 1;
        }
    }
    //collect the N closest elements to X
    int result[N];
    int count = 0;

    // Now left and right are pointing to the closest elements on either side of X
    while(N > 0) {
        //check if left pointer is out of bounds//X此时在数组的最左边
        if (left < 0) {
            result[count++] = arr[right++];
        }
        else if (right >= size) {//X此时在数组的最右边
            result[count++] = arr[left--];
        }
        else {//X在数组的中间的时候，比较两边选出与x差值较小的元素输出
            if (abs(arr[left] - X) <= abs(arr[right] - X)) {//如果左边的差值较小或者相等，输出左边的元素并将左边的指针向左移一位
                result[count++] = arr[left];
                left--;
            } else {//如果右边的差值较小，输出右边的元素，并将右边的指针向右移一位
                result[count++] = arr[right];
                right++;
            }
        }
        N--;
    }
    // Sort result to restore original array order
    sort(result, result + count);
    // Print the result
    for (int i = 0; i < count; i++) {
        cout << result[i] << " ";
    }
}

/*
CASE_1: Input: N = 4, X = 35
               arr[] = {12, 16, 22, 30, 35, 39, 42, 45, 48, 50, 53, 55, 56}
               Output: 30 39 42 45

CASE_2: Input: N = 3, X = 16 
               arr[] = {12, 16, 22, 30, 35, 39, 42, 45, 48, 50, 53, 55, 56}
               Output: 12 22 30
*/


int main() {
    int arr[] = {12, 16, 22, 30, 35, 39, 42, 45, 48, 50, 53, 55, 56};
    int size = sizeof(arr) / sizeof(arr[0]);
    int N, X;
    N = 4, X = 35;
    cout << "output: ";
    findClosestElements(arr, size, N, X);
    cout << endl;

    N = 3, X = 16;
    cout << "output: ";
    findClosestElements(arr, size, N, X);
    cout << endl;
}

//recursive version
void findClosestElements(int arr[], int left, int size, int right, int N, int X) {
    if (N == 0) {
        return;
    }
    int mid = left + (right - left) / 2;
    if (arr[mid] < X) {
        findClosestElements(arr, mid + 1, size, right, N, X);
    }
    else if (arr[mid] > X) {
        findClosestElements(arr, left, size, mid - 1, N, X);
    }
    else {
        int l = mid - 1, r = mid + 1;
        int result[N];
        int count = 0;
        while (N > 0) {
            //if element is on the left of X
            if (l < 0) {
                result[count++] = arr[r++];
            }
            else if (r >= size) {
                result[count++] = arr[l--];
            }
            else {
                if (abs(arr[l] - X) <= abs(arr[r] - X)) {
                    result[count++] = arr[l--];
                } else {
                    result[count++] = arr[r++];
                }
            }
            N--;
        }
        sort(result, result + count);
        for (int i = 0; i < count; i++) {
            cout << result[i] << " ";
        }
    }
}