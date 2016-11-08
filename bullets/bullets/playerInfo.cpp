//ArrayBasedBounds.cpp
//William Horn
//10.31.2016
#include <iostream>
using std::cout;
using std::cin;
using std::endl;
#include <vector>
using std::vector;
#include <string>
using std::string;
#include <Windows.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include "readLevel.h"
#include "entityEnum.h"
#include "GAME_SETTINGS.h"
#include "playerInfo.h"

struct playerInfo
{
    int xPos;
    int yPos;
    char model;
    vector<vector<int> > prevPositions;
    //Stop Character From going out through walls

    playerInfo(vector<vector<int> > prevIn) : xPos(XMAX / 2), yPos(YMAX / 2),
                                    model('@'), prevPositions(prevIn) {}

    void movePlayer(vector<vector<entity> > bounds)
    {
        int U = GetAsyncKeyState(0x57); //W virtual key code
        int D = GetAsyncKeyState(0x53); //S virtual key code
        int L = GetAsyncKeyState(0x41); //A virtual key code
        int R = GetAsyncKeyState(0x44); //D virtual key code

        if(U != 0 && (bounds[yPos - 1][xPos] != wall))   this-> yPos-=1;
        if(D != 0 && (bounds[yPos + 1][xPos] != wall))   this-> yPos+=1;

        if(L != 0 && (bounds[yPos][xPos - 1] != wall))   this-> xPos-=1;
        if(R != 0 && (bounds[yPos][xPos + 1] != wall))   this-> xPos+=1;
        return;
    }
};
