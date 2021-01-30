#include "object.h"

vector<string> object::v_tag = { "food-nohurt","food-hurt","nofood-hurt","nofood-nohurt" };
long long object::all_num = 0;

struct OBJECT_TAG obj_tag;
struct OBJECT_SHAPE obj_shape;

object::object(vector<double> color, double size, int shape, pair<double, double> position, string tag)
{
	this->color = color;
	this->position = position;
	this->size = size;
	this->tag = obj_tag.NOFOOD_NOHURT;
	this->shape = shape;
	this->id = _getid();
    all_num++;
}

object::object(vector<double> color, pair<double, double> position)
{
    this->color = color;
    this->position = position;
    this->size = 0.01;
    this->tag = obj_tag.NOFOOD_NOHURT;
    this->shape = obj_shape.TRI;
    this->id = _getid();
    all_num++;
}

object::object()
{
    this->color = my_lib_func_randColor();   
    this->size = my_lib_func_random(0.001,0.1,1).at(0);
    this->position = { my_lib_func_random(-1.0 + size, 1.0 - size, 1).at(0), my_lib_func_random(-1.0 + size, 1.0 - size, 1).at(0) };
    this->tag = obj_tag.NOFOOD_NOHURT;
    this->shape = obj_shape.TRI;
    this->id = _getid();
    all_num++;
}

object::~object()
{
    ifmovep.close();
    ofmovep.close();
}

void object::tell()
{
    cout << "id:" << id << " tag:" << tag << " shape:" << shape;
    cout << " position:" << position.first << "," << position.second << endl;
}

void object::makefile()
{
    if (ispofileexist == true)
    {
        char t;
        vector<char> indata;
        vector<string> data;
        vector<double> mp;
        while (ifmovep >> t)
        {
            indata.push_back(t);
        }

        data = my_lib_func_oCSString({ ',','\n' }, my_lib_func_vcToString(indata));
        for (auto& x : data)
        {
            mp.push_back(stod(x));
        }

        position.first = mp[0];
        position.second = mp[1];
    }
    else
    {
        ofmovep << position.first << "," << position.second << endl;
    }
 }

void object::make()
{
    int i;
    if (ismake == false)
    {
        cout << "生成";
        glBegin(GL_POLYGON);
        glColor3f(color[0], color[1], color[2]);
        for (i = 0; i < shape; ++i)
            glVertex2f(size * cos(2 * M_PI / shape * i) + position.first, size * sin(2 * M_PI / shape * i) + position.second);

        glEnd();
        ismake = true;
        isexist = true;

        if (_access("file/", 0) == -1)
        {
            _mkdir("file"); //不存在创建
        }
        else;
            // 存在

        string filet = "file/" + id + ".txt";

        if (_access(filet.c_str(), 0) == -1)
            ofmovep.open("file\\" + id + ".txt", ios::out | ios::_Noreplace | ios::ate);
        else
        {
            ofmovep.open("file\\" + id + ".txt", ios::out | ios::app);
            ispofileexist = true;
        }

        ifmovep.open("file\\" + id + ".txt", ios::in | ios::app);

        makefile();

        tell();
    }
}

void object::exist()
{

    if (isexist == false && isnumj == false)
    {
        cout << "还剩" << object::all_num << "个食物没被吃" << endl;
        isnumj = true;
    }

    if (isate == true && isexist == true)
    {
        if (tag == obj_tag.FOOD_NOHURT)
        {
            isexist = false;
            all_num--;

            //cout << "ATE";
        }
        else if (tag == obj_tag.FOOD_HURT)
        {
            isexist = false;
            all_num--;
            //cout << "ATE";
        }
        else if (tag == obj_tag.NOFOOD_HURT)
        {
            isate = false;
            //cout << "NO-ATE";
        }
        else if (tag == obj_tag.NOFOOD_NOHURT)
        {
            isate = false;
            //cout << "NO-ATE";
        }
    }
        

    if (ismake == true && isexist == true)
    {
        int i;
        glBegin(GL_POLYGON);
        glColor3f(color[0], color[1], color[2]);
        for (i = 0; i < shape; ++i)
            glVertex2f(size * cos(2 * M_PI / shape * i) + position.first, size * sin(2 * M_PI / shape * i) + position.second);

        glEnd();
    }
}
