// Monica owns an ice cream shop, and every scoop of ice cream costs $5. Customers line up to buy ice cream, and each customer pays using either a $5 note or a $10 note. Monica starts the day with no money in her cash register.

// Given the queue of customers (represented by the notes they use to pay), determine whether Monica can successfully sell ice cream to every customer by always providing the correct change. Assume that the queue of customers is fixed and that no new customers will join the line.

// **Example 1**

// Queue: 5, 5, 5, 10, 5

// Output: YES

// Explanation: When the fourth customer pays with a $10 note, Monica has enough $5 notes to give correct change. The fifth customer pays with a $5 note, so no change is required.

// **Example 2**

// Queue: 5, 10, 10, 5

// Output: NO

// Explanation:When the second customer pays with a $10 note, Monica gives one $5 note as change. When the third customer pays with a $10 note, Monica no longer has a $5 note to give as change, so the transaction fails.

#include <queue>
#include <iostream>

using namespace std;

int main() {
    queue<int> customers;

    customers.push(5);
    customers.push(10);
    customers.push(10);
    customers.push(10);//head->tail: 5,10,10,10

    int fiveCount = 0;   
    bool possible = true;

    while (!customers.empty()) {
        int bill = customers.front();//获取队列头部元素，即当前顾客支付的钞票面额
        customers.pop();//弹出队列头部元素，表示该顾客已完成支付

        if (bill == 5) {
            fiveCount++;
        } else if (bill == 10) 
            {
                if (fiveCount > 0) {//如果有足够的5美元钞票找零
                    fiveCount--;   
            } 
                else //没有足够的5美元钞票找零
                {
                    possible = false;//无法找零，交易失败
                    break;//退出循环
                }
        }
    }

    if (possible) {
        cout << "YES" << endl;
    } else {
        cout << "NO" << endl;
    }

    return 0;
}
