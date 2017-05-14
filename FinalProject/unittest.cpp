/*  File: unittest.cpp
    Final Project, 600.120 Spring 2017

    David A. Kleinberg
    600.120 | dkleinb1
    dkleinb1@jhu.edu
    ~~~~~~~~~~~~~~~~~~~
    Benjamin A. Kaminow
    600.120 | bkamino1
    bkamino1@jhu.edu
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <fstream>
#include "Chess.h"
#include "Game.h"
#include "Terminal.h"
#include "Prompts.h"

using std::cout;
using std::endl;

void testPawn(){
  ChessGame chess;
  Position whiteArray[4] = {Position(0,1), Position(0,5), Position(1,1), Position(3, 4)};
  Position blackArray[4] = {Position(0,2), Position(0,6), Position(1,6), Position(4, 3)};

  for (Position p : whiteArray)
    chess.initPiece(PAWN_ENUM, WHITE, p);
  for (Position p : blackArray)
    chess.initPiece(PAWN_ENUM, BLACK, p);

  Piece* whitePieces[2] = {chess.getPiece(whiteArray[0]), chess.getPiece(whiteArray[2])};
  Piece* blackPieces[2] = {chess.getPiece(blackArray[1]), chess.getPiece(blackArray[2])};  

  //-----White Pawn Tests-----
  assert(whitePieces[0]->validMove(whiteArray[0], blackArray[0], chess.getBoard()) == MOVE_ERROR_BLOCKED); //Pawn tries to move on top of another pawn
  assert(whitePieces[0]->validMove(whiteArray[0], Position(0,3), chess.getBoard()) == MOVE_ERROR_BLOCKED); //Pawn tries to move two spaces over another pawn
  assert(whitePieces[0]->validMove(whiteArray[0], Position(1,2), chess.getBoard()) == MOVE_ERROR_ILLEGAL); //Pawn tries to move diagonally in a non-capture situation

  assert(whitePieces[1]->validMove(whiteArray[2], blackArray[0], chess.getBoard()) == SUCCESS); //Pawn tries to capture pawn of opposite color
  assert(whitePieces[1]->validMove(whiteArray[2], Position(1,2), chess.getBoard()) == SUCCESS); //Pawn tries to move forward one space (no blocking pieces)
  assert(whitePieces[1]->validMove(whiteArray[2], Position(1,3), chess.getBoard()) == SUCCESS); //Pawn tries to move forward two spaces from the start (no blocking pieces)
  assert(whitePieces[1]->validMove(whiteArray[2], Position(2,1), chess.getBoard()) == MOVE_ERROR_ILLEGAL); //Pawn tries to move one space to the side.
  assert(whitePieces[1]->validMove(whiteArray[2], Position(1,0), chess.getBoard()) == MOVE_ERROR_ILLEGAL); //Pawn tries to move backward

  //-----Black Pawn Tests-----
  assert(blackPieces[0]->validMove(blackArray[1], whiteArray[1], chess.getBoard()) == MOVE_ERROR_BLOCKED); //Pawn tries to move on top of another pawn
  assert(blackPieces[0]->validMove(blackArray[1], Position(0,4), chess.getBoard()) == MOVE_ERROR_BLOCKED); //Pawn tries to move two spaces over another pawn
  assert(blackPieces[0]->validMove(blackArray[1], Position(1,5), chess.getBoard()) == MOVE_ERROR_ILLEGAL); //Pawn tries to move diagonally in a non-capture situation

  assert(blackPieces[1]->validMove(blackArray[2], whiteArray[1], chess.getBoard()) == SUCCESS); //Pawn tries to capture pawn of opposite color
  assert(blackPieces[1]->validMove(blackArray[2], Position(1,5), chess.getBoard()) == SUCCESS); //Pawn tries to move forward one space (no blocking pieces)
  assert(blackPieces[1]->validMove(blackArray[2], Position(1,4), chess.getBoard()) == SUCCESS); //Pawn tries to move forward two spaces from the start (no blocking pieces)
  assert(blackPieces[1]->validMove(blackArray[2], Position(2,6), chess.getBoard()) == MOVE_ERROR_ILLEGAL); //Pawn tries to move one space to the side.
  assert(blackPieces[1]->validMove(blackArray[2], Position(1,7), chess.getBoard()) == MOVE_ERROR_ILLEGAL); //Pawn tries to move backward

  std::cout << "All pawn movement tests passed!" << std::endl;
}
void testRook(){
  ChessGame chess;
  Position whiteArray[3] = {Position(0,0), Position(3,7), Position(7,7)};
  Position blackArray[3] = {Position(1,7), Position(3,0), Position(7,0)};

  for (Position p : whiteArray)
    chess.initPiece(ROOK_ENUM, WHITE, p);
  for (Position p : blackArray)
    chess.initPiece(ROOK_ENUM, BLACK, p);

  Piece* whitePieces[3] = {chess.getPiece(whiteArray[0]), chess.getPiece(whiteArray[1]), chess.getPiece(whiteArray[2])};
  Piece* blackPieces[3] = {chess.getPiece(blackArray[0]), chess.getPiece(blackArray[1]), chess.getPiece(blackArray[2])};

  Position wPos = whiteArray[0];
  Position bPos = blackArray[0];
    
  //Rook tries to move forward 1-7 spaces
  for (unsigned int i = 1; i < 7; i++){
    assert(whitePieces[0]->validMove(wPos, Position(wPos.x, wPos.y+i), chess.getBoard()) == SUCCESS);
    assert(blackPieces[0]->validMove(bPos, Position(bPos.x, bPos.y-i), chess.getBoard()) == SUCCESS);
  }

  //-----White Rook Tests-----
  assert(whitePieces[1]->validMove(whiteArray[1], blackArray[0], chess.getBoard()) == SUCCESS); //White rook tries to capture black rook with no pieces in between
  assert(whitePieces[1]->validMove(whiteArray[1], whiteArray[2], chess.getBoard()) == MOVE_ERROR_BLOCKED); //White rook tries to capture white rook
  assert(whitePieces[2]->validMove(whiteArray[2], blackArray[0], chess.getBoard()) == MOVE_ERROR_BLOCKED); //White rook tries to capture black rook with piece in the way
  assert(whitePieces[2]->validMove(whiteArray[2], whiteArray[0], chess.getBoard()) == MOVE_ERROR_ILLEGAL); //White rook tried to move diagonally

  //-----Black Rook Tests-----
  assert(blackPieces[1]->validMove(blackArray[1], whiteArray[0], chess.getBoard()) == SUCCESS); //Black rook tries to capture white rook with no pieces in between
  assert(blackPieces[1]->validMove(blackArray[1], blackArray[2], chess.getBoard()) == MOVE_ERROR_BLOCKED); //Black rook tries to capture black rook
  assert(blackPieces[2]->validMove(blackArray[2], whiteArray[0], chess.getBoard()) == MOVE_ERROR_BLOCKED); //Black rook tries to capture white rook with piece in the way
  assert(blackPieces[2]->validMove(blackArray[2], blackArray[0], chess.getBoard()) == MOVE_ERROR_ILLEGAL); //Black rook tried to move diagonally

  std::cout << "All rook movement tests passed!" << std::endl;
}

void testBishop(){
  ChessGame chess;

  Position whiteArray[3] = {Position(3,3), Position(7,0), Position(7,7)};
  Position blackArray[3] = {Position(0,0), Position(0,7), Position(3,4)};

  for (Position p : whiteArray)
    chess.initPiece(BISHOP_ENUM, WHITE, p);
  for (Position p : blackArray)
    chess.initPiece(BISHOP_ENUM, BLACK, p);

  Piece* whitePieces[3] = {chess.getPiece(whiteArray[0]), chess.getPiece(whiteArray[1]), chess.getPiece(whiteArray[2])};
  Piece* blackPieces[3] = {chess.getPiece(blackArray[0]), chess.getPiece(blackArray[1]), chess.getPiece(blackArray[2])};

  Position wPos = whiteArray[0];
  Position bPos = blackArray[2];

  for (unsigned int i = 1; i < 3; i++){
    assert(whitePieces[0]->validMove(wPos, Position(wPos.x+i, wPos.y+i), chess.getBoard()) == SUCCESS); //White bishop moves up and to the right 1-3 squares
    assert(whitePieces[0]->validMove(wPos, Position(wPos.x-i, wPos.y+i), chess.getBoard()) == SUCCESS); //White bishop moves up and to the left 1-3 squares
    assert(whitePieces[0]->validMove(wPos, Position(wPos.x+i, wPos.y-i), chess.getBoard()) == SUCCESS); //White bishop moves down and to the right 1-3 squares
    assert(whitePieces[0]->validMove(wPos, Position(wPos.x-i, wPos.y-i), chess.getBoard()) == SUCCESS); //White bishop moves down and to the left 1-3 squares

    assert(blackPieces[0]->validMove(bPos, Position(bPos.x+i, bPos.y+i), chess.getBoard()) == SUCCESS); //Black bishop moves up and to the right 1-3 squares
    assert(blackPieces[0]->validMove(bPos, Position(bPos.x-i, bPos.y+i), chess.getBoard()) == SUCCESS); //Black bishop moves up and to the left 1-3 squares
    assert(blackPieces[0]->validMove(bPos, Position(bPos.x+i, bPos.y-i), chess.getBoard()) == SUCCESS); //Black bishop moves down and to the right 1-3 squares
    assert(blackPieces[0]->validMove(bPos, Position(bPos.x-i, bPos.y-i), chess.getBoard()) == SUCCESS); //Black bishop moves down and to the left 1-3 squares
  }

  assert(whitePieces[0]->validMove(wPos, whiteArray[2], chess.getBoard()) == MOVE_ERROR_BLOCKED); //White bishop tries to capture white bishop
  assert(whitePieces[0]->validMove(wPos, blackArray[0], chess.getBoard()) == SUCCESS); //White bishop tries to capture black bishop
  assert(whitePieces[0]->validMove(wPos, Position(7,3), chess.getBoard()) == MOVE_ERROR_ILLEGAL); //White bishop tries to move sideways

  assert(blackPieces[2]->validMove(bPos, blackArray[1], chess.getBoard()) == MOVE_ERROR_BLOCKED); //Black bishop tries to capture black bishop
  assert(blackPieces[2]->validMove(bPos, whiteArray[1], chess.getBoard()) == SUCCESS); //Black bishop tries to capture white bishop
  assert(blackPieces[2]->validMove(bPos, Position(7,4), chess.getBoard()) == MOVE_ERROR_ILLEGAL); //Black bishop tries to move sideways
  
  std::cout << "All bishop movement tests passed!" << std::endl;
}

void testKnight(){
  ChessGame chess;
  Position pos(4,4);
  chess.initPiece(KNIGHT_ENUM, WHITE, pos);
  chess.initPiece(PAWN_ENUM, WHITE, Position(4,5));
  Piece* piece = chess.getPiece(pos);

  assert(piece->validMove(pos, Position(5,6), chess.getBoard()) == SUCCESS); //Check valid move while "jumping" over a piece
  assert(piece->validMove(pos, Position(2,3), chess.getBoard()) == SUCCESS); //Valid move with no piece in the path
  assert(piece->validMove(pos, Position(7,7), chess.getBoard()) == MOVE_ERROR_ILLEGAL); //Knight Can't move diagonally

  std::cout << "All knight movement tests passed!" << std::endl;
}

//Minimal testing is necessary since the Queen validMove function uses the already tested bishop and rook validMove functions.
void testQueen(){
  ChessGame chess;
  Position pos(4,4);
  chess.initPiece(QUEEN_ENUM, WHITE, pos);
  Piece* piece = chess.getPiece(pos);

  assert(piece->validMove(pos, Position(7,7), chess.getBoard()) == SUCCESS); //Check moving diagonally
  assert(piece->validMove(pos, Position(7,4), chess.getBoard()) == SUCCESS); //Check moving straight
  assert(piece->validMove(pos, Position(5,6), chess.getBoard()) == MOVE_ERROR_ILLEGAL); //Check that Queen can't make Knight moves

  std::cout << "All queen movement tests passed!" << std::endl;
}

void testKing(){
  ChessGame chess;
  Position pos(4,4);
  chess.initPiece(KING_ENUM, WHITE, pos);
  Piece* piece = chess.getPiece(pos);

  //Test movement to all squares one spot away from the king
  for (int xMod = -1; xMod < 2; xMod++){
    for (int yMod = -1; yMod < 2; yMod++){
      if ((xMod == 0) && (yMod == 0))
	continue;
      assert(piece->validMove(pos, Position(pos.x+xMod, pos.y+yMod), chess.getBoard()) == SUCCESS);
    }
  }

  assert(piece->validMove(pos, Position(7,7), chess.getBoard()) == MOVE_ERROR_ILLEGAL); //Test that King can't move illegally

  std::cout << "All king movement tests passed!" << std::endl;
}

void testCheck(){
  ChessGame chess;
  chess.initPiece(KING_ENUM, WHITE, Position(0,0));
  chess.initPiece(ROOK_ENUM, BLACK, Position(7,0));
  chess.initPiece(ROOK_ENUM, BLACK, Position(6,1));

  assert(chess.checkChecked());

  std::cout << "Check test passed!" << std::endl;
}

void testTestMove(){
  ChessGame chess;
  Position king(0,0);
  Position pawn(1,1);
  Position bishop(5,5);
  chess.initPiece(KING_ENUM, WHITE, king);
  chess.initPiece(PAWN_ENUM, WHITE, pawn);
  chess.initPiece(BISHOP_ENUM, BLACK, bishop);
  
  chess.moveKing(WHITE, Position(0,0));
  chess.moveKing(BLACK, Position(7,7));
  chess.presetTurn(WHITE);
  
  assert(chess.testMove(pawn, Position(1,2), WHITE, false) == MOVE_ERROR_CANT_EXPOSE_CHECK);
  assert(chess.testMove(king, Position(1,0), WHITE, false) == SUCCESS);

  std::cout << "Test Move test passed!" << std::endl;
}

void testCheckmate(){
  ChessGame chess;
  chess.initPiece(KING_ENUM, WHITE, Position(0,0));
  chess.initPiece(ROOK_ENUM, BLACK, Position(7,0));
  chess.initPiece(ROOK_ENUM, BLACK, Position(6,1));
  chess.presetTurn(WHITE);
  chess.moveKing(WHITE, Position(0,0));
  chess.moveKing(BLACK, Position(7,7));
  chess.checkChecked();
  
  assert(chess.checkCheckmate(false)); //Test positive checkmate


  ChessGame chess1;
  chess1.initPiece(KING_ENUM, WHITE, Position(0,0));
  chess1.initPiece(PAWN_ENUM, WHITE, Position(0,1));
  chess1.initPiece(PAWN_ENUM, WHITE, Position(1,0));
  chess1.initPiece(BISHOP_ENUM, BLACK, Position(5,5));
  chess1.presetTurn(WHITE);
  chess1.moveKing(WHITE, Position(0,0));
  chess1.moveKing(BLACK, Position(7,7));
  chess1.checkChecked();

  assert(chess1.checkCheckmate(false)); //Test positive checkmate

  ChessGame chess2;
  chess2.initPiece(KING_ENUM, WHITE, Position(0,0));
  chess2.initPiece(PAWN_ENUM, WHITE, Position(0,1));
  chess2.initPiece(PAWN_ENUM, BLACK, Position(1,0));
  chess2.initPiece(BISHOP_ENUM, BLACK, Position(5,5));
  chess2.presetTurn(WHITE);
  chess2.moveKing(WHITE, Position(0,0));
  chess2.moveKing(BLACK, Position(7,7));
  chess2.checkChecked();
  
  assert(!chess2.checkCheckmate(false));

  std::cout << "Checkmate test passed!" << std::endl; //Test not checkmate
}

int main() {
  testPawn();
  testRook();
  testBishop();
  testKnight();
  testQueen();
  testKing();
  testCheck();
  testTestMove();
  testCheckmate();
  return 0;
}
