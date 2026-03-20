#include <iostream>
#define MAX_SIZE 100 //define的意思是定义一个宏常量，这里定义了栈的最大容量为100，宏常量是在预处理阶段进行替换的，不占用内存空间，使用范围是从定义处到文件末尾

class Stack {
    int arr[MAX_SIZE];  
    int top;            // Index of the top element in the stack

public:
    Stack() 
    {
        top = -1; 
    }

    bool isEmpty() 
    {
        if (top == -1)
            return true;
        
        return false;
    }

    bool isFull() 
    {
        if (top == MAX_SIZE - 1)
        {
            return true;
        }
        
        return false;
    }

    void push(int value) 
    {
        if (isFull()) 
        {
            std::cout << "Stack Overflow! Cannot push " << value << std::endl;
        }
        arr[++top] = value;  // Increment top and add value to stack
    }

    int pop() 
    {
        if (isEmpty()) 
        {
            std::cout << "Stack Underflow! Cannot pop from an empty stack." << std::endl;
            return -1;  
        }
        return arr[top--]; //先返回栈顶元素，再将栈顶指针top减1
    }


    int peek() //返回栈顶元素但不弹出
    {
        if (isEmpty()) 
        {
            std::cout << "Stack is empty! No top element to peek." << std::endl;
            return -1;  
        }
        return arr[top];
    }

 
    void display() //显示栈中所有元素
    {
        if (isEmpty()) 
        {
            std::cout << "Stack is empty!" << std::endl;
            return;
        }
        std::cout << "Stack elements: ";
        for (int i = 0; i <= top; i++) 
        {
            std::cout << arr[i] << " ";
        }
        std::cout << std::endl;
    }
};

int main() {
    Stack s;

    s.push(10);
    s.push(20);
    s.push(30);

    s.display();

    std::cout << "Top element: " << s.peek() << std::endl;

    std::cout << "Popped element: " << s.pop() << std::endl;
    s.display();

    std::cout << "Is stack empty? " << (s.isEmpty() ? "Yes" : "No") << std::endl;
    std::cout << "Is stack full? " << (s.isFull() ? "Yes" : "No") << std::endl;

    return 0;
}