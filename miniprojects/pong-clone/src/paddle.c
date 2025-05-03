#include "paddle.h"
#include <SDL2/SDL.h>

// Initialize paddle with the given x, y position
void init_paddle(Paddle *paddle, int x, int y) {
    paddle->x = x;               // Set initial x position
    paddle->y = y;               // Set initial y position
    paddle->w = PADDLE_WIDTH;    // Set paddle width
    paddle->h = PADDLE_HEIGHT;   // Set paddle height
    paddle->dy = 6;              // Set paddle speed (how fast it moves vertically)
    paddle->score = 0;           // Initialize score to 0
}

// Update paddle position based on input keys
void update_paddle(Paddle *paddle, int up_key, int down_key) {
    if (up_key && paddle->y > 0) {  // Move up (avoid going off the top)
        paddle->y -= paddle->dy;
    }
    if (down_key && paddle->y + paddle->h < 480) {  // Move down (avoid going off the bottom)
        paddle->y += paddle->dy;
    }
}

// Render paddle on the screen using SDL
void render_paddle(void *renderer, Paddle *paddle) {
    SDL_Renderer *sdl_renderer = (SDL_Renderer *)renderer;
    SDL_Rect rect = { paddle->x, paddle->y, paddle->w, paddle->h };  // Define paddle rectangle
    SDL_SetRenderDrawColor(sdl_renderer, 255, 255, 255, 255);  // Set color to white
    SDL_RenderFillRect(sdl_renderer, &rect);  // Render the paddle
}
