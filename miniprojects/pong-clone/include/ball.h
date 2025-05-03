#ifndef BALL_H
#define BALL_H

#include "paddle.h"

typedef struct {
    float x, y;
    float vx, vy;   // velocity on x and y axis
    int size;
} Ball;

void ball_init(Ball *b);
void ball_update(Ball *b, Paddle *p1, Paddle *p2, int *score1, int *score2);
void ball_draw(void *renderer, Ball *b);
bool ball_collides_with_paddle(Ball *ball, Paddle *paddle);
void reset_ball(Ball *b);

#endif // BALL_H
