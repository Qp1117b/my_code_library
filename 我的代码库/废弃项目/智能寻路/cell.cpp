#include "cell.h"
struct CELL_TAG cell_tag;

long long cell::all_num = 0;

cell::cell(vector<double> color, double size, int shape, double speed,pair<double, double> position)
{
	this->color = color;
	this->size = size;
    this->position = position;
    this->shape = shape;
    this->speed = speed;
    this->viewpoint = 1 - size;    
    this->tag = cell_tag.CELL;
    this->id = _getid();
    this->all_life_time = my_lib_func_random(10, 100, 1).at(0);
    this->bad_all_delay_time = my_lib_func_random(10, 20, 1).at(0);
    this->bad_speed = my_lib_func_random(0.001, 0.0001, 1).at(0);
    all_num++;
}

cell::cell(vector<double> color, pair<double, double> position)
{
    this->color = color;
    this->size = 0.01;
    this->position = position;
    this->shape = 50;
    this->speed = 0.0001;
    this->viewpoint = 1 - size;
    this->tag = cell_tag.CELL;
    this->id = _getid();
    this->all_life_time = my_lib_func_random(10, 100, 1).at(0);
    this->bad_all_delay_time = my_lib_func_random(10, 20, 1).at(0);
    this->bad_speed = my_lib_func_random(0.0001, 0.001, 1).at(0);
    all_num++;
}

cell::cell()
{
    this->color = my_lib_func_randColor();
    this->size = my_lib_func_random(0.001,0.1,1).at(0);
    this->position = my_lib_fuc_randPosition();
    this->shape = my_lib_func_random(0,50,1).at(0);
    this->speed = 0.0001;
    this->viewpoint = 1 - size;
    this->tag = cell_tag.CELL;
    this->id = _getid();
    this->all_life_time = my_lib_func_random(10, 100, 1).at(0);
    this->bad_all_delay_time = my_lib_func_random(10, 20, 1).at(0);
    this->bad_speed = my_lib_func_random(0.0001, 0.001, 1).at(0);
    all_num++;
}

cell::~cell()
{
    ofmovep.close();
    ifmovep.close();
}

void cell::birthfile()
{
    if (isfileexist == true)
    {
        cout << "文件存在开始初始化" << endl;
        char c;
        vector<char> allc;
        while (ifmovep >> c)
        {
            allc.push_back(c);
        }

        string filedata = my_lib_func_vcToString(allc);
        vector<string> vc = my_lib_func_oCSString({'\n','\r',',',':','@'},filedata);
        vector<double> d10;

        int i = 0;
        for (auto& x : vc)
        {
            i++;
            d10.push_back(stod(x));

            if (i == 10)
            {
                ptree.insert(pair<pair<double,double>, vector<double>>({d10[0], d10[1]}, { d10[2],d10[3],d10[4],d10[5],d10[6],d10[7],d10[8],d10[9] }));
                d10.clear();
                i = 0;
            }
        }
        cout << "初始化完成,共有" << ptree.size() << "条记录" << endl;

    }
    else
    {
        double height = 1 - position.second;
        double width = 1 - position.first;
        road = height * width;
        roadtime = lifetime;
        vector<double> t = movedp;
        ofmovep << position.first << "," << position.second << ":";
        int i = 0;
        for (auto& x : movedp)
        {
            i++;
            ofmovep << x;
            if (i == 4)
            {
                ofmovep << ":";
            }
            else
            {
                ofmovep << ",";
            }
        }
        ofmovep << 0 << "," << -1 << ":" << road << "," << roadtime << "@" << endl;
        t.push_back(0);
        t.push_back(-1);
        t.push_back(road);
        t.push_back(roadtime);
        ptree.insert(pair<pair<double,double>, vector<double>>(position, t));
    }
}

