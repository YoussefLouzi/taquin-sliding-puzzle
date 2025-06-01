#include "functions.h"

// Global game instance
GameData game = {0};

// Error handling
void SDL_ExitWithError(const char *message) {
    SDL_Log("ERROR: %s > %s\n", message, SDL_GetError());
    cleanup_game();
    exit(EXIT_FAILURE);
}

// Game initialization
int init_game(void) {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        fprintf(stderr, "SDL_Init Error: %s\n", SDL_GetError());
        return 0;
    }

    // Create window
    game.window = SDL_CreateWindow("Taquin - Sliding Puzzle",
                                   SDL_WINDOWPOS_CENTERED,
                                   SDL_WINDOWPOS_CENTERED,
                                   WINDOW_WIDTH, WINDOW_HEIGHT,
                                   SDL_WINDOW_SHOWN);
    if (!game.window) {
        SDL_ExitWithError("Failed to create window");
        return 0;
    }

    // Create renderer
    game.renderer = SDL_CreateRenderer(game.window, -1, 
                                       SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!game.renderer) {
        SDL_ExitWithError("Failed to create renderer");
        return 0;
    }

    // Initialize game state
    game.state = GAME_STATE_MENU;
    game.board_size = 3;
    game.is_animating = SDL_FALSE;
    
    // Initialize stats
    memset(&game.stats, 0, sizeof(GameStats));
    for (int i = 0; i <= MAX_BOARD_SIZE; i++) {
        game.stats.best_moves[i] = -1;
        game.stats.best_time[i] = -1;
    }

    // Load textures and settings
    if (!load_textures()) {
        return 0;
    }
    
    load_settings();
    load_best_scores();
    
    return 1;
}

void cleanup_game(void) {
    free_textures();
    
    if (game.renderer) {
        SDL_DestroyRenderer(game.renderer);
        game.renderer = NULL;
    }
    
    if (game.window) {
        SDL_DestroyWindow(game.window);
        game.window = NULL;
    }
    
    SDL_Quit();
}

int load_textures(void) {
    // Load number textures
    for (int i = 0; i < MAX_TEXTURES - 1; i++) {
        char filename[64];
        snprintf(filename, sizeof(filename), "images/numbers/N%d.bmp", i + 1);
        
        SDL_Surface* surface = SDL_LoadBMP(filename);
        if (!surface) {
            fprintf(stderr, "Failed to load %s: %s\n", filename, SDL_GetError());
            continue;
        }
        
        game.number_textures[i] = SDL_CreateTextureFromSurface(game.renderer, surface);
        SDL_FreeSurface(surface);
        
        if (!game.number_textures[i]) {
            fprintf(stderr, "Failed to create texture from %s: %s\n", filename, SDL_GetError());
            return 0;
        }
    }
    
    // Load UI textures
    const char* ui_files[] = {
        "images/inteface/1.bmp",
        "images/inteface/2.bmp", 
        "images/inteface/3.bmp",
        "images/inteface/4.bmp",
        "images/inteface/5.bmp"
    };
    
    for (int i = 0; i < 5; i++) {
        SDL_Surface* surface = SDL_LoadBMP(ui_files[i]);
        if (surface) {
            game.ui_textures[i] = SDL_CreateTextureFromSurface(game.renderer, surface);
            SDL_FreeSurface(surface);
        }
    }
    
    return 1;
}

void free_textures(void) {
    // Free number textures
    for (int i = 0; i < MAX_TEXTURES; i++) {
        if (game.number_textures[i]) {
            SDL_DestroyTexture(game.number_textures[i]);
            game.number_textures[i] = NULL;
        }
    }
    
    // Free UI textures
    for (int i = 0; i < 6; i++) {
        if (game.ui_textures[i]) {
            SDL_DestroyTexture(game.ui_textures[i]);
            game.ui_textures[i] = NULL;
        }
    }
}

// Game logic functions
void init_board(int size) {
    game.board_size = size;
    
    // Initialize board in solved state
    int value = 1;
    for (int y = 0; y < size; y++) {
        for (int x = 0; x < size; x++) {
            if (x == size - 1 && y == size - 1) {
                game.board[x][y] = 0;  // Empty tile
                game.empty_x = x;
                game.empty_y = y;
            } else {
                game.board[x][y] = value++;
            }
        }
    }
    
    // Reset stats
    game.stats.moves = 0;
    game.stats.time_seconds = 0;
}

void shuffle_board(void) {
    srand((unsigned int)time(NULL));
    
    int empty_x = game.empty_x;
    int empty_y = game.empty_y;
    
    // Perform random valid moves to shuffle
    for (int i = 0; i < SHUFFLE_MOVES; i++) {
        int direction = rand() % 4;
        int new_x = empty_x;
        int new_y = empty_y;
        
        switch (direction) {
            case 0: new_x--; break;  // Left
            case 1: new_x++; break;  // Right
            case 2: new_y--; break;  // Up
            case 3: new_y++; break;  // Down
        }
        
        // Check if move is valid
        if (new_x >= 0 && new_x < game.board_size && 
            new_y >= 0 && new_y < game.board_size) {
            
            // Swap tiles
            game.board[empty_x][empty_y] = game.board[new_x][new_y];
            game.board[new_x][new_y] = 0;
            
            empty_x = new_x;
            empty_y = new_y;
        }
    }
    
    game.empty_x = empty_x;
    game.empty_y = empty_y;
}

int is_valid_move(int x, int y) {
    if (x < 0 || x >= game.board_size || y < 0 || y >= game.board_size) {
        return 0;
    }
    
    if (game.board[x][y] == 0) {
        return 0;  // Can't move empty tile
    }
    
    // Check if adjacent to empty tile
    int dx = abs(x - game.empty_x);
    int dy = abs(y - game.empty_y);
    
    return (dx == 1 && dy == 0) || (dx == 0 && dy == 1);
}

int make_move(int x, int y) {
    if (!is_valid_move(x, y)) {
        return 0;
    }
    
    // Start animation
    start_tile_animation(x, y, game.empty_x, game.empty_y, game.board[x][y]);
    
    // Swap tiles
    game.board[game.empty_x][game.empty_y] = game.board[x][y];
    game.board[x][y] = 0;
    
    game.empty_x = x;
    game.empty_y = y;
    
    game.stats.moves++;
    
    return 1;
}

int check_win_condition(void) {
    int expected = 1;
    
    for (int y = 0; y < game.board_size; y++) {
        for (int x = 0; x < game.board_size; x++) {
            if (x == game.board_size - 1 && y == game.board_size - 1) {
                // Last tile should be empty
                if (game.board[x][y] != 0) {
                    return 0;
                }
            } else {
                if (game.board[x][y] != expected) {
                    return 0;
                }
                expected++;
            }
        }
    }
    
    return 1;
}

void reset_game(int size) {
    init_board(size);
    shuffle_board();
    game.state = GAME_STATE_PLAYING;
}
