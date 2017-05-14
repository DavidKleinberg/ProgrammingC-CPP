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

	1. Main.cpp
	2. Board.cpp
	3. Chess.cpp
	4. Chess.h
	5. Game.h
	6. Terminal.h
	7. Makefile

	Additional files:
	1. almostCheckmate.txt
	2. almostStalemate.txt
	3. missingKing.txt
	4. multipleKings.txt
	5. testPrompts.txt
	6. upperLower.txt
	7. wrongGame.txt

	8.  test_in_1.txt
	9.  test_in_1.txt
	10. test_in_1.txt
	11. test_in_1.txt
	12. test_in_1.txt
	13. test_in_1.txt
	14. test_in_1.txt
	15. test_in_1.txt
	16. test_in_1.txt
	17. test_in_1.txt
	18. test_in_1.txt

	19. test_out_1.txt
	20. test_out_1.txt
	21. test_out_1.txt
	22. test_out_1.txt
	23. test_out_1.txt
	24. test_out_1.txt
	25. test_out_1.txt
	26. test_out_1.txt
	27. test_out_1.txt
	28. test_out_1.txt
	29. test_out_1.txt


DESIGN:

We tried to take advantage of C++'s object oriented programming.
We kept all methods relevant to a board game in the Board class and
methods, variables, and other data relevant to only a chess game in
the "chess-related" classes. This meant creating a new ChessPiece class
so that more functionality could be shared with the pieces specific to chess
without code reuse and without interfering with Board's ability to operate a 
different type of game.

We put special thought into the checkmate and checking functions. As check
requires an iterative operation (determining whether any opposing piece has a
valid move to the king), we used this iteration to also collect all the pieces
that are threatening the king. This way it is efficient to check for checkmate
IF AND ONLY IF! check returned true. Now that there is a list built of threatening
pieces, we can simply check if the size is 1 or greater than 1. If 1, the solutions
to escape check are to block the threatening piece, capture it, or move the king.
If there are more than one, the only way if for the king to move, thus putting more priority
to this operation and making the program more efficient.

	UNIT TESTING

		Pawns:
		pawn cannot move backwards
		pawn can move two forward on first turn
		pawn can move only one forward after
		pawn can only capture diagonally ONE
		pawn gets upgraded to queen after reaching the other side

		Rook:
		can move up to 7 spaces forwards
		can move up to 7 spaces backwards
		can move up to 7 spaces left
		can move up to 7 spaces right
		cannot move any spaces diagonally
		cannot move through a blocked path

		Bishop:
		can move up to 7 spaces up-left
		can move up to 7 spaces up-right
		can move up to 7 spaces down-left
		can move up to 7 spaces down-right
		cannot move to any adjacent tile
		cannot move through a blocked path

		Knight:

		Queen:
		inherits mobility of rooks and bishops
		cannot move through a blocked path

		King:
		can move to any adjacent or directly diagonal tile.
		cannot move to a space that will put king in check.

		Checkmate:
		checked by more than one piece
		checked by one piece
		quits after this condition
		(and any other messages/return values)

		does not occur if king is not in check
		does not occur if king is in check but:
			can move
			can block threatening piece (cannot block more than one)
			can capture threathing piece (cannot capture more than one)
			another piece can block threatening piece
			another piece can capture threatening piece

		Stalemate:
		king is not in check
		current player must move king
		king has no move except check
		*no other pieces have a valid move

	END-TO-END TESTING

		Loading Files:
			test_in_1.txt
				Check for the presence of the "chess" flag
				Loads wrongGame.txt

			test_in_2.txt
				Check for upper/lowercase insensitivity
				Ex: "CheSs" and "1 A7 0" vs. "1 b7 0"
				Loads upperLower.txt

			test_in_3.txt
				Check for a missing king
				Loads missingKing.txt

			test_in_4.txt
				Check for multiple kings of same player
				Loads multipleKings.txt

			test_in_5.txt
				Check for invalid input file 

		Board & Movement:
			test_in_6.txt
				Move white and black pawns
				Check board, turn, and other prompts

			test_in_7.txt
				Check prompts for capturing piece

			test_in_8.txt
				Check prompts for forfeiting game

			test_in_9.txt
				Check prompts for stalemate
				Loads almostStalemate.txt

			test_in_10.txt
				Check prompts for checkmate
				Loads almostCheckmate.txt

			test_in_11.txt
				Checks for cannot parse prompt
				Checks for out of bounds
				Checks for no piece (and moving opponents piece)
				Checks for blocked pieces/paths
				Checks for white putting itself in check
				*Ensures correctness of prompt priority 

				Check prompts for invalid Pawn moves
				Check prompts for invalid Rook moves
				Check prompts for invalid Knight moves
				Check prompts for invalid Bishop moves
				Check prompts for invalid Queen moves
				Check prompts for invalid King moves

				Afterwards, it threatens white king with black knight
				- Must handle check 
				- Tries moving a different piece
				- Tries moving to another threatened space
				- King frees itself

COMPLETENESS:

We are not aware of any missing/incorrect functionality

SPECIAL INSTRUCTIONS:

Added a \n in the end game prompt in Prompts.h.
We wanted to make you aware of this in case the diff prompts an error

There is an additional Main.cpp file that handles the conflict of compiling
and running unittest and chess.
To compile the game: "make"
To compile the unittests: "make unittest"
To run the game: "./Chess"
To run the tests: "./unittest"

