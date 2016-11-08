#include <iostream>
using std::cout;
using std::endl;
#include <string>
using std::string;
#include <fstream>
using std::ifstream;
#include <windows.h>
#include "readLevel.h"

string readLevel(int num)
{
    string line;
    string currLevel = "\n\n\n\n\n";
    string levelNum;
    switch(num)
    {
    case 1:
        levelNum = "1";
        break;
    case 2:
        levelNum = "2";
        break;
    case 3:
        levelNum = "3";
        break;
    case 4:
        levelNum = "4";
        break;
    case 5:
        levelNum = "5";
        break;
    case 6:
        levelNum = "6";
        break;
    case 7:
        levelNum = "7";
        break;
    case 8:
        levelNum = "8";
        break;
    case 9:
        levelNum = "9";
        break;
    case 10:
        levelNum = "10";
        break;
    }

    string levelFile = "Levels/level" + levelNum + ".txt";
    ifstream myfile (levelFile);

    if (myfile.is_open())
    {
        while ( getline (myfile,line) )
        {
            currLevel += "\t\t" + line + "\n";
        }
        myfile.close();
    }
    else cout << "Unable to open file";

    return currLevel;
}

void printLevel(int level)
{
    system("cls");
    system("Color F0");
    cout << readLevel(level) << "\n\t\t\t\t\t";
    Sleep(1000);
    system("Color 0F");
    system("cls");
}

