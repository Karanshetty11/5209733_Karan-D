#include <assert.h>
#include <ctype.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* readline();
char* ltrim(char*);
char* rtrim(char*);
char** split_string(char*);

int parse_int(char*);

/*
 * Complete the 'lonelyinteger' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts INTEGER_ARRAY a as parameter.
 */

int lonelyinteger(int a_count, int* a) {
    // Initialize a variable to hold the result of XORing all numbers.
    // Start with 0, as XORing any number with 0 yields the number itself.
    int unique_number = 0;

    // Iterate through each element in the input array.
    for (int i = 0; i < a_count; i++) {
        // XOR the current element with the 'unique_number' accumulator.
        // If a number appears twice, its bits will cancel out (e.g., 5 ^ 5 = 0).
        // The lonely integer, appearing only once, will remain.
        unique_number = unique_number ^ a[i];
    }

    // After iterating through all elements, 'unique_number' will hold the
    // value of the integer that appears only once.
    return unique_number;
}

int main()
{
    FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");

    // --- Input Reading for 'a' array ---
    int n = parse_int(ltrim(rtrim(readline()))); // Read the count of elements

    char** a_temp = split_string(rtrim(readline())); // Read the line of space-separated numbers

    int* a = malloc(n * sizeof(int)); // Allocate memory for the integer array
    if (a == NULL) {
        fprintf(stderr, "Memory allocation failed for array 'a'.\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < n; i++) {
        int a_item = parse_int(*(a_temp + i)); // Parse each string token to an integer
        *(a + i) = a_item; // Store the integer in the array
    }

    // --- Call the lonelyinteger function ---
    int result = lonelyinteger(n, a);

    // --- Print result to the output file ---
    fprintf(fptr, "%d\n", result);

    fclose(fptr);

    // --- Memory Cleanup (CRUCIAL FOR NO LEAKS) ---
    // Free the dynamically allocated array 'a'.
    free(a);
    
    // Free the temporary string array returned by split_string.
    // Note: strtok modifies the original string from readline().
    // If split_string itself allocated new memory for tokens, each token would need freeing.
    // Assuming a_temp points to parts of the original string, free the array of pointers.
    // The string returned by readline() (which 'a_temp' refers to parts of) needs to be freed too,
    // but the contest template typically manages 'readline()'s return or it's implicitly handled
    // by the contest system's lifecycle for the single execution.
    free(a_temp); 


    return 0;
}

// --- Boilerplate Input Reading Functions (Unchanged from your template) ---
// These functions handle reading lines from stdin, dynamic resizing, trimming whitespace, and parsing integers.

char* readline() {
    size_t alloc_length = 1024;
    size_t data_length = 0;

    char* data = malloc(alloc_length);

    while (true) {
        char* cursor = data + data_length;
        char* line = fgets(cursor, alloc_length - data_length, stdin);

        if (!line) {
            break;
        }

        data_length += strlen(cursor);

        if (data_length < alloc_length - 1 || data[data_length - 1] == '\n') {
            break;
        }

        alloc_length <<= 1;

        data = realloc(data, alloc_length);

        if (!data) {
            data = '\0';

            break;
        }
    }

    if (data[data_length - 1] == '\n') {
        data[data_length - 1] = '\0';

        data = realloc(data, data_length);

        if (!data) {
            data = '\0';
        }
    } else {
        data = realloc(data, data_length + 1);

        if (!data) {
            data = '\0';
        } else {
            data[data_length] = '\0';
        }
    }

    return data;
}

char* ltrim(char* str) {
    if (!str) {
        return '\0';
    }

    if (!*str) {
        return str;
    }

    while (*str != '\0' && isspace(*str)) {
        str++;
    }

    return str;
}

char* rtrim(char* str) {
    if (!str) {
        return '\0';
    }

    if (!*str) {
        return str;
    }

    char* end = str + strlen(str) - 1;

    while (end >= str && isspace(*end)) {
        end--;
    }

    *(end + 1) = '\0';

    return str;
}

char** split_string(char* str) {
    char** splits = NULL;
    char* token = strtok(str, " ");

    int spaces = 0;

    while (token) {
        splits = realloc(splits, sizeof(char*) * ++spaces);

        if (!splits) {
            return splits;
        }

        splits[spaces - 1] = token;

        token = strtok(NULL, " ");
    }

    return splits;
}

int parse_int(char* str) {
    char* endptr;
    long value = strtol(str, &endptr, 10);

    if (endptr == str || *endptr != '\0') {
        exit(EXIT_FAILURE);
    }

    return (int)value;
}