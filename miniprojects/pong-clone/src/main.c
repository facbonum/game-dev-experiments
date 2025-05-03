#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "score_display.h"
#include "paddle.h"
#include "ball.h"
#include "score.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int SCREEN_WIDTH = 640;
int SCREEN_HEIGHT = 480;

void draw_dashed_net(SDL_Renderer *renderer, int screen_width, int screen_height) {
    int line_width = 2; // The width of the dashes
    int dash_gap = 6;   // The gap between each dash
    int start_y = -2 * (screen_height / 4) / 2 - dash_gap / 2; // Starting Y position for the center line

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // Set the color to white for the net

    // Draw the dashed line vertically along the middle of the screen
    for (int y = start_y; y < screen_height; y += dash_gap + line_width) {
        SDL_Rect dash = {screen_width / 2 - line_width / 2, y, line_width, line_width};
        SDL_RenderFillRect(renderer, &dash);
    }
}

int main() {
    srand(time(NULL));

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Window *window = SDL_CreateWindow("Pong Clone", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (!window) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    if (TTF_Init() == -1) {
        printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    TTF_Font *font = TTF_OpenFont("C:\\Windows\\Fonts\\lucon.ttf", 24);
    if (!font) {
        printf("Failed to load font! SDL_ttf Error: %s\n", TTF_GetError());
        TTF_Quit();
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    Paddle player1, player2;
    Ball ball;
    int score1 = 0;
    int score2 = -1;

    init_paddle(&player1, 20, 200);  // Player 1 starting position
    init_paddle(&player2, SCREEN_WIDTH - 30, 200);  // Player 2 starting position
    reset_ball(&ball);

    SDL_Event e;
    int quit = 0;
    const Uint8 *state = SDL_GetKeyboardState(NULL);

    while (!quit) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                quit = 1;
            }
        }

        update_paddle(&player1, state[SDL_SCANCODE_W], state[SDL_SCANCODE_S]);
        update_paddle(&player2, state[SDL_SCANCODE_UP], state[SDL_SCANCODE_DOWN]);

        ball_update(&ball, &player1, &player2, &score1, &score2);

        if (ball_collides_with_paddle(&ball, &player1)) {
            ball.vx = -ball.vx;
        }
        if (ball_collides_with_paddle(&ball, &player2)) {
            ball.vx = -ball.vx;
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        draw_dashed_net(renderer, 640, 480); // Draw the dashed center line

        render_paddle(renderer, &player1);
        render_paddle(renderer, &player2);
        ball_draw(renderer, &ball);

        draw_score(renderer, score1, 10, 10);
        draw_score(renderer, score2, SCREEN_WIDTH - 84, 10);

        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }

    TTF_CloseFont(font);
    TTF_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
