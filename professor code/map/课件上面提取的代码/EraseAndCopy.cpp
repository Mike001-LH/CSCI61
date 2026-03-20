#include <iostream>
#include <map>

using namespace std;

int main() {

    map<int, int> demo;

    demo.insert(make_pair(1, 20));
    demo.insert(make_pair(2, 10));

    map<int, int> demo1 = demo;

    cout << demo[1] << endl;//输出: 20

    demo.clear();//我们调用demo.clear()函数来清空demo中的所有元素，这样demo就不再包含任何键值对了。

    cout << demo1[1] << endl;//输出: 20，说明demo1是demo的一个副本，修改demo不会影响demo1。
    cout << demo[1] << endl;//输出: 0，说明demo已经被清空了，访问demo[1]会返回默认值0，因为map中没有键1了。

    return 0;
}
