#include <iostream>
using std::cout;
using std::endl;
using std::cin;
#include <string>
using std::string;
#include <vector>
using std::vector;
#include <windows.h>
#include <cmath>
using std::pow;
#include <fstream>
using std::ofstream;

#define SECOND 100
#define NUM_SECONDS 1
#define X_MAX 50
#define Y_MAX 25
#define SCALE 0.01
#define GRAVITY -9.81

class Particle
{
public:
    double _mass; //(kg)
    double _Xvelocity; // meters/second
    double _Xacceleration; // m/s^2
    double _Yvelocity; // meters/second
    double _Yacceleration; // m/s^2
    double _xPos;
    double _yPos;

public:
    Particle(double m = 10,
             double v_X = 0,
             double v_Y = 10,
             double a_X = 0,
             double a_Y = GRAVITY * SCALE,
             double x_Pos = X_MAX / 2,
             double y_Pos = Y_MAX) : _mass(m),
                                       _Xvelocity(v_X),
                                       _Yvelocity(v_Y),
                                       _Xacceleration(a_X),
                                       _Yacceleration(a_Y),
                                       _xPos(x_Pos),
                                       _yPos(y_Pos){}
    double getXPos() const {return _xPos;}
    double getYPos() const {return _yPos;}

    void vel_X_change(unsigned long time)
    {
        _Xvelocity = _Xvelocity + _Xacceleration * time;
    }
    void vel_Y_change(unsigned long time)
    {
        _Yvelocity = _Yvelocity + _Yacceleration * time;
    }
    void y_move(unsigned long time)
    {
        _yPos = _yPos + (_Yvelocity * time) + (.5 * _Yacceleration * pow(time, 2.));
    }
};

string genWorld(const vector<Particle> & particles)
{
    string world = "";
    for(int y = Y_MAX; y >= 0; --y)
    {
        for(int x = X_MAX; x >= 0; --x)
        {
            //check all the particles
            for(int i = 0; i < (int)particles.size(); ++i)
            {
                if(particles[i].getXPos() == x &&
                   particles[i].getYPos() == y)
                   {
                       world += (char)254;
                   }
                else world += ' ';
            }
        }
        world += '\n';
    }
    return world;
}

void printWorld(string world)
{
    cout << world;
}
int main()
{
    ofstream fileOut("y_positions.csv");

    vector<Particle> particles;

    Particle ball(1);
    particles.push_back(ball);

    bool flipped = false;

    cout << "Caculating..." << endl;

    for(double time = 0; time < 100; ++time)
    {
        for(int i = 0; i < particles.size(); ++i)
        {
            particles[i].vel_Y_change(time);
            particles[i].y_move(time);

            if(particles[i].getYPos() > 0 && !flipped)
            {
                particles[i]._Yacceleration *= (-1.);
                flipped = true;
            }
            else
            {
                particles[i]._Yacceleration *= (-1.);

            }
            fileOut << particles[i].getXPos() << "," << particles[i].getYPos() << endl;
        }
    }
    cout << "Done!" << endl;


}
