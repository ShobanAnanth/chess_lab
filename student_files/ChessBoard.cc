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
    if (fromRow == toRow && fromColumn == toColumn) {
        return false;
    }
    ChessPiece *piece = board.at(fromRow).at(fromColumn);
    if (piece == nullptr) {
        return false;
    }
    if (!piece->canMoveToLocation(toRow, toColumn)) {
        return false;
    }

    // temporarily make the move to see if our king would be in check
    ChessPiece *captured = board.at(toRow).at(toColumn);
    board.at(toRow).at(toColumn) = piece;
    board.at(fromRow).at(fromColumn) = nullptr;
    piece->setPosition(toRow, toColumn);

    // find this color's king after the temporary move
    int kingRow = -1;
    int kingCol = -1;
    for (int r = 0; r < numRows; r++) {
        for (int c = 0; c < numCols; c++) {
            ChessPiece *p = board.at(r).at(c);
            if (p != nullptr && p->getType() == King && p->getColor() == piece->getColor()) {
                kingRow = r;
                kingCol = c;
            }
        }
    }

    bool leavesInCheck = false;
    if (kingRow != -1) {
        leavesInCheck = isPieceUnderThreat(kingRow, kingCol);
    }

    // undo the temporary move
    board.at(fromRow).at(fromColumn) = piece;
    board.at(toRow).at(toColumn) = captured;
    piece->setPosition(fromRow, fromColumn);

    if (leavesInCheck) {
        return false;
    }

    return true;
}

bool ChessBoard::isPieceUnderThreat(int row, int column)
{
    if (row < 0 || row >= numRows || column < 0 || column >= numCols) {
        return false;
    }
    ChessPiece *target = board.at(row).at(column);
    if (target == nullptr) {
        return false;
    }

    // only check if an opponent piece can attack this square,
    // even if that opponent piece could not legally move due to check
    for (int r = 0; r < numRows; r++) {
        for (int c = 0; c < numCols; c++) {
            ChessPiece *piece = board.at(r).at(c);
            if (piece == nullptr || piece->getColor() == target->getColor()) {
                continue;
            }
            if (piece->canMoveToLocation(row, column)) {
                return true;
            }
        }
    }
    return false;
}

std::ostringstream ChessBoard::displayBoard()
{
    std::ostringstream outputString;
    //top scale
    outputString << "  ";
    for (int i = 0; i < numCols; i++){
        outputString << i << " ";
    }
    outputString << std::endl << "  ";
    //top border
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
