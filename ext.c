#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    FILE* file = fopen("HTML.html", "r");
    if (!file) {
        perror("Failed to open file");
        return 1;
    }

    FILE* outFile = fopen("ext.txt", "a");
    if (!outFile) {
        perror("Failed to open output file");
        fclose(file);
        return 1;
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
  

    fclose(file);
    fclose(outFile);
	
	printf("[ INFO ] 메뉴 RAW 데이터 추출 완료\n");
    return 0;
}
