#include <iostream>
#include <vector>
#include <limits>
using namespace std;

// Instructions
void instructions(){
    cout<<"The positions on the board are as follows";
    cout<<endl;
    for (int i = 0; i < 9; i++) {
        cout << i<<" ";
        if (i % 3 == 2) cout << endl;
    }
    cout << endl;
}
// Display board
void printBoard(const vector<int>& board) {
    for (int i = 0; i < 9; i++) {
        if (board[i] == 1) cout << "X ";
        else if (board[i] == -1) cout << "O ";
        else cout << ". ";
        if (i % 3 == 2) cout << endl;
    }
    cout << endl;
}

// Check winner
int checkboard(const vector<int>& board) {
    int wins[8][3] = {
        {0,1,2},{3,4,5},{6,7,8},
        {0,3,6},{1,4,7},{2,5,8},
        {0,4,8},{2,4,6}
    };

    for (auto& line : wins) {
        int a = board[line[0]], b = board[line[1]], c = board[line[2]];
        if (a != 0 && a == b && b == c)
            return a;
    }

    for (int i = 0; i < 9; i++)
        if (board[i] == 0)
            return 2; // still playing

    return 0; // draw
}

// Minimax
int minimax(vector<int>& board, bool isMaximizing, int aiSymbol) {
    int result = checkboard(board);
    if (result != 2) // If someone has won or it's a draw
        return result * aiSymbol; 

    if (isMaximizing) {  // Ai's Turn
        int bestScore = numeric_limits<int>::min();
        for (int i = 0; i < 9; i++) {
            if (board[i] == 0) {
                board[i] = aiSymbol;
                int score = minimax(board, false, aiSymbol); // sending false as next is players turn and we need to minimise
                board[i] = 0;
                bestScore = max(bestScore, score);
            }
        }
        return bestScore;
    } else {  // Humans's Turn
        int bestScore = numeric_limits<int>::max();
        for (int i = 0; i < 9; i++) {
            if (board[i] == 0) {
                board[i] = -aiSymbol;
                int score = minimax(board, true, aiSymbol);
                board[i] = 0;
                bestScore = min(bestScore, score);
            }
        }
        return bestScore;
    }
}

// Best move for AI
int bestmove(vector<int>& board, int aiSymbol) {
    int bestScore = numeric_limits<int>::min();
    int move = -1;
    for (int i = 0; i < 9; i++) {
        if (board[i] == 0) {
            board[i] = aiSymbol; // Place AI's move temporarily
            int score = minimax(board, false, aiSymbol);
            board[i] = 0; //Restore the cell 
            if (score > bestScore) {
                bestScore = score;
                move = i;
            }
        }
    }
    return move;
}

int main() {
    vector<int> board(9, 0);
    instructions();
    int playerFirst;
    cout << "Do you want to go first? (1 = Yes, 0 = No): ";
    cin >> playerFirst;

    int playerSymbol, aiSymbol;
    int turn;

    if (playerFirst) {
        playerSymbol = 1;  // You are X
        aiSymbol = -1;     // AI is O
        turn = 1;          // X plays first
    } else {
        playerSymbol = -1; // You are O
        aiSymbol = 1;      // AI is X
        turn = 1;          // X plays first
    }

    cout << "You are playing as '" << (playerSymbol == 1 ? "X" : "O") << "'\n\n";

    while (checkboard(board) == 2) {
        printBoard(board);

        if (turn == playerSymbol) {
            int move;
            do {
                cout << "Enter your move (0–8): ";
                cin >> move;
            } while (move < 0 || move > 8 || board[move] != 0);
            board[move] = playerSymbol;
        } else {
            int move = bestmove(board, aiSymbol);
            board[move] = aiSymbol;
            cout << "AI played at position " << move << "\n";
        }

        turn *= -1;
    }

    printBoard(board);

    int result = checkboard(board);
    if (result == playerSymbol)
        cout << "You win!\n";
    else if (result == aiSymbol)
        cout << "AI wins!\n";
    else
        cout << "It's a draw!\n";

    return 0;
}
