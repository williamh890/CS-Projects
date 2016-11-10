#ifndef BULLETFUNCS_H_INCLUDED
#define BULLETFUNCS_H_INCLUDED

void moveBullets(vector<struct bulletInfo> & bullets,
                 vector<vector<entity >> bounds)
{
    for(int bulletIndex = 0; bulletIndex < (int)bullets.size(); ++bulletIndex)
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


#endif // BULLETFUNCS_H_INCLUDED
