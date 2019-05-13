#include "Dir.h"

MenuArray ListPartDir(const char *path, char * file_ext) {
	char *search_list[] = { "@" , file_ext};
	char **ch_array = NULL, **tmp_array = NULL;
	int ch_len = 0, tmp_len;
	for (int i = 0; i < 2; i++) {
		tmp_array = get_char_list(path, search_list[i], &tmp_len);

		if (i == 0) {
			ch_array = tmp_array;
		}
		else{
			ch_array = (char **)realloc(ch_array, (ch_len + tmp_len) * sizeof(char*));
			
			if (tmp_array != NULL){
				for (int j = 0; j < (tmp_len); j++) {
					ch_array[j + ch_len] = tmp_array[j];
				}
				free(tmp_array);
			}
		}
		if (tmp_array != NULL)
			ch_len += tmp_len;
	}
	MenuArray ret = {.ArraySize = ch_len, .MenuArray = ch_array };
	return ret;
}



char **get_char_list(const char *path, char * file_ext, int * array_len)
{
	WIN32_FIND_DATA fdFile;
	HANDLE hFind = NULL;

	char sPath[2048];
	char **tmp = NULL;
	int FilesAmount = 0, ArraySize = 0;
	bool onlyFiles = false;

	if (file_ext == "@") {
		sprintf_s(sPath, 2048, "%s\\*.*", path);
		onlyFiles = true;
	}
	else
		sprintf_s(sPath, 2048, "%s\\%s", path, file_ext);

	if ((hFind = FindFirstFile(sPath, &fdFile)) == INVALID_HANDLE_VALUE)
	{
		return NULL;
	}

	ArraySize = 1;
	tmp = (char **)malloc(ArraySize * sizeof(char*));

	do
	{
		if (FilesAmount >= ArraySize) {
			tmp = (char **)realloc(tmp, ArraySize * 2 * sizeof(char*));
			if (tmp) {
				ArraySize *= 2;
			}
			else {
				printf("Memory allocation error");
				exit(1);
			}
		}

		if (strcmp(fdFile.cFileName, ".") != 0 && strcmp(fdFile.cFileName, "..") != 0){
			sprintf_s(sPath, 2048, "%s\\%s", path, fdFile.cFileName);
			if (fdFile.dwFileAttributes &FILE_ATTRIBUTE_DIRECTORY) {
				tmp[FilesAmount] = (char *)malloc((strlen(fdFile.cFileName) + 1) * sizeof(char));
				strcpy_s(tmp[FilesAmount], strlen(fdFile.cFileName) + 1, fdFile.cFileName);
				FilesAmount++;
			}
			else if (!onlyFiles) {
				tmp[FilesAmount] = (char *)malloc(strlen(fdFile.cFileName) * sizeof(char));
				strcpy_s(tmp[FilesAmount], strlen(fdFile.cFileName) + 1, fdFile.cFileName);
				FilesAmount++;
			}
		}
		else if(strcmp(fdFile.cFileName, "..") == 0 && onlyFiles){
			tmp[FilesAmount] = (char *)malloc(strlen("cd..") * sizeof(char));
			strcpy_s(tmp[FilesAmount], strlen("cd..") + 1, "cd..");
			FilesAmount++;
		}

	} while (FindNextFile(hFind, &fdFile));
	FindClose(hFind);

	tmp = (char **)realloc(tmp, (FilesAmount + 1) * sizeof(char*));
	*array_len = FilesAmount;

	return tmp;
}