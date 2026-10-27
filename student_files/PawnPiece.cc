
#include "PawnPiece.hh"
#include "ChessBoard.hh"
// needed headers

using namespace Student;

PawnPiece::PawnPiece(ChessBoard &board, Color color, int row, int column)
    : ChessPiece(board, color, row, column, Pawn)
{
}

const char* PawnPiece::toString() {
    if (getColor() == White) {
        return "♙";
    }
    return "♟";
}

bool PawnPiece::canMoveToLocation(int toRow, int toColumn) {
    int direction;

    if (getColor() == White) {
        direction = -1;
    }
    else {
        direction = 1; // its black
    }

    int rowDiff;
    int colDiff;

    rowDiff = toRow - getRow(); // passed row - current
    colDiff = toColumn - getColumn(); // passed col - current


    // calculating the starting row
    // white is 2 up from bottom, black is 1 (top)
    int startRow;

    if (getColor() == White){
        startRow = getBoard().getNumRows() - 2; // 2nd last
    }
    else {
        startRow = 1; // black on top
    }
    // check bounds
    if (toRow < 0 || toRow >= getBoard().getNumRows() ||
        toColumn < 0 || toColumn >= getBoard().getNumCols()) {
        return false;
    }

    // can we move, is there another pice?
    if (rowDiff == direction && colDiff == 0) {
        if (getBoard().getPiece(toRow, toColumn) == nullptr) {
            return true; // empty
        }
        return false; // not by def :(
    }

    if (getRow() == startRow && rowDiff == 2 * direction && colDiff == 0){
        if (getBoard().getPiece(getRow() + direction, getColumn()) == nullptr &&
            getBoard().getPiece(toRow, toColumn) == nullptr) {
            return true; // empty
        }
    }


// check if one move
    // check diagonal capture
    if (rowDiff == direction && (colDiff == 1 || colDiff == -1)) {
        ChessPiece* target = getBoard().getPiece(toRow, toColumn);

        if (target != nullptr && target->getColor() != getColor()) {
            return true;
        }
    }

    return false;
}

