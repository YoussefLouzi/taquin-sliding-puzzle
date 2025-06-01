#include "functions.h"

// Rendering functions
void render_background(void) {
    SDL_Color bg = COLOR_BACKGROUND;
    SDL_SetRenderDrawColor(game.renderer, bg.r, bg.g, bg.b, bg.a);
    SDL_RenderClear(game.renderer);
}

void render_tile(int x, int y, int value) {
    int tile_size = get_tile_size();
    int screen_x, screen_y;
    board_to_screen_coords(x, y, &screen_x, &screen_y);
    
    SDL_Rect rect = {screen_x, screen_y, tile_size, tile_size};
    
    if (value == 0) {
        // Empty tile
        SDL_Color empty = COLOR_EMPTY;
        SDL_SetRenderDrawColor(game.renderer, empty.r, empty.g, empty.b, empty.a);
        SDL_RenderFillRect(game.renderer, &rect);
    } else {
        // Number tile
        if (value <= MAX_TEXTURES && game.number_textures[value - 1]) {
            SDL_RenderCopy(game.renderer, game.number_textures[value - 1], NULL, &rect);
        } else {
            // Fallback: colored rectangle
            SDL_Color tile = COLOR_TILE;
            SDL_SetRenderDrawColor(game.renderer, tile.r, tile.g, tile.b, tile.a);
            SDL_RenderFillRect(game.renderer, &rect);
        }
    }
    
    // Draw border
    SDL_Color border = COLOR_BORDER;
    SDL_SetRenderDrawColor(game.renderer, border.r, border.g, border.b, border.a);
    SDL_RenderDrawRect(game.renderer, &rect);
}

void render_game(void) {
    render_background();
    
    // Render all tiles
    for (int y = 0; y < game.board_size; y++) {
        for (int x = 0; x < game.board_size; x++) {
            render_tile(x, y, game.board[x][y]);
        }
    }
    
    render_ui_elements();
    SDL_RenderPresent(game.renderer);
}

void render_menu(void) {
    render_background();
    
    // Render menu background if available
    if (game.ui_textures[0]) {
        SDL_RenderCopy(game.renderer, game.ui_textures[0], NULL, NULL);
    }
    
    SDL_RenderPresent(game.renderer);
}

void render_win_screen(void) {
    render_background();
    
    // Render win screen if available
    if (game.ui_textures[4]) {
        SDL_RenderCopy(game.renderer, game.ui_textures[4], NULL, NULL);
    }
    
    SDL_RenderPresent(game.renderer);
}

void render_ui_elements(void) {
    // This function can be expanded to render score, timer, etc.
    // For now, it's a placeholder for future UI elements
}

// Utility functions
int get_tile_size(void) {
    int game_area_size = (WINDOW_HEIGHT < WINDOW_WIDTH) ? WINDOW_HEIGHT - 100 : WINDOW_WIDTH - 100;
    return game_area_size / game.board_size;
}

void screen_to_board_coords(int screen_x, int screen_y, int *board_x, int *board_y) {
    int tile_size = get_tile_size();
    int offset_x = (WINDOW_WIDTH - (tile_size * game.board_size)) / 2;
    int offset_y = (WINDOW_HEIGHT - (tile_size * game.board_size)) / 2;
    
    *board_x = (screen_x - offset_x) / tile_size;
    *board_y = (screen_y - offset_y) / tile_size;
}

void board_to_screen_coords(int board_x, int board_y, int *screen_x, int *screen_y) {
    int tile_size = get_tile_size();
    int offset_x = (WINDOW_WIDTH - (tile_size * game.board_size)) / 2;
    int offset_y = (WINDOW_HEIGHT - (tile_size * game.board_size)) / 2;
    
    *screen_x = offset_x + (board_x * tile_size);
    *screen_y = offset_y + (board_y * tile_size);
}

void get_empty_position(int *x, int *y) {
    *x = game.empty_x;
    *y = game.empty_y;
}

// Animation functions
void start_tile_animation(int from_x, int from_y, int to_x, int to_y, int tile_value) {
    game.is_animating = SDL_TRUE;
    game.animation_progress = 0;
    game.animation_start_x = from_x;
    game.animation_start_y = from_y;
    game.animation_end_x = to_x;
    game.animation_end_y = to_y;
    game.animation_tile = tile_value;
}

void update_animations(void) {
    if (!game.is_animating) {
        return;
    }
    
    game.animation_progress += ANIMATION_SPEED;
    
    if (game.animation_progress >= 100) {
        game.is_animating = SDL_FALSE;
        game.animation_progress = 0;
    }
}

// Input handling
void handle_mouse_click(int mouse_x, int mouse_y) {
    if (game.state != GAME_STATE_PLAYING || game.is_animating) {
        return;
    }
    
    int board_x, board_y;
    screen_to_board_coords(mouse_x, mouse_y, &board_x, &board_y);
    
    if (board_x >= 0 && board_x < game.board_size && 
        board_y >= 0 && board_y < game.board_size) {
        
        if (make_move(board_x, board_y)) {
            if (check_win_condition()) {
                game.state = GAME_STATE_WIN;
                save_best_score();
            }
        }
    }
}

void handle_game_input(SDL_Event *event) {
    switch (event->type) {
        case SDL_MOUSEBUTTONDOWN:
            if (event->button.button == SDL_BUTTON_LEFT) {
                handle_mouse_click(event->button.x, event->button.y);
            }
            break;
            
        case SDL_KEYDOWN:
            switch (event->key.keysym.sym) {
                case SDLK_ESCAPE:
                    game.state = GAME_STATE_MENU;
                    break;
                case SDLK_r:
                    reset_game(game.board_size);
                    break;
                case SDLK_n:
                    shuffle_board();
                    game.stats.moves = 0;
                    break;
            }
            break;
    }
}

void handle_menu_input(SDL_Event *event) {
    switch (event->type) {
        case SDL_KEYDOWN:
            switch (event->key.keysym.sym) {
                case SDLK_3:
                    reset_game(3);
                    break;
                case SDLK_4:
                    reset_game(4);
                    break;
                case SDLK_5:
                    reset_game(5);
                    break;
                case SDLK_ESCAPE:
                case SDLK_q:
                    exit(0);
                    break;
            }
            break;
    }
}

// Statistics and settings (placeholder implementations)
void update_stats(void) {
    // Update game timer and other stats
    // This would be called in the main game loop
}

void save_best_score(void) {
    int size = game.board_size;
    if (game.stats.best_moves[size] == -1 || game.stats.moves < game.stats.best_moves[size]) {
        game.stats.best_moves[size] = game.stats.moves;
    }
    
    if (game.stats.best_time[size] == -1 || game.stats.time_seconds < game.stats.best_time[size]) {
        game.stats.best_time[size] = game.stats.time_seconds;
    }
    
    save_settings();
}

void load_best_scores(void) {
    // Load from file - placeholder implementation
    // In a full implementation, this would read from a save file
}

void load_settings(void) {
    // Load settings from file - placeholder implementation
}

void save_settings(void) {
    // Save settings to file - placeholder implementation
}
