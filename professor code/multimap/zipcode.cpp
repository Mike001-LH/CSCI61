#include <iostream>
#include <map>

using namespace std;

int main()
{
    multimap<string, int> cities;
    multimap<string, int>::const_iterator i;

    cities.insert(make_pair("Santa Clara", 95050));
    cities.insert(make_pair("Santa Clara", 95051));
    cities.insert(make_pair("Santa Clara", 95052));
    cities.insert(make_pair("Santa Clara", 95053));
    cities.insert(make_pair("Dallas", 75252));
    cities.insert(make_pair("Dallas", 75001));
    cities.insert(make_pair("Santa Clara", 95054));
    cities.insert(make_pair("Santa Clara", 95055));
    cities.insert(make_pair("Santa Clara", 95056));
    /*
    最后结构如下：
    cities = {
        "Santa Clara": [95050, 95051, 95052, 95053, 95054, 95055, 95056],
        "Dallas": [75252, 75001]
    }
        cities的size为9，因为我们插入了9个键值对。虽然有重复的键"Santa Clara"，但multimap允许重复键，所以每个插入的键值对都会被存储在cities中。
    */

    for (i = cities.begin(); i != cities.end(); ++i)
    {
        cout << i->first << '\t' << i->second << endl;
    }
    /*输出：
    Dallas 75001
    Dallas 75252
    Santa Clara 95050
    Santa Clara 95051
    Santa Clara 95052
    Santa Clara 95053
    Santa Clara 95054
    Santa Clara 95055
    Santa Clara 95056
    */

    return 0;
}