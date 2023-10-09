#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int extMenu(FILE* file ,FILE* outfile);
void removeSpace(char *str);
int tagRemove(FILE* inputFile, FILE* outputFile);