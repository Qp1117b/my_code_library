#include "my_lib_include.h"

using namespace std;

struct EIC_ORDER_ITEM eic_order_item;

vector<int> my_lib_func_random(int min, int max, int count)
{
    vector<int> temp;
    random_device rd;
    default_random_engine gen = default_random_engine(rd());
    uniform_int_distribution<int> dis(min, max);

    for (int i = 0; i < count; i++)
    {
        int t = dis(gen);
        temp.push_back(t);
    }
    return temp;
}

bool my_lib_func_pTRand(int p)
{
    random_device rd;
    default_random_engine gen = default_random_engine(rd());
    uniform_int_distribution<int> dis(0, 100);
    int mp;

    mp = dis(gen);

    if (mp >= 1 && mp <= p)
        return true;
    else
        return false;
}

