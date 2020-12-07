#include "Piezas.h"
#include <vector>
/** CLASS Piezas
 * Class for representing a Piezas vertical board, which is roughly based
 * on the game "Connect Four" where pieces are placed in a column and 
 * fall to the bottom of the column, or on top of other pieces already in
 * that column. For an illustration of the board, see:
 *  https://en.wikipedia.org/wiki/Connect_Four
 *
 * Board coordinates [row,col] should match with:
 * [2,0][2,1][2,2][2,3]
 * [1,0][1,1][1,2][1,3]
 * [0,0][0,1][0,2][0,3]
 * So that a piece dropped in column 2 should take [0,2] and the next one
 * dropped in column 2 should take [1,2].
**/


/**
 * Constructor sets an empty board (default 3 rows, 4 columns) and 
 * specifies it is X's turn first
**/
Piezas::Piezas() : turn(X)
{
    // resize board
    board.resize(BOARD_ROWS);
    for (int i = 0; i < BOARD_ROWS; ++i)
        board[i].resize(BOARD_COLS);

    reset();
}

/**
 * Resets each board location to the Blank Piece value, with a board of the
 * same size as previously specified
**/
void Piezas::reset()
{
    for (int i = 0; i < BOARD_ROWS; ++i)
    {
        for (int j = 0; j < BOARD_COLS; ++j)
            board[i][j] = Blank;
    }
}

/**
 * Places a piece of the current turn on the board, returns what
 * piece is placed, and toggles which Piece's turn it is. dropPiece does 
 * NOT allow to place a piece in a location where a column is full.
 * In that case, placePiece returns Piece Blank value 
 * Out of bounds coordinates return the Piece Invalid value
 * Trying to drop a piece where it cannot be placed loses the player's turn
**/ 
Piece Piezas::dropPiece(int column)
{   
    // checking bounds
    if (column < 0 || column >= BOARD_COLS)
    {
        turn = (turn == X) ? O : X;
        return Invalid;
    }

    // scan column from bottom up
    for (int i = 0; i < BOARD_ROWS; ++i)
    {
        // if there is a blank spot
        if (board[i][column] == Blank)
        {
            // place turn, toggle turn, return piece placed 
            board[i][column] = turn;
            turn = (turn == X) ? O : X;
            return board[i][column];
        }
    }
    
    // if you've reached here, the col is full
    turn = (turn == X) ? O : X;
    return Blank;
}

/**
 * Returns what piece is at the provided coordinates, or Blank if there
 * are no pieces there, or Invalid if the coordinates are out of bounds
**/
Piece Piezas::pieceAt(int row, int column)
{
    // checking bounds
    if (column < 0 || column >= BOARD_COLS || 
        row    < 0 || row    >= BOARD_ROWS )
    {
        return Invalid;
    }

    return board[row][column];  
}

/**
 * Returns which Piece has won, if there is a winner, Invalid if the game
 * is not over, or Blank if the board is filled and no one has won ("tie").
 * For a game to be over, all locations on the board must be filled with X's 
 * and O's (i.e. no remaining Blank spaces). The winner is which player has
 * the most adjacent pieces in a single line. Lines can go either vertically
 * or horizontally. If both X's and O's have the same max number of pieces in a
 * line, it is a tie.
**/
Piece Piezas::gameState()
{
    // check for blank spots
    for (int i = 0; i < BOARD_ROWS; ++i)
    {
        for (int j = 0; j < BOARD_COLS; ++j)
        {
            if (board[i][j] == Blank)
                return Invalid;
        }
    }

    int xMax = 0;
    int oMax = 0;

    // count max in horizontal
    for (int r = 0; r < BOARD_ROWS; ++r)
    {
        int curMax = 0;
        Piece p = board[r][0];
        for (int c = 0; c < BOARD_COLS; ++c)
        {
            if (board[r][c] == p)
            {
                ++curMax;
                if (p == X && curMax > xMax)
                    xMax = curMax;
                else if (p == O && curMax > oMax)
                    oMax = curMax;
            }
            else
            {
                curMax = 0;
                p = board[r][c];
            }
        }
    }

    // count max in vertical
    for (int c = 0; c < BOARD_COLS; ++c)
    {
        int curMax = 0;
        Piece p = board[0][c];
        for (int r = 0; r < BOARD_ROWS; ++r)
        {
            if (board[r][c] == p)
            {
                ++curMax;
                if (p == X && curMax > xMax)
                    xMax = curMax;
                else if (p == O && curMax > oMax)
                    oMax = curMax;
            }
            else
            {
                curMax = 0;
                p = board[r][c];
            }
        }
    }


    if (xMax == oMax)     return Blank;
    else if (xMax > oMax) return X;
    else                  return O;
}
























