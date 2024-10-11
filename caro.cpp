#include "caro.h"
#include <iostream>

Cell::Cell() : row(0), col(0), state(EMPTY) {}

Cell::Cell(int mrow, int mcol) : row(mrow), col(mcol), state(EMPTY) {}

void Cell::draw(SDL_Renderer* renderer, SDL_Texture* textureX, SDL_Texture* textureO) {
    SDL_Rect rect = { col * 40, row * 40, 40, 40 }; // Adjust cell size
    if (state == X) {
        SDL_RenderCopy(renderer, textureX, NULL, &rect);
    } else if (state == O) {
        SDL_RenderCopy(renderer, textureO, NULL, &rect);
    }
}

void Cell::setState(CellState mstate) {
    state = mstate;
}

CellState Cell::getState() {
    return state;
}

BoardGame::BoardGame(SDL_Renderer* renderer) : turn(X) {
    textureX = IMG_LoadTexture(renderer, "x.png");
    textureO = IMG_LoadTexture(renderer, "o.png");
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            cells[i][j] = Cell(i, j);
}

void BoardGame::click(int mrow, int mcol) {
    if (gameOver) return; // Prevent further moves if the game is over

    if (cells[mrow][mcol].getState() == EMPTY) {
        cells[mrow][mcol].setState(turn);
        if (checkWinner(turn, mrow, mcol)) {
            winnerMessage = "Player " + std::string(1, turn == X ? 'X' : 'O') + " wins!"; // Set winner message
            std::cout << winnerMessage << std::endl; // Optional: Print to console
            gameOver = true; // Set gameOver to true
        } else if (isFull()) {
            winnerMessage = "It's a draw!"; // Set draw message
            std::cout << winnerMessage << std::endl; // Optional: Print to console
            gameOver = true; // Set gameOver to true
        }
        turn = (turn == X) ? O : X; // Switch turn
    }
}

void BoardGame::draw(SDL_Renderer* renderer) {
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            cells[i][j].draw(renderer, textureX, textureO);
}

bool BoardGame::checkWinner(CellState player, int row, int col) {
    // Check for 5 in a row horizontally
    for (int i = -4; i <= 0; i++) {
        if (col + i >= 0 && col + i + 4 < SIZE &&
            cells[row][col + i].getState() == player &&
            cells[row][col + i + 1].getState() == player &&
            cells[row][col + i + 2].getState() == player &&
            cells[row][col + i + 3].getState() == player &&
            cells[row][col + i + 4].getState() == player) {
            return true;
        }
    }

    // Check for 5 in a row vertically
    for (int i = -4; i <= 0; i++) {
        if (row + i >= 0 && row + i + 4 < SIZE &&
            cells[row + i][col].getState() == player &&
            cells[row + i + 1][col].getState() == player &&
            cells[row + i + 2][col].getState() == player &&
            cells[row + i + 3][col].getState() == player &&
            cells[row + i + 4][col].getState() == player) {
            return true;
        }
    }

    // Check for 5 in a row diagonally (top-left to bottom-right)
    for (int i = -4; i <= 0; i++) {
        if (row + i >= 0 && row + i + 4 < SIZE && col + i >= 0 && col + i + 4 < SIZE &&
            cells[row + i][col + i].getState() == player &&
            cells[row + i + 1][col + i + 1].getState() == player &&
            cells[row + i + 2][col + i + 2].getState() == player &&
            cells[row + i + 3][col + i + 3].getState() == player &&
            cells[row + i + 4][col + i + 4].getState() == player) {
            return true;
        }
    }

    // Check for 5 in a row diagonally (top-right to bottom-left)
    for (int i = -4; i <= 0; i++) {
        if (row + i >= 0 && row + i + 4 < SIZE && col - i >= 0 && col - i - 4 < SIZE &&
            cells[row + i][col - i].getState() == player &&
            cells[row + i + 1][col - i - 1].getState() == player &&
            cells[row + i + 2][col - i - 2].getState() == player &&
            cells[row + i + 3][col - i - 3].getState() == player &&
            cells[row + i + 4][col - i - 4].getState() == player) {
            return true;
        }
    }

    return false; // No winner found
}

// Implement the isFull method
bool BoardGame::isFull() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (cells[i][j].getState() == EMPTY) {
                return false; // Found an empty cell
            }
        }
    }
    return true; // No empty cells found
}