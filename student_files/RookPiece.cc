#include "RookPiece.hh"
#include "ChessBoard.hh"
using namespace Student;

RookPiece::RookPiece(ChessBoard &board, Color color, int row, int column)
    : ChessPiece(board, color, row, column, Rook)
{
}

const char* RookPiece::toString() {
    if (getColor() == White) {
        return "♖";
    }
    return "♜";
}

bool RookPiece::canMoveToLocation(int toRow, int toColumn) {
    // checking the board bounds -- has to be inside
    if (toRow < 0 || toRow >= getBoard().getNumRows() ||
        toColumn < 0 || toColumn >= getBoard().getNumCols()) {
        return false;
    }


    if (getRow() != toRow && getColumn() != toColumn) {
        return false;
    }

    int rowDirection = (toRow > getRow()) ? 1 : (toRow < getRow()) ? -1 : 0;
    int colDirection = (toColumn > getColumn()) ? 1 : (toColumn < getColumn()) ? -1 : 0;

    //check for any pieces blockingd the path
    int row = getRow() + rowDirection;
    int col = getColumn() + colDirection;

    while (row != toRow || col != toColumn) {
        if (getBoard().getPiece(row, col) != nullptr) {
            return false;
        }
        row += rowDirection;
        col += colDirection;
    }

    //check destination spot
    ChessPiece* target = getBoard().getPiece(toRow, toColumn);
    if (target != nullptr && target->getColor() == getColor()) {
        return false; // cannot capture own piece
    }

    return true; // valid move
}

