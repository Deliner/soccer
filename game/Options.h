//
// Created by deliner on 07.12.2020.
//

#ifndef SOCCER_OPTIONS_H
#define SOCCER_OPTIONS_H


#define BALL_SIZE 1.0f
#define PLAYER_SIZE (2*BALL_SIZE)
#define PLAYER_PUNCH_SIZE  (3*BALL_SIZE)
#define PLAYER_PUNCH_ANGLE 90.0

#define PLAYER_SPEED (5.0*PLAYER_SIZE)
#define MAX_BALL_SPEED (25.0*PLAYER_SIZE)
#define MIN_BALL_SPEED (6.25*PLAYER_SIZE)
#define BALL_SPEED_DECREASE (6.25*PLAYER_SIZE)

#define FIELD_X_SIZE (110*PLAYER_SIZE)
#define FIELD_Y_SIZE (50*PLAYER_SIZE)

#define GOAL_Y_SIZE (7*PLAYER_SIZE)
#define GOAL_X_SIZE (4*PLAYER_SIZE)

#define INPUT_TIME_UPDATE (1000 / 5)

#define PLAYER_PER_TEAM 1

#define LINE_SIZE BALL_SIZE
#define GAME_X_SIZE  ((LINE_SIZE+ GOAL_X_SIZE+FIELD_X_SIZE+GOAL_X_SIZE+LINE_SIZE)*1.1)
#define GAME_Y_SIZE ((LINE_SIZE+FIELD_Y_SIZE+LINE_SIZE)*1.1)
#endif //SOCCER_OPTIONS_H
