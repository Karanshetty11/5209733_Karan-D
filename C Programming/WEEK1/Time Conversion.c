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

/*
 * Complete the 'timeConversion' function below.
 *
 * The function is expected to return a STRING.
 * The function accepts STRING s as parameter.
 */

/*
 * To return the string from the function, you should either do static allocation or dynamic allocation
 *
 * For example,
 * char* return_string_using_static_allocation() {
 *     static char s[] = "static allocation of string";
 *
 *     return s;
 * }
 *
 * char* return_string_using_dynamic_allocation() {
 *     char* s = malloc(100 * sizeof(char));
 *
 *     s = "dynamic allocation of string";
 *
 *     return s;
 * }
 *
 */
char* timeConversion(char* s) {
    // The input string format is HH:MM:SSAM/PM (10 characters long).
    // The output format is HH:MM:SS (8 characters long).
    // We need 1 extra byte for the null terminator '\0'.
    char* result = (char*)malloc(sizeof(char) * 9); // Allocate space for 8 chars + null terminator

    if (result == NULL) {
        // Handle allocation failure, though for contest problems this often isn't explicitly tested
        return NULL; 
    }

    // Extract the hour part from the input string (s[0] and s[1])
    // Convert these two character digits to an integer.
    // Example: "07" -> 7, "12" -> 12
    int hour = (s[0] - '0') * 10 + (s[1] - '0');

    // Get the AM/PM indicator (s[8])
    char ampm_indicator = s[8];

    // Apply the time conversion logic based on AM/PM
    if (ampm_indicator == 'P') { // If it's PM
        if (hour != 12) { // For 01PM to 11PM, add 12 to get 24-hour format
            hour += 12;
        }
        // If it's 12 PM (noon), it remains 12 in 24-hour format. No change needed.
    } else { // If it's AM
        if (hour == 12) { // For 12 AM (midnight), convert to 00 in 24-hour format
            hour = 0;
        }
        // For 01 AM to 11 AM, the hour remains the same. No change needed.
    }

    // Format the converted hour into the result string.
    // The "%02d" specifier ensures a leading zero for single-digit hours (e.g., 7 becomes "07").
    sprintf(result, "%02d", hour);

    // Copy the minutes and seconds part (MM:SS) directly from the input string.
    // These characters are from index 2 to 7 of the input string, which is 6 characters long.
    // They will be copied starting at result[2].
    strncpy(result + 2, s + 2, 6);

    // Null-terminate the result string to make it a valid C string.
    result[8] = '\0';

    return result;
}

int main()
{
    // The following code is boilerplate, typically provided by the online judge environment.
    // It handles reading input and writing output.
    FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w"); // Opens file for output

    char* s = readline(); // Reads the input time string (e.g., "07:05:45PM")

    char* result = timeConversion(s); // Calls your function

    fprintf(fptr, "%s\n", result); // Prints the converted time to the output file

    fclose(fptr); // Closes the output file

    // It's good practice to free memory allocated by readline and timeConversion.
    free(s);
    free(result);

    return 0;
}

// --- Boilerplate Input Reading Functions (Provided by typical coding platforms) ---
// These functions are usually given and handle reading lines, trimming whitespace, etc.

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