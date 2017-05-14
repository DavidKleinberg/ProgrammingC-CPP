/*  File: Chess.cpp
    Final Project, 600.120 Spring 2017

    David A. Kleinberg
    600.120 | dkleinb1
    dkleinb1@jhu.edu
    ~~~~~~~~~~~~~~~~~~~
    Benjamin A. Kaminow
    600.120 | bkamino1
    bkamino1@jhu.edu
*/

#undef FOR_RELEASE

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <algorithm>
#include <cstdlib>
#include "Game.h"
#include "Chess.h"
#include "Prompts.h"
#include "Terminal.h"

using std::string;
using std::cout;
using std::cin;
using std::endl;

//virtual check functions for left diagonal etc

// Make a move on the board. Return an int, with < 0 being failure
int ChessGame::makeMove(Position start, Position end) {
  if (!validPosition(start) || !validPosition(end)) {
    Prompts::outOfBounds();
    return MOVE_ERROR_OUT_OF_BOUNDS;
  }

  Piece* piece = m_pieces.at(index(start));

  //Check that there the player whose turn it is has a piece at the desired start position.
  if (!piece || piece->owner() != this->playerTurn()) {
    Prompts::noPiece();
    return MOVE_ERROR_NO_PIECE;
  }

  //Check that the player is not trying to move the piece to the same spot it already occupies.
  if (index(start) == index(end)) {
    Prompts::illegalMove();
    return MOVE_ERROR_ILLEGAL;
  }
  
  int moveStatus = testMove(start, end, playerTurn(), false);
  
  if (moveStatus == MOVE_ERROR_ILLEGAL) {
    Prompts::illegalMove();
        return MOVE_ERROR_ILLEGAL;
  }
  if (moveStatus == MOVE_ERROR_BLOCKED) {
    Prompts::blocked(); 
    return MOVE_ERROR_BLOCKED;
  }

  if (moveStatus == MOVE_ERROR_CANT_EXPOSE_CHECK){
    Prompts::cantExposeCheck();
    return MOVE_ERROR_CANT_EXPOSE_CHECK;
  }

  if (moveStatus == MOVE_ERROR_MUST_HANDLE_CHECK){
    Prompts::mustHandleCheck();
    return MOVE_ERROR_MUST_HANDLE_CHECK;
  }

  //If the player puts the other player in check, check to see if it is checkmate.
  //If the other player is not in check, check to see if they're in stalemate.
  if (moveStatus == MOVE_CHECK){
    if (checkCheckmate(false)){
      Prompts::checkMate(playerTurn());
      Prompts::win(playerTurn(), turn());
      return MOVE_CHECKMATE;
    }
    Prompts::check(Player(playerTurn()));
  }
  else {
    if (checkStalemate()){
      Prompts::staleMate();
      return MOVE_STALEMATE;
    }
  }

  //if (getPiece(end)) {
    
  //}

    //delete endPiece;
  this->m_turn += 1;
  return SUCCESS;
  
}

// Setup the chess board with its initial pieces
void ChessGame::setupBoard() {
    std::vector<int> pieces {
        ROOK_ENUM, KNIGHT_ENUM, BISHOP_ENUM, QUEEN_ENUM,
        KING_ENUM, BISHOP_ENUM, KNIGHT_ENUM, ROOK_ENUM
    };
    for (size_t i = 0; i < pieces.size(); ++i) {
        initPiece(PAWN_ENUM, WHITE, Position(i, 1));
        initPiece(pieces[i], WHITE, Position(i, 0));
        initPiece(pieces[i], BLACK, Position(i, 7));
        initPiece(PAWN_ENUM, BLACK, Position(i, 6));
    }

    //Set the positions for the kings. This allows us to find them easily later in order to check for checkmate/stalemate.
    whiteKing = Position(4, 0);
    blackKing = Position(4, 7);
}

//Allows us to easily find the king. This function is to minimize code duplication (i.e. so we don't have this if statement every time we want to get the king's position).
Position ChessGame::findKing(Player owner) {
    if (owner == WHITE) {
        return whiteKing;
    } else {
        return blackKing;
    }
}

//Updates the king's position. Minimizes code duplication in the same manner as the findKing method.
void ChessGame::moveKing(Player owner, Position newPosition) {
    if (owner == WHITE) {
        whiteKing = newPosition;
    } else {
        blackKing = newPosition;
    }
}

