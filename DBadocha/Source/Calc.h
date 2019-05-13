#pragma once
#include <stdio.h>
#include <math.h>
#include <conio.h>
#include <stdbool.h>

typedef struct coord coord;
struct coord {
	int id;
	double x;
	double y;
};

typedef struct dist dist;
struct dist {
	int id;
	double dist_to[4];
};

typedef struct poly poly;
struct poly {
	int id;
	int len;
	int vertex_list[10];
	coord decoded_vertex[10];
	int tags_id_len;
	int *tags_id;
};

typedef struct data_handler data_handler;
struct data_handler {
	coord *anchors;
	int anchors_len;
	dist *tags;
	int tags_len;
	poly *polys;
	int polys_len;
	coord *nodes;
	int nodes_len;
	coord *found_tags;
	int found_tags_len;
};

coord get_single_coord(coord anchors[], int test_list[3], dist *tag_list);
coord get_coord(coord * anchors, dist* tag_list);
double dist_p1_p2(coord p1, coord p2);
coord count_coord_average(coord anchors[]);
int tags_in_poly(data_handler *data, int tag_array_id, int poly_array_id);
int tags_in_poly_e(data_handler *data, int tag_array_id, int poly_array_id, int poly_array_id_e);
void fill_poly_tags(data_handler *data);
void add_tag_to_poly(data_handler *data, int tag_array_id, int poly_array_id);
int comp(const void * elem1, const void * elem2);