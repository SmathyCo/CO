#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cJSON.h"

#define MAX_BUFFER_SIZE 1024

typedef struct {
    char *type;
    char *name;
    char *value;
} TypeInfo;

TypeInfo *process_json(const char *json_str, int *num_entries) {
    cJSON *json = cJSON_Parse(json_str);
    if (json == NULL) {
        printf("Error parsing JSON: %s\n", cJSON_GetErrorPtr());
        return NULL;
    }

    // Count number of objects in the JSON array
    int array_size = cJSON_GetArraySize(json);
    if (array_size == 0) {
        printf("Error: JSON array is empty.\n");
        cJSON_Delete(json);
        return NULL;
    }

    // Allocate memory for array of TypeInfo structures
    TypeInfo *info = (TypeInfo *)malloc(array_size * sizeof(TypeInfo));
    if (info == NULL) {
        printf("Error allocating memory.\n");
        cJSON_Delete(json);
        return NULL;
    }

    cJSON *item = NULL;
    int index = 0;
    cJSON_ArrayForEach(item, json) {
        cJSON *type_value = cJSON_GetObjectItemCaseSensitive(item, "Type");
        if (type_value != NULL && cJSON_IsString(type_value)) {
            const char *type = cJSON_GetStringValue(type_value);
            info[index].type = strdup(type); // Allocate memory for Type
            info[index].name = NULL;
            info[index].value = NULL;

            if (strcmp(type, "functionExecution") == 0) {
                cJSON *name_value = cJSON_GetObjectItemCaseSensitive(item, "Name");
                if (name_value != NULL && cJSON_IsString(name_value)) {
                    const char *name = cJSON_GetStringValue(name_value);
                    info[index].name = strdup(name); // Allocate memory for Name
                }

                cJSON *value_value = cJSON_GetObjectItemCaseSensitive(item, "Value");
                if (value_value != NULL && cJSON_IsString(value_value)) {
                    const char *value = cJSON_GetStringValue(value_value);
                    info[index].value = strdup(value); // Allocate memory for Value
                }
            }
            index++;
        }
    }

    cJSON_Delete(json);
    *num_entries = index; // Update number of entries found
    return info;
}

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
        // Process each line (assuming JSON is on one line or read line-by-line)
        int num_entries;
        TypeInfo *info = process_json(buffer, &num_entries);
        if (info != NULL) {
            // Print Type, Name, and Value for functionExecution
            for (int i = 0; i < num_entries; i++) {
                if (strcmp(info[i].type, "functionExecution") == 0) {
                    printf("Type: %s, Name: %s\n", info[i].type, info[i].name != NULL ? info[i].name : "N/A");
                    if (strcmp(info[i].name, "print") == 0) {
                        printf(info[i].value != NULL ? info[i].value : "N/A");
                    }
                }
                free(info[i].type); // Free allocated memory for Type
                free(info[i].name); // Free allocated memory for Name
                free(info[i].value); // Free allocated memory for Value
            }
            free(info); // Free memory for array of TypeInfo structures
        }
    }

    fclose(json_file);
    return 0;
}