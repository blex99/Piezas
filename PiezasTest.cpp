/**
 * Unit Tests for Piezas
**/

#include <gtest/gtest.h>
#include "Piezas.h"
 
class PiezasTest : public ::testing::Test
{
	protected:
		PiezasTest(){} //constructor runs before each test
		virtual ~PiezasTest(){} //destructor cleans up after tests
		virtual void SetUp(){} //sets up before each test (after constructor)
		virtual void TearDown(){} //clean up after each test, (before destructor) 
};

TEST(PiezasTest, dropPiece)
{
	Piezas p;

	// returns what piece is placed
	ASSERT_TRUE(X == p.dropPiece(0));

	// turn was toggled 
	ASSERT_TRUE(O == p.dropPiece(0));
	ASSERT_TRUE(X == p.dropPiece(0)); // pieces on col 0 is now maxed

	// cannot place a piece in a location where a column is full (return blank)
	ASSERT_TRUE(Blank == p.dropPiece(0));

	// out of bounds coordinates (return invalid)
	ASSERT_TRUE(Invalid == p.dropPiece(-1));
	ASSERT_TRUE(Invalid == p.dropPiece(BOARD_COLS));
}

TEST(PiezasTest, pieceAt)
{
	Piezas p;
	p.dropPiece(0);
	p.dropPiece(0);
	p.dropPiece(1);

	// Returns what piece is at the provided coordinates
	ASSERT_TRUE(p.pieceAt(0, 0) == X);
	ASSERT_TRUE(p.pieceAt(1, 0) == O);
	ASSERT_TRUE(p.pieceAt(0, 1) == X);

	// Blank if there are no pieces there
	ASSERT_TRUE(p.pieceAt(BOARD_ROWS-1, BOARD_COLS-1) == Blank);
	
	// Invalid if the coordinates are out of bounds
	ASSERT_TRUE(p.pieceAt(-1		, 0			) == Invalid);
	ASSERT_TRUE(p.pieceAt(0			, -1		) == Invalid);
	ASSERT_TRUE(p.pieceAt(BOARD_ROWS, 0			) == Invalid);
	ASSERT_TRUE(p.pieceAt(0			, BOARD_COLS) == Invalid);
}

TEST(PiezasTest, gameState)
{
	Piezas p;
	// Invalid if the game is not over
	// _ _ _ _
	// _ _ _ _ <== return invalid
	// O X O X 
	p.dropPiece(1); p.dropPiece(0);
	p.dropPiece(2); p.dropPiece(3);
	ASSERT_TRUE(p.gameState() == Invalid);
	p.reset();

	// The winner is which player has the most adjacent pieces in a single line.
	// Lines can go either vertically or horizontally.
	// O O X O 
	// O O X O
	// X X X X <== X wins
	p.dropPiece(0); p.dropPiece(0);
	p.dropPiece(1); p.dropPiece(1);
	p.dropPiece(2); p.dropPiece(0);
	p.dropPiece(3); p.dropPiece(1);
	p.dropPiece(2); p.dropPiece(3);
	p.dropPiece(2); p.dropPiece(3);
	ASSERT_TRUE(p.gameState() == X);
	p.reset();

	// X X O O <== O wins
	// O X X O
	// X O X O 
	p.dropPiece(0); p.dropPiece(1);
	p.dropPiece(2); p.dropPiece(3);
	p.dropPiece(1); p.dropPiece(0);
	p.dropPiece(2); p.dropPiece(3);
	p.dropPiece(0); p.dropPiece(2);
	p.dropPiece(1); p.dropPiece(3);
	ASSERT_TRUE(p.gameState() == O);
	p.reset();

	// If both X's and O's have the same number of pieces in a line, it is a tie.
	// Blank if the board is filled and no one has won ("tie").
	// X O X O 
	// O O O O <== tie
	// X X X X <== tie
	p.dropPiece(0); p.dropPiece(0);
	p.dropPiece(1); p.dropPiece(1);
	p.dropPiece(2); p.dropPiece(2);
	p.dropPiece(3); p.dropPiece(3);
	p.dropPiece(0); p.dropPiece(1);
	p.dropPiece(2); p.dropPiece(3);
	ASSERT_TRUE(p.gameState() == Blank);
	p.reset();
	
	//     v v == tie
	// X O X O
	// X O X O
	// X O X O
	p.dropPiece(0); p.dropPiece(1);
	p.dropPiece(0); p.dropPiece(1);
	p.dropPiece(0); p.dropPiece(1);
	p.dropPiece(2); p.dropPiece(3);
	p.dropPiece(2); p.dropPiece(3);
	p.dropPiece(2); p.dropPiece(3);
	ASSERT_TRUE(p.gameState() == Blank);
	p.reset();
}





















