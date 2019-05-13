#pragma once

#include <allegro5/allegro.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>

#include "Calc.h"

typedef struct graph graph;
struct graph {
	ALLEGRO_DISPLAY *display;
	ALLEGRO_BITMAP *bmp;
	double offset;
	double magnify;
};

void create_new_display(graph *display_data);
void draw_all(data_handler *handler, graph *display_data);
void draw_anchors(data_handler *handler, graph *display_data);
void draw_polygon(data_handler *handler, graph *display_data, int id);
void draw_axis(data_handler *handler, graph *display_data);
double scale(graph *display_data, double to_scale);
void draw_tag(data_handler *handler, graph *display_data, int id);
ALLEGRO_COLOR rand_color(int range, int offset);
void destroy_display(graph *display_data);
void draw_anchor_circle(data_handler *handler, graph *display_data, int anch_id, int dist_id);
void draw_tags_in_poly(data_handler *data, graph *display_data, int poly_id);
void draw_how_i_found(data_handler *data, graph *display_data);
void clear_bmp(graph *display_data);