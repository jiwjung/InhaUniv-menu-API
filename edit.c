#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

void removeSpace(char *str) {
    int i = 0, j = 0;

    // Find the first non-whitespace character
    while (str[i] != '\0' && isspace(str[i])) {
        i++;
    }

    // Shift the string to remove leading whitespace
    while (str[i] != '\0') {
        str[j++] = str[i++];
    }

    // Null-terminate the new string
    str[j] = '\0';
}

void tagRemove(const char *inputFileName, const char *outputFileName) {
    FILE *inputFile = fopen(inputFileName, "r");
    FILE *outputFile = fopen(outputFileName, "w");

    if (!inputFile || !outputFile) {
        perror("File opening failed");
        exit(EXIT_FAILURE);
    }

    char line[1024];
    int isValidChar = 0;

    while (fgets(line, sizeof(line), inputFile)) {
		removeSpace(line);
		
        for (int i = 0; line[i] != '\0'; ++i) {
            if (isspace(line[i])) {
                if (isValidChar) {
                    fputc(line[i], outputFile);
                }
            } else if (line[i] == '<') {
                isValidChar = 0;
            } else if (line[i] == '>') {
                isValidChar = 1;
            } else if (isValidChar) {
                fputc(line[i], outputFile);
            }
        }
    }

    fclose(inputFile);
    fclose(outputFile);
}

int main() {
    tagRemove("ext.txt", "ext_edit.txt");
    printf("[ INFO ] 불필요한 공백과 태그를 모두 삭제했습니다. (ext_edit.txt)\n");
	
    return 0;
}
