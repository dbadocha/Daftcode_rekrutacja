#pragma once

#include <windows.h>
#include <tchar.h> 
#include <stdio.h>
#include <strsafe.h>
#include <stdbool.h>

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#include "Menu.h"

MenuArray ListPartDir(const char *path, char * file_ext);
char **get_char_list(const char *path, char * file_ext, int * array_len);