#include <iostream>
#include <map>
#include <string>

using namespace std;

int main() {
    map<string, string> myMap;

    myMap["us"] = "United States";
    myMap["br"] = "Brazil";
    myMap["es"] = "Spain";

    cout << myMap["us"] << endl; // 输出: United States

    map<string, string>::iterator it;//知识点回顾：迭代器（iterator）是C++ STL中用于遍历容器元素的对象。
    //语法复习：::是scope resolution operator，用于访问类的成员或命名空间中的成员。在这里，map<string, string>::iterator表示map<string, string>类型的迭代器。

    for (it = myMap.begin(); it != myMap.end(); ++it) {//我们使用迭代器it来遍历myMap中的所有键值对。myMap.begin()返回指向map第一个元素的迭代器，myMap.end()返回指向map末尾之后位置的迭代器。通过++it，我们可以逐个访问map中的元素，直到it等于myMap.end()为止。
        cout << it->first << " => " << it->second << endl; // 输出键值对，first是迭代器指向的元素的键，second是迭代器指向的元素的值。例如：输出 us => United States, br => Brazil, es => Spain。
    }
    // 输出:
    // us => United States
    // br => Brazil
    // es => Spain

    return 0;
}

/*
map结构示意图：
keys         values
“us”  =>    “United States”
“br”  =>    “Brazil”
“es”  =>    “Spain”
*/