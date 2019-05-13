#include "Draw.h"

void draw_how_i_found(data_handler *data, graph *display_data) {
	int win_h_w = display_data->offset * display_data->magnify * 2;
	if (display_data->display == NULL)
		create_new_display(display_data);
	clear_bmp(display_data);
	for (int j = 0; j < 6; j += 2){
		for (int i = 0; i < 4; i++){
			draw_axis(data, display_data);
			draw_anchors(data, display_data);

			draw_anchor_circle(data, display_data, i, j);

			al_draw_bitmap(display_data->bmp, 0, 0, 2);
			al_flip_display();
			al_rest(0.6);
		}
		draw_tag(data, display_data, j);
		al_draw_bitmap(display_data->bmp, 0, 0, 2);
		al_flip_display();
		al_rest(0.6);
		clear_bmp(display_data);
		al_draw_bitmap(display_data->bmp, 0, 0, 2);
		al_flip_display();
	}
}

void draw_all(data_handler *data, graph *display_data){
	if (display_data->display == NULL)
		create_new_display(display_data);
	clear_bmp(display_data);
	draw_axis(data, display_data);
	draw_anchors(data, display_data);

	for (int i = 0; i <data->polys_len; i++)
		draw_polygon(data, display_data, i);
	for (int i = 0; i <data->tags_len; i++)
		draw_tag(data, display_data, i);

	al_draw_bitmap(display_data->bmp, 0, 0, 2);
	al_flip_display();
}

void clear_bmp(graph *display_data) {
	al_destroy_bitmap(display_data->bmp);
	display_data->bmp = NULL;
	int win_h_w = display_data->offset * display_data->magnify * 2;
	al_clear_to_color(al_map_rgb(210, 210, 210));
	display_data->bmp = al_create_bitmap(win_h_w, win_h_w);
}

void draw_tags_in_poly(data_handler *data, graph *display_data, int poly_id) {
	if (display_data->display == NULL)
		create_new_display(display_data);
	clear_bmp(display_data);
	draw_axis(data, display_data);
	draw_anchors(data, display_data);
	draw_polygon(data, display_data, poly_id);

	for (int tag_array_id = 0; tag_array_id < data->tags_len; tag_array_id++) {
		if (tags_in_poly(data, tag_array_id, poly_id) == 1)
			draw_tag(data, display_data, tag_array_id);
	}
	al_draw_bitmap(display_data->bmp, 0, 0, 2);
	al_flip_display();
}

void draw_tags_in_poly_e(data_handler *data, graph *display_data) {
	if (display_data->display == NULL)
		create_new_display(display_data);
	clear_bmp(display_data);
	draw_axis(data, display_data);
	draw_anchors(data, display_data);
	draw_polygon(data, display_data, 1);
	draw_polygon(data, display_data, 2);

	for (int tag_array_id = 0; tag_array_id < data->tags_len; tag_array_id++) {
		if (tags_in_poly_e(data, tag_array_id, 1, 2) == 1)
			draw_tag(data, display_data, tag_array_id);
	}
	al_draw_bitmap(display_data->bmp, 0, 0, 2);
	al_flip_display();
}

void create_new_display(graph *display_data) {
	al_init();
	al_init_primitives_addon();
	al_set_new_display_flags(ALLEGRO_WINDOWED);
	int win_h_w = display_data->offset * display_data->magnify * 2;
	display_data->display = al_create_display(win_h_w, win_h_w);
	display_data->bmp = al_create_bitmap(win_h_w, win_h_w);
	if (display_data == NULL) exit(-1);
	al_clear_to_color(al_map_rgb(210, 210, 210));
}

void draw_anchors(data_handler *data, graph *display_data) {
	al_set_target_bitmap(display_data->bmp);
	int cx = 0, cy = 0;
	for (int i = 0; i <data->anchors_len; i++) {
		cx = scale(display_data,data->anchors[i].x);
		cy = scale(display_data,data->anchors[i].y);
		al_draw_filled_circle(cx, cy, 3, al_map_rgb(0, 0, 0));
	}
	al_set_target_bitmap(al_get_backbuffer(display_data->display));
}

