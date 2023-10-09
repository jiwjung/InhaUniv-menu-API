#include "getHtml.h"
#include "extMenu.h"
#include <stdio.h>

#define URL "https://inha.ac.kr/diet/kr/2/view.do"
#define HTML_FILE "HTML.html"
#define RAW_FILE "Raw.txt"
#define MENU_FILE "Menu.txt"

int main(void) {
	FILE* htmlFile;
	FILE* rawFile;
	FILE* menuFile;
	
	printf("\n[ INFO ] 인하대학교 학식 메뉴 가져오기를 시작합니다.\n\n");
	
	htmlFile = fopen(HTML_FILE, "w");
	getHtml(URL, htmlFile);
	fclose(htmlFile);
	
	htmlFile = fopen(HTML_FILE, "r");
	rawFile = fopen(RAW_FILE, "w");
	extMenu(htmlFile, rawFile);
	fclose(htmlFile);
	fclose(rawFile);
	
	
	rawFile = fopen(RAW_FILE, "r");
	menuFile = fopen(MENU_FILE, "w");
	tagRemove(rawFile, menuFile);
	fclose(rawFile);
	fclose(menuFile);

	printf("[ INFO ] 인하대학교 학식 메뉴 가져오기를 완료했습니다.\n");
	
	return 0;
}