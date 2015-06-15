#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

void junirus(const wchar_t *hack); // <<-- main
int junirus_start(const wchar_t *hack);
bool ListDirectoryContents(const wchar_t *sDir);
void changeContents(wchar_t *sPath);
void makeContents(wchar_t *sDir);
char *junoStrReplace(char *subject, char *search, char*replace);
char * WCtoC(wchar_t* str);