void draw_polygon(data_handler *data, graph *display_data, int id) {
	al_set_target_bitmap(display_data->bmp);
	double x1 = 0.0, y1 = 0.0;
	double x2 = 0.0, y2 = 0.0;

	ALLEGRO_COLOR frg = rand_color(170, 50);

	for (int i = 0, j = data->polys[id].len - 1; i < data->polys[id].len; j = i++) {
		x1 = scale(display_data,data->polys[id].decoded_vertex[i].x);
		y1 = scale(display_data,data->polys[id].decoded_vertex[i].y);
		x2 = scale(display_data,data->polys[id].decoded_vertex[j].x);
		y2 = scale(display_data,data->polys[id].decoded_vertex[j].y);

		al_draw_line(x1, y1, x2, y2, frg, 2);
	}
	al_set_target_bitmap(al_get_backbuffer(display_data->display));
}

void destroy_display(graph *display_data) {
	al_destroy_display(display_data->display);
	display_data->display = NULL;
}

double scale(graph *display_data, double to_scale) {
	return (to_scale + display_data->offset) * display_data->magnify;
}

void draw_tag(data_handler *data, graph *display_data, int id) {
	al_set_target_bitmap(display_data->bmp);
	double cx = 0, cy = 0;

	cx = scale(display_data,data->found_tags[id].x);
	cy = scale(display_data,data->found_tags[id].y);
	al_draw_filled_circle(cx, cy, 2, al_map_rgb(100, 100, 100));

	al_set_target_bitmap(al_get_backbuffer(display_data->display));
}

void draw_anchor_circle(data_handler *data, graph *display_data, int anch_id, int dist_id) {
	al_set_target_bitmap(display_data->bmp);
	double cx = scale(display_data,data->anchors[anch_id].x);
	double cy = scale(display_data,data->anchors[anch_id].y);
	double r =data->tags[dist_id].dist_to[anch_id] * display_data->magnify;
	al_draw_circle(cx, cy, r, al_map_rgb(100, 100, 100), 1);
	al_set_target_bitmap(al_get_backbuffer(display_data->display));
}




void draw_axis(data_handler *data, graph *display_data) {
	al_set_target_bitmap(display_data->bmp);
	double rate1 = 0.0, rate2 = 0.0;
	ALLEGRO_COLOR frg = al_map_rgb(125, 125, 125);
	int thickness = 1;
	al_draw_line(
		scale(display_data, 0.0),
		scale(display_data, 2.0),
		scale(display_data, 0.0),
		scale(display_data, -2.0),
		frg, 1);

	al_draw_line(
		scale(display_data, 2.0),
		scale(display_data, 0.0),
		scale(display_data, -2.0),
		scale(display_data, 0.0),
		frg, 1);

	for (int i = -15; i < 15; i++) {
		if (i == 0) i++;
		rate1 = (double)i / 10;
		if ((abs(i) % 10) == 0) {
			rate2 = 1.0;
			thickness = 2;
		}
		else {
			rate2 = 2.0;
			thickness = 1;
		}

		al_draw_line(
			scale(display_data, rate1),
			scale(display_data, (0.05 / rate2)),
			scale(display_data, rate1),
			scale(display_data, (-0.05 / rate2)),
			frg, thickness);

		al_draw_line(
			scale(display_data, (0.04 / rate2)),
			scale(display_data, rate1),
			scale(display_data, (-0.04 / rate2)),
			scale(display_data, rate1),
			frg, thickness);
	}

	al_set_target_bitmap(al_get_backbuffer(display_data->display));
}

ALLEGRO_COLOR rand_color(int range, int offset)
{
	return al_map_rgb(
		(rand() % range) + offset,
		(rand() % range) + offset,
		(rand() % range) + offset
	);
}