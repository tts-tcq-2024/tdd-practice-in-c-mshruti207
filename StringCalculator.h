
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NUMBER 1000

// Helper function to replace specific characters with a replacement
void replace_characters(char* str, const char* targets, char replacement) {
    char* p = str;
    while ((p = strpbrk(p, targets)) != NULL) {  // Find target characters
        *p = replacement;  // Replace them with the given character
        p++;
    }
}

// Function to replace newlines and delimiters with commas
char* replace_with_commas(const char* input, const char* delimiters) {
    char* result = strdup(input);
    if (!result) return NULL;  // Error handling if memory allocation fails

    // Replace newlines and delimiters
    replace_characters(result, "\n", ',');
    replace_characters(result, delimiters, ',');

    return result;
}

// Helper function to extract custom delimiters or use default ones
static const char* extract_custom_delimiter(const char* input, char* delimiters) {
    if (input[0] == '/' && input[1] == '/') {
        delimiters[0] = input[2];  // Custom delimiter after "//"
        delimiters[1] = '\n';      // Delimiter includes newline
        delimiters[2] = '\0';      // Null-terminate
        return strchr(input, '\n') + 1; // Return the string after the newline
    }
    strcpy(delimiters, ",\n");     // Default delimiters: comma and newline
    return input;                  // Return the original string if no custom delimiter
}

// Function to replace delimiters and newlines with commas
char* find_delimiter(const char* input) {
    char delimiters[3];            // Delimiters (can hold custom or default)
    const char* numbers_str = extract_custom_delimiter(input, delimiters); 
    char* updated_input = replace_with_commas(numbers_str, delimiters); 
    return updated_input;
}

// Helper function to check for negative numbers
void find_negatives(const char* updated_input) {
    char* input_copy = strdup(updated_input);
    char* token = strtok(input_copy, ",");
    while (token) {
        if (atoi(token) < 0) {
            free(input_copy);
            fprintf(stderr, "Error: Negatives not allowed\n");
            exit(EXIT_FAILURE);
        }
        token = strtok(NULL, ",");
    }
    free(input_copy);
}

// Helper function to calculate the sum of numbers
int find_sum(const char* updated_input) {
    char* input_copy = strdup(updated_input);
    char* token = strtok(input_copy, ",");
    int sum = 0;
    while (token) {
        int number = atoi(token);
        sum += (number <= MAX_NUMBER) ? number : 0;
        token = strtok(NULL, ",");
    }
    free(input_copy);
    return sum;
}

// Main add function
int add(const char* input) {
    if (input == NULL || strlen(input) == 0) {
        return 0;
    }
    char* updated_input = find_delimiter(input);
    find_negatives(updated_input);
    int sum = find_sum(updated_input);
    free(updated_input);
    return sum;
}
