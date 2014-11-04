#include <stdio.h>
#include <string.h> 

void println_int(int num) {
	printf("%d\n", num);
}
  
void println_string(const char* str){ 
    fwrite(str, 1, strlen(str), stdout);
    printf("\n");
}

void print_int(int num) {
	printf("%d", num);
}

void print_string(const char* str){ 
    fwrite(str, 1, strlen(str), stdout);
}

extern void alpha_main();

int main() {
	alpha_main();
}