#include <stdio.h>
#include <string.h>
#include <time.h>

#include "Menu.h"
#include "ReadData.h"
#include "Calc.h"
#include "Dir.h"
#include "Draw.h"
#include "Print.h"



int main()
{
	srand(time(NULL));

	data_handler data = {
		.anchors = NULL,
		.anchors_len = 0,
		.tags = NULL,
		.tags_len = 0,
		.polys = NULL,
		.polys_len = 0,
		.nodes = NULL,
		.nodes_len = 0,
		.found_tags = NULL,
		.found_tags_len = 0
	};

	graph display_data = {
		.display = NULL,
		.bmp = NULL,
		.offset = 1.4,
		.magnify = 250
	};

	char *ptr = NULL, *tmp_path = NULL;
	ptr = _getcwd(tmp_path, 255);
	if (ptr == NULL && errno != ERANGE)
	{
		exit(-1);
	}

	char path[512] = "";
	strcpy_s(&path, 512, ptr);
	MenuArray Lista;
	char *title = "SELECT FILE DIR";
	char tmp[512] = "";
	int file_menu = 0;
	int test = 0;
	do {
		Lista = ListPartDir(path, "*.txt");

		strcpy_s(&tmp, 512, path);
		strcat_s(&tmp, 512, "\n");
		strcat_s(&tmp, 512, title);
		file_menu = menu(&tmp, 1, Lista.ArraySize, Lista.MenuArray);

		if (file_menu == 1) {
			tmp_path = strrchr(path, '\\');
			if (tmp_path == NULL) {
			}
			else {
				memset(tmp_path, '\0', strlen(tmp_path));
			}
		}
		else if (strstr(Lista.MenuArray[file_menu - 1], ".txt") == NULL) {
			strcat_s(path, 512, "\\");
			strcat_s(path, 512, Lista.MenuArray[file_menu - 1]);
			printf("%s\n", path);
		}
		else {
			strcpy_s(&tmp, 512, path);
			strcat_s(tmp, 512, "\\");
			strcat_s(tmp, 512, Lista.MenuArray[file_menu - 1]);
			system("cls");
			test = Read(tmp, &data);
			Sleep(1000);
		}
	} while (strstr(Lista.MenuArray[file_menu - 1], ".txt") == NULL || test != 1);
	
	data.found_tags = (coord *)malloc(data.tags_len * sizeof(coord));
	for (int i = 0; i < data.tags_len; i++) {
		data.found_tags[i] = get_coord(data.anchors, &data.tags[i]);
		data.found_tags[i].id = i;
	}
	fill_poly_tags(&data);
	


	const char *start_list_title = "OPTIONS:";
	const char *start_list[] = {"DRAW", "PRINT", "EXIT" };

	const char *draw_title = "DRAW:";
	const char *draw[] = {"ALL", "TAGS IN POLYGON", "HOW DID I FOUND TAGS", "RETURN"};
	const char *list[] = { "0", "1", "2", "3", "1-2", "RETURN"};

	const char *print_title = "PRINT:";
	const char *print[] = {"TAGS IN POLYGON", "TAGS NOT IN ANY POLYGON", "THE MOST COMMON TAG ID", "RETURN" };
	int menu_size = 3;
	int response = 0;

	do {
	response = menu(start_list_title, 1, 3, start_list);
		switch (response)
		{
		case 1:
			do {
				response = menu(draw_title, 1, 4, draw);
				if (response == 1)
					draw_all(&data, &display_data);
				if (response == 2){
					response = menu(draw_title, 1, 6, list);
					if (response == 5)
						draw_tags_in_poly_e(&data, &display_data);
					else if (response != 6 )
						draw_tags_in_poly(&data, &display_data, response-1);
					response = 0;
				}
				if (response == 3)
					draw_how_i_found(&data, &display_data);
			} while (response != 4);
			break;
		case 2:
			do {
				response = menu(print_title, 1, 4, print);
				if (response == 1) {
					response = menu(draw_title, 1, 6, list);
					if (response == 5)
						Print_Poly_Tags_e(&data);
					else if (response != 6)
						Print_Poly_Tags(&data, response - 1);
					response = 0;
				}
				if (response == 2)
					Not_in_Any_Polygon(&data);
				if (response == 3)
					MostCommonTag(&data);
			} while (response != 4);
			break;
		case 3:
			destroy_display(&display_data);
			exit(0);
		}
		destroy_display(&display_data);
	} while (1);
	return 0;
}