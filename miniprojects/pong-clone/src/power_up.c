#include "power_up.h"
#include "paddle.h"
#include <SDL2/SDL.h>

void power_up_init(PowerUp *p, int start_x, int start_y) {
    p->x = start_x;
    p->y = start_y;
    p->dx = 1.2f;
    p->dy = 1.0f;
    p->w = 10;  // Changed from width to w
    p->h = 10;  // Changed from height to h
    p->active = 1;
    p->last_collector = 0;
}

void update_power_up(PowerUp *p, int screen_width, int screen_height) {
    if (!p->active) return;

    p->x += p->dx;
    p->y += p->dy;

    // Bounce off walls
    if (p->x <= 0 || p->x + p->w >= screen_width) p->dx = -p->dx;
    if (p->y <= 0 || p->y + p->h >= screen_height) p->dy = -p->dy;
}

void power_up_draw(SDL_Renderer *renderer, PowerUp *p) {
    SDL_Rect rect = { (int)p->x, (int)p->y, p->w, p->h };  // Changed from width to w
    SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255); // Yellow box
    SDL_RenderFillRect(renderer, &rect);
}

int power_up_collides_with_paddle(PowerUp *p, Paddle *paddle) {
    SDL_Rect powerRect = { (int)p->x, (int)p->y, p->w, p->h };  // Changed from width to w
    SDL_Rect paddleRect = { paddle->x, paddle->y, paddle->w, paddle->h };  // Changed from width/height to w/h
    if (SDL_HasIntersection(&powerRect, &paddleRect)) {
        p->active = 0;
        return 1;
    }
    return 0;
}