//Checks in the row of start and end to see if there's a piece in the way. Minimizes code duplication (rook and pawn share the same code).
bool ChessPiece::checkRow(Position start, Position end, const Board& board) const {
  if (start.x < end.x) { //unnecessary (for loop condition)
        for (unsigned int i = start.x+1; i < end.x; i++) {
            if (board.getPiece(Position(i, end.y)) != nullptr) {
                return false;
            }
        }
    } else {
        for (unsigned int i = start.x-1; i > end.x; i--) {
            if (board.getPiece(Position(i, end.y)) != nullptr) {
                return false;
            }
        }
    }
    return true;
}


//Checks in the column of start and end to see if there's a piece in the way. Also minimzes code duplication.
bool ChessPiece::checkColumn(Position start, Position end, const Board& board) const {
    if (start.y < end.y) { //Shouldn't the for loop prevent this condition?
        for (unsigned int i = start.y+1; i < end.y; i++) {
	  if (board.getPiece(Position(end.x, i)) != nullptr) {
                //return MOVE_ERROR_BLOCKED;
                return false;
            }
        }
    } else {
        for (unsigned int i = start.y-1; i > end.y; i--) {
            if (board.getPiece(Position(end.x, i)) != nullptr) {
                //return MOVE_ERROR_BLOCKED;
                return false;
            }
        }
    }
    return true;
}

//Function to perform a move and then undo the move if it puts the moving player in check or fails to handle check.
//The checkmate flag is used if this function is called from the checkmate/stalemate functions. In this case, we want the move to be undone regardless of whether it's successful or not.
//If this function is called normally from the makeMove function, we want the move to be kept (assuming it doesn't place the player in check.
int ChessGame::testMove(Position start, Position end, Player turn, bool checkmate){
  Piece* piece = m_pieces.at(index(start));

  int moveStatus = piece->validMove(start, end, getBoard());
  if (moveStatus < 0)
    return moveStatus;
  
  Piece* endPiece = m_pieces.at(index(end));
  bool checked = checkChecked();
  Player playerChecked;
  if (checked)
    playerChecked = Player(!(m_pieces.at(index(threateningPieces[0]))->owner()));
  
  m_pieces.at(index(end)) = piece;
  m_pieces.at(index(start)) = nullptr;
  
  if (piece->id() == KING_ENUM)
    moveKing(Player(turn), end);

  std::vector<Position> tempThreatPieces = threateningPieces;
  
  bool endChecked = checkChecked();
  if (endChecked){
    Player endPlayerChecked = Player(!(m_pieces.at(index(threateningPieces[0]))->owner()));
          
    if (endPlayerChecked == turn){
      m_pieces.at(index(end)) = endPiece;
      m_pieces.at(index(start)) = piece;
      if (piece->id() == KING_ENUM)
	moveKing(Player(turn), start);
      threateningPieces = tempThreatPieces;
      if (!checked)
	return MOVE_ERROR_CANT_EXPOSE_CHECK;
      else if (playerChecked == endPlayerChecked)
	return MOVE_ERROR_MUST_HANDLE_CHECK;
    }
    if (checkmate){
      m_pieces.at(index(end)) = endPiece;
      m_pieces.at(index(start)) = piece;
      if (piece->id() == KING_ENUM)
	moveKing(Player(turn), start);
      threateningPieces = tempThreatPieces;
    }
    else if (endPiece) {
      Prompts::capture(this->playerTurn());
      delete endPiece;
    }
    return MOVE_CHECK;
  }

  if (checkmate){
    m_pieces.at(index(end)) = endPiece;
    m_pieces.at(index(start)) = piece;
    if (piece->id() == KING_ENUM)
      moveKing(Player(turn), start);
    threateningPieces = tempThreatPieces;
  }
  else if (endPiece) {
      Prompts::capture(this->playerTurn());
      delete endPiece;
  }

  if (piece->id() == PAWN_ENUM)
    promotePawn();
  
  return SUCCESS;
}
  
//Function to check if either king is in check.
//Does so by looping through each piece and seeing if it has a valid move to the opponent's king.
//Store all the pieces threatening the king in a vector in case there happens to be more than one (can happen if a piece is moved to expose check in one direction while also checking
//	the king from another point.
bool ChessGame::checkChecked() {
  threateningPieces.clear();
  
  unsigned int i = 0;
  for (Piece* p : m_pieces) {
   if (!p) {
      i++;
      continue;
   }

   
   Position start = getPos(i);
   
   Player opponent = Player(!(p->owner()));
   
   if (p->validMove(start, findKing(opponent), getBoard()) > 0){
     threateningPieces.push_back(start);
   }
   i++;
  }
  return threateningPieces.size() > 0; 
}

