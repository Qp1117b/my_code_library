#include "my_lib_include.h"

using namespace std;

struct EIC_ORDER_ITEM eic_order_item;

bool eic_cmpdata(int x, int y)
{
    return x > y;
}

bool eic_numdown(pair<int, int> a, pair<int, int> b)
{
    return a.first > b.first;
}

bool eic_numcmpup(pair<int, int> a, pair<int, int> b)
{
    return a.first < b.first;
}

bool eic_countdown(pair<int, int> a, pair<int, int> b)
{
    return a.second > b.second;
}

bool eic_countcmpup(pair<int, int> a, pair<int, int> b)
{
    return a.second < b.second;
}

bool eic_countdownup(pair<int, int> a, pair<int, int> b)
{
    if (a.second == b.second)
        return a.first < b.first;
    
    return a.second > b.second;
}

bool eic_countdowndown(pair<int, int> a, pair<int, int> b)
{
    if (a.second == b.second)
        return a.first > b.first;

    return a.second > b.second;
}

bool eic_countupdown(pair<int, int> a, pair<int, int> b)
{
    if (a.second == b.second)
        return a.first > b.first;

    return a.second < b.second;
}

bool eic_countupup(pair<int, int> a, pair<int, int> b)
{
    if (a.second == b.second)
        return a.first < b.first;

    return a.second < b.second;
}

vector<pair<int, int>> my_lib_func_eic(vector<int> data, int direction) //第一个1函数
{
    map<int,int> datamap;
    int size = data.size();

    sort(data.begin(),data.end(),eic_cmpdata);

    int j = 0;
    for (; j < size - 1; )
    {
        int count = 1;
        for (;j < size - 1;j++)
        {
            if (data[j] == data[j+1])
            {
                count++;
            }
            else
            {
                j++;
                break;
            }
        }
        datamap.insert(pair<int,int>(data[j - 1],count));
    }

    vector<pair<int,int>> out(datamap.begin(),datamap.end());
    
    if (direction == eic_order_item.COUNT_DOWN)
    {
        sort(out.begin(),out.end(),eic_countdown);
    }
    else if (direction == eic_order_item.COUNT_UP)
    {
        sort(out.begin(),out.end(),eic_countcmpup);
    }
    else if (direction == eic_order_item.NUM_DOWN)
    {
        sort(out.begin(),out.end(),eic_numdown);
    }
    else if (direction == eic_order_item.NUM_UP)
    {
        sort(out.begin(),out.end(),eic_numcmpup);
    }
    else if (direction == eic_order_item.COUNT_DOWN_UP)
    {
        sort(out.begin(), out.end(), eic_countdown);
        sort(out.begin(), out.end(), eic_countdownup);
    }
    else if (direction == eic_order_item.COUNT_DOWN_DOWN)
    {
        sort(out.begin(), out.end(), eic_countdown);
        sort(out.begin(), out.end(), eic_countdowndown);
    }
    else if (direction == eic_order_item.COUNT_UP_UP)
    {
        sort(out.begin(), out.end(), eic_countcmpup);
        sort(out.begin(), out.end(), eic_countupup);
    }
    else if (direction == eic_order_item.COUNT_UP_DOWN)
    {
        sort(out.begin(), out.end(), eic_countcmpup);
        sort(out.begin(), out.end(), eic_countupdown);
    }

    return out;
}

