// Unit tests for ChessBoard::isPieceUnderThreat.
// Kept outside student_files/ so the course Makefile does not compile a second main().
//
// Build and run from the repo root:
//   g++ -std=c++17 -Wall -I student_files student_files/ChessBoard.cc student_files/ChessPiece.cc \
//       student_files/PawnPiece.cc student_files/RookPiece.cc student_files/BishopPiece.cc \
//       tests/test_isPieceUnderThreat.cc -o tests/test_isPieceUnderThreat && ./tests/test_isPieceUnderThreat

#include "ChessBoard.hh"
#include <cstdio>

using Student::ChessBoard;

static int failures = 0;

static void check(const char *name, bool got, bool want)
{
    if (got == want) {
        printf("ok   %s\n", name);
    } else {
        printf("FAIL %s: got %s, want %s\n", name, got ? "true" : "false", want ? "true" : "false");
        failures++;
    }
}

static void testEmptyAndOutOfBounds()
{
    ChessBoard b(8, 8);
    b.createChessPiece(Black, Rook, 0, 0);
    check("empty square is not threatened", b.isPieceUnderThreat(3, 3), false);
    check("empty square in an enemy's path is not threatened", b.isPieceUnderThreat(0, 5), false);
    check("negative row", b.isPieceUnderThreat(-1, 0), false);
    check("negative column", b.isPieceUnderThreat(0, -1), false);
    check("row past the board", b.isPieceUnderThreat(8, 0), false);
    check("column past the board", b.isPieceUnderThreat(0, 8), false);
    check("lone piece is not threatened", b.isPieceUnderThreat(0, 0), false);
}

static void testRook()
{
    ChessBoard b(8, 8);
    b.createChessPiece(White, Bishop, 4, 4);
    b.createChessPiece(Black, Rook, 4, 0);
    check("rook threatens along a row", b.isPieceUnderThreat(4, 4), true);
    check("threat goes both ways (bishop can't reach rook)", b.isPieceUnderThreat(4, 0), false);

    ChessBoard c(8, 8);
    c.createChessPiece(White, Bishop, 4, 4);
    c.createChessPiece(Black, Rook, 0, 4);
    check("rook threatens along a column", c.isPieceUnderThreat(4, 4), true);

    c.createChessPiece(White, Pawn, 2, 4);
    check("rook blocked by the target's own piece", c.isPieceUnderThreat(4, 4), false);

    c.createChessPiece(Black, Pawn, 2, 4);
    check("rook blocked by its own piece", c.isPieceUnderThreat(4, 4), false);

    ChessBoard d(8, 8);
    d.createChessPiece(White, Bishop, 4, 4);
    d.createChessPiece(Black, Rook, 0, 0);
    check("rook does not threaten diagonally", d.isPieceUnderThreat(4, 4), false);
}

static void testBishop()
{
    ChessBoard b(8, 8);
    b.createChessPiece(White, Rook, 5, 5);
    b.createChessPiece(Black, Bishop, 1, 1);
    check("bishop threatens along a diagonal", b.isPieceUnderThreat(5, 5), true);

    b.createChessPiece(White, Pawn, 3, 3);
    check("bishop blocked on the diagonal", b.isPieceUnderThreat(5, 5), false);

    ChessBoard c(8, 8);
    c.createChessPiece(White, Rook, 5, 5);
    c.createChessPiece(Black, Bishop, 5, 1);
    check("bishop does not threaten along a row", c.isPieceUnderThreat(5, 5), false);

    ChessBoard d(8, 8);
    d.createChessPiece(White, Rook, 2, 5);
    d.createChessPiece(Black, Bishop, 5, 2);
    check("bishop threatens on the anti-diagonal", d.isPieceUnderThreat(2, 5), true);
}

