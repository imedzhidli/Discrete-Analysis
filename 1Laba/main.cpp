#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;


void counting_sort( vector<pair<int, string>> &elems )
{
    if (elems.empty())
    {
        return ;
    }

    int32_t max_elem = elems[0].first;

    for (size_t i = 1; i < elems.size(); ++i)
    {
        auto pair = elems[i];
        max_elem = max(max_elem, pair.first);
    }

    vector<int> tmp(max_elem + 1);

    for (size_t i = 0; i < elems.size(); ++i)
    {
        ++tmp[elems[i].first];
    }

    for (size_t i = 1; i < tmp.size(); ++i)
    {
        tmp[i] += tmp[i-1];
    }

    vector<pair<int, string>> result( elems.size() );
    for (int i = elems.size()-1; i >= 0; --i )
    {
        auto key = elems[i].first;
        auto pos = tmp[key]--;
        result[pos-1] = elems[i];
    }

    swap(elems, result);
}


int main()
{
    ios::sync_with_stdio(0); cin.tie(0);
    int key;
    string value;

    vector<pair<int, string>> elems;
    while (cin >> key >> value)
    {
        elems.push_back( make_pair(key, value) );
    }

    // Counting sort.
    counting_sort( elems );

    for (auto& elem : elems)
    {
        cout << elem.first << "\t" << elem.second << "\n";
    }

    return 0;
}
