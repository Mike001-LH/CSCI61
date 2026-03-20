/*
Can I store a map in a map?

You definitely can!

Multidimensional maps are nested maps; that is, they map a key to another map, which itself stores combinations of key values with corresponding mapped values.

Creating a two-dimensional map:
map< key_1_type, map< key_2_type, value_type > > object;

Creating an N-dimensional map:
map< key_1_type, map< key_2_type, ... map< key_N_type, value_type > > > object;
*/
#include <iostream>
#include <map>
#include <string>

using namespace std;

int main() {

    map<string, map<int, int>> m;//二维map，外层map的键类型是string，值类型是另一个map；内层map的键类型是int，值类型也是int。

    map<string, map<int, int>>::iterator itr;//我们定义了一个迭代器itr，用于遍历外层map m中的元素。这个迭代器的类型是map<string, map<int, int>>::iterator，因为它指向的是外层map中的元素，每个元素都是一个pair<string, map<int, int>>类型的键值对。
    map<int, int>::iterator ptr;//我们定义了另一个迭代器ptr，用于遍历内层map中的元素。这个迭代器的类型是map<int, int>::iterator，因为它指向的是内层map中的元素，每个元素都是一个pair<int, int>类型的键值对。

    m["Ross"].insert(make_pair(0, 5));

    m["Rachel"].insert(make_pair(1, 10));
    m["Rachel"].insert(make_pair(2, 20));
    /*插入完了以后是这样的：
    m = {
        "Ross" : {
            0 : 5
        },
        "Rachel" : {
            1 : 10,
            2 : 20
        }
    }
    */

    for (itr = m.begin(); itr != m.end(); itr++) {//我们使用迭代器itr来遍历外层map m中的所有元素。也就是Ross和Rachel这两个键值对。m.begin()返回指向map第一个元素的迭代器，m.end()返回指向map末尾之后位置的迭代器。通过++itr，我们可以逐个访问map中的元素，直到itr等于m.end()为止。
        for (ptr = itr->second.begin();
             ptr != itr->second.end();
             ptr++) {//对于外层map中的每个元素，我们使用迭代器ptr来遍历内层map中的所有元素。也就是Ross对应的{0:5}和Rachel对应的{1:10, 2:20}这两个map。itr->second是指向当前外层map元素的值，也就是一个内层map，我们调用begin()和end()来获取内层map的迭代器范围，通过++ptr来访问内层map中的每个元素，直到ptr等于内层map的end()为止。

            cout << "First key is " << itr->first
                 << " And second key is " << ptr->first
                 << " And value is " << ptr->second
                 << endl;
        }
    }
    /*
    输出：
    First key is Ross And second key is 0 And value is 5
    First key is Rachel And second key is 1 And value is 10
    First key is Rachel And second key is 2 And value is 20
    */

    return 0;
}
