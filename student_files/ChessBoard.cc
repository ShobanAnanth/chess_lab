#include "ChessBoard.hh"
#include "PawnPiece.hh"
#include "RookPiece.hh"
#include "BishopPiece.hh"
#include "KingPiece.hh"

using Student::ChessBoard;


//derived class
ChessBoard::ChessBoard(int numRow, int numCol)
    : numRows(numRow),
      numCols(numCol),
      board(numRow, std::vector<ChessPiece *>(numCol, nullptr))
{
  
    


}

ChessBoard::~ChessBoard()
{
    for (int i = 0; i < numRows; i++) {
        for (int j = 0; j < numCols; j++) {
            delete board[i][j];
        }
    }
}

void ChessBoard::createChessPiece(Color col, Type ty, int startRow, int startColumn)
{
  
    if (startRow < 0 || startRow >= numRows || startColumn < 0 || startColumn >= numCols) {
        return;
    }

    if (board[startRow][startColumn] != nullptr) {
        delete board[startRow][startColumn];
        board[startRow][startColumn] = nullptr; 
    }


    switch (ty) {
        case Type::Pawn:
            board[startRow][startColumn] =
                new Student::PawnPiece(*this, col, startRow, startColumn);
            break;
        case Type::Rook:
            board[startRow][startColumn] =
                new Student::RookPiece(*this, col, startRow, startColumn);
            break;
        case Type::Bishop:
            board[startRow][startColumn] =
                new Student::BishopPiece(*this, col, startRow, startColumn);
            break;
        case Type::King:
            board[startRow][startColumn] =
                new Student::KingPiece(*this, col, startRow, startColumn);
            break;
    }
}

bool ChessBoard::movePiece(int fromRow, int fromColumn, int toRow, int toColumn)
{
    // check if move is valid
    if (!isValidMove(fromRow, fromColumn, toRow, toColumn)) {
        return false;
    }

    if (fromRow == toRow && fromColumn == toColumn) {
        return false;
    }

    ChessPiece* piece = board[fromRow][fromColumn];

    // check if its this pieces turn
    if (piece->getColor() != turn) {
        return false;
    }

    // remove opponent piece if capturing
    if (board[toRow][toColumn] != nullptr) {
        delete board[toRow][toColumn];
    }

    // move piece to new position
    board[toRow][toColumn] = piece;
    board[fromRow][fromColumn] = nullptr;

    piece->setPosition(toRow, toColumn);

    // switch turns
    if (turn == White) {
        turn = Black;
    }
    else {
        turn = White;
    }

    return true;
}

bool ChessBoard::isValidMove(int fromRow, int fromColumn, int toRow, int toColumn)
{

    if (fromRow < 0 || fromRow >= numRows || fromColumn < 0 || fromColumn >= numCols) {
        return false;
    }
    if (toRow < 0 || toRow >= numRows || toColumn < 0 || toColumn >= numCols) {
        return false;
    }
    ChessPiece *piece = board.at(fromRow).at(fromColumn);
    if (piece == nullptr) {
        return false;
    }
    return piece->canMoveToLocation(toRow, toColumn);
    // there. Include any rules about capturing or blocking other pieces.
}

bool ChessBoard::isPieceUnderThreat(int row, int column)
{

    return false;
}

std::ostringstream ChessBoard::displayBoard()
{
    std::ostringstream outputString;
    // top scale
    outputString << "  ";
    for (int i = 0; i < numCols; i++){
        outputString << i << " ";
    }
    outputString << std::endl << "  ";
    // top border
    for (int i = 0; i < numCols; i++){
        outputString << "– ";
    }
    outputString << std::endl;

    for (int row = 0; row < numRows; row++){
        outputString << row << "|";
        for (int column = 0; column < numCols; column++){
            ChessPiece *piece = board.at(row).at(column);
            outputString << (piece == nullptr ? " " : piece->toString()) << " ";
        }
        outputString << "|" << std::endl;
    }

    // bottom border
    outputString << "  ";
    for (int i = 0; i < numCols; i++){
        outputString << "– ";
    }
    outputString << std::endl << std::endl;

    return outputString;


}
