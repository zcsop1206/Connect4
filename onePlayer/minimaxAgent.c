#include "/workspaces/Connect4/configureBoard.c"

int evaluateBoard(char gameBoard[][COLS], char turn);
int alphaBetaPruning(char gameBoard[][COLS], int lastRow, int lastCol, int depth, bool isMaximizing, char turn, int alpha, int beta);

int getComputerInput(char gameBoard[][COLS], char turn, int lastRow, int lastCol) {
    int bestScore = -10000;
    int bestMove = -1;
    
    for (int c = 0; c < COLS; c++) {
        if (gameBoard[0][c] == '-') {  // Column not full
            int row = insertPiece(gameBoard, c, turn);
            int score = alphaBetaPruning(gameBoard, lastRow, lastCol, 0, false, turn, -10000, 10000);
            gameBoard[row][c] = '-';  // Undo move
            
            if (score > bestScore) {
                bestScore = score;
                bestMove = c;
            }
        }
    }
    
    printf("Computer played in column: %d\n", bestMove);
    return bestMove;
}

int alphaBetaPruning(char gameBoard[][COLS], int lastRow, int lastCol, int depth, bool isMaximizing, char turn, int alpha, int beta) {
    if (checkWinner(gameBoard, lastRow, lastCol)) {
        return isMaximizing ? -1000 + depth : 1000 - depth;
    }
    if (depth == 4) {
        return evaluateBoard(gameBoard, turn);
    }

    char opponent = (turn == 'R') ? 'Y' : 'R';
    int bestScore = isMaximizing ? -10000 : 10000;

    for (int c = 0; c < COLS; c++) {
        if (gameBoard[0][c] == '-') {
            int row = insertPiece(gameBoard, c, isMaximizing ? turn : opponent);
            int score = alphaBetaPruning(gameBoard, lastRow, lastCol, depth + 1, !isMaximizing, turn, alpha, beta);
            gameBoard[row][c] = '-';  // Undo move

            if (isMaximizing) {
                bestScore = (score > bestScore) ? score : bestScore;
                alpha = (alpha > bestScore) ? alpha : bestScore;
            } else {
                bestScore = (score < bestScore) ? score : bestScore;
                beta = (beta < bestScore) ? beta : bestScore;
            }
            
            if (beta <= alpha) break;  // Prune the search
        }
    }
    return bestScore;
}

int evaluateBoard(char gameBoard[][COLS], char turn) {
    int score = 0;
    char opponent = (turn == 'R') ? 'Y' : 'R';

    // Simple heuristic: +10 for 3-in-a-row, +100 for 4-in-a-row
    for (int r = 0; r < ROWS; r++) {
        for (int c = 0; c < COLS; c++) {
            if (gameBoard[r][c] == turn) {
                score += 10;  // Reward positions with AI pieces
            } else if (gameBoard[r][c] == opponent) {
                score -= 10;  // Penalize opponent pieces
            }
        }
    }
    
    return score;
}