void cell::growfile()
{
    string tc = to_string(position.second);
    string ts = to_string(position.first);
    position.first = stod(ts);
    position.second = stod(tc);
    map<pair<double,double>, vector<double>>::iterator it = ptree.find(position);
    bool isjlpo = false;

    if (it != ptree.end())
    {
        isjlpo = true;
    }
    else
    {
        isjlpo = false;
    }

    movedp = my_lib_func_random(0.0, 1.0, 4);

    if (isjlpo == false) //位置还未记录
    {
        double height = 1 - position.second;
        double width = 1 - position.first;
        road = height * width;
        roadtime = lifetime;

        if (iseatobj == true)
        {
            iseatobj = false;
            cout << "未记录,未记录为吃,这次记录为吃" << endl;
        }
        else
        {
            eatjl = 0;
            lifetimejl = -1;
        }

        vector<double> t = movedp;
        ofmovep << position.first << "," << position.second << ":";
        int i = 0;
        for (auto& x : movedp)
        {
            i++;
            ofmovep << x;
            if (i == 4)
            {
                ofmovep << ":";
            }
            else
            {
                ofmovep << ",";
            }
        }

        ofmovep << eatjl << "," << lifetimejl << ":" <<road << "," << roadtime << "@" << endl;;
        t.push_back(eatjl);
        t.push_back(lifetimejl);
        t.push_back(road);
        t.push_back(roadtime);
        ptree.insert(pair<pair<double,double>, vector<double>>(position, t));
        eatjl = 0;
        lifetimejl = -1;
    }
    else if (isjlpo == true)
    {
        vector<double> td = it->second;
        vector<double> tmovedp = { td[0],td[1],td[2],td[3] };
        double teatjl = td[4];
        double tlifetimejl = td[5];
        double troad = td[6];
        double troadtime = td[7];

        movedp = tmovedp;

        if (iseatobj == true)
        {
            if (teatjl == 1)
            {
                if (lifetimejl - tlifetimejl < 0)
                cout << "上次记录为:" << tlifetimejl << ",比上次记录快:" << fabs(lifetimejl - tlifetimejl) << ",";
                else if(lifetimejl - tlifetimejl == 0)
                cout << "上次记录为:" << tlifetimejl << ",和上次记录一样,";
                else
                cout << "上次记录为:" << tlifetimejl << ",比上次记录慢:" << fabs(lifetimejl - tlifetimejl) << ",";

                if (tlifetimejl > lifetimejl)
                {
                    vector<double> t = movedp;
                    t.push_back(eatjl);
                    t.push_back(lifetimejl);
                    t.push_back(troad);
                    t.push_back(troadtime);
                    it->second = t;
                    cout << "优，记录改变" << endl;
                }
                else if (tlifetimejl == lifetimejl)
                {
                    cout << "记录未改变" << endl;
                    //vector<double> t = tmovedp;
                    //t.push_back(eatjl);
                    //t.push_back(tlifetimejl);
                    //it->second = t;
                }
                else
                {
                    cout << "记录未改变" << endl;
                }
            }
            else
            {
                cout << "记录，未记录为吃,这次记录为吃" << endl;

                double height = 1 - position.second;
                double width = 1 - position.first;
                road = height * width;
                roadtime = lifetime;

                eatjl = 1;
                vector<double> t = tmovedp;
                t.push_back(eatjl);
                t.push_back(lifetimejl);
                t.push_back(troad);
                t.push_back(roadtime);
                it->second = t;
            }

            iseatobj = false;
            eatjl = 0;
            lifetimejl = -1;
        }
        else
        {
            //double height = 1 - position.second;
            //double width = 1 - position.first;
            //road = height * width;
            //roadtime = lifetime;

            //if (roadtime < troadtime)
            //{
            //    vector<double> t = tmovedp;
            //    t.push_back(teatjl);
            //    t.push_back(tlifetimejl);
            //    t.push_back(road);
            //    t.push_back(roadtime);
            //    it->second = t;
            //}
            //else
            //{
            //}

            eatjl = 0;
            lifetimejl = -1;
        }
        //位置以记录
    }
}

double cell::getExistTime()
{
    existtime = lifetime + bad_delay_time + bad_need_time;
    return existtime;
}

