#include "score.h"

void render_scores(SDL_Renderer *renderer, int p1_score, int p2_score, int screen_width) {
    draw_score(renderer, p1_score, 10, 10);
    draw_score(renderer, p2_score, screen_width - 40, 10);
}
