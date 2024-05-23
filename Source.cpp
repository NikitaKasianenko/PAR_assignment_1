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

        if (strcmp(input, "3") == 0) {
            file = fopen("C:\\Windows\\Temp\\test.txt", "w");

            if (file == NULL) {
                printf("Can't open file\n");
            }

            if (file != NULL) {
                for (int i = 0; i <= nrow; i++) {
                    for (int b = 0; b < COLS; b++) {
                        fputc(array[i][b], file);

                    }
                    fputc('\n', file);
                }
                fclose(file);
            }
        }

        if (strcmp(input, "4") == 0) {
            nrow = 0;
            printf("Enter path to file: ");
            fgets(input, bufferSize, stdin);
            input[strcspn(input, "\n")] = '\0';

            char mystring[100];
            file = fopen(input, "r");
            if (file == NULL)
            {
                printf("Error opening file");
            }
            else
            {
                int row = 0;
                while (fgets(mystring, 100, file) != NULL)
                {


                    for (int i = 0; i < strlen(mystring); i++) {

                        if (mystring[i] == '\n') {
                            array[row][i] = '\0';
                        }
                        else {
                            array[row][i] = mystring[i];
                        }
                    }
                    row++;
                }
                nrow = row;
                fclose(file);
            }
        }

        if (strcmp(input, "5") == 0) {

            for (int i = 0; i <= nrow; i++) {
                if (i > 0) {
                    printf("\n");
                }
                for (int j = 0; j < COLS; j++)
                    printf("%c", array[i][j]);
            }

            printf("\n");
        }

        if (strcmp(input, "6") == 0) {

            int currow = 0;
            int curcol = 0;

            printf("Choose line and index: ");
            fgets(input, bufferSize, stdin);
            sscanf(input, "%d %d", &currow, &curcol);

            printf("Enter text to insert: ");
            fgets(input, bufferSize, stdin);
            input[strcspn(input, "\n")] = '\0';
            int text_length = strlen(input);

            for (int i = strlen(array[currow]); i >= curcol; i--) {
                array[currow][i + text_length] = array[currow][i];
            }

            for (int i = 0; i < text_length; i++) {
                array[currow][curcol + i] = input[i];
            }


        }

        if (strcmp(input, "7") == 0) {
            printf("Enter text to search: ");
            fgets(input, bufferSize, stdin);
            input[strcspn(input, "\n")] = '\0';
            char* to_search = input;
            bool found = false;
            char* name = NULL;

            for (int i = 0; i <= nrow; i++) {

                name = strstr(array[i], to_search);
                if (name) {

                    printf("Substring found at index: %d %d\n", i, ((int)name - (int)array[i]));
                    found = true;
                }
            }

            if (!found) {
                printf("Substring not found\n");
            }
        }


        if (strcmp(input, "exit") == 0) {
            free(input);
            break;
        }


        free(input);

    }


    return 0;

}