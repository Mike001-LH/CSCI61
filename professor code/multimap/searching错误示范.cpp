#include <iostream>
#include <map>

using namespace std;
//错误示范：
int main()
{
    multimap<int, int> demo;

    demo.insert(pair<int, int>(1, 10));
    demo.insert(pair<int, int>(2, 10));
    demo.insert(pair<int, int>(2, 20));

    cout << demo[2] << endl;   // ❌ multimap 不支持 operator[]

    return 0;
}

