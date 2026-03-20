#include <iostream>
#include <map>
#include <string>

using namespace std;

int main() {
    map<string, int> myMap;

    myMap.insert(make_pair("Mercury", 1));//inserting data with insert member function
    myMap.insert(make_pair("Venus", 2));
    myMap.insert(make_pair("Earth", 3));

    myMap["Mars"] = 4;

    myMap.insert(pair<string, int>("Jupiter", 5));//Also insert data in std::map using operator []

    cout << myMap["Earth"] << endl; // 输出: 3
    cout << myMap["Mars"] << endl;  // 输出: 4
    cout << myMap["Jupiter"] << endl; // 输出: 5

    return 0;
}
/*
*/