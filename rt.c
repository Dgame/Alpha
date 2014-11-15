#include <stdio.h>
#include <string.h>

extern void alpha_main();

void print_int(int num) {
	printf("%d", num);
}

void print_str(const char* str) {
    fwrite(str, 1, strlen(str), stdout);
}

void print_ln() {
	printf("\n");
}

int main() {
	alpha_main();
}