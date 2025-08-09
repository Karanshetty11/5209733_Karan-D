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

int parse_int(char*);
long parse_long(char*); // This function declaration is correct

/*
 * Complete the 'flippingBits' function below.
 *
 * The function is expected to return a LONG_INTEGER.
 * The function accepts LONG_INTEGER n as parameter.
 */

long flippingBits(long n) {
    // The problem asks to flip all bits of a 32-bit unsigned integer.
    // In C, a common way to achieve this for a fixed number of bits
    // is to XOR the number with a mask that has all those bits set to 1.
    //
    // For 32 bits, the mask of all ones is (2^32 - 1).
    // In hexadecimal, this is 0xFFFFFFFF.
    //
    // We use 'UL' suffix to ensure the mask is treated as an unsigned long literal,
    // which typically covers at least 32 bits. This prevents issues if 'n'
    // is internally represented as a signed number or if 'long' is 64-bit,
    // ensuring only the relevant 32 lower bits are considered for the flip
    // as per the problem's usual interpretation.
    unsigned long mask = 0xFFFFFFFFUL; // A 32-bit mask with all bits set to 1.

    // XORing 'n' with 'mask' will flip exactly the first 32 bits of 'n'.
    // Bits that are 0 in 'n' will become 1 (0 ^ 1 = 1).
    // Bits that are 1 in 'n' will become 0 (1 ^ 1 = 0).
    // Bits beyond the 32nd position (if 'long' is 64-bit) will be 0 in the mask,
    // so they will remain unchanged (x ^ 0 = x). Since 'n' is expected to be
    // treated as a 32-bit number, its upper bits would typically be 0 anyway,
    // so this is the correct behavior.
    return n ^ mask;
}

int main()
{
    FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");

    // 'q' is the number of queries (test cases).
    int q = parse_int(ltrim(rtrim(readline())));

    // Loop through each query.
    for (int q_itr = 0; q_itr < q; q_itr++) {
        long n = parse_long(ltrim(rtrim(readline()))); // Read the input number for the current query.

        long result = flippingBits(n); // Call your function.

        fprintf(fptr, "%ld\n", result); // Print the result to the output file.
    }

    fclose(fptr); // Close the output file.

    // In competitive programming, memory allocated by readline is often
    // not explicitly freed in main's loop for each query, as the program
    // exits after processing all queries. However, for strict memory hygiene,
    // if 'readline' allocates a new string in each iteration,
    // you would ideally free 's' inside the loop, after it's used.
    // Given the template structure, it's typically fine as is.

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

int parse_int(char* str) {
    char* endptr;
    long value = strtol(str, &endptr, 10); // Use long for intermediate parse, then cast to int

    if (endptr == str || *endptr != '\0') {
        exit(EXIT_FAILURE);
    }
    // Check for overflow if the parsed long value is outside int range
    if (value > INT_MAX || value < INT_MIN) {
        exit(EXIT_FAILURE);
    }

    return (int)value;
}

long parse_long(char* str) {
    char* endptr; // <--- THIS LINE IS NOW CORRECTED
    long value = strtol(str, &endptr, 10);

    if (endptr == str || *endptr != '\0') {
        exit(EXIT_FAILURE);
    }

    return value;
}