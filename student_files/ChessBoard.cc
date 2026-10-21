#include "ChessBoard.hh"
#include "PawnPiece.hh"
#include "RookPiece.hh"
#include "BishopPiece.hh"
#include "KingPiece.hh"

using Student::ChessBoard;

ChessBoard::ChessBoard(int numRow, int numCol)
    : numRows(numRow),
      numCols(numCol),
      board(numRow, std::vector<ChessPiece *>(numCol, nullptr))
{
    // The board is now sized, and every square starts empty.
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
    //Check that the starting position is within the board.
    if (startRow < 0 || startRow >= numRows || startColumn < 0 || startColumn >= numCols) {
        return;
    }

    //Delete any piece already at this position.
    if (board[startRow][startColumn] != nullptr) {
        delete board[startRow][startColumn];
        board[startRow][startColumn] = nullptr; 
    }

    //creates the requested piece type  and store it at this position.
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
    // TODO: Check bounds, piece presence, whose turn it is, and whether the
    // move is valid. If valid, update the board and the piece's position.
    // TODO: Update the turn after a successful move.
    return false;
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
    // TODO: Check bounds and that a piece exists at this position.
    // TODO: Check whether any opposing piece can legally move to this square.
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
