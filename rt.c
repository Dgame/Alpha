#include <stdio.h>
#include <string.h> 

void print_int(int num) {
	printf("%d\n", num);
}
  
void print_string(const char* str){ 
    fwrite(str, 1, strlen(str), stdout);
    printf("\n");
}

extern void alpha_main();

int main() {
	alpha_main();
}