#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#ifdef _WIN32
    #include <SDL.h>
#else
    #include <SDL2/SDL.h>
#endif
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include "constant.h"

// Error handling
void SDL_ExitWithError(const char *message);

// Game initialization and cleanup
int init_game(void);
void cleanup_game(void);
int load_textures(void);
void free_textures(void);

// Game logic
void init_board(int size);
void shuffle_board(void);
int is_valid_move(int x, int y);
int make_move(int x, int y);
int check_win_condition(void);
void reset_game(int size);

// Rendering
void render_game(void);
void render_menu(void);
void render_win_screen(void);
void render_tile(int x, int y, int value);
void render_background(void);
void render_ui_elements(void);

// Input handling
void handle_menu_input(SDL_Event *event);
void handle_game_input(SDL_Event *event);
void handle_mouse_click(int mouse_x, int mouse_y);

// Animation
void update_animations(void);
void start_tile_animation(int from_x, int from_y, int to_x, int to_y, int tile_value);

// Utility functions
void get_empty_position(int *x, int *y);
int get_tile_size(void);
void screen_to_board_coords(int screen_x, int screen_y, int *board_x, int *board_y);
void board_to_screen_coords(int board_x, int board_y, int *screen_x, int *screen_y);

// Statistics and scoring
void update_stats(void);
void save_best_score(void);
void load_best_scores(void);

// Settings and configuration
void load_settings(void);
void save_settings(void);

#endif // FUNCTIONS_H
