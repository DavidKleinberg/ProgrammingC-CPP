#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char* argv[]) {
  if (argc < 3) {
    puts("Usage: filegen size filename");
    exit(1);
  }
  int size = 0;
  sscanf(argv[1], "%d", &size);
  char* filename = argv[2];

  srand(time(0));

  char choices[] = {'t', 'c', 'a', 'g', 'T', 'C', 'A', 'G', ' ', '\n'};

  FILE* fp = fopen(filename, "w");
  for (int i=0; i<size; i++) {
    int r = rand() % (sizeof(choices) / sizeof(choices[0]));
    fputc(choices[r], fp);
  }
  fclose(fp);
}
