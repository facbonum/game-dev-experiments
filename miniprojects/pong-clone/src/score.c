#include "score.h"

// 8x8 bitmaps for digits 0–9, inspired by Intellivision GROM-style font
static const uint8_t digit_bitmaps[10][8] = {
    {0x3C, 0x66, 0x6E, 0x76, 0x66, 0x66, 0x66, 0x3C}, // 0
    {0x18, 0x38, 0x18, 0x18, 0x18, 0x18, 0x18, 0x3C}, // 1
    {0x3C, 0x66, 0x06, 0x0C, 0x18, 0x30, 0x60, 0x7E}, // 2
    {0x3C, 0x66, 0x06, 0x1C, 0x06, 0x06, 0x66, 0x3C}, // 3
    {0x0C, 0x1C, 0x2C, 0x4C, 0x7E, 0x0C, 0x0C, 0x0C}, // 4
    {0x7E, 0x60, 0x60, 0x7C, 0x06, 0x06, 0x66, 0x3C}, // 5
    {0x1C, 0x30, 0x60, 0x7C, 0x66, 0x66, 0x66, 0x3C}, // 6
    {0x7E, 0x06, 0x0C, 0x18, 0x30, 0x30, 0x30, 0x30}, // 7
    {0x3C, 0x66, 0x66, 0x3C, 0x66, 0x66, 0x66, 0x3C}, // 8
    {0x3C, 0x66, 0x66, 0x66, 0x3E, 0x06, 0x0C, 0x38}  // 9
};

void draw_digit(SDL_Renderer *renderer, int digit, int x, int y) {
    if (digit < 0 || digit > 9) return;

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    const int scale = 5;

    for (int row = 0; row < 8; ++row) {
        uint8_t bits = digit_bitmaps[digit][row];
        for (int col = 0; col < 8; ++col) {
            if (bits & (1 << (7 - col))) {
                SDL_Rect pixel = {
                    x + col * scale,
                    y + row * scale,
                    scale,
                    scale
                };
                SDL_RenderFillRect(renderer, &pixel);
            }
        }
    }
}


void draw_score(SDL_Renderer *renderer, int score, int x, int y) {
    if (score < 0) score = 0;
    if (score > 99) score = 99;

    int high = (score / 10) % 10;
    int low = score % 10;

    draw_digit(renderer, high, x, y);
    draw_digit(renderer, low, x + 42, y); // 8px wide + 2px spacing
}
