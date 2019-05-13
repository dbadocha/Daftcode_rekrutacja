#include "ReadData.h"

int Read(char *main_path, data_handler *handler) {
	char buff[255] = "";
	FILE *stream = NULL;

	if (fopen_s(&stream, main_path, "r") == 0)
	{
		while (fgets(buff, 255, stream) != NULL) {
			if (strstr(buff, "anchor_id") != NULL) {
				handler->anchors = read_coord(stream, buff, &handler->anchors_len);
			}
			if (strstr(buff, "tag_id") != NULL) {
				handler->tags = read_tags(stream, buff, &handler->tags_len);
			}
			if (strstr(buff, "poly_id") != NULL) {
				handler->polys = read_polys(stream, buff, &handler->polys_len);
			}
			if (strstr(buff, "node_id") != NULL) {
				handler->nodes = read_coord(stream, buff, &handler->nodes_len);
			}
		}
	}
	else
	{
		printf("The file 'data2' was not opened\n");
		return -1;
	}
	fclose(stream);
	
	if (handler->anchors_len > 0
		&& handler->tags_len > 0
		&& handler->polys_len > 0
		&& handler->nodes_len > 0)
	{
		join_poly_node(handler->polys, handler->nodes, handler->polys_len, handler->nodes_len);
		//TestPrint(handler);
		printf("Data loaded correctly\n");
		return 1;
	}
	else {
		printf("Wrong file structure\n");
		return -2;
	}

}

coord *read_coord(FILE *stream, char buff[], int *len) {
	int amount = 0, splits_count = 0;
	char *lf_buff = NULL;
	char *next = NULL;
	char signs[] = " \t\n";
	double tmp_coord_data[10];

	*len = 1;
	coord *tmp = (coord *)malloc(*len * sizeof(coord));

	while (fgets(buff, 255, stream) != NULL && strlen(buff) > 2) {
		lf_buff = strtok_s(buff, signs, &next);
		while (lf_buff != NULL) {
			sscanf_s(lf_buff, "%lf", &tmp_coord_data[splits_count]);
			lf_buff = strtok_s(NULL, signs, &next);
			splits_count++;
		}

		if (amount >= *len) {
			tmp = (coord *)realloc(tmp, *len * 2 * sizeof(coord));
			if (tmp) {
				*len *= 2;
			}
			else {
				printf("Memory allocation error");
				exit(-1);
			}
		}
		
		tmp[amount].id = (int)tmp_coord_data[0];
		tmp[amount].x = tmp_coord_data[1];
		tmp[amount].y = tmp_coord_data[2];

		splits_count = 0;
		amount++;
	}
	*len = amount;
	return c_realloc_and_check(tmp, len, 1);
}

dist *read_tags(FILE *stream, char buff[], int *len) {
	int amount = 0, splits_count = 0;
	char *lf_buff = NULL;
	char *next = NULL;
	char signs[] = "[] \t\n";
	double tmp_anch_data[10];

	*len = 1;
	dist *tmp = (dist *)malloc(*len * sizeof(dist));
	tmp[amount].id = 1;

	while (fgets(buff, 255, stream) != NULL && strlen(buff) > 2) {
		lf_buff = strtok_s(buff, signs, &next);
		while (lf_buff != NULL) {
			sscanf_s(lf_buff, "%lf", &tmp_anch_data[splits_count]);
			lf_buff = strtok_s(NULL, signs, &next);
			splits_count++;
		}

		if (amount >= *len) {
			tmp = (dist *)realloc(tmp, *len * 2 * sizeof(dist));
			if (tmp) {
				*len *= 2;
			}
			else {
				printf("Memory allocation error");
				exit(-1);
			}
		}

		tmp[amount].id = (int)tmp_anch_data[0];

		for (int i = 0; i < splits_count - 1; i++) {
			tmp[amount].dist_to[i] = tmp_anch_data[i+1];
		}
		splits_count = 0;
		amount++;
	}

	*len = amount;
	return d_realloc_and_check(tmp, len, 1);
}

