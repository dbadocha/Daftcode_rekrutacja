#include "Calc.h"

coord get_coord(coord * anchors, dist* tag_list) {

	int test_list[] = { 0, 0, 0 };
	coord coord_list[6];

	for (int i = 0; i < 6; i++) {
		for (int j = 0, k = 0; j < 3; j++) {
			if (i > 3 && j == 1)
				k = 1;
			test_list[j] = (i + j + k) % 4;
		}
		coord_list[i] = get_single_coord(anchors, test_list, tag_list);
		coord_list[i].id = i;
	}
	return count_coord_average(coord_list);
}

double dist_p1_p2(coord p1, coord p2) {
	double x = p2.x - p1.x;
	double y = p2.y - p1.y;
	double dist = x*x + y*y;
	return sqrt(dist);
}

coord count_coord_average(coord anchors[]) {
	double x = 0.0, y = 0.0;
	int anch_amount = 0;
	for (int i = 0; i < 6; i++)
	{
		if (anchors[i].x != 0.0 || anchors[i].y != 0.0) {
			x += anchors[i].x;
			y += anchors[i].y;
			anch_amount++;
		}
	}
	coord tmp = { .x = x / anch_amount , .y = y / anch_amount };
	return tmp;
}

void fill_poly_tags(data_handler *data) {
	for (int poly_array_id = 0; poly_array_id < data->polys_len; poly_array_id++) {
		for (int tag_array_id = 0; tag_array_id < data->tags_len; tag_array_id++) {
			if (tags_in_poly(data, tag_array_id, poly_array_id) == 1)
				add_tag_to_poly(data, tag_array_id, poly_array_id);
		}
	}
}

int tags_in_poly(data_handler *data, int tag_array_id, int poly_array_id) {
	double x1, x2, y1, y2;
	double px = data->found_tags[tag_array_id].x;
	double py = data->found_tags[tag_array_id].y;
	int i, j, count = 0;
	for (i = 0, j = data->polys[poly_array_id].len - 1; i < data->polys[poly_array_id].len; j = i++) {
		x1 = data->polys[poly_array_id].decoded_vertex[i].x;
		y1 = data->polys[poly_array_id].decoded_vertex[i].y;
		x2 = data->polys[poly_array_id].decoded_vertex[j].x;
		y2 = data->polys[poly_array_id].decoded_vertex[j].y;

		if ((((y1 >= py) && (y2 <= py)) || ((y1 <= py) && (y2 >= py)))
			&& (px < (x2 - x1) * (py - y1) / (y2 - y1) + x1)) {
			count = !count;
		}
	}
	return count;
}

void add_tag_to_poly(data_handler *data, int tag_array_id, int poly_array_id) {
	int p_len = data->polys[poly_array_id].tags_id_len;
	int t_id = data->found_tags[tag_array_id].id;
	int *tmp = NULL;

	for (int i = 0; i < data->polys[poly_array_id].tags_id_len; i++) {
		if (data->polys[poly_array_id].tags_id[i] == t_id) {
			return;
		}
	}

	if (p_len == 0) {
		data->polys[poly_array_id].tags_id = (int *)malloc(sizeof(int));
	}
	else {
		data->polys[poly_array_id].tags_id = (int *)realloc(data->polys[poly_array_id].tags_id, (t_id + 1) * sizeof(int));

		if (data->polys[poly_array_id].tags_id == NULL) {
			exit(-1);
		}
	}
	data->polys[poly_array_id].tags_id[p_len] = t_id;
	data->polys[poly_array_id].tags_id_len++;
}

int tags_in_poly_e(data_handler *data, int tag_array_id, int poly_array_id, int poly_array_id_e) {
	int count = 0;
	count += tags_in_poly(data, tag_array_id, poly_array_id);
	count += tags_in_poly(data, tag_array_id, poly_array_id_e);
	return count % 2;
}


coord get_single_coord(coord anchors[], int test_list[3], dist *tag_list){
	coord p1 = anchors[test_list[0]];
	coord p2 = anchors[test_list[1]];
	coord p3 = anchors[test_list[2]];

	double r1 = tag_list->dist_to[test_list[0]];
	double r2 = tag_list->dist_to[test_list[1]];
	double r3 = tag_list->dist_to[test_list[2]];

	double dist_p12 = dist_p1_p2(p1, p2);

	if (dist_p12 < fabs(r1 - r2) || dist_p12 >(r1 + r2)) {
		coord c_empty = { .x = 0.0,.y = 0.0 };
		return c_empty;
	}

	double a = (r1 * r1 - r2 * r2 + dist_p12 * dist_p12) / (2 * dist_p12);
	double h = sqrt(r1 * r1 - a * a);
	
	double cx2 = p1.x + a * (p2.x - p1.x) / dist_p12;
	double cy2 = p1.y + a * (p2.y - p1.y) / dist_p12;

	coord tmp_p1 = {
		.x = (double)(cx2 + h * (p2.y - p1.y) / dist_p12),
		.y = (double)(cy2 - h * (p2.x - p1.x) / dist_p12)
	};

	coord tmp_p2 = {
		.x = (double)(cx2 - h * (p2.y - p1.y) / dist_p12),
		.y = (double)(cy2 + h * (p2.x - p1.x) / dist_p12)
	};

	double dist_tp1_p3 = dist_p1_p2(tmp_p1, p3) - r3;
	double dist_tp2_p3 = dist_p1_p2(tmp_p2, p3) - r3;

	if (dist_tp1_p3 < dist_tp2_p3) {
		return tmp_p1;
	}
	else {
		return tmp_p2;
	}

}

int comp(const void * elem1, const void * elem2)
{
	int f = *((int*)elem1);
	int s = *((int*)elem2);
	if (f > s) return  1;
	if (f < s) return -1;
	return 0;
}