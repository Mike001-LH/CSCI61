implementation choices and any challenges have been written in the code

Heap:

Q1:
^C
mike@Rentians-MacBook-Pro-5 trees % cd "/Users/mike/Documents/CSCI61/homework/HW02/heaps"     
mike@Rentians-MacBook-Pro-5 heaps % g++ -std=c++11 1.cpp -o 1.run                        
1.cpp:56:9: error: use of undeclared identifier 'MaxHeapify'
   56 |         MaxHeapify(arr, n, i);
      |         ^
1 error generated.
(I Fixed name the the function)

mike@Rentians-MacBook-Pro-5 heaps % g++ -std=c++11 1.cpp -o 1.run
mike@Rentians-MacBook-Pro-5 heaps % ./1.run                                              
Max Heap Elements: 17 15 13 9 6 5 10 4 8 3 1 
Min Heap Elements: 17 15 13 9 6 5 10 4 8 3 1 
(I fix the implementation of buildMinHeap)

mike@Rentians-MacBook-Pro-5 heaps % g++ -std=c++11 1.cpp -o 1.run
mike@Rentians-MacBook-Pro-5 heaps % ./1.run                      
Max Heap Elements: 17 15 13 9 6 5 10 4 8 3 1 
Min Heap Elements: 1 3 5 4 6 13 10 9 8 15 17 
mike@Rentians-MacBook-Pro-5 heaps % 
(Success)



Q2:
mike@Rentians-MacBook-Pro-5 heaps % g++ -std=c++11 2.cpp -o 2.run
mike@Rentians-MacBook-Pro-5 heaps % ./2.run                      
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
mike@Rentians-MacBook-Pro-5 heaps % 
