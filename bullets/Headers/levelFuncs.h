#ifndef LEVELFUNCS_H_INCLUDED
#define LEVELFUNCS_H_INCLUDED

#include "Game_Settings.h"
#include <vector>
using std::vector;

struct enemies;
struct deaths;
struct playerInfo;
struct deathInfo;

void generateLevel(vector<vector<entity >> & bounds,
                   struct playerInfo player,
                   vector<struct bulletInfo> bullets,
                   vector<struct enemyInfo> enemies,
                   vector<struct deathInfo> deaths,
                   bool initial)
{
    for(int y = 0; y < (int)bounds.size(); y++)
    {
        for(int x = 0; x < (int)bounds[y].size(); x++)
        {
            int charsPrinted = 0;

            if(levelBounds(x,y) && initial)
            {
                bounds[y][x] = wall;
                continue;
            }
            if(player.xPos == x && player.yPos == y)
            {
                bounds[y][x] = character;
                continue;
            }
            for(int bulletIndex = 0; bulletIndex < (int)bullets.size(); ++bulletIndex)
            {
                if(bullets[bulletIndex].xPos == x && bullets[bulletIndex].yPos == y)
                {
                    bounds[y][x] = bullet;
                    charsPrinted++;
                    break;
                }
            }
            for(int deathNum = 0; deathNum < (int)deaths.size(); ++deathNum)
            {
                if(deaths[deathNum].xPos == x && deaths[deathNum].yPos == y)
                {
                    bounds[y][x] = death;
                    charsPrinted++;
                    break;
                }
            }
            if(charsPrinted) continue;

            for(int enemyIndex = 0; enemyIndex < (int)enemies.size(); ++enemyIndex)
            {
                if(enemies[enemyIndex].xPos == x && enemies[enemyIndex].yPos == y)
                {
                    bounds[y][x] = enemy;
                    charsPrinted++;
                }
            }
            if(charsPrinted) continue;
            if(bounds[y][x] != wall) bounds[y][x] = space;
        }
    }
}

void draw(vector<vector<entity>> bounds, playerInfo player,
          vector<struct bulletInfo> & bullets,
          vector<struct deathInfo> deaths)
{
    string render = "";

    for(int y = 0; y < (int)bounds.size(); y++)
        {
            for(int x = 0; x < (int)bounds[y].size(); x++)
            {
                if(bounds[y][x] == wall)
                {
                    render += (char)219;
                }
                if(bounds[y][x] == character)
                {
                    render += player.model;
                }
                if(bounds[y][x] == space)
                {
                    render += ' ';
                }
                if(bounds[y][x] == bullet)
                {
                    for(int i = 0; i < (int)bullets.size(); ++i)
                    {
                        if(bullets[i].xPos == x  && bullets[i].yPos == y)
                            render += bullets[i].model;
                    };
                }
                if(bounds[y][x] == death)
                {
                    for(int deathNum = 0; deathNum < (int)deaths.size(); ++deathNum)
                    {
                        if(deaths[deathNum].xPos == x && deaths[deathNum].yPos == y)
                        {
                            render += deaths[deathNum].model;
                        }
                    }
                }
                if(bounds[y][x] == enemy)
                {
                    render += (char)237;
                }
            }
            if(y != (int)bounds.size() - 1) render += '\n';
        }
        cout << render;
}



#endif // LEVELFUNCS_H_INCLUDED
