# Lines starting with # are comments

# Some variable definitions to save typing later on
CC = gcc
CFLAGS = -std=c99 -Wall -Wextra -pedantic -g

# Default (first) target -- fill this in
hw5: hw5.o catalog.o transcript.o prompts.o functions.o
	$(CC) $(CFLAGS) -o hw5 hw5.o catalog.o transcript.o prompts.o functions.o

# Links the test executable
unittest: unittest.o catalog.o transcript.o prompts.o functions.o
	$(CC) $(CFLAGS) -o unittest unittest.o catalog.o transcript.o prompts.o functions.o

# Compiles hw5.c into an object file
hw5.o: hw5.c catalog.h transcript.h prompts.h functions.h
	$(CC) $(CFLAGS) -c hw5.c

# Compiles catalog.c into an object file
catalog.o: catalog.c catalog.h
	$(CC) $(CFLAGS) -c catalog.c

# Compiles transcript.c into an object file
transcript.o: transcript.c transcript.h
	$(CC) $(CFLAGS) -c transcript.c

# Compiles prompts.c into an object file
prompts.o: prompts.c prompts.h
	$(CC) $(CFLAGS) -c prompts.c

# Compiles functions.c into an object file
functions.o: functions.c functions.h
	$(CC) $(CFLAGS) -c functions.c

# Compiles unittest.c into an object file
unittest.o: unittest.c catalog.h transcript.h prompts.h functions.h
	$(CC) $(CFLAGS) -c unittest.c

# 'make clean' will remove intermediate & executable files
clean:
	rm -f *.o unittest hw5

