#pragma once
#include <stdio.h>
#include <string.h>

#define YEAR "2023"

void dateEdit(char* date_old, char* date_new);
void makeJson(FILE* menuFile ,FILE* jsonFile);