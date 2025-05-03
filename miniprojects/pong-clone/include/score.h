#ifndef SCORE_H
#define SCORE_H

#include <SDL2/SDL.h>
#include <stdint.h>

void draw_digit(SDL_Renderer *renderer, int digit, int x, int y);
void draw_score(SDL_Renderer *renderer, int score, int x, int y);

#endif // SCORE_H
