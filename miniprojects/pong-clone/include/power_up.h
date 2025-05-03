#ifndef POWER_UP_H
#define POWER_UP_H

#include <SDL2/SDL.h>
#include "paddle.h"

typedef struct {
    float x, y;
    float dx, dy;
    int w, h;       // Use w and h for PowerUp's dimensions
    int active;
    int last_collector; // Who collected this power-up
} PowerUp;

void power_up_init(PowerUp *p, int start_x, int start_y);
void update_power_up(PowerUp *p, int screen_width, int screen_height);
void power_up_draw(SDL_Renderer *renderer, PowerUp *p);
int power_up_collides_with_paddle(PowerUp *p, Paddle *paddle);

#endif // POWER_UP_H
