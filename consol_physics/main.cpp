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



class Particle
{
public:
    double _mass; //(kg)
    double _velocity;
    double _acceleration;

    Particle(double m, double v, double a) : _mass(m), _velocity(v), _acceleration(a){}

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
    ofstream fileOut("positions.csv");

    Particle p1(1,1,1);

    cout << "Caculating..." << endl << endl;

    fileOut << "Velocity: " << p1._velocity << "Acceleration: " << p1._acceleration << endl;

    for(double time = 0; time < 100; ++time)
    {

            fileOut << "Velocity: " << p1._velocity << "Acceleration: " << p1._acceleration << endl;
    }
    cout << "Done!" << endl;


}
