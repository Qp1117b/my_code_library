#ifndef _MY_LIB_H_
#define _MY_LIB_H_

#include <vector>
#include <map>
#include <algorithm>
#include <bits/stdc++.h>

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

#endif