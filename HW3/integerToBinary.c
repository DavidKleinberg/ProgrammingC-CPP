#include <stdio.h>

int* recurse(int number, int binary[], int count);

int main() {
	int number = 10;
	int binary[32]; //size 32 just curious

	int* string = recurse(number, binary, number);

	for (int i = 0; i < 32; i++) {
		printf("%d", string[i]);
	}

return 0;
}

int* recurse(int number, int binary[], int count) {
	//base case
	if (number/2 == 0) {
		//binary[31 - count] = number % 2;
		binary[count] = number % 2;
		printf("Hello");
		return binary;
	} else {
		binary[count] = number % 2;
		count++;
		printf("Hello");
		recurse(number/2, binary, count);
	}

	printf("hello");

	return NULL;
}
