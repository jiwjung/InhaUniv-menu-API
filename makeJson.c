#include "makeJson.h"

//-----------------------------------------------------------------------------------NEW CODE
void dateEdit(char* date_old, char* date_new) {
	strcpy(date_new, YEAR);
	int j = 4;
	
	for (int i = 0; i < strlen(date_old); i++) {
        if ('0' <= date_old[i] && date_old[i] <= '9') {
            date_new[j] = date_old[i];
            j++;
        }
    }
	date_new[j] = '\0';
}



void makeJson(FILE* menuFile ,FILE* jsonFile) {
	char date[16];
    char day[10];
    char ttukbaegi[256];
    char katsukatsu_A[256];
    char katsukatsu_B[256];
    char globalnoodle[256];
	
	char temp[256];
	
	fprintf(jsonFile, "[\n");
	
	for(int k = 0 ; k < 5 ; k++) { //월화수목금 반복
		fgets(temp, sizeof(temp), menuFile);
		strcpy(day, temp); //요일 추출
		day[9] = '\0';
		//str[strlen(str) - 1] = '\0';
		
		for(int i = 0 ; i < strlen(temp) ; i++) { //날짜 추출
			date[i] = temp[i+10];
		}
		date[8] = '\0';
		//-----------------------------LINE 1 END
		for(int n = 0 ; n < 4; n++) { //요일별 각 메뉴 추출
			//printf("[ %d ]\n", n);
			for(int i = 0 ; i < 5 ; i++) { //공백 행 및 비유효 데이터 읽어오기
				fgets(temp, sizeof(temp), menuFile);
			}
			for(int i = 0 ; i < strlen(temp) ; i++) {
				if(temp[i] == 13) temp[i] = 44; //'\r' => ','
			}
			temp[strlen(temp)-2] = '\0'; //가장 마지막 ',' => '\0'
			switch(n) {
				case 0:
					strcpy(ttukbaegi, temp);
					break;
				case 1:
					strcpy(katsukatsu_A, temp);
					break;
				case 2:
					strcpy(katsukatsu_B, temp);
					break;
				case 3:
					strcpy(globalnoodle, temp);
					break;
				default:
					printf("CASE ERROR!\n");
			}
		}
		for(int i = 0 ; i < 4 ; i++) {
			fgets(temp, sizeof(temp), menuFile);
		}
		
		
		char date_new[9];
		dateEdit(date, date_new);

		fprintf(jsonFile,
				"    {\n"
				"        \"date\": \"%s\",\n"
				"        \"day\": \"%s\",\n"
				"        \"ttukbaegi\": \"%s\",\n"
				"        \"katsukatsu_A\": \"%s\",\n"
				"        \"katsukatsu_B\": \"%s\",\n"
				"        \"globalnoodle\": \"%s\",\n"
				"    },\n",
				date_new, day, ttukbaegi, katsukatsu_A, katsukatsu_B, globalnoodle);
		
	}
	fprintf(jsonFile, "]\n");
	
	printf("[ INFO ] 메뉴 데이터 파싱 및 Json 파일 생성 완료\n\n");
}