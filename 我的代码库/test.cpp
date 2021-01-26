#include "my_lib_include.h"

using namespace std;

int main()
{
    //vector<string> a = {"a","b","c","c","a","x"};
    //vector<pair<string,int>> b = my_lib_func_eic(a,eic_order_item.COUNT_UP
    vector<char> a = {'a','b'};
    vector<pair<char,int>> b = my_lib_class_eic<char>::my_lib_func_eic(a, eic_order_item.COUNT_UP);

    for (auto & c : b)
    cout << c.first << " has " << c.second << endl;

    return 0;
}