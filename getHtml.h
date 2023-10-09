#pragma once
#include <stdio.h>
#include <curl/curl.h>

//#define URL "https://inha.ac.kr/diet/kr/2/view.do"
//#define OUTPUT_FILE "HTML.html"

size_t write_callback(void *contents, size_t size, size_t nmemb, FILE *file);
int getHtml(char* URL ,FILE* OUTPUT_FILE);