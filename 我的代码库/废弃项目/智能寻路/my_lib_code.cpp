#include "my_lib_include.h"

using namespace std;

struct EIC_ORDER_ITEM eic_order_item;

bool my_lib_func_pTRand(int p)
{
    return false;
}

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

vector<double> my_lib_func_random(double min, double max, int count)
{
    vector<double> temp;
    random_device rd;
    default_random_engine gen = default_random_engine(rd());
    uniform_real_distribution<double> dis(min, max);

    for (int i = 0; i < count; i++)
    {
        double t = dis(gen);
        temp.push_back(t);
    }
    return temp;
}

vector<double> my_lib_func_randColor()
{
    return my_lib_func_random(0.0, 1.0, 3);
}

pair<double, double> my_lib_fuc_randPosition()
{
    vector<double> t = my_lib_func_random(-1.0, 1.0, 2);
    return pair<double, double> {t[0], t[1]};
}

bool my_lib_func_pTRand(double p)
{
    random_device rd;
    default_random_engine gen = default_random_engine(rd());
    uniform_real_distribution<double> dis(0.0, 100.0);
    double mp;

    mp = dis(gen);

    if (mp > 0.0 && mp <= p)
        return true;
    else
        return false;
}

vector<string> my_lib_func_oCSString(vector<char> sc, string in)
{
    int size = in.size();
    bool issplite = false;
    vector<string> re;
    string t;
    int i = 0;

    for (auto& tc : in)
    {
        i++;        

        for (auto& scc : sc)
        {
            if (tc == scc)
            {
                issplite = true;
            }

        }

        if (issplite != true)
            t += tc;

        if (issplite == true || i == size)
        {
            re.push_back(t);
            t = "";
            issplite = false;
            continue;
        }

    }

    return re;
}

string my_lib_func_vcToString(vector<char> in)
{
    string re = "";
    for (auto& x : in)
    {
        re += x;
    }

    return re;
}
