#include "getHtml.h"
#include "extMenu.h"
#include "makeJson.h"
#include <stdio.h>

#define URL "https://inha.ac.kr/diet/kr/2/view.do"
#define HTML_FILE "HTML.html"
#define RAW_FILE "Raw.txt"
#define MENU_FILE "Menu.txt"
#define JSON_FILE "Json.json"

int main(void) {
	FILE* htmlFile;
	FILE* rawFile;
	FILE* menuFile;
	FILE* jsonFile;
	
	printf("\n[ INFO ] 인하대학교 학식 메뉴 가져오기를 시작합니다.\n\n");
	
	//GET HTML
	htmlFile = fopen(HTML_FILE, "w");
	getHtml(URL, htmlFile);
	fclose(htmlFile);
	
	//EXT RAW FILE
	htmlFile = fopen(HTML_FILE, "r");
	rawFile = fopen(RAW_FILE, "w");
	extMenu(htmlFile, rawFile);
	fclose(htmlFile);
	fclose(rawFile);
	
	//EXT MENU FILE
	rawFile = fopen(RAW_FILE, "r");
	menuFile = fopen(MENU_FILE, "w");
	tagRemove(rawFile, menuFile);
	fclose(rawFile);
	fclose(menuFile);
	
	//MAKE JSON FILE
	menuFile = fopen(MENU_FILE, "r");
	jsonFile = fopen(JSON_FILE, "w");
	makeJson(menuFile, jsonFile);
	fclose(menuFile);
	fclose(jsonFile);

	printf("[ INFO ] 인하대학교 학식 메뉴 가져오기를 완료했습니다.\n");
	
	return 0;
}