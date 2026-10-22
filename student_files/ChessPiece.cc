#include "ChessPiece.hh"

using namespace Student;

ChessPiece::ChessPiece(ChessBoard &board, Color color, int row, int column, Type type)
    : board(board), color(color), type(type), row(row), column(column)
{
}

Color ChessPiece::getColor() {
    return color;
}

Type ChessPiece::getType() {
    return type;
}

int ChessPiece::getRow() {
    return row;
}

int ChessPiece::getColumn() {
    return column;
}

void ChessPiece::setPosition(int row, int column) {
    this->row = row;
    this->column = column;
}