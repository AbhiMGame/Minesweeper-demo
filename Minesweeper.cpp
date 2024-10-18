#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <limits>

using namespace std;

class Board {
private:
    vector<vector<char>> board;      // Holds the board representation
    vector<vector<bool>> revealed;   // Tracks revealed cells
    int n;                            // Size of the board
    int mineCount;                   // Total mines on the board
    bool gameOver;                   // Status of the game

    void placeMines(int firstX, int firstY) {
        // Place mines randomly, ensuring no mine at (firstX, firstY)
        int placedMines = 0;
        srand(static_cast<unsigned>(time(0))); // Seed for random number generation

        while (placedMines < mineCount) {
            int x = rand() % n;
            int y = rand() % n;

            // Ensure we don't place a mine at the first click position or on already placed mines
            if (board[x][y] != 'M' && !(x == firstX && y == firstY)) {
                board[x][y] = 'M';
                placedMines++;
            }
        }
    }

    void calculateNumbers() {
        // Calculate numbers for each cell based on adjacent mines
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (board[i][j] == 'M') continue; // Skip mines

                int count = 0;
                // Check all adjacent cells
                for (int dx = -1; dx <= 1; dx++) {
                    for (int dy = -1; dy <= 1; dy++) {
                        if (dx == 0 && dy == 0) continue; // Skip the current cell
                        int newX = i + dx, newY = j + dy;
                        if (newX >= 0 && newX < n && newY >= 0 && newY < n && board[newX][newY] == 'M') {
                            count++;
                        }
                    }
                }
                if (count > 0) {
                    board[i][j] = count + '0'; // Store number as character
                }
            }
        }
    }

public:
    Board(int size, int mines) : n(size), mineCount(mines), gameOver(false) {
        // Initialize board with empty cells
        board.resize(n, vector<char>(n, ' '));
        revealed.resize(n, vector<bool>(n, false));
    }

    void generateBoard(int firstX, int firstY) {
        placeMines(firstX, firstY);
        calculateNumbers();
    }

    void revealCell(int x, int y) {
        if (gameOver || x < 0 || x >= n || y < 0 || y >= n) return;

        if (board[x][y] == 'M') {
            cout << "You hit a mine! Game Over." << endl;
            gameOver = true;
            return;
        }

        revealed[x][y] = true;

        // Check if the cell is a number or empty and reveal adjacent cells if necessary
        if (board[x][y] == ' ') {
            for (int dx = -1; dx <= 1; dx++) {
                for (int dy = -1; dy <= 1; dy++) {
                    if (dx == 0 && dy == 0) continue;
                    revealCell(x + dx, y + dy);
                }
            }
        }
    }

    void printBoard(bool revealMines = false) {
        cout << "Current Board:" << endl;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (revealed[i][j]) {
                    cout << board[i][j] << " ";
                } else if (revealMines && board[i][j] == 'M') {
                    cout << "M "; // Show mines if the game is over
                } else {
                    cout << "# "; // Show hidden cells
                }
            }
            cout << endl;
        }
        cout << endl;
    }

    bool isGameOver() {
        return gameOver;
    }
};

int main() {
    int n;
    cout << "Enter the size of the board (n >= 9): ";
    cin >> n;

    // Input validation for board size
    while (n < 9) {
        cout << "Board size must be at least 9. Please enter again: ";
        cin >> n;
    }

    int mineCount;
    cout << "Enter the number of mines: ";
    cin >> mineCount;

    // Ensure mines are not more than the cells
    while (mineCount >= n * n) {
        cout << "Number of mines must be less than the total cells. Please enter again: ";
        cin >> mineCount;
    }

    Board board(n, mineCount);
    
    int firstX, firstY;
    cout << "Enter the first click position (x y): ";
    cin >> firstX >> firstY;

    // Input validation for first click position
    while (firstX < 0 || firstX >= n || firstY < 0 || firstY >= n) {
        cout << "Invalid position. Please enter again (x y): ";
        cin >> firstX >> firstY;
    }

    // Generate the board after the first click
    board.generateBoard(firstX, firstY);
    board.revealCell(firstX, firstY);

    // Game loop
    while (!board.isGameOver()) {
        board.printBoard();
        
        int x, y;
        cout << "Enter the next click position (x y): ";
        cin >> x >> y;

        // Input validation for click position
        while (x < 0 || x >= n || y < 0 || y >= n || board.isGameOver()) {
            cout << "Invalid position or game over. Please enter again (x y): ";
            cin >> x >> y;
        }

        board.revealCell(x, y);
    }

    // Final status
    cout << "Game Over! Final Board Status:" << endl;
    board.printBoard(true); // Show mines

    cout << "Press Enter to exit...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Ignore any leftover newline character
    cin.get();     // Wait for the user to press Enter

    return 0;
}
