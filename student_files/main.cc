#include "ChessBoard.hh"
#include <iostream>

using namespace Student;

int main() {
    ChessBoard board(8, 8);

    board.createChessPiece(White, Pawn, 6, 3);
    board.createChessPiece(Black, Pawn, 1, 3);

    // white moves first
    std::cout << board.movePiece(6, 3, 5, 3) << std::endl; // 1

    // white cannot move twice
    std::cout << board.movePiece(5, 3, 4, 3) << std::endl; // 0

    // black moves next
    std::cout << board.movePiece(1, 3, 2, 3) << std::endl; // 1

    // white can move again
    std::cout << board.movePiece(5, 3, 4, 3) << std::endl; // 1

    // confirm board updated
    std::cout << (board.getPiece(6, 3) == nullptr) << std::endl; // 1
    std::cout << (board.getPiece(4, 3) != nullptr) << std::endl; // 1

    // test capturing and position updates
    {
        ChessBoard board(8, 8);
        board.createChessPiece(White, Rook, 4, 2);
        board.createChessPiece(Black, Pawn, 4, 5);

        std::cout << board.movePiece(4, 2, 4, 5) << std::endl; // 1
        std::cout << (board.getPiece(4, 2) == nullptr) << std::endl; // 1
        std::cout << (board.getPiece(4, 5)->getColor() == White) << std::endl; // 1
        std::cout << (board.getPiece(4, 5)->getRow() == 4) << std::endl; // 1
        std::cout << (board.getPiece(4, 5)->getColumn() == 5) << std::endl; // 1
    }

    // test invalid move does not switch turns
    {
        ChessBoard board(8, 8);
        board.createChessPiece(White, Pawn, 6, 3);
        board.createChessPiece(Black, Pawn, 1, 3);

        std::cout << board.movePiece(6, 3, 7, 3) << std::endl; // 0
        std::cout << board.movePiece(1, 3, 2, 3) << std::endl; // 0
        std::cout << board.movePiece(6, 3, 5, 3) << std::endl; // 1
    }

    return 0;
}