poly *read_polys(FILE *stream, char buff[], int *len) {
	int amount = 0, splits_count = 0;
	char *lf_buff = NULL;
	char *next = NULL;
	char signs[] = " \t\n";
	int tmp_anch_data[10];

	*len = 1;
	poly *tmp = (poly *)malloc(*len * sizeof(poly));

	while (fgets(buff, 255, stream) != NULL && strlen(buff) > 2) {
		lf_buff = strtok_s(buff, signs, &next);
		while (lf_buff != NULL) {
			remove_char(lf_buff, " []()");
			sscanf_s(lf_buff, "%i", &tmp_anch_data[splits_count]);
			lf_buff = strtok_s(NULL, signs, &next);
			splits_count++;
		}

		if (amount >= *len) {
			tmp = (poly *)realloc(tmp, *len * 2 * sizeof(poly));
			if (tmp) {
				*len *= 2;
			}
			else {
				printf("Memory allocation error");
				exit(-1);
			}
		}
		tmp[amount].tags_id_len = 0;
		tmp[amount].id = (int)tmp_anch_data[0];
		tmp[amount].len = splits_count - 1;
		for (int i = 0; i < splits_count - 1; i++) {
			tmp[amount].vertex_list[i] = (int)tmp_anch_data[i + 1];
		}
		splits_count = 0;
		amount++;

	}
	*len = amount;
	return p_realloc_and_check(tmp, len, 1);
}

void remove_char(char *string, char * char_list) {
	bool ch_detected;
	char buff[32] = "";
	for (int i = 0, k = 0; i < strlen(string); i++){
		ch_detected = false;
		for (int j = 0; j < strlen(char_list); j++) {
			if (string[i] == char_list[j]) {
				ch_detected = true;
				break;
			}
		}
		if (!ch_detected){
			buff[k] = string[i];
			k++;
		}
	}
	strcpy_s(string, strlen(buff) + 1, buff);
	return;
}

//no templates : (
dist *d_realloc_and_check(dist *tmp, int *ArraySize, int multip) {
	tmp = (dist *)realloc(tmp, *ArraySize * multip * sizeof(dist));
	if (tmp) {
		*ArraySize *= multip;
	}
	else {
		printf("Memory allocation error");
		exit(-1);
	}
	return tmp;
}

poly *p_realloc_and_check(poly *tmp, int *ArraySize, int multip) {
	tmp = (poly *)realloc(tmp, *ArraySize * multip * sizeof(poly));
	if (tmp) {
		*ArraySize *= multip;
	}
	else {
		printf("Memory allocation error");
		exit(-1);
	}
	return tmp;
}

coord *c_realloc_and_check(coord *tmp, int *ArraySize, int multip) {
	tmp = (coord *)realloc(tmp, *ArraySize * multip * sizeof(coord));
	if (tmp) {
		*ArraySize *= multip;
	}
	else {
		printf("Memory allocation error");
		exit(-1);
	}
	return tmp;
}

void TestPrint(data_handler *handler)
{
	printf("Anchors\n");
	for (int i = 0; i < handler->anchors_len; i++) {
		printf("id = %i, ", handler->anchors[i].id);
		printf("x = %lf, ", handler->anchors[i].x);
		printf("y = %lf\n", handler->anchors[i].y);
	}

	printf("Tags\n");
	for (int i = 0; i < handler->tags_len; i++) {
		printf("id = %i: ", handler->tags[i].id);
		printf("dist: ");
		for (int j = 0; j < 4; j++) {
			printf("%lf, ", handler->tags[i].dist_to[j]);
		}
		printf("\n");
	}

	printf("Polys\n");
	for (int i = 0; i < handler->polys_len; i++) {
		printf("id = %i, ", handler->polys[i].id);
		printf("len = %i, ", handler->polys[i].len);
		printf("vertex: ");
		for (int j = 0; j < 10; j++) {
			if (handler->polys[i].vertex_list[j] == 0xCDCDCDCD) { break; }
			printf("%i, ", handler->polys[i].vertex_list[j]);
		}
		printf("\n");
		printf("decoded_vertex: \n");
		for (int j = 0; j < 10; j++) {
			if (handler->polys[i].vertex_list[j] == 0xCDCDCDCD) { break; }
			printf("x: %lf, ", handler->polys[i].decoded_vertex[j].x);
			printf("y: %lf", handler->polys[i].decoded_vertex[j].y);
			printf("\n");
		}
		printf("\n");
	}

	printf("Nodes\n");
	for (int i = 0; i < handler->nodes_len; i++) {
		printf("id = %i, ", handler->nodes[i].id);
		printf("x = %lf, ", handler->nodes[i].x);
		printf("y = %lf\n", handler->nodes[i].y);
	}

	_getch();
	return;
}


void join_poly_node(poly *polys, coord *nodes, int polys_len, int nodes_len) {
	for (int i = 0; i < polys_len; i++) {
		for (int j = 0; j < polys[i].len; j++) {
			for (int k = 0; k < nodes_len; k++) {
				if (polys[i].vertex_list[j] == nodes[k].id) {
					polys[i].decoded_vertex[j] = nodes[k];
					break;
				}
			}
		}
	}
}