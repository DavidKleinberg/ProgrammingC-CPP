File: README
Homework 4, 600.120 Spring 2017

600.120 | dkleinb1
dkleinb1@jhu.edu
~~~~~~~~~~~~~~~~~~
David A. Kleinberg
Assignment 4
03-08-2017


Below are the files included for assignment 4:
	
	1. hw4.c

	2. dnasearch.c
		- This holds all the functions called by hw4.c and tested by unittest.c
		- Though it may look like I reused a lot of code, I made the design
			choice to dynamically allocate memory for the DNA string received
			from the input file thereby making the program more space efficient.
			This code had to stand separately.

	3. dnasearch.h

	4. unittest.c
		- I tried to replicate the end to end tests as best I could. I therefore
			created input that would make a function return an error (usually a 1)
			and assert that the error was returned, even though the error message
			may not have been printed.

	5. Makefile

	6. test.sh
		- Description for inputs below

	7. dna(1-8).txt

	8. in(1-8).txt

	9. out(1-8).txt

	10. gitlog.txt


End to End Tests:
	dna1.txt	Normal genome
	in1.txt 	Normal query
	out1.txt 	Returns results

	dna2.txt	Normal genome
	in2.txt 	Mixed lower and uppercase
	out2.txt 	Returns query results - no errors

	dna3.txt	Normal genome
	in3.txt 	Query contains invalid nucleotide
	out3.txt 	Reports invalid pattern

	dna4.txt	Contains invalid nucleotide
	in4.txt 	Contains empty file
	out4.txt 	Reports invalid text file

	dna5.txt 	Contains 19 nucleotide characters
	in5.txt 	Queries 20 nucleotide characters
	out5.txt 	Reports invalid pattern

	dna6.txt 	Normal genome
	in6.txt 	Empty input
	out6.txt 	Empty output - no errors

	dna7.txt 	Contains 15001 characters
	in7.txt 	Empty input
	out7.txt 	Reports invalid text file

	dna8.txt 	Contains 0 nucleotides
	in8.txt 	Empty input
	out8.txt 	Reports invalid text file
