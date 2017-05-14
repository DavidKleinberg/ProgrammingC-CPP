#include <stdio.h>

int main() {
	unsigned int number = 700000;
	int num = (int)number;
	printf("%d\n", num);
	unsigned int mask = 1;
	mask <<= 31;
	for (int i = 0; i < 32; i++) {
		if (number & mask) {
			printf("1");
		} else {
			printf("0");
		}
		mask>>=1;
	}

return 0;
}
