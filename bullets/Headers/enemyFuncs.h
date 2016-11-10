#ifndef ENEMYFUNCS_H_INCLUDED
#define ENEMYFUNCS_H_INCLUDED

void moveEnemies(vector<struct enemyInfo> & enemies,
                 playerInfo player,
                 vector<vector<entity >> bounds)
{
    for(int i = 0; i < (int)enemies.size(); ++i)
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

    for(int check = 0; check < (int)enemies.size(); ++check)
    {
        for(int curr = 0; curr < (int)enemies.size(); ++curr)
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
                  bool & game_Over)
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

    for(int i = 0; i < numEnemies; ++i)
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
    for(int i = 0; i < (int)deaths.size(); ++i)
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

#endif // ENEMYFUNCS_H_INCLUDED
