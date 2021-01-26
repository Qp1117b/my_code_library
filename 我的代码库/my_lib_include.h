#ifndef _MY_LIB_H_
#define _MY_LIB_H_

#include <vector>
#include <map>
#include <algorithm>
#include <bits/stdc++.h>
#include <random>

using namespace std;

struct EIC_ORDER_ITEM
{
    int NUM_DOWN = 0;
    int NUM_UP = 1;
    int COUNT_DOWN = 2;
    int COUNT_UP = 3;
    int COUNT_UP_DOWN = 4;
    int COUNT_UP_UP = 5;
    int COUNT_DOWN_UP = 6;
    int COUNT_DOWN_DOWN = 7;

};
extern struct EIC_ORDER_ITEM eic_order_item;

template <class T> //这个模板类计算一组数据中不同元素的个数，然后按照给出的方式排序，返回一个vector<pair<T,int>>
class my_lib_class_eic {
public:
    static vector<pair<T, int>> my_lib_func_eic(vector<T> data, int direction);
private:
    static bool eic_cmpdata(T x, T y);
    static bool eic_numdown(pair<T, int> a, pair<T, int> b);
    static bool eic_numcmpup(pair<T, int> a, pair<T, int> b);
    static bool eic_countdown(pair<T, int> a, pair<T, int> b);
    static bool eic_countcmpup(pair<T, int> a, pair<T, int> b);
    static bool eic_countdownup(pair<T, int> a, pair<T, int> b);
    static bool eic_countdowndown(pair<T, int> a, pair<T, int> b);
    static bool eic_countupdown(pair<T, int> a, pair<T, int> b);
    static bool eic_countupup(pair<T, int> a, pair<T, int> b);
};

template <class T>
bool my_lib_class_eic<T>::eic_cmpdata(T x, T y)
{
    return x > y;
}

template <class T>
bool my_lib_class_eic<T>::eic_numdown(pair<T, int> a, pair<T, int> b)
{
    return a.first > b.first;
}

template <class T>
bool my_lib_class_eic<T>::eic_numcmpup(pair<T, int> a, pair<T, int> b)
{
    return a.first < b.first;
}

template <class T>
bool my_lib_class_eic<T>::eic_countdown(pair<T, int> a, pair<T, int> b)
{
    return a.second > b.second;
}

template <class T>
bool my_lib_class_eic<T>::eic_countcmpup(pair<T, int> a, pair<T, int> b)
{
    return a.second < b.second;
}

template <class T>
bool my_lib_class_eic<T>::eic_countdownup(pair<T, int> a, pair<T, int> b)
{
    if (a.second == b.second)
        return a.first < b.first;

    return a.second > b.second;
}

template <class T>
bool my_lib_class_eic<T>::eic_countdowndown(pair<T, int> a, pair<T, int> b)
{
    if (a.second == b.second)
        return a.first > b.first;

    return a.second > b.second;
}

template <class T>
bool my_lib_class_eic<T>::eic_countupdown(pair<T, int> a, pair<T, int> b)
{
    if (a.second == b.second)
        return a.first > b.first;

    return a.second < b.second;
}

template <class T>
bool my_lib_class_eic<T>::eic_countupup(pair<T, int> a, pair<T, int> b)
{
    if (a.second == b.second)
        return a.first < b.first;

    return a.second < b.second;
}

template <class T>
vector<pair<T, int>>  my_lib_class_eic<T>::my_lib_func_eic(vector<T> data, int direction)
{
    map<T, int> datamap;
    int size = data.size();

    sort(data.begin(), data.end(), eic_cmpdata);

    int j = 0;
    int count = 1;
    for (int y = 0; y < size; y++)
    {
        for (; j < size - 1; )
        {
            count = 1;
            for (; j < size - 1; j++)
            {
                if (data[j] == data[j + 1])
                {
                    count++;
                }
                else
                {
                    j++;
                    break;
                }
            }
            datamap.insert(pair<T, int>(data[j - 1], count));
        }

        if (y == size - 1)
        {
            datamap.insert(pair<T, int>(data[j], count));
        }
    }

    vector<pair<T, int>> out(datamap.begin(), datamap.end());

    if (direction == eic_order_item.COUNT_DOWN)
    {
        sort(out.begin(), out.end(), eic_countdown);
    }
    else if (direction == eic_order_item.COUNT_UP)
    {
        sort(out.begin(), out.end(), eic_countcmpup);
    }
    else if (direction == eic_order_item.NUM_DOWN)
    {
        sort(out.begin(), out.end(), eic_numdown);
    }
    else if (direction == eic_order_item.NUM_UP)
    {
        sort(out.begin(), out.end(), eic_numcmpup);
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


vector<int> my_lib_func_random(int min, int max,int count); //这个函数返回指定的（最小）min 到 （最大）max的（个数）count个的随机数，以vector<int>返回

bool my_lib_func_pTRand(int p); //返回出现概率为p的真

template <typename T, typename Y>
vector<pair<T, Y>> my_lib_func_vTVP(vector<T> first, vector<Y> second, T fillf, Y fills) //将两组vector转成vector<pair<>>返回,如果缺少元素，就以fillf或fills填充,填充类型与对应类型一致
{
    vector<pair<T, Y>> t;

    int j = 0;
    int ssize = second.size();
    int fsize = first.size();

    if (fsize >= ssize)
        for (auto & x : first)
        {
            if (j > ssize - 1)
                t.push_back({ x,fills });
            else
                t.push_back({ x,second.at(j) });
            j++;
        }
    else if (fsize < ssize)
        for (auto & x : second)
        {
            if (j > fsize - 1)
                t.push_back({ fillf, x});
            else
                t.push_back({first.at(j), x});
            j++;
        }

    return t;
}

template <typename T, typename Y>
Y my_lib_func_pNRand(T ele, int p, Y nop) //返回以概率p出现的元素ele，或者不满足概率时的nop
{
    bool b = my_lib_func_pTRand(p);

    if (b == true)
        return ele;

    return nop;
}

template <typename T>
T my_lib_func_pGRand(vector<pair<T, int>> in) //返回数据中以指定概率出现的一个数，first是数，second是概率（0-100）
{
    random_device rd;
    default_random_engine gen = default_random_engine(rd());
    vector<T> data;
    vector<int> p;

    for (auto & t : in)
    {
        data.push_back(t.first);
        p.push_back(t.second);
    }

    discrete_distribution<int> d{ p.begin(),p.end() };

    return data[d(gen)];
}
#endif