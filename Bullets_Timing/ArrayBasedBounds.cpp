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
#include <iostream>
#include <chrono>
#include <fstream>
using std::ofstream;
#include <thread>
using std::thread;
#include <future>
using std::future;
using std::promise;
#include <algorithm>
#include <utility>
using std::pair;
using std::make_pair;

#include "readLevel.h"

#define MAX_THREADS std::thread::hardware_concurrency()
#define XMAX (200)
#define YMAX (75)

#define SHOT_DELAY 5
#define PLAYER_SPEED 2
//Delay enemies movements
#define ENEMY_SPEED 1
#define ENEMY_SPEED_DIF 0
#define ENEMY_REACTION_TIME 10
#define DECTECTION_RANGE 75
#define START_DEATH_STAGE 3
#define DEATH_SPEED 16

#define BUFFER 5

#define LEVEL_MOD 400
#define LEVELS_TO_WIN 1

#define REFRESH 25

#define START_CLK auto frameBegin = std::chrono::high_resolution_clock::now()

#define END_CLK auto frameEnd = std::chrono::high_resolution_clock::now(); \
                frameTimeFile << std::chrono::duration_cast<std::chrono::nanoseconds>(frameEnd-frameBegin).count() << "," << endl

ofstream frameTimeFile("FunctionSpread320_104_8Threads/TIMEvsENEMIES.csv");

enum entity
{
    enemy,
    character,
    wall,
    destructableWall,
    bullet,
    space,
    death
};

vector<vector<int >> makePrePositions(int x, int y)
{
    vector<vector<int >> prevPositions;
    for(int i = 0; i < ENEMY_REACTION_TIME; ++i)
    {
        vector<int> currentPos {x, y};
        prevPositions.push_back(currentPos);
    }
    return prevPositions;
}

struct playerInfo
{
    int xPos = XMAX / 2;
    int yPos = YMAX / 2;
    char model = '@';
    vector<vector<int> > prevPositions;
    //Stop Character From going out through walls

    playerInfo() : prevPositions(makePrePositions(XMAX / 2, YMAX / 2)){}

    void movePlayer(vector<vector<entity>> bounds)
    {
        int U = GetAsyncKeyState(0x57); //W virtual key code
        int D = GetAsyncKeyState(0x53); //S virtual key code
        int L = GetAsyncKeyState(0x41); //A virtual key code
        int R = GetAsyncKeyState(0x44); //D virtual key code

        if(U != 0 && (bounds[yPos - 1][xPos] != wall))   this-> yPos-=1;
        if(D != 0 && (bounds[yPos + 1][xPos] != wall))   this-> yPos+=1;

        if(L != 0 && (bounds[yPos][xPos - 1] != wall))   this-> xPos-=1;
        if(R != 0 && (bounds[yPos][xPos + 1] != wall))   this-> xPos+=1;
        }
};

bool legalPosition(vector<vector<entity>> bounds, int xPos, int yPos)
{
    return (bounds[yPos][xPos] != wall);
}

struct enemyInfo
{
    int xPos; //current x position of the enemy
    int yPos; //current #define XMAX 80
    bool fastReaction;
    int vision;
    int speedMod;
    unsigned int enemyType;
    int speedCounter = 3;

    enum{momentum = 0, random = 1};


    vector<int> currentDirection {0,0}; //{X_movement, Y_movement}

    enemyInfo(){}
    enemyInfo(int x, int y) : xPos(x), yPos(y)
    {
        speedMod = rand() % 2 + 1;
        vision = (5 - rand() % 10) + DECTECTION_RANGE;
        fastReaction = (bool)rand() % 3;
        enemyType = rand() % 2;
    }


    void moveEnemy(playerInfo player, vector<vector<entity> > bounds)
    {
        if(1)
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
                else                                              currentDirection[0] =  1 - (rand() % 3);
                //Changes the y direction to move toward the player
                if     (yPos < player.prevPositions[reaction][1]) currentDirection[1] =  1;
                else if(yPos > player.prevPositions[reaction][1]) currentDirection[1] = -1;
                else                                              currentDirection[1] =  1 - (rand() % 3);
                //If the direction before the changes == direction after the changes
            }
            //Otherwise move the enemy closer to the player
            xPos += currentDirection[0];
            yPos += currentDirection[1];

             if(!legalPosition(bounds, this->xPos, this->yPos))
            {
                 if(bounds[tempY][tempX + 1] == wall) xPos-=1;
                 if(bounds[tempY][tempX - 1] == wall) xPos+=1;

                 if(bounds[tempY - 1][tempX] == wall) yPos+=1;
                 if(bounds[tempY + 1][tempX] == wall) yPos-=1;
            }
        }
        else if(enemyType == momentum)
        {

        }
    }
};

struct deathInfo
{
    int xPos;
    int yPos;
    int stage;
    char model;
};

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

    inline bool legalMove(vector<vector<entity> > bounds)
    {
        return ((bounds[yPos][xPos] != wall)  ||
                (bounds[yPos][xPos] != wall)  ||
                (bounds[yPos][xPos] != wall)  ||
                (bounds[yPos][xPos] != wall));
    }
};