void cell::death_action()
{
    if (isdeathtell == false)
    {
        tag = cell_tag.FOOD;
        if (KX > 0 && food > 0)
        {
            death_position = position;
            cout << "正常死亡:" << "活动总时间为:" << lifetime << "秒 " << "id:" << id << " tag:" << tag << " shape:" << shape;
            //cout << " color:" << color[0] << "," << color[1] << "," << color[2];
            cout << " position:" << position.first << "," << position.second << endl;
        } else if (KX > 0 && food <= 0)
        {
            death_position = position;
            cout << "饿死死亡:" << "活动总时间为:" << lifetime << "秒 " << "id:" << id << " tag:" << tag << " shape:" << shape;
            //cout << " color:" << color[0] << "," << color[1] << "," << color[2];
            cout << " position:" << position.first << "," << position.second << endl;
        }
        else if (KX <= 0 && food > 0)
        {
            death_position = position;
            cout << "中毒死亡:" << "活动总时间为:" << lifetime << "秒 " << "id:" << id << " tag:" << tag << " shape:" << shape;
            //cout << " color:" << color[0] << "," << color[1] << "," << color[2];
            cout << " position:" << position.first << "," << position.second << endl;
        }
        else if (KX <= 0 && food <= 0)
        {
            death_position = position;
            cout << "饿死且中毒死亡:" << "活动总时间为:" << lifetime << "秒 " << "id:" << id << " tag:" << tag << " shape:" << shape;
            //cout << " color:" << color[0] << "," << color[1] << "," << color[2];
            cout << " position:" << position.first << "," << position.second << endl;
        }
        isdeathtell = true;
    }

    if (isbad == false)
    {
        bad_start = system_clock::now();
        end_clock = bad_start;
        auto x = duration<double>(end_clock - birth_end);
        if (x.count() > bad_all_delay_time)
        {
            isbad = true;
            bad_delay_time = x.count();
        }

        int i;
        glBegin(GL_POLYGON);
        glColor3f(color[0], color[1], color[2]);
        for (i = 0; i < shape; ++i)
            glVertex2f(size * cos(2 * M_PI / shape * i) + death_position.first, size * sin(2 * M_PI / shape * i) + death_position.second);
        glEnd();
    }
    else if (isbad == true)
    {
        bad_action();
    }
}

void cell::bad_action()
{
    if (isbadtell == false)
    {
        cout << "开始腐败" << "id:" << id << " tag:" << tag << " shape:" << shape;
        //cout << " color:" << color[0] << "," << color[1] << "," << color[2];
        cout << " position:" << position.first << "," << position.second << endl;
        isbadtell = true;
    }

    if (isbadtell == true && isate == false)
    {
        if (isbadend == false)
        {
            int i = 0;
            glBegin(GL_POLYGON);
            color[0] -= bad_speed;
            color[1] -= bad_speed;
            color[2] -= bad_speed;
            glColor3f(color[0], color[1], color[2]);
            for (i = 0; i < shape; ++i)
                glVertex2f(size * cos(2 * M_PI / shape * i) + position.first, size * sin(2 * M_PI / shape * i) + position.second);

            glEnd();

            if (color[0] <= 0 && color[1] <= 0 && color[2] <= 0)
            {
                isbadend = true;
                end_clock = system_clock::now();
                auto t = duration<double>(end_clock - bad_start);
                bad_need_time = t.count();
            }
        }

        if (isbadend == true)
        {
            if (isexist == true)
            {
                getExistTime();
                cout << "腐败完成，彻底消失" << "id:" << id << " tag:" << tag << " shape:" << shape;
                //cout << " color:" << color[0] << "," << color[1] << "," << color[2];
                cout << " position:" << position.first << "," << position.second << " 总生存时间:" << lifetime;
                cout << " 死亡到腐败等待时间" << bad_delay_time << " 腐败需要时间" << bad_need_time << " 总存在时间" << existtime << endl;
                isexist = false;
                if (isexist == false && isnumj == false)
                {
                    all_num--;
                    isnumj = true;
                }
            }
        }
    }
}

void cell::tell()
{
    cout << "id:" << id << " tag:" << tag << " shape:" << shape;
    //cout << " color:" << color[0] << "," << color[1] << "," << color[2];
    cout << " position:" << position.first << "," << position.second << " 生命总时间:" << all_life_time << " 腐败需要等待时间" << bad_all_delay_time << endl;
}

void cell::birth()
{
	int i;
    if (isbirth == false)
    {
        cout << "生成";
        glBegin(GL_POLYGON);
        glColor3f(color[0], color[1], color[2]);
        for (i = 0; i < shape; ++i)
            glVertex2f(size * cos(2 * M_PI / shape * i) + position.first, size * sin(2 * M_PI / shape * i) + position.second);

        glEnd();
        isbirth = true;
        tell();
        birth_start = system_clock::now();
        start_clock = birth_start;
        if (_access("file/", 0) == -1)
        {
            _mkdir("file"); //不存在创建
        }
        else;
            //存在
        string filet = "file/" + id + ".txt";

        if (_access(filet.c_str(),0) == -1)
            ofmovep.open("file\\" + id + ".txt", ios::out | ios::_Noreplace | ios::ate);
        else
        {
            ofmovep.open("file\\" + id + ".txt", ios::out | ios::app);
            isfileexist = true;
        }

        ifmovep.open("file\\" + id + ".txt", ios::in | ios::app);
        birthfile();
        lifetime = 0;
    }
}

