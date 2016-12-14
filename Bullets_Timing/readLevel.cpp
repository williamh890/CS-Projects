#include <iostream>
using std::cout;
using std::endl;
#include <string>
using std::string;
#include <fstream>
using std::ifstream;
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

void printTitle()
{
    cout << "\n\n\n" << endl;
    cout << R"(
                  _______________________________________________
                 |                                               |
                 |       __                   __  ___   ___      |
                 |      l  \  |  |  |   |    |     |   |         |
                 |      l__/  |  |  |   |    |__   |   |__       |
                 |      l  \  |  |  |   |    |     |      |      |
                 |      l__/  |__|  |__ |__  |__   |   ___|      |
                 |                                               |
                 |               : SPACE TO PLAY :               |
                 |               :  ESC TO QUIT  :               |
                 |                                               |
                 |_______________________________________________|
                                       )";
    cout << endl << "\n\n\n\n\n\n\t\t\t\t\t\t\t\t      Moni Mikes\b\b\b\b\b\b\b\b\b\b\b\b";
}

void printLose()
{
    cout << "\n\n\n" << endl;
    cout << R"(
                  _______________________________________________
                 |                                               |
                 |                                               |
                 |           __                __   ___  __      |
                 |   \   /  |  |  |  |    |   |  | |    |    |   |
                 |    \ /   |  |  |  |    |   |  | |__  |__  |   |
                 |     l    |  |  |  |    |   |  |    | |    |   |
                 |     l    |__|  |__|    |__ |__| ___| |__  .   |
                 |                                               |
                 |   ------------------------------------------  |
                 |                                               |
                 |_______________________________________________|
                                        )";
}

void printWin()
{

    cout << "\n\n\n" << endl;
    cout << R"(
                  _______________________________________________
                 |                                               |
                 |                                               |
                 |         __                                    |
                 |  \   / |  |  |  |  \          / ^  |\   |  |  |
                 |   \ /  |  |  |  |   \        /  |  | \  |  |  |
                 |    l   |  |  |  |    \  /\  /   |  |  \ |  |  |
                 |    l   |__|  |__|     \/  \/    |  |   \|  .  |
                 |                                               |
                 |   ------------------------------------------  |
                 |                                               |
                 |_______________________________________________|
                                        )";

}

