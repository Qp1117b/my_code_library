#pragma once
#include "my_lib_include.h"	
#include "object.h"

struct CELL_TAG
{
	string CELL = "cell";
	string FOOD = "food";
};

extern struct CELL_TAG cell_tag;

class cell
{
public:	
	cell(vector<double> color, double size, int shape, double speed, pair<double, double> position);
	cell(vector<double> color, pair<double, double> position);
	cell();
	~cell();
	void birthfile();
	void growfile();
	double getExistTime();
	void death_action();
	void bad_action();
	void tell();
	void birth();
	void action();
	void grow();
	void checkmeet(cell & other);
	void checkmeet(object & ob);

	double road;
	double roadtime;
	bool iseatobj = false;
	ofstream ofmovep;
	ifstream ifmovep;
	bool isate = false;
	int KX = 3;
	double food = 3;
	string tag;	
	string id;
	bool isdeath = false;
	vector<double> color;
	double size;
	int shape;
	double speed;
	static long long all_num;
	time_point<system_clock> start_clock;
	time_point<system_clock> end_clock;
	time_point<system_clock> birth_start;
	time_point<system_clock> birth_end;
	time_point<system_clock> bad_start;
	time_point<system_clock> bad_end;
	double lifetime;
	double all_life_time = 10;
	double bad_all_delay_time = 5;
	double bad_delay_time = 0;
	double bad_need_time = 0;
	double existtime = 0;
	bool isdeathtell = false;
	bool isbadtell = false;
	bool isbad = false;
	bool isbadend = false;
	bool isexist = true;
	double bad_speed = 0.0001;
	vector<double> movedp = { 1,1,1,1 };
	vector<string> movedirection = { "up","down","left","right" };
	pair<double,double> position;
	pair<double, double> death_position;
	double viewpoint;
	bool isbirth = false;
	bool isnumj = false;
	int eatobnum = 0;
	map<pair<double,double>, vector<double>> ptree;
	bool isfileexist = false;
	double eatjl;
	int growfilerun = 0;
	double lifetimejl;
	string nowmove;
	double pathtime = 0;
	double pretime;

private :
	void eat(object & ob);
	string _getid()
	{
		static long long cid = 0;
		cid++;
		return "cell-" + to_string(cid);
	}
};
