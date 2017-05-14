File: README
Final Project, 600.120 Spring 2017


TEAM:

    David A. Kleinberg
    600.120 | dkleinb1
    dkleinb1@jhu.edu
    ~~~~~~~~~~~~~~~~~~~
    Benjamin A. Kaminow
    600.120 | bkamino1
    bkamino1@jhu.edu

PROJECT BREAKDOWN:

	1. Board.cpp
	2. Chess.cpp
	3. Chess.h
	4. Game.h
	5. Terminal.h
	6. Makefile

	additional files:
	1. test_check_1.txt
	2. check_......
	3. test_pawn.txt


DESIGN:

A section titled ‘DESIGN’ which gives a brief explanation of overall design

	TESTING

		Pawns:
		*pawn cannot move backwards
		*pawn can move two forward on first turn
		*pawn can move only one forward after
		*pawn can only capture diagonally ONE
		*pawn gets upgraded to queen after reaching the other side

		Rook:
		can move up to 7 spaces forwards
		can move up to 7 spaces backwards
		can move up to 7 spaces left
		can move up to 7 spaces right
		cannot move any spaces diagonally
		cannot move through a blocked path
		can castle (special conditions)

		Bishop:
		can move up to 7 spaces up-left
		can move up to 7 spaces up-right
		can move up to 7 spaces down-left
		can move up to 7 spaces down-right
		cannot move to any adjacent tile
		cannot move through a blocked path

		Knight:

		Queen:

		King:

		Checkmate:
		checked by more than one piece
		checked by one piece
		quits after this condition
		(and any other messages/return values)

		does not occur if king is not in check
		does not occur if king is in check but...
			can move
			can block threatening piece (cannot block more than one)
			can capture threathing piece (cannot capture more than one)
			another piece can block threatening piece
			another piece can capture threatening piece

		Stalemate:
		Ben you know this better

		I/O (though some of this might only be done in end-to-end):

COMPLETENESS:

A section titled ‘COMPLETENESS’ which indicates how complete your
solution is (i.e. are you aware of any missing/incorrect functionality?).

SPECIAL INSTRUCTIONS:

A section titled ‘SPECIAL INSTRUCTIONS’ which indicates how we
should run and/or test your code. (Hopefully this is not necessary -- if it is,
you may lose points per the requirements above.)

```
#!c++

Board::~Board() {
    // Delete all pointer-based resources
    for (unsigned int i=0; i < m_width * m_height; i++)
        delete m_pieces[i];
    for (size_t i=0; i < m_registeredFactories.size(); i++)
        delete m_registeredFactories[i];
}
```