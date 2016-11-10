#ifndef BOOLCHECKS_H_INCLUDED
#define BOOLCHECKS_H_INCLUDED

bool legalPosition(vector<vector<entity>> bounds, int xPos, int yPos)
{
    return (bounds[yPos][xPos] != wall);
}

bool levelBounds(int x, int y)
{
    //#define XMAX 80
    //#define YMAX 25
    int xCorner = 6;
    int yCorner = 5;
    int wallLength = 5;
    return (x == 0 || x == XMAX - 1 ||
           (y == 0 || y == YMAX - 1) ||
           ((x > XMAX / xCorner && x < (XMAX / xCorner) + wallLength * 2) && y == YMAX / yCorner ) ||
           (x == XMAX / xCorner + 1 && (y > YMAX / yCorner && y < (YMAX / yCorner) + wallLength)) ||

           ((x < 5*XMAX / xCorner && x > (5*XMAX / xCorner) - wallLength * 2) && y == YMAX / yCorner) ||
           (x == 5*XMAX / xCorner - 1 && (y > (YMAX) / yCorner && y < ((YMAX) / yCorner) + wallLength)) ||

            (x == 5*XMAX / xCorner - 1 && (y < (4*YMAX) / yCorner && y > ((4*YMAX) / yCorner) - wallLength)) ||
            ((x < 5*XMAX / xCorner && x > (5*XMAX / xCorner) - wallLength * 2) && y == 4*YMAX / yCorner) ||

            (x > XMAX / xCorner && x < (XMAX / xCorner) + wallLength * 2 && y == 4*YMAX / yCorner) ||
            (x == XMAX / xCorner + 1 && y < (4*YMAX / yCorner) && y > ((4*YMAX / yCorner) - wallLength)) ||

            (y == YMAX / yCorner + wallLength / 2 + 1&& x > XMAX / 2.5 && x < XMAX / 2.5 + 3*wallLength) ||
            (y == 3*YMAX / yCorner + wallLength / 2 && x > XMAX / 2.5 && x < XMAX / 2.5 + 3*wallLength)

            );
}

bool keyCheck(int U, int D,
              int L, int R)
{
    //If any of the keys are pressed returns true
    if(U  != 0 ||
       D  != 0 ||
       L  != 0 ||
       R  != 0) return true;
       //No key pressed
       return false;
}

bool playerSelection()
{
    while(true)
    {
        if(GetAsyncKeyState(VK_SPACE))  return true;
        if(GetAsyncKeyState(VK_ESCAPE)) return false;
    };
}

#endif // BOOLCHECKS_H_INCLUDED
