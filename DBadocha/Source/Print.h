#pragma once
#include "ReadData.h"

int check_tag(data_handler *data, int tag);
int check_doubles(int *mem, int len, int tag);
void Not_in_Any_Polygon(data_handler *data);
void MostCommonTag(data_handler *data);
int comp(const void * elem1, const void * elem2);
void Print_Poly_Tags_e(data_handler *data);
void Print_Poly_Tags(data_handler *data, int poly_id);