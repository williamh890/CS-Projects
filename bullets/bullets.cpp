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
#include <chrono>


#include "Headers/readLevel.h"
#include "Headers/Game_Settings.h"
#include "Headers/playerInfo.h"
#include "Headers/enemyInfo.h"
#include "Headers/BoolChecks.h"
#include "Headers/bulletInfo.h"
#include "Headers/levelFuncs.h"
#include "Headers/bulletFuncs.h"
#include "Headers/enemyFuncs.h"

int main()
{
    vector<vector<entity> > bounds(YMAX, vector<entity>(XMAX));

    vector<struct bulletInfo> bullets;

    playerInfo player;

    vector<struct enemyInfo> enemies;

    vector<struct deathInfo> deaths;

    int fireRate = SHOT_DELAY + 1;
    bool bulletFired = false;

    int playerMoveRate = PLAYER_SPEED + 1;
    bool playerMoved = false;

    int enemyMoveRate = ENEMY_SPEED;
    int deathAnimationRate = DEATH_SPEED;

    bool playAgain = true;

    srand(time(nullptr));

    system("Color F0");

    while(playAgain)
    {
        printTitle();
        playAgain = playerSelection();
        if(playAgain == false) break;

        system("Color 0F");
        bool game_Over = false;
        int level = 1;
        bullets.clear();
        enemies.clear();
        player = {};

        while(true)
        {
            system("cls");
            system("Color F0");
            cout << readLevel(level) << "\n\t\t\t\t\t";
            Sleep(1000);
            system("Color 0F");
            system("cls");

            generateLevel(bounds, player, bullets, enemies, deaths, true);
            generateEnemies(level, enemies, bounds);

            player.xPos = XMAX / 2;
            player.yPos = YMAX / 2;
            bullets.clear();

            while(!game_Over)
            {
                generateLevel(bounds, player, bullets, enemies, deaths, false);

                draw(bounds, player, bullets, deaths);

                //////////////Player Move/////////////
                if(!playerMoved)
                {
                    int tempX = player.xPos;
                    int tempY = player.yPos;

                    player.movePlayer(bounds);

                    if(player.xPos != tempX || player.yPos != tempY)
                    {
                        playerMoved = true;
                        playerMoveRate = 0;
                    }
                }

                if(playerMoved) playerMoveRate++;
                if(playerMoveRate == PLAYER_SPEED)
                {
                    playerMoved = false;
                    playerMoveRate = PLAYER_SPEED + 1;
                }
                ////////////////////////////////////

                ////////////Bullet Move/////////////
                if(fireRate >= SHOT_DELAY)
                {
                    int tempSize = (int)bullets.size();

                    createBullets(bullets, player);

                    if(tempSize < (int)bullets.size())
                    {
                        bulletFired = true;
                        fireRate = 0;
                    }
                }
                if(bulletFired) fireRate++;

                moveBullets(bullets, bounds);
                ////////////////////////////////////

                ////////////Enemy Move/////////////
                if(enemyMoveRate == ENEMY_SPEED)
                {
                    moveEnemies(enemies, player, bounds);
                    enemyMoveRate = 0;
                    uniqueEnemyPosition(enemies, bounds);
                }

                hitDetection(enemies, bullets, player, deaths, game_Over);
                if(deathAnimationRate > DEATH_SPEED) changeDeaths(deaths);
                //////////////////////////////////////

                vector<int> currentPos {player.xPos, player.yPos};
                player.prevPositions.push_back(currentPos);
                player.prevPositions.erase(player.prevPositions.begin());

                if(enemies.size() == 0) break;
                ++deathAnimationRate;
                ++enemyMoveRate;
                Sleep(REFRESH);
                system("cls");
            }
            if(game_Over)
            {
                printLose();
                system("Color 0C");
                Sleep(2000);
                system("cls");
                system("Color F0");
                break;
            }
            if(level == LEVELS_TO_WIN)
            {
                system("cls");
                printWin();
                system("Color 2F");
                Sleep(3000);
                system("cls");
                system("Color F0");
                break;
            }
            level++;
        }
    }
}
