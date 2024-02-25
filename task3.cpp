#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>

#ifdef _WIN32
#include <windows.h>
#endif

// Function to set text color for Windows
void setColor(int color) {
#ifdef _WIN32
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
#endif
}

// Function to display the Tic-Tac-Toe board with colors
void displayBoard(const std::vector<std::vector<char>>& board) {
    int size = board.size();
    // Display column indices
    std::cout << "  ";
    for (int col = 1; col <= size; ++col) {
        std::cout << col << " ";
    }
    std::cout << std::endl;
    // Display gridlines and rows with marks
    for (int i = 0; i < size; ++i) {
        std::cout << i + 1 << "|"; // Display row index
        for (int j = 0; j < size; ++j) {
            if (board[i][j] == 'X') {
                setColor(12); // Red color for X
                std::cout << board[i][j] << " ";
            } else if (board[i][j] == 'O') {
                setColor(10); // Green color for O
                std::cout << board[i][j] << " ";
            } else {
                std::cout << board[i][j] << " ";
            }
            setColor(7); // Reset color
        }
        std::cout << std::endl;
        // Display gridlines between rows
        std::cout << " ";
        for (int k = 0; k < size; ++k) {
            std::cout << "-+";
        }
        std::cout << std::endl;
    }
}

// Function to check if a player has won
bool checkWin(const std::vector<std::vector<char>>& board, char player, int consecutiveMarks) {
    int size = board.size();
    // Check rows
    for (int i = 0; i < size; ++i) {
        int count = 0;
        for (int j = 0; j < size; ++j) {
            if (board[i][j] == player) {
                ++count;
                if (count == consecutiveMarks) {
                    return true;
                }
            } else {
                count = 0;
            }
        }
    }
    // Check columns
    for (int j = 0; j < size; ++j) {
        int count = 0;
        for (int i = 0; i < size; ++i) {
            if (board[i][j] == player) {
                ++count;
                if (count == consecutiveMarks) {
                    return true;
                }
            } else {
                count = 0;
            }
        }
    }
    // Check diagonals
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            // Check diagonal from top-left to bottom-right
            int count = 0;
            for (int k = 0; i + k < size && j + k < size; ++k) {
                if (board[i + k][j + k] == player) {
                    ++count;
                    if (count == consecutiveMarks) {
                        return true;
                    }
                } else {
                    count = 0;
                }
            }
            // Check diagonal from top-right to bottom-left
            count = 0;
            for (int k = 0; i + k < size && j - k >= 0; ++k) {
                if (board[i + k][j - k] == player) {
                    ++count;
                    if (count == consecutiveMarks) {
                        return true;
                    }
                } else {
                    count = 0;
                }
            }
        }
    }
    return false;
}

// Function to check if the board is full (draw)
bool checkDraw(const std::vector<std::vector<char>>& board) {
    for (const auto& row : board) {
        for (char cell : row) {
            if (cell == ' ') {
                return false; // If there's an empty cell, game is not draw
            }
        }
    }
    return true; // If no empty cells, game is draw
}

// Function to get computer's move (random position)
std::pair<int, int> getComputerMove(const std::vector<std::vector<char>>& board) {
    std::pair<int, int> move;
    do {
        move.first = rand() % board.size();
        move.second = rand() % board.size();
    } while (board[move.first][move.second] != ' ');
    return move;
}

int main() {
    srand(static_cast<unsigned int>(time(nullptr))); // Seed for random number generation

    int boardSize;
    std::cout << "Enter the size of the board (minimum 3): ";
    std::cin >> boardSize;

    std::vector<std::vector<char>> board(boardSize, std::vector<char>(boardSize, ' ')); // Initialize empty board
    char currentPlayer = 'X';
    bool gameOver = false;
    bool vsComputer = false;
    std::string player1Name, player2Name;

    std::cout << "Enter player 1's name: ";
    std::cin >> player1Name;

    std::cout << "Do you want to play against the computer? (yes/no): ";
    std::string vsComputerChoice;
    std::cin >> vsComputerChoice;

    if (vsComputerChoice == "yes") {
        vsComputer = true;
        player2Name = "Computer";
    } else {
        std::cout << "Enter player 2's name: ";
        std::cin >> player2Name;
    }

    while (!gameOver) {
        // Display board
        std::cout << "Current board:" << std::endl;
        displayBoard(board);

        // Player input
        int row, col;
        if (currentPlayer == 'X' || !vsComputer) {
            std::cout << "Player " << ((currentPlayer == 'X') ? player1Name : player2Name) << ", enter your move (row column): ";
            std::cin >> row >> col;
            --row; // Adjust for indexing starting from 1
            --col; // Adjust for indexing starting from 1
        } else { // Computer's move
            std::cout << "Computer (Player " << player2Name << ") is thinking..." << std::endl;
            std::pair<int, int> computerMove = getComputerMove(board);
            row = computerMove.first;
            col = computerMove.second;
            std::cout << "Computer chose row " << row + 1 << " and column " << col + 1 << std::endl; // Adjust for indexing starting from 1
        }

        // Update board
        if (row >= 0 && row < board.size() && col >= 0 && col < board.size() && board[row][col] == ' ') {
            board[row][col] = currentPlayer;

            // Check for win
            if (checkWin(board, currentPlayer, 3)) { // Minimum 3 consecutive marks to win
                std::cout << "Player " << ((currentPlayer == 'X') ? player1Name : player2Name) << " wins!" << std::endl;
                gameOver = true;
            }
            // Check for draw
            else if (checkDraw(board)) {
                std::cout << "It's a draw!" << std::endl;
                gameOver = true;
            }
            // Switch players
            currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
        }
        else {
            std::cout << "Invalid move. Try again." << std::endl;
        }
    }

    // Display final board
    std::cout << "Final board:" << std::endl;
    displayBoard(board);

    return 0;
}
