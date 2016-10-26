#include <iostream>
#include <windows.h>
#include <vector>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

using namespace std;

//Used for  Accessing bullets the bullets vector
#define XPOS 0
#define YPOS 1
#define UP 2
#define DOWN 3
#define LEFT 4
#define RIGHT 5
////////////GAME OPTIONS////////////
#define SHOT_DELAY 5
//Delay enemies movements
#define ENEMY_TIMER 2
#define ENEMY_REACTION_TIME 5
//Starting area around player
//Free of enemies
#define BUFFER 4
//How many enemies added per level
#define LEVEL_MOD 4
//Level Size
#define XMAX 40
#define YMAX 23

#define CLOCK 60

//Holds enemies current location
struct enemy
{
    int xPos;
    int yPos;
    bool X_tendency;
};

//Checks if you and an enemy take up the same location
bool areYouDead(int xPos, int yPos,
                vector<enemy> enemies)
{
    for(int i = 0; i < (int)enemies.size(); ++i)
    {
        if(xPos == enemies[i].xPos && yPos == enemies[i].yPos) return true;
    }
    return false;
}

//Checks if bullet is vertical '|'
bool verticalBullet(int up, int down,
                    int left, int right)
{
    return((up != 0 || down != 0) &&
           (left == 0 && right == 0));
}
//Checks if bullet is horizontal '-'
bool horizBullet(int up, int down,
                 int left, int right)
{
    return ((left != 0 || right != 0) &&
           (down == 0 && up == 0));
}
//Checks if bullet is '/'
bool posSlopeBullet(int up, int down,
                    int left, int right)
{
    return ((up != 0 && right != 0) ||
            (down != 0 && left != 0));
}

//Generates values for stating enemy position
//Outside a given buffer zone, specified by
//the #define BUFFER value
int randEnemyPos(int Max)
{
    bool isBottomHalf = rand() % 2;
    if(isBottomHalf) return(rand() % ((Max /  2) - BUFFER));
    return ((rand() % ((Max /  2) - BUFFER)) +
            (Max / 2) + 5 );

}

//Generates the enemies with random locations in the
//Bounds set be randEnemyPos, and the amount of the level
void generateLevel(int level, vector<enemy> & enemies,
                   int xMax, int yMax)
{
    int numEnemies = level * LEVEL_MOD;

    for(int i = 0; i < numEnemies; ++i)
    {
        struct enemy newEnemy;
        newEnemy.xPos = randEnemyPos(xMax);
        newEnemy.yPos = randEnemyPos(yMax);
        //newEnemy.X_tendency = rand() % 2;
        enemies.push_back(newEnemy);
    }

}

//Checks if any of the arrow keys are pressed
bool keyCheck(int U, int D,
              int L, int R)
{
    //If any of the keys are pressed returns true
    if(U    != 0 ||
       D  != 0 ||
       L  != 0 ||
       R != 0) return true;
       //No key pressed
       return false;
}

