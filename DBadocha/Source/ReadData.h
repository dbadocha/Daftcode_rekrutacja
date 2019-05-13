#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <stdbool.h>

#include "Calc.h"

int Read(char * main_path, data_handler *handler);
void TestPrint(data_handler *handler);
void join_poly_node(poly *polys, coord *nodes, int polys_len, int nodes_len);
void remove_char(char *string, char * char_list);
coord *read_coord(FILE *stream, char buff[], int *len);
dist *read_tags(FILE *stream, char buff[], int *len);
poly *read_polys(FILE *stream, char buff[], int *len);
dist *d_realloc_and_check(dist * tmp, int *ArraySize, int multip);
poly *p_realloc_and_check(poly * tmp, int *ArraySize, int multip);
coord *c_realloc_and_check(coord * tmp, int *ArraySize, int multip);