#include "KingPiece.hh"
#include "ChessBoard.hh"

using namespace Student;

// pass the starting info to chesspiece
KingPiece::KingPiece(ChessBoard &board, Color color, int row, int column)
    : ChessPiece(board, color, row, column, King)
{
}

// return the symbol based on color
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

    // difference between where we are and where we wanna go
    int rowDiff = toRow - getRow();
    int colDiff = toColumn - getColumn();

    // only care about distance here, not direction
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
    // cant just stay in the same spot :)
    if (rowDiff == 0 && colDiff == 0) {
        return false;
    }

    // check destination square
    ChessPiece *target = getBoard().getPiece(toRow, toColumn);
    if (target != nullptr && target->getColor() == getColor()) {
        return false;
    }

    // empty square or an opponent piece, so this works
    return true;
}
