// Menu implementation
#include "Menu.h"

int menu(char *name, usint_td orient, usint_td array_size, char **options_array)
{
	int tmp = 0;
	char chr = "";
	usint_td opt = 0;
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);

	int title_size = (int)strlen(name) + 2;
	int format_size = 50;
	char* title_name = malloc(title_size * sizeof(char));
	char* format = malloc(format_size * sizeof(char));

	do
	{
		if (tmp != 0) chr = _getch();
		if (chr == W_GORE || chr == W_LEWO)
			(opt > 0 && opt != 0) ? opt-- : (opt = array_size - 1);
		else if (chr == W_DOL || chr == W_PRAWO)
			(opt >= 0 && opt != array_size - 1) ? opt++ : (opt = 0);
		else {}

		system("cls");

		strcpy_s(title_name, title_size, "");
		strcat_s(title_name, title_size, name);
		strcat_s(title_name, title_size, ":");

		printf(title_name);
		for (tmp = 0; tmp < array_size; tmp++)
		{
			strcpy_s(format, format_size, "");
			(orient) ? strcat_s(format, format_size, "\n") : 0;
			strcat_s(format, format_size, " ");
			if (tmp == opt) {
				strcat_s(format, format_size, options_array[tmp]);
				strcat_s(format, format_size, " ");

				SetConsoleTextAttribute(hOut, 0xF0);
				printf(format);
				SetConsoleTextAttribute(hOut, 0x0F);
			}
			else {
				strcat_s(format, format_size, options_array[tmp]);
				printf(format);
			}
		}
		printf("\n");
	} while ((chr = _getch()) != ENTER);

	free(title_name);
	free(format);
	return ++opt;
}