static void testPawn()
{
    // White pawns move toward row 0, black pawns toward the last row.
    ChessBoard b(8, 8);
    b.createChessPiece(White, Pawn, 5, 3);
    b.createChessPiece(Black, Rook, 4, 2);
    b.createChessPiece(Black, Rook, 4, 4);
    check("white pawn threatens forward-left diagonal", b.isPieceUnderThreat(4, 2), true);
    check("white pawn threatens forward-right diagonal", b.isPieceUnderThreat(4, 4), true);

    ChessBoard c(8, 8);
    c.createChessPiece(White, Pawn, 5, 3);
    c.createChessPiece(Black, Rook, 4, 3);
    check("pawn does not threaten straight ahead", c.isPieceUnderThreat(4, 3), false);

    ChessBoard d(8, 8);
    d.createChessPiece(White, Pawn, 5, 3);
    d.createChessPiece(Black, Bishop, 6, 4);
    check("white pawn does not threaten backward diagonal", d.isPieceUnderThreat(6, 4), false);

    ChessBoard e(8, 8);
    e.createChessPiece(White, Pawn, 6, 3);
    e.createChessPiece(Black, Bishop, 4, 3);
    check("pawn's two-square first move is not a threat", e.isPieceUnderThreat(4, 3), false);

    ChessBoard f(8, 8);
    f.createChessPiece(Black, Pawn, 2, 3);
    f.createChessPiece(White, Rook, 3, 4);
    f.createChessPiece(White, Rook, 1, 4);
    check("black pawn threatens downward diagonal", f.isPieceUnderThreat(3, 4), true);
    check("black pawn does not threaten upward diagonal", f.isPieceUnderThreat(1, 4), false);
}

static void testColorsAndMultipleAttackers()
{
    ChessBoard b(8, 8);
    b.createChessPiece(White, Rook, 4, 4);
    b.createChessPiece(White, Rook, 4, 0);
    b.createChessPiece(White, Bishop, 0, 0);
    check("own-color pieces never threaten", b.isPieceUnderThreat(4, 4), false);

    ChessBoard c(8, 8);
    c.createChessPiece(Black, Bishop, 3, 3);
    c.createChessPiece(White, Rook, 3, 7);
    c.createChessPiece(White, Bishop, 6, 0);
    check("black piece threatened by white", c.isPieceUnderThreat(3, 3), true);
    check("bishop can't threaten a rook on its row", c.isPieceUnderThreat(3, 7), false);

    ChessBoard d(8, 8);
    d.createChessPiece(White, Rook, 4, 4);
    d.createChessPiece(Black, Rook, 0, 0);
    d.createChessPiece(Black, Bishop, 0, 1);
    d.createChessPiece(Black, Rook, 4, 7);
    check("one of several attackers can reach", d.isPieceUnderThreat(4, 4), true);

    ChessBoard e(8, 8);
    e.createChessPiece(Black, King, 0, 4);
    e.createChessPiece(White, Rook, 7, 4);
    check("king can be threatened", e.isPieceUnderThreat(0, 4), true);
}

static void testOtherBoardSizes()
{
    ChessBoard b(4, 4);
    b.createChessPiece(White, Rook, 3, 0);
    b.createChessPiece(Black, Rook, 0, 0);
    check("4x4: rook threat across the board", b.isPieceUnderThreat(3, 0), true);

    ChessBoard c(6, 6);
    c.createChessPiece(White, Bishop, 5, 5);
    c.createChessPiece(Black, Bishop, 0, 0);
    check("6x6: bishop threat corner to corner", c.isPieceUnderThreat(5, 5), true);

    ChessBoard d(4, 6);
    d.createChessPiece(White, Rook, 3, 5);
    d.createChessPiece(Black, Rook, 3, 0);
    check("4x6: rook threat along the long side", d.isPieceUnderThreat(3, 5), true);
    check("4x6: column 6 is off the board", d.isPieceUnderThreat(3, 6), false);
}

static void testBoardUnchanged()
{
    ChessBoard b(8, 8);
    b.createChessPiece(White, Rook, 4, 4);
    b.createChessPiece(Black, Rook, 4, 0);
    Student::ChessPiece *target = b.getPiece(4, 4);
    Student::ChessPiece *attacker = b.getPiece(4, 0);
    b.isPieceUnderThreat(4, 4);
    b.isPieceUnderThreat(4, 0);
    check("pieces stay on their squares",
          b.getPiece(4, 4) == target && b.getPiece(4, 0) == attacker, true);
    check("pieces keep their positions",
          target->getRow() == 4 && target->getColumn() == 4 &&
          attacker->getRow() == 4 && attacker->getColumn() == 0, true);
    check("path squares stay empty", b.getPiece(4, 2) == nullptr, true);
}

int main()
{
    testEmptyAndOutOfBounds();
    testRook();
    testBishop();
    testPawn();
    testColorsAndMultipleAttackers();
    testOtherBoardSizes();
    testBoardUnchanged();

    printf("\n%d failure(s)\n", failures);
    return failures == 0 ? 0 : 1;
}
