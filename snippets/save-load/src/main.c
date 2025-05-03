/* saveloadtest.c
---Movement and save state test---
Saves to save.dat, can load immediately
Save = S
Load = L
Move 4 frames faster = Spacebar
Quit = Close window
*/
#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>

#define WIN_W 800
#define WIN_H 600

unsigned char memory[65536];
int direction = 1;
int target = 128;
int score = 0;
TTF_Font *font = NULL;

// Save memory to file
void save_memory(const char *filename) {
    FILE *f = fopen(filename, "wb");
    if (f) {
        fwrite(memory, 1, sizeof(memory), f);
        fclose(f);
    }
}

// Load memory from file
void load_memory(const char *filename) {
    FILE *f = fopen(filename, "rb");
    if (f) {
        fread(memory, 1, sizeof(memory), f);
        fclose(f);
    }
}

// Spawn a new target
void spawn_target(void) {
    target = rand() % 256;
}

// Check for hitting the target
void check_target_hit(void) {
    if (abs(memory[0x1234] - target) < 4) {
        score++;
        spawn_target();
    }
}

void update(void) {
    const Uint8 *keys = SDL_GetKeyboardState(NULL);

    int speed = 1;
    if (keys[SDL_SCANCODE_SPACE]) speed = 4;

    memory[0x1234] += direction * speed;

    if (memory[0x1234] >= 255) {
        memory[0x1234] = 255;
        direction = -1;
    } else if (memory[0x1234] <= 0) {
        memory[0x1234] = 0;
        direction = 1;
    }

    if (keys[SDL_SCANCODE_S]) save_memory("save.dat");
    if (keys[SDL_SCANCODE_L]) load_memory("save.dat");

    check_target_hit();
}

void draw_text(SDL_Renderer *r, const char *text, int x, int y) {
    SDL_Color color = {255, 255, 255, 255}; // white
    SDL_Surface *surf = TTF_RenderText_Solid(font, text, color);
    SDL_Texture *tex = SDL_CreateTextureFromSurface(r, surf);

    SDL_Rect dst = { x, y, surf->w, surf->h };
    SDL_RenderCopy(r, tex, NULL, &dst);

    SDL_FreeSurface(surf);
    SDL_DestroyTexture(tex);
}

void render(SDL_Renderer *r) {
    SDL_SetRenderDrawColor(r, 0, 0, 0, 255);
    SDL_RenderClear(r);

    int x = (memory[0x1234] * (WIN_W - 20)) / 256;
    int y = WIN_H / 2 - 10;

    SDL_SetRenderDrawColor(r, 255, 0, 0, 255);
    SDL_Rect rect = { x, y, 20, 20 };
    SDL_RenderFillRect(r, &rect);

    int tx = (target * (WIN_W - 20)) / 256;
    SDL_SetRenderDrawColor(r, 0, 255, 0, 255);
    SDL_Rect target_rect = { tx, y, 20, 20 };
    SDL_RenderFillRect(r, &target_rect);

    // Draw score
    char buf[32];
    snprintf(buf, sizeof(buf), "Score: %d", score);
    draw_text(r, buf, 10, 10);

    SDL_RenderPresent(r);
}

int main(void) {
    SDL_SetMainReady();
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();

    SDL_Window *win = SDL_CreateWindow("MiniGear Test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIN_W, WIN_H, 0);
    SDL_Renderer *ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);

    font = TTF_OpenFont("C:/Windows/Fonts/consola.ttf", 24); // Using system Consolas font
    if (!font) {
        printf("Failed to load font: %s\n", TTF_GetError());
        return 1;
    }

    spawn_target();
    int running = 1;
    while (running) {
        SDL_Event e;
        while (SDL_PollEvent(&e))
            if (e.type == SDL_QUIT) running = 0;

        update();
        render(ren);

        SDL_Delay(16);
    }

    TTF_CloseFont(font);
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    TTF_Quit();
    SDL_Quit();
    return 0;
}
