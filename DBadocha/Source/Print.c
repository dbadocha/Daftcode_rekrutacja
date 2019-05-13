#include "Print.h"

void Print_Poly_Tags(data_handler *data, int poly_id) {
	//for (int i = 0; i < data->polys_len; i++) {
	//	for (int j = 0; j < data->polys[i].tags_id_len; j++)
	//		printf("i = %i, tag_id = %i\n", i, data->polys[i].tags_id[j]);
	//}
	int mem[255] = { 0 };
	int len = 0;

	for (int tag_array_id = 0; tag_array_id < data->tags_len; tag_array_id++) {
		if (check_doubles(mem, len, data->tags[tag_array_id].id) == 0 && tags_in_poly(data, tag_array_id, poly_id) == 1) {
			mem[len] = data->tags[tag_array_id].id;
			len++;
		}
	}

	system("cls");
	qsort(mem, len, sizeof(*mem), comp);
	printf("Amoun of tags in any polygon_id %i: %i\n", poly_id, len);
	for (int i = 0; i < len; i++) {
		printf("Tag_Id: %i\n", mem[i]);
	}
	_getch();
}

void Print_Poly_Tags_e(data_handler *data) {
	//for (int i = 0; i < data->polys_len; i++) {
	//	for (int j = 0; j < data->polys[i].tags_id_len; j++)
	//		printf("i = %i, tag_id = %i\n", i, data->polys[i].tags_id[j]);
	//}
	int mem[255] = { 0 };
	int len = 0;

	for (int tag_array_id = 0; tag_array_id < data->tags_len; tag_array_id++) {
		if (check_doubles(mem, len, data->tags[tag_array_id].id) == 0 && tags_in_poly_e(data, tag_array_id, 1, 2) == 1) {
			mem[len] = data->tags[tag_array_id].id;
			len++;
		}
	}

	system("cls");
	qsort(mem, len, sizeof(*mem), comp);
	printf("Amoun of tags in any polygon 1 - 2: %i\n", len);
	for (int i = 0; i < len; i++) {
		printf("Tag_Id: %i\n", mem[i]);
	}
	_getch();
}

void Not_in_Any_Polygon(data_handler *data){
	int mem[255] = {0};
	int len = 0;

	for (int i = 0; i < data->tags_len; i++) {
		if (check_tag(data, data->tags[i].id) == 0 && check_doubles(mem, len, data->tags[i].id) == 0) {
			mem[len] = data->tags[i].id;
			len++;
		}
	}
	system("cls");

	qsort(mem, len, sizeof(*mem), comp);

	printf("Amoun of tags not in any polygon: %i\n", len);
	for (int i = 0; i < len; i++) {
		printf("Tag_Id: %i\n", mem[i]);
	}
	_getch();
}


int check_tag(data_handler *data, int tag) {
	for (int i = 0; i < data->polys_len; i++) {
		for (int j = 0; j < data->polys[j].tags_id_len; j++)
			if (tag == data->polys[i].tags_id[j])
				return 1;
	}
	return 0;
}

int check_doubles(int *mem, int len, int tag) {
	for (int i = 0; i < len; i++) {
		if (tag == mem[i])
			return 1;
	}
	return 0;
}

void MostCommonTag(data_handler *data) {
	int mem[255] = {0};
	int tag = 0;

	for (int i = 0; i < data->tags_len; i++) {
		mem[data->tags[i].id] += 1;
	}
	
	for (int i = 0; i < 255; i++) {
		if (mem[i] > mem[tag]){
			tag = i;
		}
	}

	system("cls");
	printf("The most common tag_id: %i\n", tag);
	_getch();
}