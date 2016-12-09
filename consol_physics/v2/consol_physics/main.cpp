#include <iostream>
using std::cout;
using std::endl;
#include <fstream>
using std::ofstream;
#include <windows.h>

#define Y_MAX 50
#define X_MAX 100

class Particle
{
public:
    double _mass;
    double _Yposition;
    double _Xposition;
    double _velocity;
    double _accelaration;


    Particle(double m, double p, double v, double a) : _mass(m),
                                                       _Yposition(p),
                                                       _velocity(v),
                                                       _accelaration(a){}
    void del_v(double time)
    {
        _velocity = _velocity + _accelaration * time;
    }
    void del_pos(double time, double v_inital)
    {
        _Yposition += (.5) * (v_inital + _velocity) * time;
    }
};

void worldPrint(Particle & p)
{
    for(int i = 0; i < Y_MAX; ++i)
    {
        if(p._Yposition == i) cout << "x";
        else cout << endl;
    }
}


int main()
{
    bool print_to_file = true;
    ofstream outFile;

    if(print_to_file)
    {
        outFile.open("motion");
        if(!outFile)
        {
            cout << "Error opening file...";
            return -1;
        }
    }

    Particle p(10, 1, 0, -1);
    double prev_V = p._velocity;

    if(print_to_file) outFile << p._velocity << ", " << p._Yposition << endl;
    while(true)
    {
        p.del_v(1);
        p.del_pos(1, prev_V);

        if(p._Yposition <= 0)
        {
            p._accelaration =  0;
            p._velocity = 0;
            p._Yposition = 0;
        }
        if(GetAsyncKeyState(VK_SPACE) != 0)
        {
            p._accelaration = -1;
            p._velocity = 5;
        }
        if(GetAsyncKeyState(VK_LEFT)) p._Xposition++;
        if(GetAsyncKeyState(VK_RIGHT)) p._Xposition--;

        system("cls");
        worldPrint(p);
        if(print_to_file) outFile << p._velocity << ", " << p._Yposition << endl;
        Sleep(50);

    }

    return 0;
}
