#ifndef PLAYERINFO_H_INCLUDED
#define PLAYERINFO_H_INCLUDED

struct playerInfo
{
    int xPos = XMAX / 2;
    int yPos = YMAX / 2;
    char model = '@';
    vector<vector<int> > prevPositions;
    //Stop Character From going out through walls

    playerInfo();

    void movePlayer(vector<vector<entity>> bounds);
};

playerInfo::playerInfo()
{
    for(int i = 0; i < ENEMY_REACTION_TIME; ++i)
    {
        vector<int> currentPos {xPos, yPos};
        prevPositions.push_back(currentPos);
    }
}

void playerInfo::movePlayer(vector<vector<entity>> bounds)
{
    int U = GetAsyncKeyState(0x57); //W virtual key code
    int D = GetAsyncKeyState(0x53); //S virtual key code
    int L = GetAsyncKeyState(0x41); //A virtual key code
    int R = GetAsyncKeyState(0x44); //D virtual key code

    if(U != 0 && (bounds[yPos - 1][xPos] != wall))     this-> yPos-=1;
    if(D != 0 && (bounds[yPos + 1][xPos] != wall))   this-> yPos+=1;

    if(L != 0 && (bounds[yPos][xPos - 1] != wall))   this-> xPos-=1;
    if(R != 0 && (bounds[yPos][xPos + 1] != wall))  this-> xPos+=1;
}

#endif // PLAYERINFO_H_INCLUDED
