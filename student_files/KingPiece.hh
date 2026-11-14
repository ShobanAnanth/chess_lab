#ifndef __KINGPIECE_H__
#define __KINGPIECE_H__

#include "ChessPiece.hh"

/**
 * Student implementation of a King chess piece.
 * The class is defined within the Student namespace.
 */
namespace Student
{
    class KingPiece : public ChessPiece
    {
    public:
        // constructor for this piece
        KingPiece(ChessBoard &board, Color color, int row, int column);

        // check the kings basic movement
        bool canMoveToLocation(int toRow, int toColumn) override;

        // get the chess symbol
        const char *toString() override;
    };

}

#endif
