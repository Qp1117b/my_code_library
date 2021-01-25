#ifndef _MY_LIB_H_
#define _MY_LIB_H_

#include <vector>
#include <map>
#include <algorithm>
#include <bits/stdc++.h>
#include <time.h>
#include <stdlib.h>
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

vector<pair<int, int>> my_lib_func_eic(vector<int> data, int direction); //这个函数计算一个数组中不同数的个数，然后按照给出的方式排序，返回一个vector<pair<int,int>>

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