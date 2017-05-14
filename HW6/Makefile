# Lines starting with # are comments

# Some variable definitions to save typing later on
CC = gcc
CFLAGS = -std=c99 -Wall -Wextra -pedantic -g

# Default (first) target -- fill this in
a6: a6.o menuUtil.o imageIO.o imageManip.o
	$(CC) $(CFLAGS) -o a6 a6.o menuUtil.o imageIO.o imageManip.o

# Links the test executable
unittest: unittest.o #NA
	$(CC) $(CFLAGS) -o unittest unittest.o catalog.o 

# Compiles a6.c into an object file
a6.o: a6.c menuUtil.h imageIO.h imageManip.h
	$(CC) $(CFLAGS) -c a6.c

# Compiles catalog.c into an object file
menuUtil.o: menuUtil.c menuUtil.h
	$(CC) $(CFLAGS) -c menuUtil.c

# Compiles transcript.c into an object file
imageIO.o: imageIO.c imageIO.h
	$(CC) $(CFLAGS) -c imageIO.c

# Compiles imageManip.c into an object file
imageManip.o: imageManip.c imageManip.h
	$(CC) $(CFLAGS) -c imageManip.c

# Compiles unittest.c into an object file
unittest.o: unittest.c catalog.h transcript.h prompts.h functions.h
	$(CC) $(CFLAGS) -c unittest.c

# 'make clean' will remove intermediate & executable files
clean:
	rm -f *.o unittest a6

