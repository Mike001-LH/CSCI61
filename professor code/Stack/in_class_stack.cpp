// **Stack with Increment Operation:** You are given a stack of integers.

// Your task is to write code that **increments the bottom k elements of the stack by a value v**.

// If the stack contains fewer than k elements, then all elements in the stack should be incremented.

// For example, if the stack contains the elements [1, 2, 3] from **bottom to top** and you increment the bottom k = 2 elements by v = 10, the stack should become [11, 12, 3], and subsequent pop operations should return 3, then 12, then 11.

// You are restricted to using only standard stack operations (push, pop, top, empty, and size) and may use at most one temporary data structure to assist your solution

#include <stack>
#include <iostream>
#include <algorithm>

using namespace std;

int main() {
    stack<int> st;
    st.push(1);
    st.push(2);
    st.push(3); // bottom->top: 1 2 3

    int k = 2, v = 10;   // try k > n
    int n = st.size();

    if (k >= n) {
        k = n;          // increment all elements
    }

    int cutoff = n - k; // first cutoff pops are NOT incremented

    stack<int> tmp;
    int cnt = 0;
    while (!st.empty()) {
        int x = st.top(); st.pop();//x是当前栈顶元素，暂时存储后弹出栈顶元素
        if (cnt >= cutoff) {//如果已经弹出的元素个数大于等于cutoff，说明当前元素在底部k个元素之内，可以被增量v
            x += v;//首先，3的时候cnt=0<cutoff=1，不加v，x=3；然后2的时候cnt=1>=cutoff=1，加v，x=12；最后1的时候cnt=2>=cutoff=1，加v，x=11
        }
        tmp.push(x);//将处理后的元素压入临时栈，3，12，11
        ++cnt;
    }

    while (!tmp.empty()) {//将临时栈中的元素重新压回原栈，以恢复原有顺序，变为11，12，3
        st.push(tmp.top());
        tmp.pop();
    }

    while (!st.empty()) {//输出栈中所有元素以验证结果，应该是3，12，11
        cout << st.top() << " ";
        st.pop();
    }
    cout << endl;

    return 0;
}
