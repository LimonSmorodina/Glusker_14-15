#include <stdio.h>
#include <inttypes.h>

#define false 0

int64_t _calc (int64_t x, int64_t y, int64_t z);

void safe_int_read (int64_t *num) {
    int reads;
    char a;
    while(((reads = scanf("%d%c", &num, &a)) != 2 && reads != EOF) || a != '\n') {
        printf("Please enter an integer only : ");
        do {
            reads = scanf("%c", &a);
        } while(reads != EOF && a != '\n');
    }
}

int main (void) {
    int readed;
    int64_t x, y, z;
    printf ("Program for solving (x%5 + z/y) >> 2\n");
    printf ("Enter x:\n");
    safe_int_read (&x);
    printf ("Enter y:\n");
    safe_int_read (&y);
    printf ("Enter z:\n");
    safe_int_read (&z);
    int64_t result = _calc (x, y, z);
    printf ("%u\n", result);
    return 0;
}
