#include <iostream>
#include <queue>
#include <string>
#include <cstdlib>  // for rand() and srand()
#include <ctime>    // for time()
#include <thread>   // for sleep
#include <chrono>   // for seconds
using namespace std;

int main() {
    queue<string> questionQueue;
    questionQueue.push("What is the capital of France?");
    questionQueue.push("How do you declare a variable in C++?");
    questionQueue.push("Explain the concept of polymorphism.");
    questionQueue.push("What is the difference between an array and a vector?");
    questionQueue.push("What are the advantages of using classes in OOP?");

    cout << "Professor's Queue of Sample Questions:" << endl;

    //initialize random seed
    srand(time(nullptr));//use current time as seed for random generator, time(nullptr) returns current time, srand sets the seed for rand()

    while(!questionQueue.empty()){
        cout << "\nQuestion: " << questionQueue.front() << endl;
        int waitTime = rand() % 3 + 1; // Random wait time between 1 to 3 seconds
        // Simulate time taken for professor to think
        this_thread::sleep_for(chrono::seconds(waitTime));//this_thread::sleep_for pauses the execution of the current thread for the specified duration
        cout << "Professor: That's a great question!" << endl;
        questionQueue.pop();
    }

    cout << "\nAll questions answered!" << endl;
}