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
 * Complete the 'countingSort' function below.
 *
 * The function is expected to return an INTEGER_ARRAY.
 * The function accepts INTEGER_ARRAY arr as parameter.
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
int* countingSort(int arr_count, int* arr, int* result_count) {
    // According to the typical constraints of "Counting Sort 1" problem,
    // the input integers are in the range [0, 99].
    // So, the frequency array (or count array) will have 100 elements,
    // where index i stores the count of number i.
    const int MAX_VALUE = 99; // Maximum possible value in the input array
    const int COUNT_ARRAY_SIZE = MAX_VALUE + 1; // Size needed for counts (0 to 99)

    // Set the size of the array to be returned.
    *result_count = COUNT_ARRAY_SIZE;

    // Dynamically allocate memory for the frequency array.
    int* counts = (int*)malloc(COUNT_ARRAY_SIZE * sizeof(int));

    // Basic error check for malloc. In competitive programming,
    // memory allocation failures are often not explicitly handled for brevity.
    if (counts == NULL) {
        fprintf(stderr, "Memory allocation failed for counts array.\n");
        exit(EXIT_FAILURE);
    }

    // Initialize all elements of the counts array to zero.
    // This is crucial to ensure accurate frequency counts.
    for (int i = 0; i < COUNT_ARRAY_SIZE; i++) {
        counts[i] = 0;
    }

    // Iterate through the input array 'arr'.
    // For each number in 'arr', increment the corresponding count in the 'counts' array.
    for (int i = 0; i < arr_count; i++) {
        // Ensure the value is within the expected range before using it as an index.
        // This prevents out-of-bounds access if input is not strictly 0-99,
        // though contest problems usually guarantee valid input.
        if (arr[i] >= 0 && arr[i] <= MAX_VALUE) {
            counts[arr[i]]++; // Increment count for the number arr[i]
        }
    }

    // Return the dynamically allocated frequency array.
    // The calling function (main) is responsible for freeing this memory.
    return counts;
}

int main()
{
    FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");

    // --- Input Reading for 'arr' array ---
    int n = parse_int(ltrim(rtrim(readline()))); // Read the count of elements

    char* arr_line = readline(); // Read the line of space-separated numbers
    char** arr_temp = split_string(rtrim(arr_line)); // Split the line into tokens

    int* arr = malloc(n * sizeof(int)); // Allocate memory for the integer array
    if (arr == NULL) {
        fprintf(stderr, "Memory allocation failed for input array 'arr'.\n");
        // Free 'arr_line' and 'arr_temp' before exiting on error
        free(arr_line);
        free(arr_temp);
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < n; i++) {
        int arr_item = parse_int(*(arr_temp + i)); // Parse each string token to an integer
        *(arr + i) = arr_item; // Store the integer in the array
    }

    // --- Call the countingSort function ---
    int result_count; // Variable to receive the size of the returned array.
    int* result = countingSort(n, arr, &result_count);

    // --- Print results to the output file ---
    for (int i = 0; i < result_count; i++) {
        fprintf(fptr, "%d", *(result + i));

        // Print a space between numbers, but not after the last one.
        if (i != result_count - 1) {
            fprintf(fptr, " ");
        }
    }

    fprintf(fptr, "\n"); // Ensure a final newline for robust output handling by the judge.

    fclose(fptr); // Close the output file.

    // --- Memory Cleanup (CRUCIAL FOR NO LEAKS) ---
    // Free the dynamically allocated input array 'arr'.
    free(arr);
    
    // Free the string array returned by split_string.
    // Note: strtok modifies the original string from readline().
    // 'arr_temp' points to parts of 'arr_line', so freeing 'arr_line' first is important
    // if 'arr_temp' were pointers to copies, not parts of 'arr_line'.
    // Here, since 'arr_temp' elements are pointers INTO 'arr_line', we free 'arr_line' itself
    // and then the array of pointers 'arr_temp'.
    free(arr_temp); 
    free(arr_line); // Free the buffer read by readline()

    // Free the result array returned by countingSort.
    free(result); 

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
    long value = strtol(str, &endptr, 10); // Use long for intermediate parse, then cast to int

    if (endptr == str || *endptr != '\0') {
        exit(EXIT_FAILURE);
    }
    // Check for overflow if the parsed long value is outside int range
    if (value > INT_MAX || value < INT_MIN) {
        exit(EXIT_FAILURE);
    }

    return (int)value; // <--- THIS LINE WAS MISSING IN YOUR PREVIOUS COPY, CAUSING THE ERROR
}