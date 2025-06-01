/**
 * Taquin - Enhanced Sliding Puzzle Game
 *
 * A modern implementation of the classic sliding puzzle game using SDL2.
 * Features multiple difficulty levels, animations, scoring system, and
 * professional code organization.
 *
 * Author: Enhanced by AI Assistant
 * Version: 2.0
 */

#include "functions.h"

int main(int argc, char *argv[]) {
    // Initialize the game
    if (!init_game()) {
        fprintf(stderr, "Failed to initialize game\n");
        return EXIT_FAILURE;
    }

    printf("=== Taquin - Sliding Puzzle Game ===\n");
    printf("Controls:\n");
    printf("  Menu: Press 3, 4, or 5 to select grid size\n");
    printf("  Game: Click tiles to move them\n");
    printf("  ESC: Return to menu\n");
    printf("  R: Reset current game\n");
    printf("  N: New shuffle\n");
    printf("  Q: Quit game\n\n");

    // Main game loop
    SDL_bool running = SDL_TRUE;
    Uint32 last_time = SDL_GetTicks();

    while (running) {
        Uint32 current_time = SDL_GetTicks();
        Uint32 delta_time = current_time - last_time;
        last_time = current_time;

        // Handle events
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = SDL_FALSE;
            } else {
                // Handle input based on current game state
                switch (game.state) {
                    case GAME_STATE_MENU:
                        handle_menu_input(&event);
                        break;

                    case GAME_STATE_PLAYING:
                        handle_game_input(&event);
                        break;

                    case GAME_STATE_WIN:
                        if (event.type == SDL_KEYDOWN) {
                            if (event.key.keysym.sym == SDLK_SPACE ||
                                event.key.keysym.sym == SDLK_RETURN) {
                                game.state = GAME_STATE_MENU;
                            } else if (event.key.keysym.sym == SDLK_r) {
                                reset_game(game.board_size);
                            }
                        }
                        break;

                    default:
                        break;
                }
            }
        }

        // Update game logic
        if (game.state == GAME_STATE_PLAYING) {
            update_animations();

            // Update timer (every second)
            static Uint32 timer_accumulator = 0;
            timer_accumulator += delta_time;
            if (timer_accumulator >= 1000) {
                game.stats.time_seconds++;
                timer_accumulator = 0;
            }
        }

        // Render based on current state
        switch (game.state) {
            case GAME_STATE_MENU:
                render_menu();
                break;

            case GAME_STATE_PLAYING:
                render_game();
                break;

            case GAME_STATE_WIN:
                render_win_screen();
                break;

            default:
                render_menu();
                break;
        }

        // Cap frame rate to ~60 FPS
        SDL_Delay(16);
    }

    // Cleanup and exit
    cleanup_game();
    printf("Thanks for playing Taquin!\n");

    return EXIT_SUCCESS;
}
