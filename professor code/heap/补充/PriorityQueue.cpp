#include <iostream>
#include <queue> // Include the priority_queue STL header

using namespace std;

int main() {
    // Create a max heap (by default) using std::priority_queue
    priority_queue<int> pQ;

    // Push elements onto the heap
    pQ.push(5);
    pQ.push(2);
    pQ.push(9);
    pQ.push(1);
    pQ.push(7);

    // Print the priority queue
    while (!pQ.empty()) {
        cout << pQ.top() << " ";
        pQ.pop();
    }

    return 0;
}
