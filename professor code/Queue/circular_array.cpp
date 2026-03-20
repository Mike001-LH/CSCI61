#include <iostream>

using namespace std;

class CircularQueue {
private:
    char* arr;//array to store queue elements
    int head;//head是队列的头指针，指向队列的第一个元素，出队时从head位置移除元素
    int tail;//tail是队列的尾指针，指向队列的最后一个元素，入队时在tail位置添加新元素
    int capacity;
    int size;

public:
    CircularQueue(int capacity) {//constructor
        this->capacity = capacity;//把传入的容量值赋给类的成员变量capacity
        arr = new char[capacity];//动态分配一个字符数组用于存储队列元素
        head = tail = -1;
        size = 0;
    }

    ~CircularQueue() {
        delete[] arr;
    }

    bool isEmpty() {
        return size == 0;
    }

    bool isFull() {
        return size == capacity;
    }

    void enqueue(char item) {
        if (isFull()) {
            cout << "Queue is full. Cannot enqueue." << endl;
            return;
        }

        if (tail == capacity - 1) {//如果尾指针到达数组末端，则循环回到数组起始位置，实现环形效果
            tail = 0;
        } else {//否则尾指针正常向后移动一位
            tail = tail + 1;
        }

        arr[tail] = item;//将新元素放在尾指针位置

        if (head == -1) {//如果队列之前为空，更新头指针指向第一个元素
            head = tail;
        }

        size++;//插入元素后，队列大小加1

        cout << "On inserting " << item
             << " Head " << head
             << " Tail " << tail << endl;
    }

    char dequeue() {
        if (isEmpty()) {
            cout << "Queue is empty. Cannot dequeue." << endl;
            return -1;
        }

        char item = arr[head];//获取头指针位置的元素作为出队元素

        if (head == tail) {//如果出队后队列变为空，重置头尾指针
            head = tail = -1;
        } else {
            if (head == capacity - 1) {
                head = 0;
            } else {
                head = head + 1;
            }
        }

        size--;

        cout << "On removing " << item
             << " Head " << head
             << " Tail " << tail << endl;

        return item;
    }

    int getFront() {
        if (isEmpty()) {
            cout << "Queue is empty. No front element." << endl;
            return -1;
        }
        return arr[head];
    }

    int getRear() {
        if (isEmpty()) {
            cout << "Queue is empty. No rear element." << endl;
            return -1;
        }
        return arr[tail];
    }
};

int main() {
    CircularQueue queue(3);

    queue.enqueue('A');
    queue.enqueue('B');
    queue.enqueue('C');

    char val = queue.dequeue();//出队第一个元素
    val = queue.dequeue();//出队第二个元素,此时队列中还剩一个元素'C'

    queue.enqueue('D');//入队新元素'D',此时队列中元素为'C','D'

    val = queue.dequeue();//出队元素'C'

    return 0;
}