bool levelBounds(int x, int y)
{
    //#define XMAX 80
    //#define YMAX 25
    int xCorner = 6;
    int yCorner = 5;
    int wallLength = YMAX / 5;
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

void generateLevelRange(vector<vector<entity >> & bounds,
                                   playerInfo player,
                                   vector<struct bulletInfo> bullets,
                                   vector<struct enemyInfo> enemies,
                                   vector<struct deathInfo> deaths,
                                   bool initial,
                                   pair<int,int> range,
                                   string & render)
{
     render = "";

     for(int y = range.first; y < (int)range.second; y++)
     {
        for(int x = 0; x < (int)bounds[y].size(); x++)
        {
            int charsPrinted = 0;

            if(levelBounds(x,y) && initial)
            {
                bounds[y][x] = wall;
                continue;
            }

            if(bounds[y][x] == wall && !initial) render += (char)219;

            if(player.xPos == x && player.yPos == y)
            {
                if(!initial) render += player.model;
                bounds[y][x] = character;
                continue;
            }
            for(int bulletIndex = 0; bulletIndex < (int)bullets.size(); ++bulletIndex)
            {
                if(bullets[bulletIndex].xPos == x && bullets[bulletIndex].yPos == y)
                {
                    if(!initial) render += bullets[bulletIndex].model;
                    bounds[y][x] = bullet;
                    charsPrinted++;
                    break;
                }
            }
            for(int deathNum = 0; deathNum < (int)deaths.size(); ++deathNum)
            {
                if(deaths[deathNum].xPos == x && deaths[deathNum].yPos == y)
                {
                    if(!initial) render += deaths[deathNum].model;
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
                    if(!initial) render += (char)237;
                    bounds[y][x] = enemy;
                    charsPrinted++;
                }
            }
            if(charsPrinted) continue;
            if(bounds[y][x] != wall)
            {
                if(!initial) render += ' ';
                bounds[y][x] = space;
            }
        }
        if(y != (int)bounds.size() - 1 && !initial) render += '\n';
    }
}

string generateLevel(vector<vector<entity >> & bounds,
                                      playerInfo player,
                                      vector<struct bulletInfo> bullets,
                                      vector<struct enemyInfo> enemies,
                                      vector<struct deathInfo> deaths,
                                      unsigned int numThreads,
                                      bool initial)
{
    //Array of unassigned threads
    thread genThreads[numThreads];
    //Array of string references
    string renders[numThreads];
    string finalRender = "";
    //Starts all the threads
    for(int i = 0; i < (int)numThreads; ++ i)
        genThreads[i] = thread(generateLevelRange,std::ref(bounds),player,bullets,enemies,deaths,initial,make_pair((bounds.size()*(i))/numThreads,(bounds.size()*(i+1))/numThreads),std::ref(renders[i]));
    //Joins all the threads
    for(int i = 0; i < (int)numThreads; ++i)
        genThreads[i].join();
    //Puts all the pieces together
    for(int i = 0; i < (int)numThreads; ++i)
        finalRender += renders[i];
    //Outputs the final frame
    return finalRender;
}

void printFrame(const string & frame)
{
    cout << frame;
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

void moveBullets(vector<struct bulletInfo> & bullets,
                 vector<vector<entity >> bounds)
{
    for(unsigned int bulletIndex = 0; bulletIndex < bullets.size(); ++bulletIndex)
    {
        bullets[bulletIndex].moveBullet();

       if(!bullets[bulletIndex].legalMove(bounds))
       {
           bullets.erase(bullets.begin() + bulletIndex);
           break;
       }
    }
}

void createBullets(vector<struct bulletInfo> & bullets,
                   playerInfo player)
{
    int U = GetAsyncKeyState(VK_UP);
    int D = GetAsyncKeyState(VK_DOWN);
    int L = GetAsyncKeyState(VK_LEFT);
    int R = GetAsyncKeyState(VK_RIGHT);

    if(keyCheck(U,D,L,R))
    {
           //Prevents stationary bullets
           if((U != 0 && D != 0) ||
              (R != 0 && L != 0)) return;

           struct bulletInfo newBullet(player.xPos, player.yPos, {U,D,L,R});
           //Adds the vector to the list of bullets
           bullets.push_back(newBullet);
    }
}

void moveEnemies(vector<struct enemyInfo> & enemies,
                 playerInfo player,
                 vector<vector<entity >> bounds)
{
    for(unsigned int i = 0; i < enemies.size(); ++i)
    {
        if(enemies[i].speedCounter >= ENEMY_SPEED_DIF)
        {
            enemies[i].moveEnemy(player, bounds);
            enemies[i].speedCounter = 0;
        }
        else enemies[i].speedCounter += enemies[i].speedMod;
    }
}

void uniqueEnemyPosition(vector<struct enemyInfo> & enemies,
                         vector<vector<entity >> bounds)
{
    bool areUnique = true;

    for(unsigned int check = 0; check < enemies.size(); ++check)
    {
        for(unsigned int curr = 0; curr < enemies.size(); ++curr)
        {
            if(check == curr) continue;

            int tempX = enemies[curr].xPos;
            int tempY = enemies[curr].yPos;

            if(enemies[check].xPos == enemies[curr].xPos &&
               enemies[check].yPos == enemies[curr].yPos)
            {
                enemies[curr].xPos += 1 - (rand() % 3);
                enemies[curr].yPos += 1 - (rand() % 3);
                areUnique = false;

                if(!legalPosition(bounds, enemies[curr].xPos, enemies[curr].yPos))
                {
                     if(bounds[tempY][tempX + 1] == wall) enemies[curr].xPos-=1;
                     if(bounds[tempY][tempX - 1] == wall) enemies[curr].xPos+=1;

                     if(bounds[tempY - 1][tempX] == wall) enemies[curr].yPos+=1;
                     if(bounds[tempY + 1][tempX] == wall) enemies[curr].yPos-=1;
                }
            }
        }
    }
    if(!areUnique) uniqueEnemyPosition(enemies, bounds);
}

int randEnemyPos(int Max)
{
    bool isBottomHalf = rand() % 2;
    if(isBottomHalf) return(rand() % ((Max /  2) - BUFFER));
    return ((rand() % ((Max /  2) - BUFFER)) +
            (Max / 2) + 5 );
}

void hitDetection(vector<struct enemyInfo> & enemies,
                  vector<struct bulletInfo> & bullets,
                  playerInfo player,
                  vector<struct deathInfo> & deaths,
                  bool game_Over)
{
    for(int enemyIndex = 0; enemyIndex < (int)enemies.size(); ++enemyIndex)
    {
        if((enemies[enemyIndex].xPos == player.xPos) &&
            (enemies[enemyIndex].yPos == player.yPos)) game_Over = true;

        for(int bulletIndex = 0; bulletIndex < (int)bullets.size(); bulletIndex++)
        {
            //If any bullets position is == to any enemies position
            if((bullets[bulletIndex].xPos == enemies[enemyIndex].xPos) &&
               (bullets[bulletIndex].yPos == enemies[enemyIndex].yPos))
            {
                deathInfo newDeath {enemies[enemyIndex].xPos, enemies[enemyIndex].yPos, START_DEATH_STAGE, (char)178};
                deaths.push_back(newDeath);
                //Remove both the bullet and the enemy
                enemies.erase(enemies.begin() + enemyIndex);
                bullets.erase(bullets.begin() + bulletIndex);
                break;
            }
        }
    }
}

//Generates the enemies with random locations in the
//Bounds set be randEnemyPos, and the amount of the level
void generateEnemies(int level,
                     vector<struct enemyInfo> & enemies,
                     vector<vector<entity> > bounds)
{
    int numEnemies = level * LEVEL_MOD;

    for(int i = 0; i < (int)numEnemies; ++i)
    {
        while(1)
        {
            struct enemyInfo newEnemy(randEnemyPos(XMAX), randEnemyPos(YMAX));
            if(bounds[newEnemy.yPos][newEnemy.xPos] != wall)
            {
                enemies.push_back(newEnemy);
                break;
            }
        }
    }
}

void changeDeaths(vector<struct deathInfo> & deaths)
{
    for(unsigned int i = 0; i < deaths.size(); ++i)
    {
        switch(deaths[i].stage)
        {
        case 3:
            deaths[i].model = (char)178;
            break;
        case 2:
            deaths[i].model = (char)177;
            break;
        case 1:
            deaths[i].model = (char)176;
            break;
        default:
            deaths.erase(deaths.begin() + i);
            break;
        }
        deaths[i].stage--;
    }
}

bool playerSelection()
{
    while(true)
    {
        if(GetAsyncKeyState(VK_SPACE))  return true;
        if(GetAsyncKeyState(VK_ESCAPE)) return false;
    };
}

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

    string frame = "";
    //Fixed rand for testing
    srand(1);

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

        //while(true)
        {
            system("cls");
            system("Color F0");
            cout << readLevel(level) << "\n\t\t\t\t\t";
            Sleep(1000);
            system("Color 0F");
            system("cls");

            frame = generateLevel(bounds, player, bullets, enemies, deaths, MAX_THREADS, true);
            generateEnemies(level, enemies, bounds);
            player.xPos = XMAX / 2;
            player.yPos = YMAX / 2;
            bullets.clear();

            while(true)//while(!game_Over)
            {
                START_CLK;
                frame = generateLevel(bounds, player, bullets, enemies, deaths, MAX_THREADS,false);
                //Sets the print in motion
                system("cls");
                thread printThread(printFrame, std::ref(frame));

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
                enemies.pop_back();

                if(enemies.size() == 0)
                {
                    printThread.join();
                    break;
                }
                ++deathAnimationRate;
                ++enemyMoveRate;
//                if(enemies.size() < 25)
//                    Sleep(REFRESH);
                printThread.join();
                END_CLK;
            }

            if(game_Over)
            {
                system("cls");
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
