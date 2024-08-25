#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../headers/lexer.h"

#define MAX_TOKENS 1000
#define BUFFER_SIZE 1000
#define MAX_TOKENS 1000
#define MAX_LINE_LENGTH 1000
#define MAX_RESULT_LENGTH 1000

char** split_string(const char* str, const char* delimiter, int* token_count) {
    char* str_copy = strdup(str);
    char** tokens = (char**)malloc(MAX_TOKENS * sizeof(char*));
    char* token;
    int count = 0;

    if (str_copy == NULL || tokens == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }

    token = strtok(str_copy, delimiter);

    while (token != NULL && count < MAX_TOKENS) {
        tokens[count] = strdup(token);
        if (tokens[count] == NULL) {
            printf("Memory allocation failed!\n");
            exit(1);
        }
        count++;
        token = strtok(NULL, delimiter);
    }

    *token_count = count;
    free(str_copy);
    return tokens;
}

void free_tokens(char** tokens, int token_count) {
    for (int i = 0; i < token_count; i++) {
        free(tokens[i]);
    }
    free(tokens);
}

struct Token {
    char line[MAX_LINE_LENGTH];
};

void lex(const char* filename) {
    struct Token tokens[MAX_TOKENS];

    int token_count = 0;

    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    char buffer[BUFFER_SIZE];
    while (fgets(buffer, sizeof(buffer), file)) {
        buffer[strcspn(buffer, "\n")] = '\0';

        int count = 0;
        char** lines = split_string(buffer, ";", &count);

        if (lines == NULL) {
            fprintf(stderr, "Error splitting string.\n");
            continue;
        }

        for (int i = 0; i < count; i++) {
            if (i < MAX_TOKENS) {
                strncpy(tokens[i].line, lines[i], MAX_LINE_LENGTH - 1);
                tokens[i].line[MAX_LINE_LENGTH - 1] = '\0';
                
                // Check for open parenthesis
                int p = 0;
                int positionOpenPar = -1;
                while (tokens[i].line[p] != '\0') {
                    if (tokens[i].line[p] == '(') {
                        positionOpenPar = p;
                        break;
                    }
                    p++;
                }
                
                if (positionOpenPar != -1) {

                    // Check for closing parenthesis
                    int pc = 0;
                    int positionClosingPar = -1;
                    while (tokens[i].line[pc] != '\0') {
                        if (tokens[i].line[pc] == ')') {
                            positionClosingPar = pc;
                            break;
                        }
                        pc++;
                    }
                    
                    if (positionClosingPar!= -1) {

                        char result2[MAX_RESULT_LENGTH] = {0};
                        char result[MAX_RESULT_LENGTH] = {0};

                        // Concatenate characters from positionOpenPar + 1 to positionClosingPar
                        for (int b = positionOpenPar + 1; b <= positionClosingPar; b++) {
                            if (strlen(result2) < MAX_RESULT_LENGTH - 1) {
                                strncat(result2, &tokens[i].line[b], 1);
                            }
                        }
                        

                        // Concatenate characters from the start of the line up to positionOpenPar
                        for (int d = 0; d < positionOpenPar; d++) {
                            if (strlen(result) < MAX_RESULT_LENGTH - 1) {
                                strncat(result, &tokens[i].line[d], 1);
                            }
                        }

                        size_t len = strlen(result2);
                        if (len > 0) {
                            result2[len - 1] = '\0';
                        }

                        printf("Function execution:\n");
                        printf("Name: %s\n", result);
                        printf("Value: %s\n", result2);
                        printf("Line: %s\n", tokens[i].line);
                        printf("\n");

                    } else {
                        int length = strlen(tokens[i].line);

                        // Print error message with colored text
                        printf("\033[31mError: \033[33mMissing a closing parenthesis.\033[0m\n\n\033[32m%s\033[0m\n", tokens[i].line);

                        // Print the ^ characters based on the length of the line
                        for (int i = 0; i < length; i++) {
                            printf("\033[31m^\033[0m");
                        }
                        printf("\n");
                        return;
                    }
                } else {
                    // MAKE AN ERROR MESSAGE, MISSING OPEN PARENTHESIS
                    int length = strlen(tokens[i].line);

                        // Print error message with colored text
                        printf("\033[31mError: \033[33mMissing an opening parenthesis.\033[0m\n\n\033[32m%s\033[0m\n", tokens[i].line);

                        // Print the ^ characters based on the length of the line
                        for (int i = 0; i < length; i++) {
                            printf("\033[31m^\033[0m");
                        }
                        printf("\n");
                        return;
                }
            } else {
                fprintf(stderr, "Too many tokens\n");
            }
        }
        token_count += count;

        free_tokens(lines, count);
    }

    fclose(file);
}