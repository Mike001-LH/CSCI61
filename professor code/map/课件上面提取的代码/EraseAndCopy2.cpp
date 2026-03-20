#include <iostream>
#include <map>

using namespace std;

int main() {

    map<int, int> myMap1;

    myMap1[1] = 40;
    myMap1[2] = 30;
    myMap1[3] = 60;
    myMap1[4] = 20;
    myMap1[5] = 50;
    myMap1[6] = 50;
    myMap1[7] = 10;

    for (auto it = myMap1.begin(); it != myMap1.end(); ++it)//我们使用迭代器it来遍历myMap1中的所有键值对。myMap1.begin()返回指向map第一个元素的迭代器，myMap1.end()返回指向map末尾之后位置的迭代器。通过++it，我们可以逐个访问map中的元素，直到it等于myMap1.end()为止。
        cout << it->first << "\t" << it->second << "\n";
    /*输出：
    1	40
    2	30
    3	60
    4	20
    5	50
    6	50
    7	10
    */

    myMap1.erase(myMap1.begin(), myMap1.find(3));//erase()函数有两个重载版本：erase(iterator position)和erase(iterator first, iterator last)。在这里，我们使用了第二个版本，传入了myMap1.begin()作为first参数，myMap1.find(3)作为last参数。这样，erase()函数会删除从myMap1.begin()到myMap1.find(3)之间的所有元素（不包括myMap1.find(3)指向的元素）。也就是说，键值为1和2的元素会被删除，而键值为3及之后的元素会保留。

    for (auto it = myMap1.begin(); it != myMap1.end(); ++it)
        cout << it->first << "\t" << it->second << "\n";
    /*输出：
    3	60
    4	20
    5	50
    6	50
    7	10
    */

    int num = myMap1.erase(4);//erase()函数的第三个重载版本是erase(const key_type& key)，它接受一个键值作为参数，删除map中键值等于该参数的元素，并返回被删除元素的数量（如果该键值存在，则返回1；如果不存在，则返回0）。在这里，我们调用myMap1.erase(4)来删除键值为4的元素，并将返回值存储在变量num中。因为键值为4的元素存在，所以num的值将是1。

    for (auto it = myMap1.begin(); it != myMap1.end(); ++it)
        cout << it->first << "\t" << it->second << "\n";
    /*输出：
    3	60
    5	50
    6	50
    7	10
    */

    return 0;
}
