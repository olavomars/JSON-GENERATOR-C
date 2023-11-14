#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define DATA_SIZE 1000

void renderInterface() {
    printf("1. Create JSON \n");
    printf("2. Visualize JSON\n");
}

char* setFilePath() {
    char *defaultPath = "data/";
    char *fileType = ".json";
    char fileName[100];
    
    printf("Name of the json file: ");
    // question jansen: I read about "%ms", m modifier for dynamic allocation in scanf, but couldn't make work
    scanf("%s", fileName);
    
    char *target = malloc(strlen(defaultPath) + strlen(fileName) + strlen(fileType) + 1);

    strcpy(target, defaultPath);
    strcat(target, fileName);
    strcat(target, fileType);

    return target;
}

int generateJson() {
    char *key = NULL;
    char *value = NULL;
    char *data = malloc(1); 
    char buffer[1000];
    FILE *fPtr;

    char *filePath = setFilePath();

    fPtr = fopen(filePath, "w");

    if (fPtr == NULL) {
        printf("Unable to create file.\n");
        exit(EXIT_FAILURE);
    }

    printf("Enter key-value pairs to store in the file (type 'no' to stop):\n");

    do {
        printf("Enter key: ");
        key = malloc(1000); 
        scanf("%s", key);

        if (strcmp(key, "no") == 0) {
            free(key);
            break;
        }

        printf("Enter value: ");
        value = malloc(1000); 
        scanf("%s", value);

        sprintf(buffer, "\"%s\": \"%s\",\n", key, value);
        data = realloc(data, strlen(data) + strlen(buffer) + 1);
        strcat(data, buffer);

        free(key);
        free(value);

    } while (strcmp(key, "no") != 0);

    data[strlen(data) - 2] = '\0';
    fputs("{\n", fPtr);
    fputs(data, fPtr);
    fputs("\n}", fPtr);

    fclose(fPtr);
    printf("File created and saved successfully. :) \n");

    free(filePath);
    free(data);

    return 0;
}

int handleUserInput() {
    int opt;
    printf("select what you want to do: \n");
    scanf("%d", &opt);
    switch (opt) {
        case 1:
            generateJson();
        break;
        case 2:
            setFilePath();
        break; 
        default:
        printf("Invalid option, please select one of the available options\n");
        return 1;
    }
    return 0;
}


void menu() {
    renderInterface();
    handleUserInput();
}

int main() 
{
    menu();

    return 0;
}

