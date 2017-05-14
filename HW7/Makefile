# Lines starting with # are comments

# Some variable definitions to save typing later on
CC = g++
CFLAGS = -std=c++11 -Wall -Wextra -pedantic -g

# Default (first) target -- fill this in
hw7a: hw7a.o Bigram.o TrigramDatabase.o #Trigram.o
	$(CC) $(CFLAGS) -o hw7a hw7a.o Bigram.o TrigramDatabase.o #imageManip.o

hw7b: hw7b.o Bigram.o TrigramDatabase.o #Trigram.o
	$(CC) $(CFLAGS) -o hw7b hw7b.o Bigram.o TrigramDatabase.o #imageManip.o

# Links the test executable
unittest: unittest.o #NA
	$(CC) $(CFLAGS) -o unittest unittest.o catalog.o

# Compiles hw7a.cpp into an object file
hw7a.o: hw7a.cpp Bigram.hpp TrigramDatabase.hpp #imageManip.h
	$(CC) $(CFLAGS) -c hw7a.cpp

# Compiles hw7a.cpp into an object file
hw7b.o: hw7b.cpp Bigram.hpp TrigramDatabase.hpp #imageManip.h
	$(CC) $(CFLAGS) -c hw7b.cpp

# Compiles catalog.c into an object file
Bigram.o: Bigram.cpp Bigram.hpp
	$(CC) $(CFLAGS) -c Bigram.cpp

# Compiles transcript.c into an object file
TrigramDatabase.o: TrigramDatabase.cpp TrigramDatabase.hpp
	$(CC) $(CFLAGS) -c TrigramDatabase.cpp

# Compiles imageManip.c into an object file
#Trigram.o: imageManip.c imageManip.h
#	$(CC) $(CFLAGS) -c imageManip.c

# Compiles unittest.c into an object file
unittest.o: unittest.c catalog.h transcript.h prompts.h functions.h
	$(CC) $(CFLAGS) -c unittest.c

# 'make clean' will remove intermediate & executable files
clean:
	rm -f *.o unittest hw7a hw7b

