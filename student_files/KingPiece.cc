#include "KingPiece.hh"
#include "ChessBoard.hh"

using namespace Student;

KingPiece::KingPiece(ChessBoard &board, Color color, int row, int column)
    : ChessPiece(board, color, row, column, King)
{
}

const char *KingPiece::toString()
{
    if (getColor() == White) {
        return "♔";
    }
    return "♚";
}

bool KingPiece::canMoveToLocation(int toRow, int toColumn)
{
    // check the board bounds
    if (toRow < 0 || toRow >= getBoard().getNumRows() ||
        toColumn < 0 || toColumn >= getBoard().getNumCols()) {
        return false;
    }

    int rowDiff = toRow - getRow();
    int colDiff = toColumn - getColumn();

    if (rowDiff < 0) {
        rowDiff = -rowDiff;
    }
    if (colDiff < 0) {
        colDiff = -colDiff;
    }

    // king moves exactly one square in any direction
    if (rowDiff > 1 || colDiff > 1) {
        return false;
    }
    if (rowDiff == 0 && colDiff == 0) {
        return false;
    }

    // check destination square
    ChessPiece *target = getBoard().getPiece(toRow, toColumn);
    if (target != nullptr && target->getColor() == getColor()) {
        return false;
    }

    return true;
}
