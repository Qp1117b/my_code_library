#include <iostream>
#include "my_lib_include.h"
#include "cell.h"
#include "object.h"

using namespace std;

void birth();
void processInputs(GLFWwindow* window);

//double s = 1;
//const double cx = 0.0002, cy = 0.0002;
//const double R = 0.01;
//const double initposi = 1 - R;
//const int n = 50;
//double nowx = initposi;
//double nowy = initposi;

int main(int argc, char * args)
{
    const int max = 50;
    cell c;
    object o[max];

    c.color = {1,0,0};
    //c.speed = 0.0002;
    c.movedp = {0,1,0,0};
    c.shape = 50;
    //c.size = 0.01;
    c.size = 0.05;
    c.viewpoint = 1 - c.size;
    c.position = { 1 - c.size,1 - c.size };
    c.all_life_time = 1000000;

    for (auto & x : o)
    {        
        x.size = 0.02;
        x.position = { my_lib_func_random(-1.0 + x.size, 1.0 - x.size, 1).at(0), my_lib_func_random(-1.0 + x.size, 1.0 - x.size, 1).at(0) };
        x.tag = obj_tag.FOOD_NOHURT;
        x.shape = obj_shape.SQR;
        x.color = my_lib_func_random(0.2, 1.0, 3);
    }

    glfwInit();

    GLFWwindow * window = glfwCreateWindow(800, 800, "Hello World", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    int init = 1;
    long long num = 23;
    while (!glfwWindowShouldClose(window))
    {
        //processInputs(window);

        //birth();
        glClearColor(0.0, 0.0, 0.0, 0.0);
        glClear(GL_COLOR_BUFFER_BIT);

        c.birth();
        c.grow();

        if (object::all_num <= max - num)
        {
            cout << "restart" << endl;
            c.position = c.position = { 1 - c.size,1 - c.size };
            cout << c.lifetime << endl;
            c.start_clock = system_clock::now();
            //cout << c.lifetime << endl;
            for (auto& x : o)
            {
                if (x.isexist == false)
                {
                    x.isexist = true;
                    x.isate = false;
                    if (object::all_num != max)
                        object::all_num++;
                }
            }
        }

        for (auto& y : o)
        {
            c.checkmeet(y);
        }

        for (auto& x : o)
        {
            x.make();
            x.exist();
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

void processInputs(GLFWwindow* window)
{
  /*  vector<string> d = { "left","right","up","down" };
    vector<double> p = { 0.3,0.25,0.25,0.25 };
    vector<pair<string, double>> dp = my_lib_func_vTVP(d, p, string("a"), 0.0);
    string t = my_lib_func_pGRand(dp);
    s = my_lib_func_random(1,10,1).at(0);

    if (t == "left")
    {
        glClearColor(0.0, 0.0, 0.0, 0.0);
        glClear(GL_COLOR_BUFFER_BIT);
        if (nowx >= -initposi)
        nowx -= cx*s;
        birth();
    }
    else if (t == "down")
    {
        glClearColor(0.0, 0.0, 0.0, 0.0);
        glClear(GL_COLOR_BUFFER_BIT);
        if (nowy >= -initposi)
        nowy -= cy*s;
        birth();
    }
    else if (t == "right")
    {
        glClearColor(0.0, 0.0, 0.0, 0.0);
        glClear(GL_COLOR_BUFFER_BIT);
        if (nowx <= initposi)
        nowx += cx*s;
        birth();
    }
    else if (t == "up")
    {
        glClearColor(0.0, 0.0, 0.0, 0.0);
        glClear(GL_COLOR_BUFFER_BIT);
        if (nowy <= initposi)
        nowy += cy*s;
        birth();
    }*/

    //if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
    //{
    //    glClearColor(0.0, 0.0, 0.0, 0.0);
    //    glClear(GL_COLOR_BUFFER_BIT);
    //    if (nowx >= -initposi)
    //        nowx -= cx;
    //    cell();
    //}
    //else if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
    //{
    //    glClearColor(0.0, 0.0, 0.0, 0.0);
    //    glClear(GL_COLOR_BUFFER_BIT);
    //    if (nowy >= -initposi)
    //        nowy -= cy;
    //    cell();
    //}
    //else if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
    //{
    //    glClearColor(0.0, 0.0, 0.0, 0.0);
    //    glClear(GL_COLOR_BUFFER_BIT);
    //    if (nowx <= initposi)
    //        nowx += cx;
    //    cell();
    //}
    //else if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
    //{
    //    glClearColor(0.0, 0.0, 0.0, 0.0);
    //    glClear(GL_COLOR_BUFFER_BIT);
    //    if (nowy <= initposi)
    //        nowy += cy;
    //    cell();
    //}
}


void birth()
{    
  /*  int i;

    glBegin(GL_POLYGON);
    glColor3f(1, 0, 0);

    for (i = 0; i < n; ++i)
        glVertex2f(R * cos(2 * M_PI / n * i) + nowx, R * sin(2 * M_PI / n * i) + nowy);

    glEnd();*/
}