//Renders the current gamestate by creating a
//Single string then printing it, this greatly
//Improves performance
void draw(int xMax, int yMax,
          int xPos, int yPos,
          vector<vector<int> > bullets,
          vector<enemy> & enemies,
          int score)
{
    string render = "";
    for(int j = 0; j <= yMax; ++j)   //Down through rows
        {
            //Prints the top
            if(j == 0 || j == yMax)
            {
                //By default, runs across the top bound
                for(int i = 0; i <= xMax ; ++i)
                {
                    render += "-";
                }
                render += "\n";
                continue;
            }
            //Prints the side for each row
            render += "l";  //Left side of the bound

            for(int i = 1; i < xMax; ++i)   //Across the rows
            {
                int charsPrinted = 0;
                //Checks if player position
                if(i == xPos && j == yPos)
                {
                    render += "@";
                    continue;
                }

                //Checks if a bullet is present
                for(int bulletIndex = 0; bulletIndex < (int)bullets.size(); bulletIndex++)
                {
                        if(i == bullets[bulletIndex][XPOS] && j == bullets[bulletIndex][YPOS])
                        {
                            /*
                                Bullet types
                                    \|/
                                    -@-
                                    /|\
                            {xPos, yPos, U, D, L, R}
                            */

                            int U = bullets[bulletIndex][UP];
                            int D = bullets[bulletIndex][DOWN];
                            int L = bullets[bulletIndex][LEFT];
                            int R = bullets[bulletIndex][RIGHT];

                            //What type of bullet to print
                            if(verticalBullet(U,D,L,R))
                            {
                                render += "|";
                            }
                            else if(horizBullet(U,D,L,R))
                            {
                                render += "-";
                            }
                            else if(posSlopeBullet(U,D,L,R))
                            {
                                render += "/";
                            }
                            else
                            {
                                render += "\\";
                            }
                            charsPrinted++;
                        }
                }
                //Checks if enemy position
                for(int enemyIndex = 0; enemyIndex < (int)enemies.size(); ++enemyIndex)
                {
                    if(i == enemies[enemyIndex].xPos && j == enemies[enemyIndex].yPos)
                    {
                        render += "x";
                        charsPrinted++;
                    }
                }
                //If both bullets and enemies are printed on the same line
                if(charsPrinted)
                {
                    i += (charsPrinted - 1);
                    continue;
                }
                else render += " ";
            }
            render += "l\n"; //Moves to print the next row
        }
        cout << render;
        cout << "SCORE: " << score;
}
//Moves the character according to what the
//W,A,S,D combinations are
void moveCharacter(int & xPos, int & yPos,
                   int xMax, int yMax)
{
    int U = GetAsyncKeyState(0x57); //W virtual key code
    int D = GetAsyncKeyState(0x53); //S virtual key code
    int L = GetAsyncKeyState(0x41); //A virtual key code
    int R = GetAsyncKeyState(0x44); //D virtual key code

    if(U != 0 && yPos != 1)         yPos-=1;
    if(D != 0 && yPos != yMax - 1)  yPos+=1;
    if(L != 0 && xPos != 2)         xPos-=1;
    if(R != 0 && xPos != xMax - 2)  xPos+=1;
}
//Creates bullets when the arrow keys are pressed
//Shoots in the direction pressed by combination
//of Arrow keys
void createBullets(vector<vector<int> > & bullets,
                   int xPos, int yPos)
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
           //Stores the information to a vector
           vector<int> newBullet {xPos, yPos, U, D, L, R};
           //Adds the vector to the list of bullets
           bullets.push_back(newBullet);
        }
}
/*
*    Moves the bullets on their respective trajectories
*    specified 2 through 5 index's in the bullets inner
*    vector. Also checks if the bullets new position is
*    That of an enemies, if yes, then deletes both the
*    bullet and the enemy, as well as increases score.
*/
void moveBullets(vector<vector<int> > & bullets,
                 vector<enemy> & enemies,
                 int xMax, int yMax,
                 int & score)
    {
        for(int bulletIndex = 0; bulletIndex < (int)bullets.size(); bulletIndex++)
        {
            int bulletSpeed = 1;
            //Move bullet up
            if(bullets[bulletIndex][UP])
            {
                bullets[bulletIndex][YPOS]-=bulletSpeed;
            }
            //Move bullet down
            if(bullets[bulletIndex][DOWN])
            {
                bullets[bulletIndex][YPOS]+=bulletSpeed;
            }
            //Move bullet left
            if(bullets[bulletIndex][LEFT])
            {
                bullets[bulletIndex][XPOS]-=(bulletSpeed);
            }
            //Move bullet right
            if(bullets[bulletIndex][RIGHT])
            {
                bullets[bulletIndex][XPOS]+=(bulletSpeed);
            }
            //If out of bounds
            if(bullets[bulletIndex][XPOS] == xMax ||
               bullets[bulletIndex][YPOS] == yMax ||
               bullets[bulletIndex][XPOS] == 0 ||
               bullets[bulletIndex][YPOS] == 0)
            {
                //Removes the bullet from the tracking list
                bullets.erase(bullets.begin()+bulletIndex);
            }
            //Checks if enemy hit
            for(int enemyIndex = 0; enemyIndex < (int)enemies.size(); ++enemyIndex)
            {
                //If any bullets position is == to any enemies position
                if((bullets[bulletIndex][XPOS] == enemies[enemyIndex].xPos) &&
                   (bullets[bulletIndex][YPOS] == enemies[enemyIndex].yPos))
                {
                    //Remove both the bullet and the enemy
                    enemies.erase(enemies.begin() + enemyIndex);
                    bullets.erase(bullets.begin() + bulletIndex);
                    //MORE POINTS!!!!
                    ++score;
                }
            }
        }
    }

