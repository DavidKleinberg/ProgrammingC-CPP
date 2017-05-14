# Lines starting with # are comments

# Some variable definitions to save typing later on
CC = gcc
CFLAGS = -std=c99 -Wall -Wextra -pedantic -g

# Default (first) target -- fill this in
hw4: hw4.o dnasearch.o
	$(CC) $(CFLAGS) -o hw4 hw4.o dnasearch.o

# Links the test executable
unittest: unittest.o dnasearch.o
	$(CC) $(CFLAGS) -o unittest unittest.o dnasearch.o

# Compiles hw4.c into an object file
hw4.o: hw4.c dnasearch.h
	$(CC) $(CFLAGS) -c hw4.c

# Compiles dnasearch.c into an object file
dnasearch.o: dnasearch.c dnasearch.h
	$(CC) $(CFLAGS) -c dnasearch.c

# Compiles unittest.c into an object file
unittest.o: unittest.c dnasearch.h
	$(CC) $(CFLAGS) -c unittest.c

# 'make clean' will remove intermediate & executable files
clean:
	rm -f *.o unittest hw4

