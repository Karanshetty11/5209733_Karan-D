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
 * Complete the 'miniMaxSum' function below.
 *
 * The function accepts INTEGER_ARRAY arr as parameter.
 */

void miniMaxSum(int arr_count, int* arr) {
    // This problem specifically deals with an array of 5 elements,
    // so arr_count will always be 5.

    // Initialize variables to store the minimum and maximum values found in the array.
    // We initialize them with the first element to ensure they are within the array's range.
    // Alternatively, you could use INT_MAX for min_val and INT_MIN for max_val.
    long long min_val = arr[0]; // Use long long just in case elements themselves are large, though int is usually fine
    long long max_val = arr[0]; // for individual elements in this problem's constraints.

    // Initialize a variable to store the sum of all elements.
    // IMPORTANT: Use 'long long' for the sum. The sum of four integers
    // can exceed the maximum value of a standard 32-bit 'int' (approx 2 * 10^9).
    // If the input values are up to 10^9, four of them sum up to 4 * 10^9,
    // which requires 'long long' (approx max 9 * 10^18).
    long long total_sum = 0;

    // Iterate through the array to find the minimum, maximum, and total sum.
    for (int i = 0; i < arr_count; i++) {
        // Update minimum value if the current element is smaller.
        if (arr[i] < min_val) {
            min_val = arr[i];
        }

        // Update maximum value if the current element is larger.
        if (arr[i] > max_val) {
            max_val = arr[i];
        }

        // Add the current element to the total sum.
        total_sum += arr[i];
    }

    // Calculate the minimum possible sum of four elements:
    // This is the total sum minus the largest element.
    long long min_sum = total_sum - max_val;

    // Calculate the maximum possible sum of four elements:
    // This is the total sum minus the smallest element.
    long long max_sum = total_sum - min_val;

    // Print the minimum and maximum sums, separated by a space.
    // Use %lld format specifier for long long integers.
    printf("%lld %lld\n", min_sum, max_sum);
}

int main()
{
    // The following code handles reading input and is provided by the platform.
    // It reads 5 integers into the array 'arr'.
    char** arr_temp = split_string(rtrim(readline()));

    int* arr = malloc(5 * sizeof(int));

    for (int i = 0; i < 5; i++) {
        int arr_item = parse_int(*(arr_temp + i));

        *(arr + i) = arr_item;
    }

    // Call the miniMaxSum function with the read array.
    miniMaxSum(5, arr); // arr_count is hardcoded to 5 as per problem.

    // Free the dynamically allocated memory for the array.
    free(arr);

    // Free the temporary string array used for parsing input.
    // Note: 'split_string' uses strtok, which modifies the input string in place.
    // A more robust solution would copy tokens, but for contest templates, this is often omitted.
    // For simplicity and to match common contest scenarios, we'll assume the platform handles freeing
    // what 'readline()' returns, or that it's a small memory leak acceptable for a single run.
    free(arr_temp); // Frees the array of char pointers.

    return 0;
}

// --- Boilerplate Input Reading Functions (Provided by typical coding platforms) ---

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
            data = '\0'; // Indicates memory allocation failure

            break;
        }
    }

    if (data[data_length - 1] == '\n') {
        data[data_length - 1] = '\0'; // Remove trailing newline

        data = realloc(data, data_length); // Shrink to actual size

        if (!data) {
            data = '\0'; // Indicates memory allocation failure
        }
    } else {
        data = realloc(data, data_length + 1); // Ensure null termination space

        if (!data) {
            data = '\0'; // Indicates memory allocation failure
        } else {
            data[data_length] = '\0'; // Null-terminate
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
    // strtok modifies the input string 'str' by inserting null terminators
    char* token = strtok(str, " ");

    int spaces = 0;

    while (token) {
        splits = realloc(splits, sizeof(char*) * ++spaces);

        if (!splits) {
            // Handle realloc failure
            return splits;
        }

        splits[spaces - 1] = token; // Store pointer to the token

        token = strtok(NULL, " "); // Get next token
    }

    return splits;
}

int parse_int(char* str) {
    char* endptr;
    // strtol converts string to long int, base 10
    long value = strtol(str, &endptr, 10);

    // Error checking for conversion:
    // endptr == str means no digits were found at all.
    // *endptr != '\0' means there were non-digit characters after the number.
    // (This check assumes no leading/trailing whitespace after trimming)
    if (endptr == str || *endptr != '\0') {
        exit(EXIT_FAILURE); // Indicates invalid input format
    }

    // Check for overflow/underflow if 'value' is outside 'int' range.
    // This is generally not strictly necessary for problems where input fits 'int',
    // but good for robustness.
    if (value > INT_MAX || value < INT_MIN) {
        exit(EXIT_FAILURE); // Value out of int range
    }

    return (int)value; // Cast to int
}