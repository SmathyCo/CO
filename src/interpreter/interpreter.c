#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BUFFER_SIZE 1024

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <json_file>\n", argv[0]);
        return 1;
    }

    // Open the JSON file
    FILE *json_file = fopen(argv[1], "r");
    if (!json_file) {
        perror("Error opening file");
        return 1;
    }

    // Read JSON data from file
    char buffer[MAX_BUFFER_SIZE];
    while (fgets(buffer, MAX_BUFFER_SIZE, json_file) != NULL) {
        // Print each line (assuming JSON is on one line or read line-by-line)
        printf("%s", buffer);
    }

    fclose(json_file);
    return 0;
}