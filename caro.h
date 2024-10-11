#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
enum CellState {
    EMPTY = -1,
    X = 1,
    O = 0
};

class Cell {
private:
    int row, col;
    CellState state;

public:
    Cell(); // Default constructor
    Cell(int mrow, int mcol);
    void draw(SDL_Renderer* renderer, SDL_Texture* textureX, SDL_Texture* textureO);
    void setState(CellState mstate);
    CellState getState();
};

class BoardGame {
private:
    static const int SIZE = 16; // Kích thước bảng 16x16
    Cell cells[SIZE][SIZE];
    CellState turn;
    SDL_Texture* textureX;
    SDL_Texture* textureO;
    std::string winnerMessage; // Add this line
    bool gameOver;

public:
    BoardGame(SDL_Renderer* renderer);
    void click(int mrow, int mcol);
    void draw(SDL_Renderer* renderer);
    bool checkWinner(CellState player, int row, int col);
    bool isFull();

    std::string getWinnerMessage() const { // Add this method
        return winnerMessage;
    }
};