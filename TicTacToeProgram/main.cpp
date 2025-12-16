#include <iostream>
#include <iomanip>

using namespace std;

const int PLAY = 0;
const int TIE = 1;
const int X_WIN = 2;
const int O_WIN = 3;

const int SPACE_LEFT = 0;
const int NO_SPACE = 1;
const int WINNER = 2;

const bool XTURN = 0;
const bool OTURN = 1;

void initializeBoard(char[3][3]);

void displayBoard(char[3][3]);

void placeToken(bool, char[3][3]);

void getLocation(int&, int&, char[3][3]);

int getBoardState(bool, char[3][3]);

int checkForWinner(bool, char[3][3]);

int main()
{
    char gameBoard[3][3];

    int gameState = PLAY;
    bool playerTurn = XTURN;

    // Board started up
    initializeBoard(gameBoard);
    displayBoard(gameBoard);

    do {
        // Player 1 (X) turn
        placeToken(XTURN, gameBoard);
        displayBoard(gameBoard);
        gameState = getBoardState(XTURN, gameBoard);

        // Player 2 (O) turn
        placeToken(OTURN, gameBoard);
        displayBoard(gameBoard);
        gameState = getBoardState(OTURN, gameBoard);

    } while (gameState == PLAY);

    if (gameState == X_WIN)
    {
        cout << "X has won.\n";
    }
    else if (gameState == O_WIN)
    {
        cout << "O has won.\n";
    }
    else if (gameState == TIE)
    {
        cout << "The game has ended in a draw.\n";
    }

    return 0;
}

/*
    Summary: Initializes the board array to * characters, getting it ready for play.
    Parameters: A board array, 2D and 3x3 to represent the spaces of Tic-Tac-Toe, char board[3][3]
    Return: None.
    Preconditions: board[][] is empty or should be reset
    Postconditions: The array, passed by reference, will be updated to a clear board of only * symbols.
*/
void initializeBoard(char board[3][3])
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            board[i][j] = '*';
        }
    }
}

/*
    Summary: Displays a crude tic-tac-toe board to screen using a 2D 3x3 character array
    Parameters: A game board, board[3][3], a 2D character array which represents the board.
    Return: None.
    Preconditions: Board is filled with asterisks or other characters, rather than spaces.
    Postconditions: Terminal/console is given a board display, with labeled columns and rows.
*/
void displayBoard(char board[3][3])
{
    // Header Row
    cout << " " << 1 << 2 << 3 << endl;

    // Row 1
    cout << 1 << board[0][0] << board[0][1] << board[0][2] << endl;

    // Row 2
    cout << 2 << board[1][0] << board[1][1] << board[1][2] << endl;

    // Row 3
    cout << 3 << board[2][0] << board[2][1] << board[2][2] << endl;

    return;
}

void placeToken(bool turn, char board[3][3])
{
    int row, column;
    getLocation(row, column, board);

    if (turn == XTURN)
    {
        board[row][column] = 'X';
    }
    else if (turn == OTURN)
    {
        board[row][column] = 'O';
    }

    return;
}

void getLocation(int& row, int& col, char board[3][3])
{
    bool badSpace = false;

    do {
        // Prompt user
        cout << "Make your move.\n";

        cout << "Row: ";
        cin >> row;

        cout << "Column: ";
        cin >> col;

        if (row < 1 || row > 3 || col < 1 || col > 3)
        {
            badSpace = true;
            cout << "Move out of board range. Try again.\n";
        }
        else if (board[row - 1][col - 1] != '*') // correct row and col here!!
        {
            badSpace = true;
            cout << "Move conflicts with taken space. Try again.\n";
        }
        else
        {
            badSpace = false;
        }

    } while (badSpace = false);

    // Convert row and col to real indexes
    row -= 1;
    col -= 1;

    cout << "Move successfully made at " << row << ", " << col << endl;
}

int getBoardState(bool turn, char board[3][3])
{
    int state = checkForWinner(turn, board);

    if (state == WINNER && turn == XTURN)
    {
        state = X_WIN;
    }
    else if (state == WINNER)
    {
        state = O_WIN;
    }
    else if (state == NO_SPACE)
    {
        state = TIE;
    }
    else
    {
        state = SPACE_LEFT;
    }

    return state;
}

int checkForWinner(bool turn, char board[3][3])
{
    int outcome = NO_SPACE;
    char token[2] = {'X', 'O'};
    // Row wins
    if (board[0][0] == token[turn] && board[0][1] == token[turn] && board[0][2] == token[turn])
    {
        outcome = WINNER;
    }
    else if (board[1][0] == token[turn] && board[1][1] == token[turn] && board[1][2] == token[turn])
    {
        outcome = WINNER;
    }
    else if (board[2][0] == token[turn] && board[2][1] == token[turn] && board[2][2] == token[turn])
    {
        outcome = WINNER;
    }
    // Column wins
    if (board[0][0] == token[turn] && board[1][0] == token[turn] && board[2][0] == token[turn])
    {
        outcome = WINNER;
    }
    else if (board[0][1] == token[turn] && board[1][1] == token[turn] && board[2][1] == token[turn])
    {
        outcome = WINNER;
    }
    else if (board[0][2] == token[turn] && board[1][2] == token[turn] && board[2][2] == token[turn])
    {
        outcome = WINNER;
    }
    // Diagonal wins
    if (board[0][0] == token[turn] && board[1][1] == token[turn] && board[2][2] == token[turn])
    {
        outcome = WINNER;
    }
    else if (board[0][2] == token[turn] && board[1][1] == token[turn] && board[2][0] == token[turn])
    {
        outcome = WINNER;
    }

    if (outcome == WINNER)
    {
        return outcome;
    }
    else
    {
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if (board[i][j] == '*')
                {
                    outcome = SPACE_LEFT;
                }
            }
        }
    }

    return outcome;
}
