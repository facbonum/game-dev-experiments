/* #ifndef PADDLE_H
#define PADDLE_H

#define PADDLE_WIDTH 10
#define PADDLE_HEIGHT 60

typedef struct {
    int x, y;
    int w, h;
    int dy;
    int score;
} Paddle;

void init_paddle(Paddle *paddle, int x, int y);
void update_paddle(Paddle *paddle, int up_key, int down_key);
void render_paddle(void *renderer, Paddle *paddle);  // abstracted renderer

#endif // PADDLE_H */

#ifndef PADDLE_H
#define PADDLE_H

#define PADDLE_WIDTH 10
#define PADDLE_HEIGHT 60

typedef struct {
    int x, y;    // Position of the paddle
    int w, h;    // Width and Height of the paddle
    int dy;      // Speed of paddle movement (vertical)
    int score;   // Score for the paddle
} Paddle;

// Function declarations for paddle-related operations
void init_paddle(Paddle *paddle, int x, int y);  // Initialize paddle with position
void update_paddle(Paddle *paddle, int up_key, int down_key);  // Update paddle position based on input
void render_paddle(void *renderer, Paddle *paddle);  // Render paddle to the screen

#endif // PADDLE_H
