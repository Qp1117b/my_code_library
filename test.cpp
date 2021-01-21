#include "my_lib_include.h"
#include <iterator>

using namespace std;

int main()
{
    vector<int> a = {1,1,1,2,2,2,3,3,3,4,4,4,2,4,0,0,0,0,0,0,111};
    vector<pair<int,int>> b = my_lib_func_eic(a,eic_order_item.NUM_DOWN);
    cout << "²¢";

    for (auto & c : b)
    cout << c.first << " has " << c.second << endl;
}