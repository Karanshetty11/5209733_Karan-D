#include <assert.h>
#include <ctype.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h> // Required for strcmp

char* readline();
char* ltrim(char*);
char* rtrim(char*);

int parse_int(char*);

/*
 * Complete the 'matchingStrings' function below.
 *
 * The function is expected to return an INTEGER_ARRAY.
 * The function accepts following parameters:
 *  1. STRING_ARRAY strings
 *  2. STRING_ARRAY queries
 */

/*
 * To return the integer array from the function, you should:
 *     - Store the size of the array to be returned in the result_count variable
 *     - Allocate the array statically or dynamically
 *
 * For example,
 * int* return_integer_array_using_static_allocation(int* result_count) {
 *     *result_count = 5;
 *
 *     static int a[5] = {1, 2, 3, 4, 5};
 *
 *     return a;
 * }
 *
 * int* return_integer_array_using_dynamic_allocation(int* result_count) {
 *     *result_count = 5;
 *
 *     int *a = malloc(5 * sizeof(int));
 *
 *     for (int i = 0; i < 5; i++) {
 *         *(a + i) = i + 1;
 *     }
 *
 *     return a;
 * }
 *
 */
int* matchingStrings(int strings_count, char** strings, int queries_count, char** queries, int* result_count) {
    // 1. Set the size of the array to be returned.
    // The result array will have one count for each query.
    *result_count = queries_count;

    // 2. Dynamically allocate memory for the result array.
    // This array will store the match counts.
    int* counts = (int*)malloc(queries_count * sizeof(int));

    // Basic error check for malloc. In competitive programming contexts,
    // memory allocation failures are often not explicitly handled for brevity,
    // assuming sufficient memory is available.
    if (counts == NULL) {
        // In a real application, you'd handle this more robustly.
        fprintf(stderr, "Memory allocation failed for counts array.\n");
        exit(EXIT_FAILURE);
    }

    // 3. Iterate through each query in the 'queries' array.
    // The outer loop handles processing each query one by one.
    for (int i = 0; i < queries_count; i++) {
        // Initialize a counter for the current query.
        int current_query_matches = 0;

        // 4. For each query, iterate through all strings in the 'strings' array.
        // The inner loop compares the current query against every available string.
        for (int j = 0; j < strings_count; j++) {
            // Compare the current query string with the current string from the 'strings' array.
            // strcmp() returns 0 if the strings are identical (a match).
            if (strcmp(queries[i], strings[j]) == 0) {
                current_query_matches++; // Increment the counter if a match is found.
            }
        }
        // Store the total number of matches found for the current query.
        counts[i] = current_query_matches;
    }

    // 5. Return the dynamically allocated array of counts.
    // The caller (main function) is responsible for freeing this memory.
    return counts;
}

int main()
{
    FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");

    // --- Input Reading for 'strings' array ---
    int strings_count = parse_int(ltrim(rtrim(readline())));
    char** strings = malloc(strings_count * sizeof(char*));
    if (strings == NULL) {
        fprintf(stderr, "Memory allocation failed for strings array of pointers.\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < strings_count; i++) {
        char* strings_item = readline();
        if (strings_item == NULL) {
            fprintf(stderr, "Memory allocation failed for a string item.\n");
            // Free previously allocated string items and the array of pointers
            for (int k = 0; k < i; k++) free(strings[k]);
            free(strings);
            exit(EXIT_FAILURE);
        }
        *(strings + i) = strings_item;
    }

    // --- Input Reading for 'queries' array ---
    int queries_count = parse_int(ltrim(rtrim(readline())));
    char** queries = malloc(queries_count * sizeof(char*));
    if (queries == NULL) {
        fprintf(stderr, "Memory allocation failed for queries array of pointers.\n");
        // Free strings array and its contents before exiting
        for (int k = 0; k < strings_count; k++) free(strings[k]);
        free(strings);
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < queries_count; i++) {
        char* queries_item = readline();
        if (queries_item == NULL) {
            fprintf(stderr, "Memory allocation failed for a query item.\n");
            // Free previously allocated memory before exiting
            for (int k = 0; k < strings_count; k++) free(strings[k]);
            free(strings);
            for (int k = 0; k < i; k++) free(queries[k]);
            free(queries);
            exit(EXIT_FAILURE);
        }
        *(queries + i) = queries_item;
    }

    // --- Call the matchingStrings function ---
    int res_count; // Variable to receive the size of the returned array.
    int* res = matchingStrings(strings_count, strings, queries_count, queries, &res_count);

    // --- Print results to the output file ---
    for (int i = 0; i < res_count; i++) {
        fprintf(fptr, "%d", *(res + i)); // THIS IS THE LINE THAT WAS INCOMPLETE

        if (i != res_count - 1) {
            fprintf(fptr, "\n");
        }
    }
    fprintf(fptr, "\n"); // Ensure a final newline for robust output handling by the judge.

    fclose(fptr);

    // --- Memory Cleanup (CRUCIAL FOR NO LEAKS) ---
    // Free each string within the 'strings' array, then free the array of pointers itself.
    for (int i = 0; i < strings_count; i++) {
        free(strings[i]);
    }
    free(strings);

    // Free each string within the 'queries' array, then free the array of pointers itself.
    for (int i = 0; i < queries_count; i++) {
        free(queries[i]);
    }
    free(queries);

    // Free the result array returned by matchingStrings.
    free(res);

    return 0;
}

// --- Boilerplate Input Reading Functions (Unchanged from your template) ---
// These functions handle reading lines from stdin, dynamic resizing, and trimming whitespace.

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

int parse_int(char* str) {
    char* endptr;
    long value = strtol(str, &endptr, 10);

    if (endptr == str || *endptr != '\0') {
        exit(EXIT_FAILURE);
    }

    return (int)value;
}