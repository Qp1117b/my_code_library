#include "my_lib_include.h"

using namespace std;

int main()
{
    //vector<int> a = {1,1,1,2,2,2,3,3,3,4,4,4,2,4,0,0,0,0,0,0,111};
    //vector<pair<int,int>> b = my_lib_func_eic(a,eic_order_item.COUNT_UP);

    //for (auto & c : b)
    //cout << c.first << " has " << c.second << endl;
    vector<string> b = { "田志鹏","唐学华","小刘","夏利" };
    vector<int> p = { 25,25,0,0 };

    vector<pair<string, int>> a = my_lib_func_vTVP(b,p,string("a"),0);
    for (auto& x : a)
        cout << x.first << ":" << x.second << endl;


    for (int i = 0; i <= 10; i++)
    {
        cout << my_lib_func_pGRand(a) << endl;
    }

    return 0;
}