//Moves the enemies closer to the players location
//Slowed down by the moveEnemyCounter to make game
//not impossible
void moveEnemies(vector<enemy> & enemies,
                 vector<vector<int> > bullets,
                 vector<vector<int> > prevPositions,
                 int xPos, int yPos)
{
    for(int i = 0; i < (int)enemies.size(); ++i)
    {
        int enemyXpos = enemies[i].xPos;
        int enemyYpos = enemies[i].yPos;
        //bool direction  = rand() %  2;

        //prevPositions.size() - ENEMY_REACTION_TIME
        int xPos = prevPositions[0][0];
        int yPos = prevPositions[0][1];

        //move enemies closer to player
        if(enemyXpos < xPos) {enemies[i].xPos++;}
        if(enemyXpos > xPos) {enemies[i].xPos--;}

        if(enemyYpos < yPos) {enemies[i].yPos++;}
        if(enemyYpos > yPos) {enemies[i].yPos--;}

        //Checks if bullet hit an enemy

    }
}
//Shell function with all bullet related action
//Pretty much just to clean up main
void bulletStage(vector<vector<int> > & bullets,
                 vector<enemy> & enemies,
                 int moveEnemyCounter,
                 int & xMax, int & yMax,
                 int & xPos, int & yPos,
                 bool & bulletFired,
                 int & fireRate,
                 int & score)
{
    if(fireRate >= SHOT_DELAY)
        {
            //If the user presses space and one of the arrow keys is pressed
            //Fires a 'o' in the direction of the pressed keys
            createBullets(bullets, xPos, yPos);
            //Resets
            bulletFired = true;
            fireRate = 0;
        }
        //Delay for next bullet to fire
        if(bulletFired) fireRate++;

        //So bullet can fire whenever the space bar is hit after a pause
        if(bulletFired == SHOT_DELAY)
        {
            bulletFired = false;
            fireRate = SHOT_DELAY + 1;
        }

        //Moves bullets in the direction they were fired in
        moveBullets(bullets, enemies, xMax, yMax, score);
}

void makePrePositions(vector<vector<int >> & prevPositions,
                       int xPos, int yPos)
{
    for(int i = 0; i < ENEMY_REACTION_TIME; ++i)
    {
        vector<int> currentPos {xPos, yPos};
        prevPositions.push_back(currentPos);
    }
}

int main()
{
    system("COLOR F0");
    srand(time(NULL));

    /////////////////VARIABLES////////////
    int level = 1;  //Level dictates the num of enemies
    int score = 0;  //Number of enemies killed

    int xMax = XMAX;  //X Dimensions
    int yMax = YMAX;  //Y Dimensions

    int xPos = xMax / 2; //Starting Player x Position
    int yPos = yMax / 2; //Starting Player y Position

    vector<vector<int> > prevPositions; //To put a delay on enemies reacting to your movement

    vector<vector<int> > bullets;  //{xPos,yPos,up,down,left,right}

    int fireRate = SHOT_DELAY + 1; //To slow down fire rate
    bool bulletFired = false;

    vector<enemy> enemies;  //Keeps track of all the enemies

    int moveEnemyCounter = 0; //Delay enemy movement

    bool didYouWin = false; //Checks if you won the level

    ////////////////////////////////////////////
    /////////////////GAME LOOP//////////////////
    ////////////////////////////////////////////

    while(true)
    {
        ///////////////GENERATE////////////////
        generateLevel(level, enemies, xMax, yMax);
        makePrePositions(prevPositions, xPos, yPos);

        /////////////////RESET//////////////////
        didYouWin = false;
        xPos = xMax / 2;
        yPos = yMax / 2;
        bullets.clear();

        //////////////LEVEL LOOP////////////
        while(!areYouDead(xPos, yPos, enemies))
        {
            /////////////////DRAW STAGE////////////////

            draw(xMax, yMax,
                 xPos, yPos,
                 bullets,
                 enemies,
                 score);

            //////////////////CHARACTER STAGE///////////

            moveCharacter(xPos, yPos,
                          xMax, yMax);

            //////////////////BULLETSTAGE////////////////

            bulletStage(bullets,
                        enemies,
                        moveEnemyCounter,
                        xMax, yMax,
                        xPos, yPos,
                        bulletFired, fireRate,
                        score);

            /////////////////ENEMY STAGE////////////////

            if(moveEnemyCounter == ENEMY_TIMER)
            {
                moveEnemies(enemies, bullets,
                            prevPositions,
                            xPos, yPos);

                moveEnemyCounter = 0; //Resets Delay
            }

            //////////////////RESET/EXIT////////////////

            Sleep(CLOCK);
            system("cls");

            if(enemies.size() == 0) //If all dead
            {
                didYouWin = true;
                break;
            }

            moveEnemyCounter++; //Timer to slow enemies

            vector<int> currentPos {xPos, yPos};
            prevPositions.push_back(currentPos);
            prevPositions.erase(prevPositions.begin());

            cout << prevPositions.size() << endl
                 << bullets.size() << endl
                 << enemies.size() << endl;
                 //<< bullets[0].size() << endl;
        }

        if(!didYouWin) break;
        cout << "\n\n\n\n\t\tLEVEL " << level << " COMPLETE" << endl;

        Sleep(1500);
        level++;
        prevPositions.clear();

    }
    //You will always lose...
    cout << "\n\n\n\n\t\tYOU LOSE...\n" << endl;
    cout << "\t      YOUR SCORE: " << score << endl;

    Sleep(10000);

    return 0;

}
