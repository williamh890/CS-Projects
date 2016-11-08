#ifndef GAME_SETTINGS_H_INCLUDED
#define GAME_SETTINGS_H_INCLUDED

#define XMAX 80
#define YMAX 25

#define SHOT_DELAY 16
#define PLAYER_SPEED 4
//Delay enemies movements
#define ENEMY_SPEED 3
#define ENEMY_SPEED_DIF 2
#define ENEMY_REACTION_TIME 15
#define DECTECTION_RANGE 25
#define START_DEATH_STAGE 3
#define DEATH_SPEED 16

#define BUFFER 5

#define LEVEL_MOD 5
#define LEVELS_TO_WIN 3

#define REFRESH 30

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


#endif // GAME_SETTINGS_H_INCLUDED
