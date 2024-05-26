#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

size_t bufferSize = 5; // Initial buffer size
FILE* file;
int initialRowCount = 10;
int nrow = 0;
int ncol = 0;
char** array = NULL;


void initialize_array() {
    array = (char**)malloc(initialRowCount * sizeof(char*));
    if (array == NULL) {
        printf("Memory allocation failed.");
        exit(1);
    }
    for (int i = 0; i < initialRowCount; i++) {
        array[i] = (char*)malloc(bufferSize * sizeof(char));
        array[i][0] = '\0';
    }
}


void newBuffer(size_t* bufferSize) {
    *bufferSize = *bufferSize * 2;
}


void freeArray() {
    for (int i = 0; i <= initialRowCount; i++)
        free(array[i]);
    free(array);
}


void reallocate_rows() {

    initialRowCount *= 2;
    array = (char**)realloc(array, initialRowCount * sizeof(char*));

    if (array == NULL) {
        printf("Memory allocation failed.");
        exit(1);
    }

    for (int i = nrow; i < initialRowCount; i++) {
        array[i] = (char*)malloc(bufferSize * sizeof(char));
        if (array[i] == NULL) {
            printf("Memory allocation failed.");
            exit(1);
        }
        array[i][0] = '\0';
    }
}

char* user_input(size_t* bufferSize) {
    char* input = (char*)malloc(*bufferSize * sizeof(char));
    if (input == NULL) {
        printf("Memory allocation failed.");
        exit(1);
    }

    int length = 0;
    int symbol;

    while ((symbol = getchar()) != '\n') {
        if (length >= *bufferSize - 1) {
            *bufferSize = *bufferSize * 2;
            input = (char*)realloc(input, *bufferSize * sizeof(char));
            if (input == NULL) {
                printf("Memory allocation failed.\n");
                exit(1);
            }
        }
        input[length++] = symbol;
    }
    input[length] = '\0';

    return input;
}

void append_text() {
    char* input = NULL;
    printf("Enter text to append: ");
    input = user_input(&bufferSize);

    if (ncol + strlen(input) >= bufferSize - 1) {
        newBuffer(&bufferSize);
        array[nrow] = (char*)realloc(array[nrow], bufferSize * sizeof(char));
        if (array[nrow] == NULL) {
            printf("Memory allocation failed.");
            exit(1);
        }
    }

    for (int i = 0; i <= strlen(input); i++) {
        array[nrow][i + ncol] = input[i];

    }
    ncol += strlen(input);
}

void new_line() {
    nrow++;
    ncol = 0;
    printf("New line is started\n");
}
void write_in_file() {
    file = fopen("C:\\Windows\\Temp\\text.txt", "w");

    if (file == NULL) {
        printf("Can't open file\n");
        return;
    }

    if (file != NULL) {
        for (int i = 0; i <= nrow; i++) {
            for (int b = 0; b < strlen(array[i]) && array[i][b] != '\0'; b++) {
                fputc(array[i][b], file);

            }
            fputc('\n', file);
        }
        printf("Successful\n");
        fclose(file);
    }


}
void read_from_file() {
    nrow = 0;
    printf("Enter path to file: ");
    char* input = NULL;
    input = user_input(&bufferSize);

    char mystring[100];
    file = fopen(input, "r");
    if (file == NULL)
    {
        printf("Error opening file");
        free(input);
        return;
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

void print() {

    for (int i = 0; i <= nrow; i++) {
        if (i > 0) {
            printf("\n");
        }
        for (int j = 0; j < strlen(array[i]) && array[i][j] != '\0'; j++)
            printf("%c", array[i][j]);
    }

    printf("\n");
}
void insert_text() {

    char* input = NULL;
    int currow = 0;
    int curcol = 0;

    while (1) {
        printf("Choose line and index: ");
        input = user_input(&bufferSize);

        if (sscanf(input, "%d %d", &currow, &curcol) == 2 &&
            currow >= 0 && currow < initialRowCount &&
            curcol >= 0 && curcol <= strlen(array[currow])) {
            free(input);
            break;
        }

        free(input);
        printf("Choose correct index separated by space in format 'x y'\n");
    }

    printf("Enter text to insert: ");
    input = user_input(&bufferSize);

    int text_length = strlen(input);

    while (text_length + strlen(array[currow]) >= bufferSize - 1) {
        newBuffer(&bufferSize);
        array[currow] = (char*)realloc(array[currow], bufferSize * sizeof(char));
        if (array[currow] == NULL) {
            printf("Memory allocation failed");
            free(input);
            exit(1);
        }

    }

    for (int i = strlen(array[currow]); i >= curcol; i--) {
        array[currow][i + text_length] = array[currow][i];
    }

    for (int i = 0; i < text_length; i++) {
        array[currow][curcol + i] = input[i];
    }
    free(input);
}
void search() {

    char* input = NULL;
    printf("Enter text to search: ");
    input = user_input(&bufferSize);
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
    free(input);
}
void help() {
    printf("You open a text redactor with this functions:\n");
    printf("Command-'1': Append text \n");
    printf("Command-'2': Start the new line \n");
    printf("Command-'3': Write your text in file\n");
    printf("Command-'4': Read text from file\n");
    printf("Command-'5': Print the current text to console\n");
    printf("Command-'6': Insert the text by line and symbol index\n");
    printf("Command-'7': Search\n");
    printf("Command-'10': Exit\n\n");


}

int main() {

    initialize_array();
    help();
    char* input = NULL;



    while (1) {

        printf("Choose the command: ");
        input = user_input(&bufferSize);

        if (nrow >= initialRowCount) {
            reallocate_rows();
            free(input);
            continue;
        }

        if (strcmp(input, "1") == 0) {
            append_text();
            free(input);
            continue;
        }

        if (strcmp(input, "2") == 0) {
            new_line();
            free(input);
            continue;

        }

        if (strcmp(input, "3") == 0) {
            write_in_file();
            free(input);
            continue;
        }

        if (strcmp(input, "4") == 0) {
            read_from_file();
            free(input);
            continue;
        }

        if (strcmp(input, "5") == 0) {
            print();
            free(input);
            continue;
        }

        if (strcmp(input, "6") == 0) {
            insert_text();
            free(input);
            continue;
        }

        if (strcmp(input, "7") == 0) {
            search();
            free(input);
            continue;
        }

        if (strcmp(input, "10") == 0) {
            free(input);
            freeArray();
            break;
        }

        else {
            printf("The command is not implemented\n");
        }

    }
    return 0;
}