//Function to loop through each position on the board and check if the piece at start has a valid move to that position. This is used by the stalemate method to determine if any piece
//	can make a move or if it is actually a stalemate.
//Only checks for the player that didn't just move since you can't put yourself in stalemate.
bool ChessGame::validMoveExists(Position start){
  //Don't need to check that there is a piece at the start position.
  //The only time this is called is during checkStalemate, in which we already check
  //	that there is a piece at the position.

  Player turn = Player(!playerTurn());
  Piece* piece = m_pieces.at(index(start));
  for (unsigned int x = 0; x < width(); x++){
    for (unsigned int y = 0; y < height(); y++){
      Position end(x, y);
      if (piece->owner() != turn)
	continue;
      if ((end.x == start.x) && (end.y == start.y))
	continue;
      if (testMove(start, end, turn, true) > 0)
	return true;
    }
  }
  return false;
}

//Function that checks for stalemate.
//Does so by looping through all of the pieces and checking if a valid move exists for them using the validMoveExists function above.
bool ChessGame::checkStalemate(){
  //Checks if the king can make a move without putting itself in check. If this is true, then it's not stalemate either.
  if (!checkCheckmate(true))
    return 0;

  unsigned int i = 0;

  for (Piece* piece : m_pieces){
    if ((!piece) || (piece->owner() == playerTurn())){
      i++;
      continue;
    }
    
    Position start = getPos(i);
    if (validMoveExists(start))
      return 0;
    i++;
  }

  return 1;
}
  
//Function that checks for checkmate.
//Does so by first checking if the king can make a move to escape. If that's not the case then:
//	First check if more than one piece is attacking the king. If this is the case, the only way to escape checkmate is for the king to move. If the function reaches this point, we know the king has no available moves. Thus, return that it is checkmate.
//	If the stalemate flag is set to true, then return true at this point. The king is not in check in stalemate so it makes no sense to check if a piece can move to block check. We only use the checkmate function to minimize code duplication, as we still want to check if the king can make a move that will not put itself in check.
//If neither of the above conditions is met, find the direction from which the piece (we now know there is only one) is threatening the king. Then, loop through the pieces that are the same color as the king that is being threatened and see if any of them have a valid move into the path of attack.
int ChessGame::checkCheckmate(bool stalemate) {
  Player turn = Player(!playerTurn());
  Position king = findKing(turn);
  for (int xMod = -1; xMod < 2; xMod++){
    for (int yMod = -1; yMod < 2; yMod++){
      if ((yMod == 0) && (xMod == 0))
	continue;
      Position newKingPos = Position(king.x+xMod, king.y+yMod);
      if (!validPosition(newKingPos))
	continue;
      if (testMove(king, newKingPos, turn, true) > 0)
	return 0;
    }
  }
  if ((threateningPieces.size() > 1) || stalemate)
    return 1;

  int xDiff = threateningPieces[0].x - king.x;
  int yDiff = threateningPieces[0].y - king.y;

  if ((abs(xDiff) <= 1) && (abs(yDiff) <= 1)){
    return 1;
  }

  int horizontal;
  if (xDiff == 0)
    horizontal = 0;
  else
    horizontal = xDiff/abs(xDiff);
  
  int vertical;
  if (yDiff == 0)
    vertical = 0;
  else
    vertical = yDiff/abs(yDiff);

  unsigned int j = 0;

  Piece* threatPiece = m_pieces.at(index(threateningPieces[0]));
  
  for (Piece* piece : m_pieces){
    if ((!piece) || (piece->owner() != turn)){
      j++;
      continue;
    }
    
    Position start = getPos(j);

    if (threatPiece->id() == KNIGHT_ENUM){
      if (testMove(start, threateningPieces[0], turn, true) > 0)
	return 0;
    }
    else {
      continue;
    }
    
    int i = 1;
    int intXPos;
    int intYPos;
    while (((horizontal) && (i < abs(xDiff)+1)) || ((vertical) && (i < abs(yDiff)+1))){
      intXPos = king.x + (i*horizontal);
      intYPos = king.y + (i*vertical);
      if (testMove(start, Position(intXPos, intYPos), turn, true) > 0){
	return 0;
      }
      i++;
    }
    j++;
  }
  return 1;
}

