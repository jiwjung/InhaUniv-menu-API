#include "extMenu.h"

int extMenu(FILE* file ,FILE* outFile) {
	if (!file || !outFile) {
        perror("[ ERROR ] 파일 열기 실패");
        exit(EXIT_FAILURE);
    }

    char buffer[1024];
    int cnt = 0;
	int weekcheck = 0;
	int lunchbool = 0;

    while (fgets(buffer, sizeof(buffer), file) != NULL) {
		cnt++;
		if (strstr(buffer, "<h2 class=\"objHeading_h2\">")){
			weekcheck++;
			if(weekcheck == 2) {
				fprintf(outFile, "%s\n", buffer);
			}
			else if(weekcheck > 3) weekcheck = 0;
		}
		
		if (strstr(buffer, "<h3 class=\"hSp15 objHeading_h3\">중식")){
			lunchbool = 1;
			fprintf(outFile, "%s\n", buffer);
		}
		
        if (lunchbool == 1 && strstr(buffer, "<tbody>") != NULL) {
            fprintf(outFile, "%s", buffer);
            while (fgets(buffer, sizeof(buffer), file)) {
				fprintf(outFile, "%s", buffer);

				if (strstr(buffer, "</tbody>") != NULL) {
					fprintf(outFile, "END\n");
					lunchbool = 0;
					break;
				}
			}
        }
    }
    // Continue reading and writing until the ending row ("</tbody>")
	
	printf("[ INFO ] 메뉴 RAW 데이터 추출 완료\n");
	
	return 0;
}

inline void removeSpace(char *str) {
    int i = 0, j = 0;

    // Find the first non-whitespace character
    while (str[i] != '\0' && isspace(str[i]))
        i++;

    // Shift the string to remove leading whitespace
    while (str[i] != '\0')
        str[j++] = str[i++];

    // Null-terminate the new string
    str[j] = '\0';
}

int tagRemove(FILE* inputFile, FILE* outputFile) {
    if (!inputFile || !outputFile) {
        perror("[ ERROR ] 파일 열기 실패");
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
	printf("[ INFO ] 메뉴 RAW 데이터의 태그, 공백 삭제 완료.\n\n");
	
	return 0;
}