/*  File: Chess.h
    Final Project, 600.120 Spring 2017

    David A. Kleinberg
    600.120 | dkleinb1
    dkleinb1@jhu.edu
    ~~~~~~~~~~~~~~~~~~~
    Benjamin A. Kaminow
    600.120 | bkamino1
    bkamino1@jhu.edu
*/

#ifndef CHESS_H
#define CHESS_H

#include <vector>
#include "Game.h"

// Game status codes
enum status {
    LOAD_FAILURE = -10,
    SAVE_FAILURE,
    PARSE_ERROR,
    MOVE_ERROR_OUT_OF_BOUNDS,
    MOVE_ERROR_NO_PIECE,
    MOVE_ERROR_BLOCKED,
    MOVE_ERROR_CANT_CASTLE,
    MOVE_ERROR_MUST_HANDLE_CHECK,
    MOVE_ERROR_CANT_EXPOSE_CHECK,
    MOVE_ERROR_ILLEGAL,
    SUCCESS = 1,
    MOVE_CHECK,
    MOVE_CAPTURE,
    MOVE_CHECKMATE,
    MOVE_STALEMATE,
    GAME_WIN,
    GAME_OVER
};

// Possible pieces
enum PieceEnum {
    PAWN_ENUM = 0,
    ROOK_ENUM,
    KNIGHT_ENUM,
    BISHOP_ENUM,
    QUEEN_ENUM,
    KING_ENUM
};

class ChessPiece : public Piece {
protected:

    ChessPiece(Player owner, int id) : Piece(owner, id) {}
    
    bool checkRow(Position start, Position end, const Board& board) const;
    bool checkColumn(Position start, Position end, const Board& board) const;
};

class Pawn : public ChessPiece {
protected:
    friend PieceFactory<Pawn>;
    Pawn(Player owner, int id) : ChessPiece(owner, id) {}
public:
    int validMove(Position start, Position end,
		  const Board& board) const override;
};
class Rook : public ChessPiece {
protected:
    friend PieceFactory<Rook>;
    Rook(Player owner, int id) : ChessPiece(owner, id) {}
    int moved = 0;
public:
    int validMove(Position start, Position end,
		  const Board& board) const override;
    int isMoved() const { return moved; }
    void setMoved() { moved = 1; }
};
class Knight : public ChessPiece {
protected:
    friend PieceFactory<Knight>;
    Knight(Player owner, int id) : ChessPiece(owner, id) {}
public:
    int validMove(Position start, Position end,
		  const Board& board) const override;
};
class Bishop : public ChessPiece {
protected:
    friend PieceFactory<Bishop>;
    Bishop(Player owner, int id) : ChessPiece(owner, id) {}
public:
    int validMove(Position start, Position end,
		  const Board& board) const override;
};
class Queen : public ChessPiece {
protected:
    friend PieceFactory<Queen>;
    Queen(Player owner, int id) : ChessPiece(owner , id) {}
public:
    int validMove(Position start, Position end,
		  const Board& board) const override;
};
class King : public ChessPiece {
protected:
    friend PieceFactory<King>;
    King(Player owner, int id) : ChessPiece(owner, id) {}
    int moved = 0;
public:
    int validMove(Position start, Position end,
		  const Board& board) const override;
    //    int checkChecked(Position newPos, const Board& board) const;
    int checkCheckmate(const Position pos, const Board& board) const;
    int isMoved() const { return moved; }
    void setMoved() { moved = 1; }
};

class ChessGame : public Board {
public:
    ChessGame() : Board(8, 8) {
        // Add all factories needed to create Piece subclasses
        addFactory(new PieceFactory<Pawn>(PAWN_ENUM));
        addFactory(new PieceFactory<Rook>(ROOK_ENUM));
        addFactory(new PieceFactory<Knight>(KNIGHT_ENUM));
        addFactory(new PieceFactory<Bishop>(BISHOP_ENUM));
        addFactory(new PieceFactory<Queen>(QUEEN_ENUM));
        addFactory(new PieceFactory<King>(KING_ENUM));
    }

    // Setup the chess board with its initial pieces
    virtual void setupBoard();

    // Whether the chess game is over
    virtual bool gameOver() const override { return false; }

    // Make a move on the board. Return an integer representing the status
    // 0 = success
    virtual int makeMove(Position start, Position end) override;

    // The actual top-level game implementation
    virtual int run();

    void directUserInput(std::string& input);

    Position findKing(Player owner);

    void moveKing(Player owner, Position newPosition);

    bool checkChecked();
    bool checkStalemate();
    bool validMoveExists(Position start);
    int checkCheckmate(bool stalemate);

    bool loadFile();

    void presetTurn(int turn);

    int testMove(Position start, Position end, Player turn, bool checkmate);

    void promotePawn();
 private:

    bool hasWhite;
    bool hasBlack;
    Position whiteKing;
    Position blackKing;

    std::vector<Position> threateningPieces;
    //Position threateningPiece;
};

#endif
