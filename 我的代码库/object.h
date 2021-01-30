#pragma once
#include "my_lib_include.h"

struct OBJECT_TAG 
{
	string FOOD_NOHURT = "food-nohurt";
	string FOOD_HURT = "food-hurt";
	string NOFOOD_HURT = "nofood-hurt";
	string NOFOOD_NOHURT = "nofood-nohurt";
};

struct OBJECT_SHAPE
{
	int CIRCLE = 50;
	int TRI = 3;
	int SQR = 4;
	int FIVE = 5;
};
extern struct OBJECT_TAG obj_tag;
extern struct OBJECT_SHAPE obj_shape;
class object
{
public :
	object(vector<double> color, double size, int shape, pair<double, double> position, string tag);
	object(vector<double> color, pair<double, double> position);
	object();
	~object();
	void make();
	void exist();
	void tell();
	ofstream ofmovep;
	ifstream ifmovep;
	void makefile();

	vector<double> color;	
	pair<double, double> position;
	double size;
	int shape;
	string tag;
	string id;
	bool ismake = false;
	bool isate = false;
	bool isexist = false;
	static long long all_num;
	bool isnumj = false;
	bool ispofileexist = false;

	static vector<string> v_tag;
	
private :
	string _getid()
	{
		static long long oid = 0;
		oid++;
		return "obj-" + to_string(oid);
	}
};
