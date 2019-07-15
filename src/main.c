/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbecker <sbecker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 16:09:10 by sbednar           #+#    #+#             */
/*   Updated: 2019/07/15 17:12:25 by sbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "guimp.h"

int move_windows(t_ui_main *m, void *a)
{
	t_ui_win    *w;
	t_list      *list;
	t_ui_win    *cur_w;
	t_vec2      pos;

	w = (t_ui_win *)a;
	if (w != NULL)
	{
		list = m->windows;
		while (list)
		{
			cur_w = (t_ui_win *)list->content;
			if (cur_w->id >= 2 || cur_w->id == w->id)
			{
				list = list->next;
				continue;
			}
			ui_sdl_get_window_position(w->sdl_window, &pos.x, &pos.y);
			if (cur_w->id == 0)
				pos.x = pos.x + GM_TOOL_WIN_W + 5;
			else if (cur_w->id == 1)
				pos.x = pos.x - GM_TOOL_WIN_W - 5;
			ui_sdl_set_window_position(cur_w->sdl_window, pos.x, pos.y);
			cur_w->pos.x = pos.x;
			cur_w->pos.y = pos.y;
			list = list->next;
		}
	}
	return (1);
}


static int	draw_canvas_renderer(t_ui_main *main, void *el_v)
{
	t_guimp	*g;
	t_ui_el	*el;
	t_list	*layer;
	int		tmp_flag;

	g = (t_guimp *)(main->data);
	el = (t_ui_el *)el_v;
	layer = g->layers.layers;
	tmp_flag = 1;
	process_tmp_layer(g);
	while (layer)
	{
		ui_sdl_render_copy(el->sdl_renderer, (t_texture *)(layer->content), &g->zoom_rect, &el->rect);
		if (tmp_flag && layer->content_size == g->layers.current_layer->parent->id)
		{
			tmp_flag = 0;
			ui_sdl_render_copy(el->sdl_renderer, g->layers.tmp_texture, &g->zoom_rect, &el->rect);
		}
		layer = layer->next;
	}
	return (1);
}

static int	start_draw_with_selected_tool(t_ui_main *main, void *el_v)
{
	t_guimp	*g;
	t_ui_el	*el;
	int		x;
	int		y;

	g = (t_guimp *)(main->data);
	el = (t_ui_el *)el_v;
	x = ((float)el->ptr_rel_pos.x / (float)el->rect.w) * g->zoom_rect.w + g->zoom_rect.x;
	y = ((float)el->ptr_rel_pos.y / (float)el->rect.h) * g->zoom_rect.h + g->zoom_rect.y;
	if ((g->draw_tool.tool < (GM_TOOL_LINE)) || (g->draw_tool.state == GM_TOOL_STATE_NONE && g->draw_tool.tool >= (GM_TOOL_LINE)))
		g->draw_tool.prew_point = (t_vec2){x, y};
	if (g->draw_tool.tool == GM_TOOL_ZOOM && g->draw_tool.zoom < GM_ZOOM_MAX_SIZE)
		tool_zoom_in(g, x, y);
	if (g->draw_tool.tool >= (GM_TOOL_LINE))
	{
		// printf("from start_draw_with_selected_tool in>>>>>>>>> %d\n", g->draw_tool.state);
		if (g->draw_tool.state == GM_TOOL_STATE_DRAW)
			g->draw_tool.state = GM_TOOL_STATE_END;
		else if (g->draw_tool.state == GM_TOOL_STATE_NONE)
			g->draw_tool.state = GM_TOOL_STATE_START;
	}
	if (g->draw_tool.tool == GM_TOOL_FILL)
	{
		Uint32 color1 = (g->draw_tool.r << 16) + (g->draw_tool.g << 8) + g->draw_tool.b;
		Uint32 color2 = ui_util_get_pixel_color_from_texture(el->sdl_renderer,
			(t_texture *)g->layers.current_layer->sdl_textures->content,
			(t_vec2){x, y});
		if (color1 != color2)
			tool_filler(g->main_win,
				(t_texture *)g->layers.current_layer->sdl_textures->content,
				(t_cvec2){color1, color2},
				(t_vec2){(int)(x * 1.0f / GM_IMAGE_SIZE_X * g->main_win->size.x), (int)(y * 1.0f / GM_IMAGE_SIZE_Y * g->main_win->size.y)});
	}
	return (1);
}

void	update_color_rect(t_guimp *gm, int r, int g, int b)
{
	t_ui_el	*el;

	el = ui_win_find_el_by_id(gm->tool_win, GM_TOOL_ID_COLOR_RECT);
	t_texture *t = (t_texture *)el->sdl_textures->content;
	ui_sdl_destroy_texture(t);
	free(el->sdl_textures);
	el->sdl_textures = NULL;
	ui_el_add_color_texture(el, (t_vec2){100, 20}, (r << 16) | (g << 8) | b, "default");
//	el = ui_win_find_el_by_id(gm->tool_win, GM_TOOL_ID_COLOR_TEXT);
}

static int	scan_tool_position(t_ui_main *main, void *el_v)
{
	t_guimp	*g;
	t_ui_el	*el;
	int		x;
	int		y;

	g = (t_guimp *)(main->data);
	el = (t_ui_el *)el_v;
	x = ((float)el->ptr_rel_pos.x / (float)el->rect.w) * g->zoom_rect.w + g->zoom_rect.x;
	y = ((float)el->ptr_rel_pos.y / (float)el->rect.h) * g->zoom_rect.h + g->zoom_rect.y;
	g->draw_tool.cur_point = (t_vec2){x, y};
	// printf(">>>>>>>>>>>>>>%d>>>>>>>>>>>>>>%d\n", g->draw_tool.cur_point.x, g->draw_tool.cur_point.y);
	return (1);
}

static int	start_draw_with_selected_tool_pointer_up(t_ui_main *main, void *el_v)
{
	t_guimp	*g;

	g = (t_guimp *)(main->data);
	(void)el_v;
	// printf("from start_draw_with_selected_tool_pointer_up in>>>>>>>>> %d\n", g->draw_tool.state);
	if (g->draw_tool.tool >= GM_TOOL_LINE)
		if (g->draw_tool.state == GM_TOOL_STATE_START)
			g->draw_tool.state = GM_TOOL_STATE_DRAW;
	// printf("from start_draw_with_selected_tool_pointer_up out>>>>>>>>> %d\n", g->draw_tool.state);
	return (1);
}

static int	start_alt_with_selected_tool(t_ui_main *main, void *el_v)
{
	t_guimp	*g;
	t_ui_el	*el;
	int		x;
	int		y;

	g = (t_guimp *)(main->data);
	el = (t_ui_el *)el_v;
	x = ((float)el->ptr_rel_pos.x / (float)el->rect.w) * g->zoom_rect.w + g->zoom_rect.x;
	y = ((float)el->ptr_rel_pos.y / (float)el->rect.h) * g->zoom_rect.h + g->zoom_rect.y;
	g->draw_tool.prew_point = (t_vec2){x, y};
	if (g->draw_tool.tool == GM_TOOL_ZOOM && g->draw_tool.zoom > 1)
		tool_zoom_out(g, x, y);
	return (1);
}

static int	move_draw_canvas_with_zoom(t_ui_main *main, void *el_v)
{
	t_guimp	*g;
	t_ui_el	*el;
	float	x;
	float	y;

	g = (t_guimp *)(main->data);
	el = (t_ui_el *)el_v;
	x = 0;
	y = 0;
	if (g->draw_tool.tool == GM_TOOL_ZOOM)
	{
		if (el->ptr_rel_pos.x > el->rect.w * (1.0 - GM_ZOOM_MOVE_ZONE))
			x = ((float)el->ptr_rel_pos.x / (float)el->rect.w - (1.0 - GM_ZOOM_MOVE_ZONE)) / (GM_ZOOM_MOVE_ZONE);
		if (el->ptr_rel_pos.x < el->rect.w * GM_ZOOM_MOVE_ZONE)
			x = -(GM_ZOOM_MOVE_ZONE - (float)el->ptr_rel_pos.x / (float)el->rect.w) / GM_ZOOM_MOVE_ZONE;
		if (el->ptr_rel_pos.y > el->rect.h * (1.0 - GM_ZOOM_MOVE_ZONE))
			y = ((float)el->ptr_rel_pos.y / (float)el->rect.h - (1.0 - GM_ZOOM_MOVE_ZONE)) / (GM_ZOOM_MOVE_ZONE);
		if (el->ptr_rel_pos.y < el->rect.h * GM_ZOOM_MOVE_ZONE)
			y = -(GM_ZOOM_MOVE_ZONE - (float)el->ptr_rel_pos.y / (float)el->rect.h) / GM_ZOOM_MOVE_ZONE;
		g->zoom_rect.x += x * (GM_ZOOM_MOVE_SPEED / g->draw_tool.zoom);
		g->zoom_rect.y += y * (GM_ZOOM_MOVE_SPEED / g->draw_tool.zoom);
		g->zoom_rect.x = g->zoom_rect.x < 0 ? 0 : g->zoom_rect.x;
		g->zoom_rect.x = g->zoom_rect.x + g->zoom_rect.w > GM_IMAGE_SIZE_X ? GM_IMAGE_SIZE_X - g->zoom_rect.w : g->zoom_rect.x;
		g->zoom_rect.y = g->zoom_rect.y < 0 ? 0 : g->zoom_rect.y;
		g->zoom_rect.y = g->zoom_rect.y + g->zoom_rect.h > GM_IMAGE_SIZE_Y ? GM_IMAGE_SIZE_Y - g->zoom_rect.h : g->zoom_rect.y;
	}
	return (1);
}

static int	draw_color_rect(t_ui_main *main, void *el_v)
{
	t_guimp	*g;
	t_ui_el	*el;

	g = (t_guimp *)(main->data);
	el = (t_ui_el *)el_v;
	ui_sdl_set_render_target(el->sdl_renderer, ui_el_get_current_texture(el));
	ui_sdl_set_render_draw_color(el->sdl_renderer, &(t_color){g->draw_tool.r, g->draw_tool.g, g->draw_tool.b, 255});
	ui_sdl_render_fill_rect(el->sdl_renderer, NULL);
	ui_sdl_set_render_target(el->sdl_renderer, NULL);
	ui_sdl_render_copy(el->sdl_renderer, ui_el_get_current_texture(el), NULL, &el->rect);
	return (1);
}

static void	ft_strjoin_free(char **to, char *what)
{
	char	*tmp;

	tmp = *to;
	*to = ft_strjoin(*to, what);
	free(tmp);
	free(what);
}

static int text_test(t_ui_main *m, void *a)
{
	t_ui_el	*el;
	t_ui_el	*dr;

	(void)m;
	el = (t_ui_el *)a;
	dr = (t_ui_el *)el->data;
	if (dr->params & EL_IS_PTR_INSIDE)
	{
		char *res = ft_strdup("(");
		ft_strjoin_free(&res, ft_itoa(dr->ptr_rel_pos.x));
		ft_strjoin_free(&res, ft_strdup(";"));
		ft_strjoin_free(&res, ft_itoa(dr->ptr_rel_pos.y));
		ft_strjoin_free(&res, ft_strdup(")"));
		ui_el_update_text(el, res);
		free(res);
	}
	else
		ui_el_update_text(el, " ");
	return (1);
}

int		main()
{
	t_guimp	g_main;

	ui_sdl_init();
	gm_init(&g_main);
	if (!(g_main.ui_main = ui_main_init()))
	{
		printf("ui_main malloc error in struct g_main\n");
		return (0);
	}
	ui_main_fill_default_surfaces(g_main.ui_main);
	ui_main_fill_default_functions(g_main.ui_main);
	ui_main_add_function_by_id(g_main.ui_main, ui_el_event_show_child, "ui_el_event_show_child");
	ui_main_add_function_by_id(g_main.ui_main, ui_el_event_default_draw, "ui_el_event_default_draw");
	ui_main_add_function_by_id(g_main.ui_main, draw_canvas_renderer, "draw_canvas_renderer");
	ui_main_add_function_by_id(g_main.ui_main, draw_with_selected_tool, "draw_with_selected_tool");
	ui_main_add_function_by_id(g_main.ui_main, start_draw_with_selected_tool, "start_draw_with_selected_tool");
	ui_main_add_function_by_id(g_main.ui_main, start_alt_with_selected_tool, "start_alt_with_selected_tool");
	ui_main_add_function_by_id(g_main.ui_main, move_draw_canvas_with_zoom, "move_draw_canvas_with_zoom");
	ui_main_add_function_by_id(g_main.ui_main, OnPtrLBD, "testOnPtrLBD");
	ui_main_add_function_by_id(g_main.ui_main, PressedLBD, "PressedLBD");
	ui_main_add_function_by_id(g_main.ui_main, OnPtrEnter, "testOnPtrEnter");
	ui_main_add_function_by_id(g_main.ui_main, OnPtrExit, "testOnPtrExit");
	ui_main_add_function_by_id(g_main.ui_main, ui_el_event_set_default_texture, "ui_el_event_set_default_texture");
	ui_main_add_function_by_id(g_main.ui_main, ui_el_event_set_focused_texture, "ui_el_event_set_focused_texture");
	ui_main_add_function_by_id(g_main.ui_main, ui_el_event_set_active_texture, "ui_el_event_set_active_texture");
	ui_main_add_function_by_id(g_main.ui_main, ui_el_event_children_set_default, "ui_el_event_children_set_default");
	ui_main_add_function_by_id(g_main.ui_main, add_layer, "test_add_layer");
	ui_main_add_function_by_id(g_main.ui_main, del_layer, "test_del_layer");
	ui_main_add_function_by_id(g_main.ui_main, draw_color_rect, "draw_color_rect");
	ui_main_add_function_by_id(g_main.ui_main, scan_tool_position, "scan_tool_position");

	ui_main_add_function_by_id(g_main.ui_main, set_brush_texture_from_el, "set_brush_texture_from_el");
	ui_main_add_function_by_id(g_main.ui_main, switch_fill_mode, "switch_fill_mode");


	ui_main_add_function_by_id(g_main.ui_main, ui_save_image, "ui_save_image");
	ui_main_add_function_by_id(g_main.ui_main, ui_open_image, "ui_open_image");
	ui_main_add_function_by_id(g_main.ui_main, start_draw_with_selected_tool_pointer_up, "start_draw_with_selected_tool_pointer_up");
	ui_main_fill_default_fonts(g_main.ui_main);
	ui_main_set_font_params(g_main.ui_main, "Neco", (t_font_params){0, 0, 1, 0});
	g_main.ui_main->data = (void *)(&g_main);
	g_main.draw_tool.brush_size = GM_BRUSH_DEF_SIZE;
	g_main.draw_tool.tool_mode = GM_TOOL_MODE_EMPTY;
	g_main.draw_tool.a = 255;
	g_main.draw_tool.zoom = 1;
	g_main.draw_tool.state = GM_TOOL_STATE_NONE;
	g_main.draw_tool.tool = GM_TOOL_BRUSH;
	g_main.zoom_rect.x = 0;
	g_main.zoom_rect.y = 0;
	g_main.zoom_rect.w = GM_IMAGE_SIZE_X;
	g_main.zoom_rect.h = GM_IMAGE_SIZE_Y;

	if (ui_jtoc_main_from_json(g_main.ui_main, "./json/main_new.json"))
		return (0);

	 g_main.main_win = ui_main_find_window_by_id(g_main.ui_main, 0);
	 g_main.tool_win = ui_main_find_window_by_id(g_main.ui_main, 1);
	ui_sdl_raise_window(g_main.main_win->sdl_window);


	t_ui_el	*cur_el;
//	cur_el = ui_win_find_el_by_id((t_ui_win *)g_main.ui_main->windows->content, 30);


	cur_el = ui_win_find_el_by_id(g_main.main_win, 3);

	g_main.layers.tmp_texture = ui_el_get_texture_by_id(cur_el, "tmp_layer");

	cur_el = ui_win_find_el_by_id(g_main.main_win, 63000);
	g_main.layers.current_layer = cur_el;
	t_list	*tmp;
	tmp = ft_lstnew(NULL, 0);
	tmp->content = cur_el->sdl_textures->content;
	tmp->content_size = 63;
	ft_lstadd(&(g_main.layers.layers), tmp);

 	cur_el = ui_win_find_el_by_id(g_main.tool_win, 31);
	cur_el->data = ui_win_find_el_by_id(g_main.main_win, GM_MAIN_ID_DRAW);
	ui_event_add_listener(cur_el->events->on_render, text_test);

	cur_el = ui_win_find_el_by_id(g_main.tool_win, 32);
	ui_event_add_listener(cur_el->events->on_pointer_left_button_pressed, clear_all_layers);

	cur_el = ui_win_find_el_by_id(g_main.main_win, 63001);
	ui_event_add_listener(cur_el->events->on_pointer_left_button_pressed, clear_layer);
	cur_el->data = ui_el_get_texture_by_id(ui_win_find_el_by_id(g_main.main_win, 63000), "default");

	cur_el = ui_win_find_el_by_id(g_main.tool_win, 1000);
	cur_el->data = ui_el_get_texture_by_id(
			ui_win_find_el_by_id(g_main.main_win, 3), "brush_circle");

	cur_el = ui_win_find_el_by_id(g_main.tool_win, 1001);
	cur_el->data = ui_el_get_texture_by_id(
			ui_win_find_el_by_id(g_main.main_win, 3), "brush_rect");

	cur_el = ui_win_find_el_by_id(g_main.tool_win, 1002);
	cur_el->data = ui_el_get_texture_by_id(
			ui_win_find_el_by_id(g_main.main_win, 3), "brush_cloud");

	cur_el = ui_win_find_el_by_id(g_main.tool_win, 1003);
	cur_el->data = ui_el_get_texture_by_id(
			ui_win_find_el_by_id(g_main.main_win, 3), "brush_star");

    cur_el = ui_win_find_el_by_id(g_main.tool_win, 1004);
    cur_el->data = ui_el_get_texture_by_id(
            ui_win_find_el_by_id(g_main.main_win, 3), "brush_boom");

	cur_el = ui_win_find_el_by_id(g_main.tool_win, 1100);
	cur_el->data = ui_el_get_texture_by_id(
			ui_win_find_el_by_id(g_main.main_win, 3), "sticker_frolov");

	cur_el = ui_win_find_el_by_id(g_main.tool_win, 1101);
	cur_el->data = ui_el_get_texture_by_id(
			ui_win_find_el_by_id(g_main.main_win, 3), "sticker_max");

	cur_el = ui_win_find_el_by_id(g_main.tool_win, 1102);
	cur_el->data = ui_el_get_texture_by_id(
			ui_win_find_el_by_id(g_main.main_win, 3), "sticker_petya");

	cur_el = ui_win_find_el_by_id(g_main.tool_win, 1103);
	cur_el->data = ui_el_get_texture_by_id(
			ui_win_find_el_by_id(g_main.main_win, 3), "sticker_jab");

	cur_el = ui_win_find_el_by_id(g_main.tool_win, 1104);
	cur_el->data = ui_el_get_texture_by_id(
			ui_win_find_el_by_id(g_main.main_win, 3), "sticker_poop");

	cur_el = ui_win_find_el_by_id(g_main.tool_win, 1105);
	cur_el->data = ui_el_get_texture_by_id(
			ui_win_find_el_by_id(g_main.main_win, 3), "sticker_jana");

	cur_el = ui_win_find_el_by_id(ui_main_find_window_by_id(g_main.ui_main, 5), 2);
	cur_el->data =  ui_win_find_el_by_id(ui_main_find_window_by_id(g_main.ui_main, 5), 5);
	ui_event_add_listener(cur_el->events->on_pointer_left_button_pressed, ui_save_image);

	cur_el = ui_win_find_el_by_id(ui_main_find_window_by_id(g_main.ui_main, 4), 2);
	cur_el->data =  ui_win_find_el_by_id(ui_main_find_window_by_id(g_main.ui_main, 4), 5);
	ui_event_add_listener(cur_el->events->on_pointer_left_button_pressed, ui_open_image);

//	t_ui_win *w = ui_main_find_window_by_id(g_main.ui_main, 4);
//	t_ui_el *el = ui_el_init();
//	el->id = 100;
//	ui_el_add_child(w->canvas, el);
//	ui_el_set_pos(el, PIXEL, (t_fvec2){10, 10});
//	ui_el_set_size(el, PIXEL, (t_fvec2){100, 100});
//	ui_el_setup_default(el);
//	el->modal_win = w;
//	ui_event_add_listener(el->events->onPointerLeftButtonPressed, ui_el_event_close_window);
//	t_ui_text *t = ui_main_get_font_by_id(g_main.ui_main, "SansSerif");
//	ui_el_set_text(el, t->font,
//				   (t_text_params){(t_color){0, 0, 0, 0}, (t_color){170, 170, 170, 0},
//								   0, TEXT_IS_REGULAR | TEXT_IS_INPUTTING | t->params, TEXT_IS_SOLID});
//	ui_el_update_text(el, "KEEEK");


	//SDL_DisplayMode DM;
	//SDL_GetCurrentDisplayMode(0, &DM);
	//if (DM.w - g_main.tool_win->size.x < g_main.main_win->size.x)
	//{
	//	g_main.tool_win->pos = (t_vec2){0, (DM.h - g_main.tool_win->size.y) / 2};
	//	SDL_SetWindowPosition(g_main.tool_win->sdl_window, g_main.tool_win->pos.x, g_main.tool_win->pos.y);
	//	g_main.main_win->pos = (t_vec2){g_main.tool_win->size.x + 10, g_main.tool_win->pos.y};
	//	SDL_SetWindowPosition(g_main.main_win->sdl_window, g_main.main_win->pos.x, g_main.main_win->pos.y);
	//	int size_x = DM.w - g_main.tool_win->size.x;
	//	g_main.main_win->size = (t_vec2){size_x, size_x / 2.13f};
	//	SDL_SetWindowSize(g_main.main_win->sdl_window, g_main.main_win->size.x, g_main.main_win->size.y);
	//	g_main.main_win->canvas->rect.w = g_main.main_win->size.x;
	//	g_main.main_win->canvas->rect.h = g_main.main_win->size.y;
	//	g_main.main_win->canvas->crect = g_main.main_win->canvas->rect;
	//	bfs_for_resize(g_main.main_win->canvas, &g_main);
	//}

	// ui_set_pixel_color_to_texture(
	// 		g_main.main_win->sdl_renderer,
	// 		(t_texture *)g_main.layers.current_layer->sdl_textures->content,
	// 		(t_vec2){10, 10}, (t_color){0, 0, 255, 155});

//	 cur_el = ui_win_find_el_by_id(g_main.tool_win, 12);
//	 cur_el->sdl_renderer = g_main.tool_win->sdl_renderer;
//	 cur_el->data = (void *)(&(t_cursor){ui_main_get_surface_by_id(g_main.ui_main, "brush"), 100, 100});
//	 ui_event_add_listener(cur_el->events->onPointerLeftButtonPressed, ui_cursor_from_el_data);
//
//	 cur_el = ui_win_find_el_by_id(g_main.tool_win, 14);
//	 ui_event_add_listener(cur_el->events->onPointerLeftButtonPressed, ui_cursor_to_default);
//
//	 ui_el_add_texture_from_file(cur_el, "/home_sbednar/21school/guimp_json/images/bl.png", "default");
//	 ui_el_add_texture_from_file_dialog(cur_el);

	ui_main_run_program(g_main.ui_main);
	return (0);
}