//Function to check if a pawn has made it to the opposite end and promote it to a queen if so.
void ChessGame::promotePawn(){
  Player turn = playerTurn();
  unsigned int yPos = (m_height-1)*(!turn);
  for (unsigned int xPos = 0; xPos < m_width; xPos++){
    Position pos(xPos, yPos);
    Piece* p = m_pieces.at(index(pos));
    if ((!p) || (p->owner() != turn) || (p->id() != PAWN_ENUM))
      continue;

    m_pieces.at(index(pos)) = nullptr;
    initPiece(QUEEN_ENUM, turn, pos);
    delete p;
    return;
  }
}
    
//Pawn validMove function. Utilizes the previously defined checkColumn function.
int Pawn::validMove(Position start, Position end, const Board& board) const {

    Piece* endPiece = board.getPiece(end);

    //check forwards
    if ((m_owner == WHITE) && ((int)end.y - (int)start.y <= 0)) {
        return MOVE_ERROR_ILLEGAL;
    }
    if ((m_owner == BLACK) && ((int)end.y - (int)start.y >= 0)) {
        return MOVE_ERROR_ILLEGAL;
    }

    unsigned int yDiff = abs((int)end.y - (int)start.y);
    
    //moving two squares on pawn's first move
    if (((yDiff > 1) && (start.y != 1) && (start.y != 6)) || (yDiff > 2)) {
        //can do 1 or 6 because 2 from the opposite is out of bounds
        return MOVE_ERROR_ILLEGAL;
    }

    if (start.x == end.x) {
        if (!checkColumn(start, Position(end.x, end.y+1), board)) {
            return MOVE_ERROR_BLOCKED;
	} else if (!checkColumn(start, Position(end.x, end.y-1), board)) {
            return MOVE_ERROR_BLOCKED;
        } else if (yDiff <= 2) {
          return SUCCESS;
        }
    } else {
      //Must be capture:
      //Moving diagonal forwards (one space)
      if (abs((int)end.y - (int)start.y) == 1 && abs((int)end.x - (int)start.x) == 1) {
          if (endPiece != nullptr && endPiece->owner() != m_owner) {
              return SUCCESS;
          }
      }
    }
  return MOVE_ERROR_ILLEGAL;
}

//Rook validMove function. Utilizes the previously defined checkColumn and checkRow functions.
int Rook::validMove(Position start, Position end, const Board& board) const {
    //Does not include castling functionality yet
    Piece* endPiece = board.getPiece(end);

    //Moving left and right
    if (start.y == end.y) {

        if (!checkRow(start, end, board)) {
          return MOVE_ERROR_BLOCKED;
        }
        
    } else if (start.x == end.x) {

        if (!checkColumn(start, end, board)) {
          return MOVE_ERROR_BLOCKED;
        }

    } else {
        return MOVE_ERROR_ILLEGAL;
    }

    //It wasn't blocked and the destination is open
    if (endPiece == nullptr) { //is this necessary?
        return SUCCESS;
    }

    //It wasn't blocked and the destination
    //does not have a piece from the same player
    if (owner() == endPiece->owner()) {
        return MOVE_ERROR_BLOCKED;
    }

    return SUCCESS;
}

//Knight validMove function. There is no elegant solution for this, just need to manually check each position that the knight can move to.
int Knight::validMove(Position start, Position end, const Board& board) const {
    if ((((start.x == end.x+2) || (start.x == end.x-2)) && ((start.y == end.y+1) || (start.y == end.y-1))) || (((start.y == end.y+2) || (start.y == end.y-2)) && ((start.x == end.x+1) || (start.x == end.x-1)))) {
        Piece* endPiece = board.getPiece(end);

        if ((endPiece == nullptr) || (owner() != endPiece->owner()))
            return SUCCESS;
        return MOVE_ERROR_BLOCKED;
    }
    return MOVE_ERROR_ILLEGAL;
}