void cell::grow()
{
    end_clock = system_clock::now();
    auto t = duration<double>(end_clock - start_clock);

    if (isate == true && isexist == true)
    {
        getExistTime();
        cout << "被吃" << "id:" << id << " tag:" << tag << " shape:" << shape;
        //cout << " color:" << color[0] << "," << color[1] << "," << color[2];
        cout << " position:" << position.first << "," << position.second << " 总生存时间:" << lifetime;
        cout << " 死亡到腐败等待时间" << bad_delay_time << " 腐败需要时间" << bad_need_time << " 总存在时间" << existtime << endl;
        isbadtell = true;
        isexist = false;
        if (isexist == false && isnumj == false)
        {
            all_num--;
            isnumj = true;
        }
    }

    if (isdeath == false)
    {
        lifetime = t.count();

        if (KX <= 0)
        {
            birth_end = end_clock;
            isdeath = true;
        }

        if (lifetime >= all_life_time)
        {
            birth_end = end_clock;
            isdeath = true;
            tag = cell_tag.FOOD;
        }
    }

    if (isexist == true)
        getExistTime();

    if (isdeath == true && isexist == true)
    {
        death_action();
    }

    if (isbirth == true && isdeath == false)
    {
        growfile();
        vector<pair<string, double>> dp = my_lib_func_vTVP(movedirection, movedp, string("NULL"), 0.0);
        string nowmove = my_lib_func_pGRand(dp);
        double s = 1;

        if (nowmove == "left")
        {
            if (position.first >= -viewpoint)
                position.first -= speed;
            action();
        }
        else if (nowmove == "down")
        {
            if (position.second >= -viewpoint)
                position.second -= speed;
            action();
        }
        else if (nowmove == "right")
        {
            if (position.first <= viewpoint)
                position.first += speed;
            action();
        }
        else if (nowmove == "up")
        {
            if (position.second <= viewpoint)
                position.second += speed;
            action();
        }
    }
}

void cell::checkmeet(cell & other)
{
    double ox = other.position.first;
    double oy = other.position.second;
    double dx = fabs(ox - position.first);
    double dy = fabs(oy - position.second);
    double le = sqrt(pow(dx, 2) + pow(dy, 2));

    if (le <= fabs(size + other.size) && isdeath == false && id != other.id && isexist == true && other.tag == cell_tag.FOOD)
    {
        other.isate = true;
    }
}

void cell::checkmeet(object & ob)
{
    double ox = ob.position.first;
    double oy = ob.position.second;
    double dx = fabs(ox - position.first);
    double dy = fabs(oy - position.second);
    double le = sqrt(pow(dx, 2) + pow(dy, 2));

    if (le <= fabs(size + ob.size) && isdeath == false && ob.isexist == true)
    {
        iseatobj = true;
        ob.isate = true;
        cout << ob.id << "在位置:" << position.first << "," << position.second << "被吃掉" << ",生命活动时间为" << lifetime << "." << endl;
        eatjl = 1;
        lifetimejl = lifetime;
        eat(ob);
        growfile();
    }

}

void cell::eat(object & ob)
{
    if (ob.tag == obj_tag.FOOD_NOHURT)
    {
        eatobnum++;
    }
    else if (ob.tag == obj_tag.FOOD_HURT)
    {
        eatobnum++;
        KX--;
    }
    else if (ob.tag == obj_tag.NOFOOD_HURT)
    {
        KX--;
    }
    else if (ob.tag == obj_tag.NOFOOD_NOHURT)
    {
    }
}

void cell::action()
{
    int i;
    if (isbirth == true && isdeath == false)
    {
        glBegin(GL_POLYGON);
        glColor3f(color[0], color[1], color[2]);
        for (i = 0; i < shape; ++i)
            glVertex2f(size * cos(2 * M_PI / shape * i) + position.first, size * sin(2 * M_PI / shape * i) + position.second);

        glEnd();
    }
}
