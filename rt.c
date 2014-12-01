#include <stdio.h>

extern void alpha_main();

inline void print_int(int num) {
    printf("%d", num);
}

inline void print_str(const char* str) {
    fputs(str, stdout);
}

inline void print_ln() {
    putchar('\n');
}

int main() {
    alpha_main();
}