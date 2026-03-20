#include <iostream>
#include <map>

using namespace std;

int main()
{
    multimap<int, int> multi1;

    multi1.insert(pair<int, int>(3, 60));
    multi1.insert(pair<int, int>(4, 50));
    multi1.insert(pair<int, int>(5, 10));
    multi1.insert(pair<int, int>(6, 50));
    multi1.insert(pair<int, int>(6, 10));
    /*
    结构为：
    multi1 = {
        3: [60],
        4: [50],
        5: [10],
        6: [50, 10]
    }
    */

    // 复制整个 multimap
    multimap<int, int> multi2(multi1.begin(), multi1.end());//名称为multi2的multimap被初始化为multi1中从begin()到end()之间的所有元素的副本。也就是说，multi2将包含与multi1相同的键值对，结构如下：

    int num;//我们定义了一个整数变量num，用于存储erase()函数返回的被删除元素的数量。
    num = multi2.erase(4);   // 删除 key = 4 的所有元素，并将返回值存储在num中。因为multi2中有一个键值为4的元素，所以num的值将是1。//如果multi2中没有键值为4的元素，那么num的值将是0，表示没有元素被删除。//如果multi2中有多个键值为4的元素，那么num的值将是这些元素的数量，表示所有键值为4的元素都被删除了。

    multimap<int, int>::iterator itr;

    for (itr = multi2.begin(); itr != multi2.end(); ++itr)
    {
        cout << "\t" << itr->first
             << "\t" << itr->second << "\n";
    }

    return 0;
}
    /*
    erase()这个删除函数的返回值是一个整数，表示被删除元素的数量。
    情况 1：erase(key)
    int num = multi2.erase(4);
    返回值：
    👉 size_type（整数）
    表示：删除了多少个 key=4 的元素
    比如，如果 multi2 中有一个 key=4 的元素，那么 num 的值将是 1；如果 multi2 中没有 key=4 的元素，那么 num 的值将是 0；如果 multi2 中有多个 key=4 的元素，那么 num 的值将是这些元素的数量。
    
    情况 2：erase(iterator)
    multimap<int, int>::iterator it = multi2.find(5);
    multi2.erase(it);
    返回值：
    iterator（下一个位置）
    表示：删除了迭代器 it 指向的元素

    情况 3：erase(first, last)
    multi.erase(begin, end);
    返回值：
    iterator（删除区间之后的位置）
    表示：删除了迭代器范围 [first, last) 内的所有元素
    */