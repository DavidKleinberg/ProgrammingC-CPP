/*  File: Board.cpp
    Final Project, 600.120 Spring 2017

    David A. Kleinberg
    600.120 | dkleinb1
    dkleinb1@jhu.edu
    ~~~~~~~~~~~~~~~~~~~
    Benjamin A. Kaminow
    600.120 | bkamino1
    bkamino1@jhu.edu
*/

#include <assert.h>
#include <cctype>
#include <iostream>
#include <fstream>
#include <algorithm>
#include "Game.h"
#include "Prompts.h"

#include <locale>
#include <cwchar>

using std::cout;
using std::endl;
using std::string;

///////////////
// Board //
///////////////

Board::~Board() {
    // Delete all pointer-based resources
    for (unsigned int i=0; i < m_width * m_height; i++)
        delete m_pieces[i];
    for (size_t i=0; i < m_registeredFactories.size(); i++)
        delete m_registeredFactories[i];
}

// Get the Piece at a specific Position, or nullptr if there is no
// Piece there or if out of bounds.
Piece* Board::getPiece(Position position) const {
    if (validPosition(position))
        return m_pieces[index(position)];
    else {
      Prompts::outOfBounds();
      return nullptr;
    }
}

// Create a piece on the board using the factory.
// Returns true if the piece was successfully placed on the board
bool Board::initPiece(int id, Player owner, Position position) {
    Piece* piece = newPiece(id, owner);
    if (!piece) return false;

    // Fail if the position is out of bounds
    if (!validPosition(position)) {
        Prompts::outOfBounds();
        return false;
    }
    // Fail if the position is occupied
    if (getPiece(position)) {
        Prompts::blocked();
        return false;
    }
    m_pieces[index(position)] = piece;
    return true;
}

// Add a factory to the Board to enable producing
// a certain type of piece
bool Board::addFactory(AbstractPieceFactory* pGen) {
    // Temporary piece to get the ID
    Piece* p = pGen->newPiece(WHITE);
    int id = p->id();
    delete p;

    PieceGenMap::iterator it = m_registeredFactories.find(id);
    if (it == m_registeredFactories.end()) { // not found
        m_registeredFactories[id] = pGen;
        return true;
    } else {
        std::cout << "Id " << id << " already has a generator\n";
        return false;
    }
}

// Search the factories to find a factory that can translate `id' to
// a Piece, and use it to create the Piece. Returns nullptr if not found.
Piece* Board::newPiece(int id, Player owner) {
    PieceGenMap::iterator it = m_registeredFactories.find(id);
    if (it == m_registeredFactories.end()) { // not found
        std::cout << "Id " << id << " has no generator\n";
        return nullptr;
    } else {
        return it->second->newPiece(owner);
    }
}

Position Board::getPos(unsigned int index) const {
  unsigned int xPos = index%m_width;
  unsigned int yPos = (index-xPos)/m_width;
  return Position(xPos, yPos);
}


void Board::displayBoard() {
    //string pieceSymbol[] = {"P", "K", "R", "B", "Q", "X"};
    string whiteSymbol[] = {"\u2659", "\u2656", "\u2658", "\u2657", "\u2655", "\u2654"};
    string blackSymbol[] = {"\u265F", "\u265C", "\u265E", "\u265D", "\u265B", "\u265A"};

    Terminal::Color color1 = Terminal::WHITE;
    Terminal::Color color2 = Terminal::RED;
    Terminal::Color frame = Terminal::BLACK;
    
    frameTopBottom(frame);
    frameTopBottom(frame);
    for (int r = 56; r >= 0; r -= 8) {
        padTiles(color1, color2, frame);
        frameSides(frame);
        for (int c = 0; c < 8; c++) {
            Terminal::colorBg(color1);
            //Terminal::colorAll(true, frame, color1);
            Piece* piece = m_pieces.at(r+c);
            if (!piece) {
                cout << "       ";
            } else {
                if (piece->owner() == BLACK) {
		  Terminal::colorFg(false, Terminal::BLACK);
		          //Terminal::colorFg(false, frame);
                    cout << "   " << blackSymbol[piece->id()] << "   ";

                } else {
                    Terminal::colorFg(true, Terminal::BLACK);
		              //Terminal::colorFg(true, frame);
                    cout << "   " << whiteSymbol[piece->id()] << "   ";
                }
                //cout << "   " << pieceSymbol[piece->id()] << "   ";
            }
            term.set_default();
            alternate(color1, color2);
        }
        //frameSides(frame);
        Terminal::colorAll(true, Terminal::WHITE, frame);
        cout << " " << r/8 + 1 << "  ";
        term.set_default();
        cout << endl;
        padTiles(color1, color2, frame);
        alternate(color1, color2);
    }
    //frameTopBottom(frame);
    //Terminal::set_default();

    Terminal::colorAll(true, Terminal::WHITE, frame);
    cout << "    ";
    for (int c = 0; c < 8; c++) {
        cout << "   " << char(c + 97) << "   ";
    }
    cout << "    ";
    term.set_default();
    cout << endl;
    frameTopBottom(frame);
    cout << "\n" << endl;
}

void Board::padTiles(Terminal::Color color1, Terminal::Color color2, Terminal::Color frame) const {
    frameSides(frame);
    for (int c = 0; c < 4; c++) {
        Terminal::colorBg(color1);
        cout << "       ";
        Terminal::colorBg(color2);
        cout << "       ";
    }
    term.set_default();
    frameSides(frame);
    cout << endl;
}

void Board::frameTopBottom(Terminal::Color color) const {
    Terminal::colorBg(color);
    for (int c = 0; c < 64; c++) {
        cout << " ";
        
    }
    term.set_default();
    cout << endl;
}

void Board::frameSides(Terminal::Color color) const {
    Terminal::colorBg(color);
    cout << "    ";
    term.set_default();
}

void Board::alternate(Terminal::Color& c1, Terminal::Color& c2) {
    Terminal::Color temp = c1;
    c1 = c2;
    c2 = temp;
}

