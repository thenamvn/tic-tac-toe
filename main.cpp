#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h> // Include TTF library
#include "caro.h"

const int WIDTH = 640, HEIGHT = 640; // Window size

int main(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init(); // Initialize TTF
    SDL_Window* window = SDL_CreateWindow("Tic Tac Toe 16x16", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    // Create font
    TTF_Font* font = TTF_OpenFont("arial.ttf", 24); // Ensure arial.ttf is in the working directory
    if (!font) {
        std::cerr << "Failed to load font: " << TTF_GetError() << std::endl;
        return 1;
    }

    BoardGame game(renderer);
    SDL_Event event;
    bool running = true;
    std::string winnerMessage;

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
            if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
                int row = event.button.y / 40; // Adjust cell size
                int col = event.button.x / 40; // Adjust cell size
                game.click(row, col);
                winnerMessage = game.getWinnerMessage(); // Retrieve the winner message
                if (!winnerMessage.empty()) {
                    std::cout << winnerMessage << std::endl;
                }
            }
        }

        // Set background color (e.g., white)
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // White color
        SDL_RenderClear(renderer); // Clear screen with the set background color

        game.draw(renderer); // Draw game board

        // Draw grid lines
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Black color for grid lines
        for (int i = 1; i < 16; i++) {
            // Draw horizontal lines
            SDL_RenderDrawLine(renderer, 0, i * 40, WIDTH, i * 40);
            // Draw vertical lines
            SDL_RenderDrawLine(renderer, i * 40, 0, i * 40, HEIGHT);
        }

        // Draw win message
        if (!winnerMessage.empty()) {
            SDL_Color textColor = { 0, 0, 0, 255 }; // Black color for text
            SDL_Surface* textSurface = TTF_RenderText_Solid(font, winnerMessage.c_str(), textColor);
            SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
            SDL_Rect textRect = { WIDTH / 2 - textSurface->w / 2, HEIGHT - 50, textSurface->w, textSurface->h };
            SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
            SDL_FreeSurface(textSurface);
            SDL_DestroyTexture(textTexture);
        }

        SDL_RenderPresent(renderer); // Update screen
    }

    // Free resources
    TTF_CloseFont(font);
    TTF_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}