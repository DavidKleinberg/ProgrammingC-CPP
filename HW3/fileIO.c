#include <stdio.h>

int main(void) {
	
	FILE* filePointer1 = fopen("output.txt", "w");

	if (!filePointer1) {
		fprintf(stderr, "error");
		return 1;
	}

	fprintf(filePointer1, "hello\n");
	fclose(filePointer1);

	FILE* filePointer2 = fopen("input.txt", "r");
	char input[100];

	if (!filePointer2) {
		fprintf(stderr, "error");
		return 1;
	}

	/*while (fgets(input, 100, filePointer2)) {
		while(fgets(input, 100, filePointer2)) {
			printf("%s", input);
			fclose(filePointer2);
		}
	}*/

	while(fgets(input, 17, filePointer2)) {
		printf("%s", input);
		printf("hello");
	}
	fclose(filePointer2);
}
