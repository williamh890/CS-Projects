#ifndef BULLETINFO_H_INCLUDED
#define BULLETINFO_H_INCLUDED

struct bulletInfo
{
    int xPos;
    int yPos;
    char model;
    vector<int> trajectory;

    enum direction {up, down, left, right};

    bulletInfo(){}
    bulletInfo(int x, int y,
               vector<int> dir) : xPos(x), yPos(y),
                                  trajectory(dir)
    {
        int U = trajectory[up];
        int D = trajectory[down];
        int L = trajectory[left];
        int R = trajectory[right];

        if((U != 0 || D != 0 ) &&
           (L == 0 && R == 0)) model = '|';

        else if((L != 0 || R != 0 ) &&
                (U == 0 && D == 0)) model = '-';

        else if((U != 0 && R != 0 ) ||
                (D != 0 && L != 0)) model = '/';

        else model = '\\';
    }

    void moveBullet()
    {
        if(trajectory[up] != 0)    this->yPos--;
        if(trajectory[down] != 0)  this->yPos++;

        if(trajectory[left] != 0)  this->xPos--;
        if(trajectory[right] != 0) this->xPos++;
    }

    bool legalUp(vector<vector<entity>> & bounds)
    {
        return (bounds[yPos][xPos] != wall);
    }
    bool legalDown(vector<vector<entity>> & bounds)
    {
        return (bounds[yPos][xPos] != wall);
    }
    bool legalLeft(vector<vector<entity>> & bounds)
    {
        return (bounds[yPos][xPos] != wall);
    }
    bool legalRight(vector<vector<entity>> & bounds)
    {
        return (bounds[yPos][xPos] != wall);
    }
    bool legalMove(vector<vector<entity> > bounds)
    {
        return (legalUp(bounds)    ||
                legalDown(bounds)  ||
                legalLeft(bounds)  ||
                legalRight(bounds));
    }
};

#endif // BULLETINFO_H_INCLUDED
