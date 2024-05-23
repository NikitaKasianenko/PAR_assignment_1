#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main() {
    char* input = NULL;
    FILE* file;
    size_t bufferSize = 256; // Initial buffer size
    const char COLS = 100;
    const char ROWS = 100;
    char array[ROWS][COLS];
    int nrow = 0;
    int ncol = 0;


    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            array[i][j] = '\0';
        }
    }

    // Allocate memory for the input buffer
    while (1) {
        input = (char*)malloc(bufferSize * sizeof(char));
        if (input == NULL) {
            printf("Memory allocation failed. Exiting...\n");
            return 1;
        }

        printf("Choose the command: ");
        // Read the string from the console
        fgets(input, bufferSize, stdin);
        input[strcspn(input, "\n")] = '\0';


        if (strcmp(input, "1") == 0) {

            printf("Enter text to append: ");
            fgets(input, bufferSize, stdin);
            input[strcspn(input, "\n")] = '\0';


            for (int i = 0; i <= strlen(input); i++) {
                array[nrow][i + ncol] = input[i];

            }
            ncol += strlen(input);

        }


        if (strcmp(input, "2") == 0) {
            nrow++;
            ncol = 0;
            printf("New line is started\n");
        }


        free(input);

    }


    return 0;

}