
#ifndef CONSTANTS_H
#define CONSTANTS_H

#ifdef _WIN32
    #include <SDL.h>
#else
    #include <SDL2/SDL.h>
#endif

// Game constants
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define MAX_BOARD_SIZE 5
#define MIN_BOARD_SIZE 3
#define MAX_TEXTURES 25
#define ANIMATION_SPEED 8
#define SHUFFLE_MOVES 1000

// Colors (RGBA)
#define COLOR_BACKGROUND {30, 30, 30, 255}
#define COLOR_TILE {70, 130, 180, 255}
#define COLOR_EMPTY {50, 50, 50, 255}
#define COLOR_BORDER {200, 200, 200, 255}
#define COLOR_TEXT {255, 255, 255, 255}
#define COLOR_BUTTON {100, 149, 237, 255}
#define COLOR_BUTTON_HOVER {135, 206, 250, 255}

// Game states
typedef enum {
    GAME_STATE_MENU,
    GAME_STATE_PLAYING,
    GAME_STATE_PAUSED,
    GAME_STATE_WIN,
    GAME_STATE_SETTINGS
} GameState;

// Game statistics
typedef struct {
    int moves;
    int time_seconds;
    int best_moves[MAX_BOARD_SIZE + 1];  // Index by board size
    int best_time[MAX_BOARD_SIZE + 1];   // Index by board size
} GameStats;

// Game data structure
typedef struct {
    int board_size;
    int board[MAX_BOARD_SIZE][MAX_BOARD_SIZE];
    SDL_Texture* number_textures[MAX_TEXTURES];
    SDL_Texture* ui_textures[6];  // Menu textures
    SDL_Renderer* renderer;
    SDL_Window* window;
    GameState state;
    GameStats stats;
    int empty_x, empty_y;  // Position of empty tile
    SDL_bool is_animating;
    int animation_progress;
    int animation_start_x, animation_start_y;
    int animation_end_x, animation_end_y;
    int animation_tile;
} GameData;

// Global game instance
extern GameData game;

#endif // CONSTANTS_H


