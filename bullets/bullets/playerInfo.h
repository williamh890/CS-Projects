#ifndef PLAYERINFO_H_INCLUDED
#define PLAYERINFO_H_INCLUDED

struct playerInfo
{
    int xPos;
    int yPos;
    char model;
    vector<vector<int> > prevPositions;

    playerInfo(vector<vector<int> > prevPositions);
    playerInfo();

    void movePlayer(vector<vector<entity> > bounds);
};



#endif // PLAYERINFO_H_INCLUDED
