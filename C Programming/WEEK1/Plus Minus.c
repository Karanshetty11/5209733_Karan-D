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
 * Complete the 'plusMinus' function below.
 *
 * The function accepts INTEGER_ARRAY arr as parameter.
 */

void plusMinus(int arr_count, int* arr) {
    // Initialize counters for positive, negative, and zero numbers.
    // Using integer types for counts is standard before calculating ratios.
    int positive_count = 0;
    int negative_count = 0;
    int zero_count = 0;

    // Iterate through each element in the input array.
    for (int i = 0; i < arr_count; i++) {
        if (arr[i] > 0) {
            // If the number is greater than 0, it's positive.
            positive_count++;
        } else if (arr[i] < 0) {
            // If the number is less than 0, it's negative.
            negative_count++;
        } else {
            // If it's neither positive nor negative, it must be zero.
            zero_count++;
        }
    }

    // Calculate the ratios.
    // It's crucial to cast 'arr_count' or one of the count variables to 'double'
    // before division to ensure floating-point division, not integer division.
    // If you perform integer division (e.g., 2/5), the result is 0, not 0.4.
    // The total number of elements is 'arr_count'.
    double ratio_positive = (double)positive_count / arr_count;
    double ratio_negative = (double)negative_count / arr_count;
    double ratio_zero = (double)zero_count / arr_count;

    // Print each ratio on a new line, formatted to 6 decimal places.
    // The "%.6f" format specifier in printf achieves this.
    printf("%.6f\n", ratio_positive);
    printf("%.6f\n", ratio_negative);
    printf("%.6f\n", ratio_zero);
}

int main()
{
    // The following code handles reading input and is provided by the platform.
    // It reads the number of elements 'n' and then the array elements.
    int n = parse_int(ltrim(rtrim(readline())));

    char** arr_temp = split_string(rtrim(readline()));

    int* arr = malloc(n * sizeof(int));

    for (int i = 0; i < n; i++) {
        int arr_item = parse_int(*(arr_temp + i));

        *(arr + i) = arr_item;
    }

    // Call the plusMinus function with the read array.
    plusMinus(n, arr);

    // Free the dynamically allocated memory for the array.
    free(arr); // It's good practice to free memory when done.

    // Free the temporary string array used for parsing input.
    // Note: The 'split_string' function uses strtok, which modifies the input string in place.
    // So, 'arr_temp' itself is pointing to parts of the original 'readline()' result.
    // A robust solution would involve copying tokens, but for contest templates, this is often omitted.
    // For simplicity and to match common contest scenarios, we'll assume the platform handles freeing
    // what 'readline()' returns, or that it's a small memory leak acceptable for a single run.
    // If 'split_string' allocated new memory for each token, you'd need a loop here to free each splits[i]
    // before freeing splits itself. Given strtok, it often doesn't.
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
    // This is generally not required for typical competitive programming constraints
    // unless specified, as input usually fits 'int'.
    if (value > INT_MAX || value < INT_MIN) {
        exit(EXIT_FAILURE); // Value out of int range
    }

    return (int)value; // Cast to int
}