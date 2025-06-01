/**
 * Taquin - Demo Version (Console Output)
 * 
 * This demo shows the enhanced game structure and logic
 * without requiring SDL2 graphics libraries.
 * 
 * To see the full graphical version, set up SDL2 and compile main.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

// Demo constants (simplified version of constant.h)
#define MAX_BOARD_SIZE 5
#define MIN_BOARD_SIZE 3
#define SHUFFLE_MOVES 100

typedef enum {
    DEMO_STATE_MENU,
    DEMO_STATE_PLAYING,
    DEMO_STATE_WIN
} DemoState;

typedef struct {
    int moves;
    int time_seconds;
} DemoStats;

typedef struct {
    int board_size;
    int board[MAX_BOARD_SIZE][MAX_BOARD_SIZE];
    DemoState state;
    DemoStats stats;
    int empty_x, empty_y;
} DemoGame;

// Global demo game instance
DemoGame demo_game = {0};

// Demo function declarations
void demo_init_board(int size);
void demo_shuffle_board(void);
void demo_print_board(void);
int demo_is_valid_move(int x, int y);
int demo_make_move(int x, int y);
int demo_check_win(void);
void demo_print_menu(void);
void demo_print_stats(void);

// Demo implementations
void demo_init_board(int size) {
    demo_game.board_size = size;
    
    int value = 1;
    for (int y = 0; y < size; y++) {
        for (int x = 0; x < size; x++) {
            if (x == size - 1 && y == size - 1) {
                demo_game.board[x][y] = 0;
                demo_game.empty_x = x;
                demo_game.empty_y = y;
            } else {
                demo_game.board[x][y] = value++;
            }
        }
    }
    
    demo_game.stats.moves = 0;
    demo_game.stats.time_seconds = 0;
}

void demo_shuffle_board(void) {
    srand((unsigned int)time(NULL));
    
    int empty_x = demo_game.empty_x;
    int empty_y = demo_game.empty_y;
    
    for (int i = 0; i < SHUFFLE_MOVES; i++) {
        int direction = rand() % 4;
        int new_x = empty_x;
        int new_y = empty_y;
        
        switch (direction) {
            case 0: new_x--; break;
            case 1: new_x++; break;
            case 2: new_y--; break;
            case 3: new_y++; break;
        }
        
        if (new_x >= 0 && new_x < demo_game.board_size && 
            new_y >= 0 && new_y < demo_game.board_size) {
            
            demo_game.board[empty_x][empty_y] = demo_game.board[new_x][new_y];
            demo_game.board[new_x][new_y] = 0;
            
            empty_x = new_x;
            empty_y = new_y;
        }
    }
    
    demo_game.empty_x = empty_x;
    demo_game.empty_y = empty_y;
}

void demo_print_board(void) {
    printf("\n");
    for (int y = 0; y < demo_game.board_size; y++) {
        printf("  ");
        for (int x = 0; x < demo_game.board_size; x++) {
            if (demo_game.board[x][y] == 0) {
                printf("   ");
            } else {
                printf("%2d ", demo_game.board[x][y]);
            }
        }
        printf("\n");
    }
    printf("\n");
}

int demo_is_valid_move(int x, int y) {
    if (x < 0 || x >= demo_game.board_size || y < 0 || y >= demo_game.board_size) {
        return 0;
    }
    
    if (demo_game.board[x][y] == 0) {
        return 0;
    }
    
    int dx = abs(x - demo_game.empty_x);
    int dy = abs(y - demo_game.empty_y);
    
    return (dx == 1 && dy == 0) || (dx == 0 && dy == 1);
}

int demo_make_move(int x, int y) {
    if (!demo_is_valid_move(x, y)) {
        return 0;
    }
    
    demo_game.board[demo_game.empty_x][demo_game.empty_y] = demo_game.board[x][y];
    demo_game.board[x][y] = 0;
    
    demo_game.empty_x = x;
    demo_game.empty_y = y;
    
    demo_game.stats.moves++;
    
    return 1;
}

int demo_check_win(void) {
    int expected = 1;
    
    for (int y = 0; y < demo_game.board_size; y++) {
        for (int x = 0; x < demo_game.board_size; x++) {
            if (x == demo_game.board_size - 1 && y == demo_game.board_size - 1) {
                if (demo_game.board[x][y] != 0) {
                    return 0;
                }
            } else {
                if (demo_game.board[x][y] != expected) {
                    return 0;
                }
                expected++;
            }
        }
    }
    
    return 1;
}

void demo_print_menu(void) {
    printf("\n=== TAQUIN - Enhanced Sliding Puzzle Demo ===\n");
    printf("This demo shows the enhanced game structure.\n");
    printf("For the full graphical version, set up SDL2 and compile main.c\n\n");
    printf("Select difficulty:\n");
    printf("  3 - Easy (3x3 grid)\n");
    printf("  4 - Medium (4x4 grid)\n");
    printf("  5 - Hard (5x5 grid)\n");
    printf("  q - Quit\n");
    printf("\nChoice: ");
}

void demo_print_stats(void) {
    printf("Moves: %d\n", demo_game.stats.moves);
}

int main(void) {
    printf("=== TAQUIN ENHANCED - DEMO VERSION ===\n");
    printf("This demonstrates the improved game logic and structure.\n");
    printf("The full version with SDL2 graphics includes:\n");
    printf("- Smooth animations\n");
    printf("- Professional graphics\n");
    printf("- Mouse controls\n");
    printf("- Sound effects (planned)\n");
    printf("- Best score tracking\n");
    printf("- Cross-platform support\n\n");
    
    demo_game.state = DEMO_STATE_MENU;
    
    while (1) {
        switch (demo_game.state) {
            case DEMO_STATE_MENU: {
                demo_print_menu();
                
                char choice;
                scanf(" %c", &choice);
                
                switch (choice) {
                    case '3':
                        demo_init_board(3);
                        demo_shuffle_board();
                        demo_game.state = DEMO_STATE_PLAYING;
                        break;
                    case '4':
                        demo_init_board(4);
                        demo_shuffle_board();
                        demo_game.state = DEMO_STATE_PLAYING;
                        break;
                    case '5':
                        demo_init_board(5);
                        demo_shuffle_board();
                        demo_game.state = DEMO_STATE_PLAYING;
                        break;
                    case 'q':
                    case 'Q':
                        printf("Thanks for trying the Taquin demo!\n");
                        return 0;
                    default:
                        printf("Invalid choice. Please try again.\n");
                        break;
                }
                break;
            }
            
            case DEMO_STATE_PLAYING: {
                demo_print_board();
                demo_print_stats();
                
                if (demo_check_win()) {
                    demo_game.state = DEMO_STATE_WIN;
                    break;
                }
                
                printf("Enter move (x y) or 'm' for menu, 'r' to reset: ");
                
                char input[10];
                scanf("%s", input);
                
                if (input[0] == 'm') {
                    demo_game.state = DEMO_STATE_MENU;
                } else if (input[0] == 'r') {
                    demo_shuffle_board();
                    demo_game.stats.moves = 0;
                } else {
                    int x, y;
                    if (sscanf(input, "%d", &x) == 1) {
                        printf("Enter y coordinate: ");
                        scanf("%d", &y);
                        
                        if (demo_make_move(x, y)) {
                            printf("Move successful!\n");
                        } else {
                            printf("Invalid move. Try again.\n");
                        }
                    }
                }
                break;
            }
            
            case DEMO_STATE_WIN: {
                printf("\n🎉 CONGRATULATIONS! 🎉\n");
                printf("You solved the puzzle in %d moves!\n", demo_game.stats.moves);
                demo_print_board();
                
                printf("Press 'm' for menu or 'q' to quit: ");
                char choice;
                scanf(" %c", &choice);
                
                if (choice == 'm') {
                    demo_game.state = DEMO_STATE_MENU;
                } else {
                    printf("Thanks for playing!\n");
                    return 0;
                }
                break;
            }
        }
    }
    
    return 0;
}
