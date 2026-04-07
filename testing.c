#include <stdio.h>

typedef struct {
    int a;
    char *b;
} histruct;

int main (int argc, char **argv) {
    histruct s;
    (void)argc;
    s.a = 2;
    s.b = argv[1];
    while (s.a > 0) {
        s.a--;
        printf("%d %s\n", s.a, s.b);
    }
    return 0; 
}   