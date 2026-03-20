#include <iostream>
#include <deque>//包含双端队列的头文件

using namespace std;

int main() {
    deque<int> myDeque;//双端队列，可以从两端插入和删除元素

    myDeque.push_back(1);//从队列尾部插入元素1，现在队列为[1]
    myDeque.push_back(2);//从队列尾部插入元素2，现在队列为[1, 2]
    myDeque.push_back(3);//从队列尾部插入元素3，现在队列为[1, 2, 3]
  
    myDeque.push_front(0);//从队列头部插入元素0，现在队列为[0, 1, 2, 3]
    myDeque.push_front(-1);//从队列头部插入元素-1，现在队列为[-1, 0, 1, 2, 3]

    // while(!myDeque.empty())
    // {
    //     cout << myDeque.front() << " "; //输出队列头部元素
    //     myDeque.pop_front(); //从队列头部删除元素
    // }
    
    // while(!myDeque.empty())
    // {
    //     cout << myDeque.back() << " "; //输出队列尾部元素
    //     myDeque.pop_back(); //从队列尾部删除元素
    // }
    
    cout << "Elements in the deque: ";
    for (int i = 0; i < myDeque.size(); ++i) {//遍历并输出双端队列中的所有元素
        cout << myDeque[i] << " ";
    }
    cout << endl;

    
    myDeque.pop_back(); //从队列尾部删除一个元素，现在队列为[-1, 0, 1, 2]
    myDeque.pop_front();//从队列头部删除一个元素，现在队列为[0, 1, 2]


    cout << "Elements in the deque after removal: ";
    for (int i = 0; i < myDeque.size(); ++i) {//遍历并输出双端队列中的所有元素
        cout << myDeque[i] << " ";
    }
    cout << endl;

    return 0;
}
