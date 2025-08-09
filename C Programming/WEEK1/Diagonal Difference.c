#include <assert.h>
#include <ctype.h>
#include <limits.h>
#include <math.h> // For fabs() or abs() if float. For int, stdlib.h has abs().
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h> // For abs()
#include <string.h>

char* readline();
char* ltrim(char*);
char* rtrim(char*);
char** split_string(char*);

int parse_int(char*);

/*
 * Complete the 'diagonalDifference' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts 2D_INTEGER_ARRAY arr as parameter.
 */

int diagonalDifference(int arr_rows, int arr_columns, int** arr) {
    // For a square matrix, arr_rows == arr_columns. Let's use 'n' for clarity.
    int n = arr_rows; 

    // Initialize sums for both diagonals. Integers are sufficient as sums
    // typically won't overflow int for common problem constraints.
    int primary_diagonal_sum = 0;
    int secondary_diagonal_sum = 0;

    // Iterate through the rows of the matrix.
    // For a square matrix, a single loop index 'i' can be used to access
    // elements on both diagonals.
    for (int i = 0; i < n; i++) {
        // Add element to primary diagonal sum: arr[i][i]
        primary_diagonal_sum += arr[i][i];

        // Add element to secondary diagonal sum: arr[i][(n - 1) - i]
        // Example for N=3:
        // i=0: arr[0][(3-1)-0] = arr[0][2]
        // i=1: arr[1][(3-1)-1] = arr[1][1]
        // i=2: arr[2][(3-1)-2] = arr[2][0]
        secondary_diagonal_sum += arr[i][(n - 1) - i];
    }

    // Calculate the absolute difference between the two sums.
    // The abs() function is defined in stdlib.h (for integers).
    return abs(primary_diagonal_sum - secondary_diagonal_sum);
}

int main()
{
    FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");

    // --- Input Reading for the 2D array 'arr' ---
    int n = parse_int(ltrim(rtrim(readline()))); // Read the size of the square matrix (n x n)

    int** arr = malloc(n * sizeof(int*)); // Allocate memory for 'n' rows (pointers to integer arrays)
    if (arr == NULL) {
        fprintf(stderr, "Memory allocation failed for array rows.\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < n; i++) {
        *(arr + i) = malloc(n * (sizeof(int))); // Allocate memory for 'n' integers in each row
        if (*(arr + i) == NULL) {
            fprintf(stderr, "Memory allocation failed for array column in row %d.\n", i);
            // Free previously allocated rows before exiting
            for (int k = 0; k < i; k++) free(arr[k]);
            free(arr);
            exit(EXIT_FAILURE);
        }

        // It's crucial to free the string returned by readline() AND the array of char pointers
        // returned by split_string for each row to prevent memory leaks.
        char* current_line = readline(); 
        char** arr_item_temp = split_string(rtrim(current_line)); 

        for (int j = 0; j < n; j++) {
            int arr_item = parse_int(*(arr_item_temp + j)); // Parse each string token to an integer
            *(*(arr + i) + j) = arr_item; // Store the integer in the matrix
        }
        free(arr_item_temp); // Free the temporary array of string pointers for the row
        free(current_line); // Free the string buffer for the current line
    }

    // --- Call the diagonalDifference function ---
    // Pass n for both rows and columns as it's a square matrix.
    int result = diagonalDifference(n, n, arr);

    // --- Print result to the output file ---
    fprintf(fptr, "%d\n", result);

    fclose(fptr); // This is the line that was reported in the error

    // --- Memory Cleanup (CRUCIAL FOR NO LEAKS) ---
    // Free the dynamically allocated 2D array.
    // First, free each row (inner arrays).
    for (int i = 0; i < n; i++) {
        free(arr[i]);
    }
    // Then, free the array of pointers (outer array).
    free(arr);

    return 0;
}

// --- Boilerplate Input Reading Functions ---

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

    if (value > INT_MAX || value < INT_MIN) {
        exit(EXIT_FAILURE);
    }

    return (int)value;
}