//Bishop validMove function.
int Bishop::validMove(Position start, Position end, const Board& board) const {
    int xdistance = end.x-start.x;
    int ydistance = end.y-start.y;
    bool posDiagonal = (xdistance == ydistance);
    bool negDiagonal = (xdistance == (-1)*ydistance);

    //Check that the differences in the x and y directions are equal.
    if (!posDiagonal && !negDiagonal)
        return MOVE_ERROR_ILLEGAL;

    Piece* endPiece = board.getPiece(end);

    //If the end position is up and to the right of start or down and to the left. Loop through all of the positions in the movement path and check that there is no piece in the way.
    if (posDiagonal) {
        if (xdistance > 0) {
            for (int i = 1; i < xdistance; i++) {
                if (board.getPiece(Position(start.x+i, start.y+i)) != nullptr)
                    return MOVE_ERROR_BLOCKED;
            }
            if ((endPiece == nullptr) || (m_owner != endPiece->owner()))
                return SUCCESS;
            return MOVE_ERROR_BLOCKED;
        }
        for (int i = 1; i < (-1)*xdistance; i++) {
            if (board.getPiece(Position(start.x-i, start.y-i)) != nullptr)
                return MOVE_ERROR_BLOCKED;
        }
        if ((endPiece == nullptr) || (m_owner != endPiece->owner()))
            return SUCCESS;
        return MOVE_ERROR_BLOCKED;
    }
    //End is up and to the left or down and to the right of the start. Same process as before.
    if (xdistance > 0) {
        for (int i = 1; i < xdistance; i++) {
            if (board.getPiece(Position(start.x+i, start.y-i)) != nullptr)
                return MOVE_ERROR_BLOCKED;
        }
        if ((endPiece == nullptr) || (m_owner != endPiece->owner()))
            return SUCCESS;
        return MOVE_ERROR_BLOCKED;
    }
    for (int i = 1; i < (-1)*xdistance; i++) {
        if (board.getPiece(Position(start.x-i, start.y+i)) != nullptr)
            return MOVE_ERROR_BLOCKED;
    }
    if ((endPiece == nullptr) || (m_owner != endPiece->owner()))
        return SUCCESS;
    return MOVE_ERROR_BLOCKED;
}

//Queen validMove function. Queen has the same movement patterns as a rook and bishop combines, so can simply create temporary rook and bishop pieces at the queen's position and check if either of them has a valid move to the end position.
int Queen::validMove(Position start, Position end, const Board& board) const {
    PieceFactory<Rook> rookFactory(ROOK_ENUM);
    PieceFactory<Bishop> bishopFactory(BISHOP_ENUM);

  Piece* rook = rookFactory.newPiece(m_owner);
  Piece* bishop = bishopFactory.newPiece(m_owner);

    int rookValid = rook->validMove(start, end, board);
    //If the rook returns an invalid move, still need to check for the bishop.
    if (rookValid != MOVE_ERROR_ILLEGAL){
      delete rook;
      delete bishop;
      return rookValid;
    }
      
    int bishopValid = bishop->validMove(start, end, board);

    delete rook;
    delete bishop;

    return bishopValid;
}

//King validMove function. Only checks that the king is trying to move one space in any direction. Handling for the king putting itself in check is done in the testMove function.
int King::validMove(Position start, Position end, const Board& board) const{
  if (((start.x == end.x) && ((start.y == end.y+1) || (start.y == end.y-1))) || ((start.y == end.y) && ((start.x == end.x+1) || (start.x == end.x-1))) || (((start.x == end.x+1) || (start.x == end.x-1)) && ((start.y == end.y+1) || (start.y == end.y-1)))){
    Piece* endPiece = board.getPiece(end);
    if ((endPiece == nullptr) || (owner() != endPiece->owner()))
      return SUCCESS;
    return MOVE_ERROR_BLOCKED;
  }
  return MOVE_ERROR_ILLEGAL;
}

//Normal run function. First gets input of 1 or 2 to decide whether to start a new game or load a saved game. Next, loops until input of q is reached (or input is set to q, which is done manually in the case of an endgame).
int ChessGame::run() {

    std::string input;
    bool valid = false;

    do {
        Prompts::menu();
        std::cin >> input;
        //std::transform(input.begin(), input.end(), input.begin(), ::tolower);

        if (input.compare("1") == 0) {
            setupBoard();
            valid = true;
            //fgetc(stdin);
        } else if (input.compare("2") == 0) {
            if (!loadFile()) {
                return 1;
            }
            valid = true;
        }
    } while (!valid); //SHOULD IT BE ABLE TO QUIT HERE?

    fgetc(stdin);

    do {
        input.clear();
        Prompts::playerPrompt(this->playerTurn(), (this->turn()+1)/2);

        char next;

        do {
            next = fgetc(stdin);
            input.append(1, next);
        } while (next != '\n');
        std::transform(input.begin(), input.end(), input.begin(), ::tolower);

        //input.back() = '\0';
        input.pop_back();
        directUserInput(input);

    } while (input.compare("q"));

    return 0;
}

