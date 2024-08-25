#include <stdio.h>
#include "../headers/lexer.h"

#define BUFFER_SIZE 1000

int main(int argc, char *argv[]) {

    if (argv[1] == NULL) {
        printf("Enter a CO file to read.");
        return 1;
    }

    lex(argv[1]);
    return 0;
}