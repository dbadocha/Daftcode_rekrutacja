//SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 110);
//printf("test");
//getchar();

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <windows.h>
#include <conio.h>
#include <string.h>

typedef unsigned short int usint_td;

int menu(char *name, usint_td orient, usint_td spacing, usint_td childs, ...)
{
	va_list args;
	int tmp = 0, pos;
	char chr = "";
	usint_td opt = 1;
	char *cursor = "->";
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);

	char* title_name = (char*)malloc((strlen(name) + 7) * sizeof(char));
	char* format = malloc(childs * (spacing + 20) * sizeof(char));

	Sleep(10);
	fflush(stdin);
	do
	{
		if (tmp != 0) chr = _getch();
		if (chr == 0x48 || chr == 0x4B)
			(opt > 1 && opt != 1) ? opt-- : (opt = childs);
		else if (chr == 0x50 || chr == 0x4D)
			(opt >= 1 && opt != childs) ? opt++ : (opt = 1);
		else {/* do nothing at this time*/ }

		memset(title_name, '\0', sizeof(title_name));
		memset(format, '\0', sizeof(format));

		strcpy_s(title_name, 50, "");
		strcat_s(title_name, 50, name);
		strcat_s(title_name, 50, ":");

		system("cls");

		va_start(args, childs);

		printf(title_name);
		for (tmp = 1; tmp <= childs; tmp++)
		{
			strcpy_s(format, 50, "");
			(orient) ? strcat_s(format, 50, "\n") : 0;
			pos = spacing;
			while ((pos--) > 0) strcat_s(format, 50, "");
			if (tmp == opt) {
				strcat_s(format, 50, va_arg(args, char*));

				SetConsoleTextAttribute(hOut, 0xF0);
				printf(format);
				SetConsoleTextAttribute(hOut, 0x0F);
			}
			else {
				strcat_s(format, 50, va_arg(args, char*));
				printf(format);
			}
		}
		va_end(args);

	} while ((chr = _getch()) != 0x0D);
	return opt;
}
