#include <stdio.h>
#include <string.h>

extern void prog();

void print_int(int n);
void println_int(int n);

void print_string(const char* str);
void println_string(const char* str);

int main() {
	prog();
}

void print_int(int n) {
	printf("%d", n);
}

void print_string(const char* str) { 
 	fwrite(str, 1, strlen(str), stdout);
}

void println_int(int n) {
	printf("%d\n", n);
}

void println_string(const char* str) { 
 	fwrite(str, 1, strlen(str), stdout);
 	putc('\n', stdout);
}