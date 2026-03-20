#include <iostream>
#include <map>

using namespace std;

int main() {

    map<char, int> first;

    // initializing (different order)
    first['b'] = 20;
    first['a'] = 10;
    first['d'] = 40;
    first['c'] = 30;

    map<char, int>::iterator it;

    for (it = first.begin(); it != first.end(); ++it) {
        cout << it->first << " => " << it->second << '\n';
    }
    /*输出:
    a => 10
    b => 20
    c => 30
    d => 40
    */

    return 0;
}
