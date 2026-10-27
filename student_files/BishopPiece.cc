#include "BishopPiece.hh"
#include "ChessBoard.hh"
#include <cstdlib>

using namespace Student;

BishopPiece::BishopPiece(ChessBoard &board, Color color, int row, int column)
    : ChessPiece(board, color, row, column, Bishop)
{
}

const char* BishopPiece::toString() {
    if (getColor() == White) { // if its white
        return "♗";
    }
    return "♝";
}

bool BishopPiece::canMoveToLocation(int toRow, int toColumn) {
    // check the board bounds, are we inside?
    if (toRow < 0 || toRow >= getBoard().getNumRows() ||
        toColumn < 0 || toColumn >= getBoard().getNumCols()) {
        return false;
    }

    int rowDiff = toRow - getRow();
    int colDiff = toColumn - getColumn();

    // bishop has to move diagnol
    if (abs(rowDiff) != abs(colDiff) || rowDiff == 0) {
        return false;
    }

    // which direction it acn move
    int rowDirection = 1;
    int colDirection = 1;

    if (rowDiff < 0) {
        rowDirection = -1;
    }

    if (colDiff < 0) {
        colDirection = -1;
    }

    int row = getRow() + rowDirection;
    int col = getColumn() + colDirection;

    // are there any pieces blocking the path to there?
    while (row != toRow && col != toColumn) {
        if (getBoard().getPiece(row, col) != nullptr) {
            return false;
        }

        row += rowDirection;
        col += colDirection;
    }

    // check destination square, before we continue
    ChessPiece* target = getBoard().getPiece(toRow, toColumn);

    if (target != nullptr && target->getColor() == getColor()) {
        return false;
    }

    return true;
}
