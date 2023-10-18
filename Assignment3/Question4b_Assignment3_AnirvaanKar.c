#include <stdio.h>
#include <stdbool.h>

// Function to check if placing a queen at given (row, col) is safe
bool isSafe(int board[], int row, int col) {
    // Check if there is a queen in the same row,column or diagonal
    for (int prevRow = 0; prevRow < row; prevRow++) {
        if (board[prevRow] == col || 
            board[prevRow] - prevRow == col - row || 
            board[prevRow] + prevRow == col + row) {
            return false;
        }
    }
    // If no queen is attacking the current position, it is safe
    return true;
}

// Function to print the board
void printSolution(int board[], int N) {
    
    for (int row = 0; row < N; row++) {
        for (int col = 0; col < N; col++) {
            if (board[row] == col) {
                printf(" Q "); // Print 'Q' for queens' positions
            } else {
                printf(" - "); // Print '-' for empty positions
            }
        }
        printf("\n");
    }
    printf("\n");
}

// Recursive function to solve the N-Queens problem
bool placement(int board[], int row, int N) {
    // If all queens are placed successfully, print the solution
    if (row == N) {
        printSolution(board, N);
        return true;
    }

    bool res = false;
    // Try placing a queen in each column of the current row
    for (int col = 0; col < N; col++) {
        // If placing the queen in this column is safe, proceed
        if (isSafe(board, row, col)) {
            board[row] = col; // Place the queen at this position
            // Recur to place the rest of the queens
            res = placement(board, row + 1, N) || res;
            board[row] = -1; // Backtrack and remove the queen for backtracking
        }
    }
    // If no column is suitable for the current queen, return false to backtrack
    return res;
}

// Function to solve the N-Queens problem
void solveNQ(int N) {
    // Create an array to represent the chessboard, initialized with -1 (no queens)
    int board[N];
    for (int i = 0; i < N; i++) {
        board[i] = -1; // Initialize the board with no queens
    }

    // Call the recursive placement function starting from the first row 
    if (!placement(board, 0, N)) {
        printf("Solution does not exist.\n"); // If no solution is found
    }
}

int main() {
    int N;
    printf("Enter the value of N: ");
    scanf("%d", &N); 
    solveNQ(N); 
    return 0; 
}
