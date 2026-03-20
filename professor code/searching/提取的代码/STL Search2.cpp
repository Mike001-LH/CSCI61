#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {

    vector<int> data = {1, 2, 4, 5, 9, 12, 18};

    int valueToFind = 5;

    bool found = binary_search(data.begin(), data.end(), valueToFind);

    if (found) {
        cout << "Value " << valueToFind << " found." << endl;
    } else {
        cout << "Value " << valueToFind << " not found." << endl;
    }

    return 0;
}