#include "ball.h"
#include <stdbool.h>
#include <SDL2/SDL.h>

void ball_init(Ball *ball) {
    ball->x = (640 - 10) / 2; // center horizontally
    ball->y = (480 - 10) / 2; // center vertically
    ball->vx = (rand() % 2 == 0) ? 4 : -4;
    ball->vy = (rand() % 2 == 0) ? 2 : -2;
    ball->size = 10;
}

void reset_ball(Ball *ball) {
    ball->x = 640 / 2;
    ball->y = 480 / 2;
    ball->vx = -ball->vx;  // change direction on reset
    ball->vy = -ball->vy;
}

/* bool ball_collides_with_paddle(Ball *ball, Paddle *paddle) {
    return (ball->x < paddle->x + PADDLE_WIDTH &&
            ball->x + ball->size > paddle->x &&
            ball->y < paddle->y + PADDLE_HEIGHT &&
            ball->y + ball->size > paddle->y);
} */
bool ball_collides_with_paddle(Ball *ball, Paddle *paddle) {
    return (ball->x < paddle->x + PADDLE_WIDTH &&
            ball->x + ball->size > paddle->x &&
            ball->y < paddle->y + PADDLE_HEIGHT &&
            ball->y + ball->size > paddle->y);
}


/* void ball_update(Ball *ball, Paddle *p1, Paddle *p2, int *score1, int *score2) {
    ball->x += ball->vx;
    ball->y += ball->vy;

    // Wall collision (top and bottom)
    if (ball->y <= 0 || ball->y + ball->size >= 480) {
        ball->vy = -ball->vy;
    }

    // Paddle collision
    if (ball_collides_with_paddle(ball, p1) || ball_collides_with_paddle(ball, p2)) {
        ball->vx = -ball->vx;
    }

    // Left/right scoring
    if (ball->x + ball->size < 0) {
        (*score2)++;
        ball_init(ball);  // Reinitialize ball
    } else if (ball->x > 640) {
        (*score1)++;
        ball_init(ball);  // Reinitialize ball
    }
}
 */
void ball_update(Ball *ball, Paddle *p1, Paddle *p2, int *score1, int *score2) {
    ball->x += ball->vx;
    ball->y += ball->vy;

    // Wall collision (top and bottom)
    if (ball->y <= 0 || ball->y + ball->size >= 480) {
        ball->vy = -ball->vy;
    }

    // Paddle collision
    if (ball_collides_with_paddle(ball, p1)) {
        // Adjust ball position to prevent it from sticking inside the paddle
        if (ball->vx < 0) {  // Ball moving left
            ball->x = p1->x + PADDLE_WIDTH;  // Position ball next to the paddle
        }
        ball->vx = -ball->vx;  // Reverse X velocity
    }

    if (ball_collides_with_paddle(ball, p2)) {
        // Adjust ball position to prevent it from sticking inside the paddle
        if (ball->vx > 0) {  // Ball moving right
            ball->x = p2->x - ball->size;  // Position ball next to the paddle
        }
        ball->vx = -ball->vx;  // Reverse X velocity
    }

    // Left/right scoring
    if (ball->x + ball->size < 0) {
        (*score2)++;
        ball_init(ball);  // Reinitialize ball
    } else if (ball->x > 640) {
        (*score1)++;
        ball_init(ball);  // Reinitialize ball
    }
}


 void ball_draw(void *renderer, Ball *ball) {
    SDL_Renderer *r = (SDL_Renderer *)renderer;
    SDL_Rect rect = { (int)ball->x, (int)ball->y, ball->size, ball->size };
    SDL_SetRenderDrawColor(r, 255, 255, 255, 255);
    SDL_RenderFillRect(r, &rect);
}
