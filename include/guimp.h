/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   guimp.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbecker <sbecker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/10 19:04:10 by sbednar           #+#    #+#             */
/*   Updated: 2019/07/15 17:12:15 by sbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GUIMP_H
# define GUIMP_H

# include "libft.h"
# include "libui.h"

# define TID_DRAW_TEXTURE		"draw_texture"

# define GM_MAIN_WIN_X			800
# define GM_MAIN_WIN_Y			SDL_WINDOWPOS_CENTERED //SDL!!!
# define GM_MAIN_WIN_W			1200
# define GM_MAIN_WIN_H			800
# define GM_MAIN_ID_DRAW		3

# define GM_TOOL_WIN_W			300
# define GM_TOOL_WIN_H			800
# define GM_TOOL_WIN_X			GM_MAIN_WIN_X - GM_TOOL_WIN_W - 5
# define GM_TOOL_WIN_Y			SDL_WINDOWPOS_CENTERED //SDL!!!
# define GM_TOOL_ID_BUT_MENU	11
# define GM_TOOL_ID_BRUSH		12
# define GM_TOOL_ID_ERASER		13
# define GM_TOOL_ID_ZOOM		14
# define GM_TOOL_ID_HAND		15
# define GM_TOOL_ID_LINE		16
# define GM_TOOL_ID_PIPETTE		17
# define GM_TOOL_ID_RECT		18
# define GM_TOOL_ID_SET_MENU	20
# define GM_TOOL_ID_SL_ROOT_RED	20
# define GM_TOOL_ID_SL_HEAD_RED	200
# define GM_TOOL_ID_SL_ROOT_GR	21
# define GM_TOOL_ID_SL_HEAD_GR	210
# define GM_TOOL_ID_SL_ROOT_BL	22
# define GM_TOOL_ID_SL_HEAD_BL	220
# define GM_TOOL_ID_SL_ROOT_SZ	23
# define GM_TOOL_ID_SL_HEAD_SZ	230
# define GM_TOOL_ID_CL_RECT		29

# define GM_TOOL_ID_COLOR_RECT	30
# define GM_TOOL_ID_COLOR_TEXT	300

# define GM_LAYER_WIN_W			300
# define GM_LAYER_WIN_H			800
# define GM_LAYER_ID_MENU		4
# define GM_LAYER_ID_ADD		5
# define GM_LAYER_ID_DEL		6
# define GM_LAYER_ID_DEF_LAYER	ID_GENERATOR_START
# define GM_LAYER_MAX_COUNT		100

# define GM_IMAGE_SIZE_X		1920
# define GM_IMAGE_SIZE_Y		1080

# define GM_BRUSH_MAX_SIZE		400
# define GM_BRUSH_DEF_SIZE		10
# define GM_ZOOM_MAX_SIZE		32
# define GM_ZOOM_MOVE_ZONE		0.3
# define GM_ZOOM_MOVE_SPEED		64
# define GM_HAND_MOVE_SPEED		1
# define GM_HAND_MIN_DIST		3

# define GM_TOOL_BRUSH			0
# define GM_TOOL_ZOOM			1
# define GM_TOOL_ERASER			2
# define GM_TOOL_HAND			3
# define GM_TOOL_PIPETTE		4
# define GM_TOOL_FILL			5
# define GM_TOOL_LINE			6
# define GM_TOOL_ELLIPSE		7
# define GM_TOOL_RECT			8
# define GM_TOOL_SQUARE			9
# define GM_TOOL_TEXT			10

# define GM_TOOL_MODE_EMPTY		0
# define GM_TOOL_MODE_FILL		1

# define GM_TOOL_STATE_NONE		0
# define GM_TOOL_STATE_START	1
# define GM_TOOL_STATE_DRAW		2
# define GM_TOOL_STATE_END		3

//id_generator flags
# define ID_GENERATOR_GET		0
# define ID_GENERATOR_ADD		1
# define ID_GENERATOR_DEL		2
# define ID_GENERATOR_START		63

/* t_layers - struct for elems in layer win */
typedef struct					s_layers
{
	t_ui_el						*current_layer;
	t_list						*layers;
	t_texture					*tmp_texture;
}								t_layers;

typedef struct					s_draw_tool
{
	t_vec2						prew_point;
	t_vec2						cur_point;
	Uint8						tool;
	SDL_Texture					*brush;
	Uint8						tool_mode;
	Uint32						brush_size;
	Uint8						r;
	Uint8						g;
	Uint8						b;
	Uint8						a;
	int							zoom;
	int							state;
}								t_draw_tool;

typedef struct					s_cvec2
{
	Uint32						color1;
	Uint32						color2;
}								t_cvec2;