void ChessGame::directUserInput(string& input) {

    std::map<string, char, std::less<string>> command;
    command.emplace("q", 'q');
    command.emplace("board", 'b');
    command.emplace("save", 's');
    command.emplace("forfeit", 'f');
    command.emplace("castle", 'c');

    char selection;

    if (command.count(input) > 0) {
        selection = command.at(input);
    } else {
        selection = 'd';
    }
    switch (selection) {
    case 'q':
        break;

    case 'b':
        changeBoardStatus();
        if (getBoardStatus()) {
            displayBoard();
        }
        break;

    case 's':
    {
        string filename;
        Prompts::saveGame();
        cin >> filename;

        //std::ofstream outputFile(filename, std::ofstream::out);
        std::ofstream outputFile;
        outputFile.open(filename);

        if (!outputFile.is_open()) {
            Prompts::saveFailure();
            return;
        }

        outputFile << "chess\n" << this->m_turn - 1 << endl;

        for (int y = 0; y < 8; y++) {
            for (int x = 0; x < 8; x++) {
                Piece* p = this->getPiece(Position(x,y));
                if (p) {
                    outputFile << p->owner() << " " << char(x+97) << y+1 << " " << p->id() << endl;
                }
            }
        }

        outputFile.close();
        input = "q";
    }
    break;

    case 'f':

        Prompts::win((Player)!playerTurn(), turn());
        Prompts::gameOver();
        input = "q";

        break;

    case 'c':

        break;

    case 'd':
    {
        char fromCol;
        char toCol;
        int fromRow;
        int toRow;

        //cout << "make move"<< endl;
        const char* move = input.c_str();
        if (sscanf(move, "%c %d %c %d", &fromCol, &fromRow, &toCol, &toRow) == 4) {
            int stat = makeMove(Position((int)(fromCol)-97, fromRow-1), Position((int)(toCol)-97, toRow-1));
            if ((status)stat == MOVE_CHECKMATE || (status)stat == MOVE_STALEMATE) {
                input = "q";
		if (getBoardStatus())
		  displayBoard();
                break;
            }
        } else {
            Prompts::parseError();
        }

        if (getBoardStatus()) {
            displayBoard();
        }
    }
    break;
    }
}

void ChessGame::presetTurn(int turn) {
    m_turn = turn;
}

bool ChessGame::loadFile() {

    string input;
    Prompts::loadGame();
    std::cin >> input;
    

    std::ifstream inputFile;
    inputFile.open(input);

    if (!inputFile.is_open()) {
      Prompts::loadFailure();
        return false;
    }

    std::transform(input.begin(), input.end(), input.begin(), ::tolower);
    if (!input.compare("chess")) {
      Prompts::loadFailure();
      return false;
    }
    
    int turn;
    inputFile >> input;
    inputFile >> turn;
    presetTurn(turn + 1);
    std::getline(inputFile, input);

    int player;
    char column;
    int row;
    int pieceID;

    while (!inputFile.eof()) {
        input.clear();
        if (!std::getline(inputFile, input)) {
            break;
        }
        std::transform(input.begin(), input.end(), input.begin(), ::tolower);

        const char* position = input.c_str();
        sscanf(position, "%d %c %d %d", &player, &column, &row, &pieceID);
        initPiece(pieceID, (Player)player, Position((int)(column)-97, row-1));
        if (pieceID == KING_ENUM) {
          if (player == BLACK) {
            if (hasBlack) {
              Prompts::loadFailure();
              return false;
            }
            blackKing = Position((int)(column)-97, row-1);
            hasBlack = !hasBlack;
          } else {
            if (hasWhite) {
              Prompts::loadFailure();
              return false;
            }
            whiteKing = Position((int)(column)-97, row-1);
            hasWhite = !hasWhite;
          }
        }
    }

    if (!hasBlack || !hasWhite) {
      Prompts::loadFailure();
      return false;
    }

    inputFile.close();
    return true;
}


/*int main() {
    ChessGame chess;
    return chess.run();
}*/

