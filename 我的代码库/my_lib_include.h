#ifndef _MY_LIB_H_
#define _MY_LIB_H_

#include <vector>
#include <map>
#include <algorithm>
#include <bits/stdc++.h>
#include <random>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#define _USE_MATH_DEFINES
#include <chrono>
#include <math.h>
#include <fstream>
#include <direct.h>
#include <io.h>
#include <cstdlib>

using namespace std;
using namespace chrono;

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
    static vector<pair<T, int>> my_lib_func_eic(vector<T> data, int direction)
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
private:
    static bool eic_cmpdata(T x, T y)
    {
        return x > y;
    }
    static bool eic_numdown(pair<T, int> a, pair<T, int> b)
    {
        return a.first > b.first;
    }
    static bool eic_numcmpup(pair<T, int> a, pair<T, int> b)
    {
        return a.first < b.first;
    }
    static bool eic_countdown(pair<T, int> a, pair<T, int> b)
    {
        return a.second > b.second;
    }
    static bool eic_countcmpup(pair<T, int> a, pair<T, int> b)
    {
        return a.second < b.second;
    }
    static bool eic_countdownup(pair<T, int> a, pair<T, int> b)
    {
        if (a.second == b.second)
            return a.first < b.first;

        return a.second > b.second;
    }
    static bool eic_countdowndown(pair<T, int> a, pair<T, int> b)
    {
        if (a.second == b.second)
            return a.first > b.first;

        return a.second > b.second;
    }
    static bool eic_countupdown(pair<T, int> a, pair<T, int> b)
    {
        if (a.second == b.second)
            return a.first > b.first;

        return a.second < b.second;
    }
    static bool eic_countupup(pair<T, int> a, pair<T, int> b)
    {
        if (a.second == b.second)
            return a.first < b.first;

        return a.second < b.second;
    }
};

template <typename T, typename Y> //将两组vector转成vector<pair<>>返回,如果缺少元素，就以fillf或fills填充,填充类型与对应类型一致
vector<pair<T, Y>> my_lib_func_vTVP(vector<T> first, vector<Y> second, T fillf, Y fills)
{
    vector<pair<T, Y>> t;

    int j = 0;
    int ssize = second.size();
    int fsize = first.size();

    if (fsize >= ssize)
        for (auto& x : first)
        {
            if (j > ssize - 1)
                t.push_back({ x,fills });
            else
                t.push_back({ x,second.at(j) });
            j++;
        }
    else if (fsize < ssize)
        for (auto& x : second)
        {
            if (j > fsize - 1)
                t.push_back({ fillf, x });
            else
                t.push_back({ first.at(j), x });
            j++;
        }

    return t;
}

vector<int> my_lib_func_random(int min, int max,int count); //这下面两个函数返回指定的（最小）min 到 （最大）max的（个数）count个的随机数，以vector<T>返回
vector<double> my_lib_func_random(double min, double max, int count);

bool my_lib_func_pTRand(double p); //返回出现概率为p的真（相对于数字100）

template <typename T>
T my_lib_func_pSRand(T ele, double p, T nop) //返回以概率p(相对于数字100)出现的元素ele，或者不满足概率时的nop
{
    bool b = my_lib_func_pTRand(p);

    if (b == true)
        return ele;

    return nop;
}

template <typename T,typename Y>
T my_lib_func_pGRand(vector<pair<T, Y>> in) //返回数据中以指定概率出现的一个数，first是数，second是概率，相对于概率总和
{
    random_device rd;
    default_random_engine gen = default_random_engine(rd());
    vector<T> data;
    vector<Y> p;

    for (auto & t : in)
    {
        data.push_back(t.first);
        p.push_back(t.second);
    }

    discrete_distribution<int> d{ p.begin(),p.end() };

    return data[d(gen)];
}

vector<double> my_lib_func_randColor(); //产生随机三位颜色

pair<double, double> my_lib_fuc_randPosition(); //产生随机位置(-1,1)

vector<string> my_lib_func_oCSString(vector<char> sc, string in); //将in以sc分割，返回string的vector

string my_lib_func_vcToString(vector<char> in);//将char的vector转变成string
#endif