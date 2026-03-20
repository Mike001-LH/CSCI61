/*
Implementation Choices:
I used a struct to define the binary tree node and initialize its members using a constructor.
I wrote the operator< function inside the struct so that it can be used to compare two FoodOrder objects by their priority.
The operator< function is used by the priority_queue to maintain the order of elements
I output messages in the processOrder function, the time delay is achieved using sleep_for from the <thread> and <chrono> libraries.

Challenges Encountered:
I don't know how to make a time delay in C++, so I researched and found that this_thread means the current thread and sleep_for can pause the thread for a specified duration.
Besides, I don't know that writing the operator< function inside the struct can help the priority_queue to compare the objects correctly, so I looked up some examples online to understand this.
*/

/*
2. (20 points) You are tasked with creating a C++ program for a restaurant to manage food orders using a priority queue. Your program should follow these specifications:

Define a  FoodOrder struct with the following attributes:

name (a string): Represents the name of the food item.
priority (an integer): Represents the priority of the order, with higher values indicating more urgent orders.
Implement a custom comparison operator for  FoodOrder objects to ensure that higher-priority orders are processed first in the priority queue.

Create a  priority_queue of  FoodOrder objects called  orderQueue to manage food orders.

Implement a function called  processOrder that simulates the processing of food orders. For this simulation, assume that it takes 2 seconds to prepare each food item. 

Add at least five example food orders with different priorities to the orderQueue.

Simulate the processing of food orders by dequeuing orders from the priority queue one by one, calling the processOrder  function for each order, and displaying a message indicating that the order is ready.

Test your program with the provided example food orders and provide the expected output.

Input: 

Food Name       Priority
--------------------------
Pizza           3
Burger          2
Salad           1
Pasta           3
Ice Cream       2

Output: 

Restaurant Orders:
Preparing Pizza (Priority: 3)
Order for Pizza (Priority: 3) is ready.
Preparing Pasta (Priority: 3)
Order for Pasta (Priority: 3) is ready.
Preparing Burger (Priority: 2)
Order for Burger (Priority: 2) is ready.
Preparing Ice Cream (Priority: 2)
Order for Ice Cream (Priority: 2) is ready.
Preparing Salad (Priority: 1)
Order for Salad (Priority: 1) is ready.

Submit your complete C++ code along with comments explaining your implementation choices and any challenges you encountered during development.


*/
#include <iostream>
#include <queue>// Include the priority_queue STL header
#include <string>
#include <thread>// For sleep_for
#include <chrono>// For seconds
using namespace std;

//1, Define a FoodOrder struct
struct FoodOrder {
    string name;    // Name of the food item
    int priority;   // Priority of the order, the higher the number, the higher the priority

    //constructor
    FoodOrder(string n, int p) : name(n), priority(p) {}

    //2, Implement a custom comparison operator for  FoodOrder objects to ensure that higher-priority orders are processed first in the priority queue.
    bool operator<(const FoodOrder& other) const {
        return priority < other.priority;
    }
};

//4, Implement a function called  processOrder that simulates the processing of food orders. 
//For this simulation, assume that it takes 2 seconds to prepare each food item. 
void processOrder(const FoodOrder& order) {
    cout << "Preparing " << order.name << " (Priority: " << order.priority << ")" << endl;
    // Simulate preparation time)"
    this_thread::sleep_for(chrono::seconds(2));//this means the current thread will sleep for 2 seconds
    cout << "Order for " << order.name << " (Priority: " << order.priority << ") is ready." << endl;
}

int main() {
    //3, Create a  priority_queue of  FoodOrder objects called  orderQueue to manage food orders.
    priority_queue<FoodOrder> orderQueue;

    //5, Add at least five example food orders with different priorities to the orderQueue.
    orderQueue.push(FoodOrder("Pizza", 3));
    orderQueue.push(FoodOrder("Burger", 2));
    orderQueue.push(FoodOrder("Salad", 1));
    orderQueue.push(FoodOrder("Pasta", 3));
    orderQueue.push(FoodOrder("Ice Cream", 2));

    cout << "Restaurant Orders:" << endl;

    //6, Simulate the processing of food orders by dequeuing orders from the priority queue one by one,
    // calling the processOrder  function for each order, and displaying a message indicating that the order is ready.
    while (!orderQueue.empty()) {
        FoodOrder currentOrder = orderQueue.top();//highest priority order
        orderQueue.pop();
        processOrder(currentOrder);//process the order
    }
}