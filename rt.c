#include <stdio.h>

void print(int num) {
	printf("%d\n", num);
}

extern void alpha_main();

int main() {
	alpha_main();
}