#ifndef ENEMYINFO_H_INCLUDED
#define ENEMYINFO_H_INCLUDED

#include "BoolChecks.h"

struct deathInfo
{
    int xPos;
    int yPos;
    int stage;
    char model;
};

struct enemyInfo
{
    int xPos; //current x position of the enemy
    int yPos; //current #define XMAX 80
    bool fastReaction;
    int vision;
    int speedMod;
    int speedCounter = 3;

    vector<int> currentDirection {0,0}; //{X_movement, Y_movement}

    enemyInfo(){}
    enemyInfo(int x, int y) : xPos(x), yPos(y)
    {
        speedMod = rand() % 2 + 1;
        vision = (5 - rand() % 10) + DECTECTION_RANGE;
        fastReaction = (bool)rand() % 3;
    }


    void moveEnemy(playerInfo player, vector<vector<entity> > bounds)
    {
        //move enemies closer to player
        int tempX = this->xPos;
        int tempY = this->yPos;
        int reaction;
        int playerDist = sqrt(pow(player.xPos - this->xPos, 2) + pow(player.yPos - this->yPos, 2));

        if(playerDist > vision)
        {
            //Random movement
            currentDirection[0] =  1 - (rand() % 3);
            currentDirection[1] =  1 - (rand() % 3);
        }
        else
        {
            if(fastReaction) reaction = ENEMY_REACTION_TIME / 3;

            else reaction = 0;

            //Changes the x direction to move toward the player
            if     (xPos < player.prevPositions[reaction][0]) currentDirection[0] =  1;
            else if(xPos > player.prevPositions[reaction][0]) currentDirection[0] = -1;
            else                                              currentDirection[0] =  (rand() % 2)*(1 - (rand() % 3));
            //Changes the y direction to move toward the player
            if     (yPos < player.prevPositions[reaction][1]) currentDirection[1] =  1;
            else if(yPos > player.prevPositions[reaction][1]) currentDirection[1] = -1;
            else                                              currentDirection[1] = (rand() % 2)*(1 - (rand() % 3));
            //If the direction before the changes == direction after the changes
        }
        //Otherwise move the enemy closer to the player
        xPos += currentDirection[0];
        yPos += currentDirection[1];

         if((bounds[yPos][xPos] == wall))
        {
             if(bounds[tempY][tempX + 1] == wall) xPos-=1;
             if(bounds[tempY][tempX - 1] == wall) xPos+=1;

             if(bounds[tempY - 1][tempX] == wall) yPos+=1;
             if(bounds[tempY + 1][tempX] == wall) yPos-=1;
        }
    }
};

#endif // ENEMYINFO_H_INCLUDED
