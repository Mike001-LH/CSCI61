/*
1. [5 points] Write a C++ program that uses search concepts discussed in class to find a 'Joey' element! 
What is a 'Joey' element you ask? A Joey element in an array of n integers (no duplicates) is an element X such that a[X] = X. 

For example: 

int a[] = {1,5,2,6,7,3}, a[2] = 2 --> 2 is a 'Joey' element! :) 

int b[] = {1,2,3,8,9} --> No 'Joey' element!
*/
#include <iostream>
#include <vector>
using namespace std;

int findJoeyElement(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        if (arr[i] == i) {
            return arr[i]; // Return the Joey element
        }
    }
    return -1; // Return -1 if no Joey element is found
}

int main() {
    int a[] = {1, 5, 2, 6, 7, 3};
    int sizeA = sizeof(a) / sizeof(a[0]);
    int joeyA = findJoeyElement(a, sizeA);
    if (joeyA != -1) {
        cout << joeyA << " is a 'Joey' element!" << endl;
    }
    else {
        cout << "No 'Joey' element!" << endl;
    }
}