#ifndef GAME_SETTINGS_H_INCLUDED
#define GAME_SETTINGS_H_INCLUDED

#define XMAX 160
#define YMAX 50

#define X_CORNER 6
#define Y_CORNER 5
#define WALL_LENGTH 10

#define SHOT_DELAY 16
#define PLAYER_SPEED 2
//Delay enemies movements
#define ENEMY_SPEED 2
#define ENEMY_SPEED_DIF 2
#define ENEMY_REACTION_TIME 25
#define DECTECTION_RANGE 40
#define START_DEATH_STAGE 3
#define DEATH_SPEED 16

#define BUFFER 5

#define LEVEL_MOD 10
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
    death,
    power_up
};


#endif // GAME_SETTINGS_H_INCLUDED