typedef struct					s_filler
{
	t_ui_win					*w;
	t_sur						*s;
	int							*q;
	char						*f;
	t_cvec2						*c;
}								t_filler;

typedef struct					s_guimp
{
	t_ui_main					*ui_main;
	t_ui_win					*main_win;
	t_ui_win					*tool_win;
	t_layers					layers;
	t_draw_tool					draw_tool;
	t_rect						zoom_rect;
}								t_guimp;

void							draw_dot(t_ui_main *ui_main, void *ui_el);
void							draw_main_canvas_event(void *el_v, void *arg);
int								draw_with_selected_tool(t_ui_main *main, void *el_v);
void							update_color_rect(t_guimp *gm, int r, int g, int b);

void							gm_init(t_guimp *g_main);
int								gm_generate_surf_id(int generate_flag);
int								gm_generator_get_surf_count(void);
int								gm_generator_get_surf_id_by_num(int surf_serial_num);

void							ui_main_fill_default_functions(t_ui_main *m);

int								move_windows(t_ui_main *m, void *a);
int								start_zoom_in(t_ui_main *m, void *wid);
int								start_zoom_out(t_ui_main *m, void *wid);

int	 							choose_fill(t_ui_main *main, void *el_v);
void							tool_filler(t_ui_win *w, t_texture *texture, t_cvec2 color, t_vec2 coord);

int	 							choose_eraser(t_ui_main *main, void *el_v);
void							tool_eraser(t_ui_el *el, t_guimp *g, int x, int y);

int								choose_zoom(t_ui_main *main, void *el_v);
void							tool_zoom_in(t_guimp *g, int x, int y);
void							tool_zoom_out(t_guimp *g, int x, int y);

int								choose_hand(t_ui_main *main, void *el_v);
void							tool_hand(t_guimp *g);

int								choose_pipette(t_ui_main *main, void *el_v);
void							tool_pipette(t_guimp *g, t_ui_el *el);

int								choose_text(t_ui_main *main, void *el_v);
int								update_text_color(t_ui_main *main, void *el_v);
void							draw_text(t_guimp *g, t_vec2 s, t_vec2 e, t_ui_el *el);
int								choose_font(t_ui_main *main, void *el_v);

int								choose_fill_mode(t_ui_main *main, void *el_v);
int								choose_empty_mode(t_ui_main *main, void *el_v);

int								get_value_from_slider(t_ui_el *s, t_ui_el *c);
int								choose_alpha(t_ui_main *main, void *el_v);
int								choose_size(t_ui_main *main, void *el_v);
int								choose_blue_color(t_ui_main *main, void *el_v);
int								choose_green_color(t_ui_main *main, void *el_v);
int								choose_red_color(t_ui_main *main, void *el_v);

int								choose_brush(t_ui_main *main, void *el_v);
void							tool_brush(t_ui_el *el, t_guimp *g, int x, int y);

int								choose_ellipse(t_ui_main *main, void *el_v);
void							draw_ellipse(t_guimp *g, t_vec2 start, t_vec2 end);
void							draw_empty_ellipse(t_guimp *g, t_vec2 s, t_vec2 e);

int								choose_line(t_ui_main *main, void *el_v);
void							draw_line(t_guimp *g, t_vec2 start, t_vec2 end);

int								choose_square(t_ui_main *main, void *el_v);
void							draw_square(t_guimp *g, t_vec2 s, t_vec2 e);
void							draw_empty_square(t_guimp *g, t_vec2 s, t_vec2 e);

int								choose_rect(t_ui_main *main, void *el_v);
void							draw_rect(t_guimp *g, t_vec2 s, t_vec2 e);
void							draw_empty_rect(t_guimp *g, t_vec2 s, t_vec2 e);

void							process_tmp_layer(t_guimp *g);
int								switch_fill_mode(t_ui_main *main, void *el_v);

int								set_brush_texture_from_el(t_ui_main *main, void *el_v);

int								ui_save_image(t_ui_main *main, void *el_v);
int								ui_open_image(t_ui_main *main, void *el_v);

t_vec2							lerp(t_vec2 p1, t_vec2 p2, float k);
t_vec2							calc_el_dot(t_vec2 *d, float k);

int								add_layer(t_ui_main *m, void *el_v);
int								del_layer(t_ui_main *main, void *el_v);
int								clear_layer(t_ui_main *main, void *el_v);
int								clear_all_layers(t_ui_main *main, void *el_v);

int								OnPtrEnter(t_ui_main *main, void *el_v);
int								OnPtrExit(t_ui_main *main, void *el_v);
int								PressedLBD(t_ui_main *main, void *el_v);
int								OnPtrLBD(t_ui_main *main, void *el_v);
#endif
