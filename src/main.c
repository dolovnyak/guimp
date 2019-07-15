/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edraugr- <edraugr-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 16:09:10 by sbednar           #+#    #+#             */
/*   Updated: 2019/07/15 17:54:28 by edraugr-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "guimp.h"

static int	scan_tool_position(t_ui_main *main, void *el_v)
{
	t_guimp	*g;
	t_ui_el	*el;
	int		x;
	int		y;

	g = (t_guimp *)(main->data);
	el = (t_ui_el *)el_v;
	x = ((float)el->ptr_rel_pos.x / (float)el->rect.w) * g->zoom_rect.w +
		g->zoom_rect.x;
	y = ((float)el->ptr_rel_pos.y / (float)el->rect.h) * g->zoom_rect.h +
		g->zoom_rect.y;
	g->draw_tool.cur_point = (t_vec2){x, y};
	return (1);
}

static int	start_draw_with_selected_tool_pointer_up(t_ui_main *main,
				void *el_v)
{
	t_guimp	*g;

	g = (t_guimp *)(main->data);
	(void)el_v;
	if (g->draw_tool.tool >= GM_TOOL_LINE)
		if (g->draw_tool.state == GM_TOOL_STATE_START)
			g->draw_tool.state = GM_TOOL_STATE_DRAW;
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
	x = ((float)el->ptr_rel_pos.x / (float)el->rect.w) * g->zoom_rect.w +
		g->zoom_rect.x;
	y = ((float)el->ptr_rel_pos.y / (float)el->rect.h) * g->zoom_rect.h +
		g->zoom_rect.y;
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
			x = ((float)el->ptr_rel_pos.x / (float)el->rect.w - (1.0 -
				GM_ZOOM_MOVE_ZONE)) / (GM_ZOOM_MOVE_ZONE);
		if (el->ptr_rel_pos.x < el->rect.w * GM_ZOOM_MOVE_ZONE)
			x = -(GM_ZOOM_MOVE_ZONE - (float)el->ptr_rel_pos.x /
				(float)el->rect.w) / GM_ZOOM_MOVE_ZONE;
		if (el->ptr_rel_pos.y > el->rect.h * (1.0 - GM_ZOOM_MOVE_ZONE))
			y = ((float)el->ptr_rel_pos.y / (float)el->rect.h -
				(1.0 - GM_ZOOM_MOVE_ZONE)) / (GM_ZOOM_MOVE_ZONE);
		if (el->ptr_rel_pos.y < el->rect.h * GM_ZOOM_MOVE_ZONE)
			y = -(GM_ZOOM_MOVE_ZONE - (float)el->ptr_rel_pos.y /
				(float)el->rect.h) / GM_ZOOM_MOVE_ZONE;
		g->zoom_rect.x += x * (GM_ZOOM_MOVE_SPEED / g->draw_tool.zoom);
		g->zoom_rect.y += y * (GM_ZOOM_MOVE_SPEED / g->draw_tool.zoom);
		g->zoom_rect.x = g->zoom_rect.x < 0 ? 0 : g->zoom_rect.x;
		g->zoom_rect.x = g->zoom_rect.x + g->zoom_rect.w > GM_IMAGE_SIZE_X ?
			GM_IMAGE_SIZE_X - g->zoom_rect.w : g->zoom_rect.x;
		g->zoom_rect.y = g->zoom_rect.y < 0 ? 0 : g->zoom_rect.y;
		g->zoom_rect.y = g->zoom_rect.y + g->zoom_rect.h > GM_IMAGE_SIZE_Y ?
			GM_IMAGE_SIZE_Y - g->zoom_rect.h : g->zoom_rect.y;
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
	ui_sdl_set_render_draw_color(el->sdl_renderer, &(t_color){g->draw_tool.r,
		g->draw_tool.g, g->draw_tool.b, 255});
	ui_sdl_render_fill_rect(el->sdl_renderer, NULL);
	ui_sdl_set_render_target(el->sdl_renderer, NULL);
	ui_sdl_render_copy(el->sdl_renderer, ui_el_get_current_texture(el), NULL,
		&el->rect);
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

static int	text_test(t_ui_main *m, void *a)
{
	t_ui_el	*el;
	t_ui_el	*dr;
	char	*res;

	(void)m;
	el = (t_ui_el *)a;
	dr = (t_ui_el *)el->data;
	if (dr->params & EL_IS_PTR_INSIDE)
	{
		res = ft_strdup("(");
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

int		main(void)
{
	t_guimp	g_main;

	ui_sdl_init();
	gm_init(&g_main);
	if (!(g_main.ui_main = ui_main_init()))
		return (0);
	ui_main_fill_default_surfaces(g_main.ui_main);
	ui_main_fill_default_functions(g_main.ui_main);
	ui_main_add_function_by_id(g_main.ui_main, ui_el_event_show_child,
		"ui_el_event_show_child");
	ui_main_add_function_by_id(g_main.ui_main, ui_el_event_default_draw,
		"ui_el_event_default_draw");
	ui_main_add_function_by_id(g_main.ui_main, draw_canvas_renderer,
		"draw_canvas_renderer");
	ui_main_add_function_by_id(g_main.ui_main, draw_with_selected_tool,
		"draw_with_selected_tool");
	ui_main_add_function_by_id(g_main.ui_main, start_draw_with_selected_tool,
		"start_draw_with_selected_tool");
	ui_main_add_function_by_id(g_main.ui_main, start_alt_with_selected_tool,
		"start_alt_with_selected_tool");
	ui_main_add_function_by_id(g_main.ui_main, move_draw_canvas_with_zoom,
		"move_draw_canvas_with_zoom");
	ui_main_add_function_by_id(g_main.ui_main, OnPtrLBD, "testOnPtrLBD");
	ui_main_add_function_by_id(g_main.ui_main, PressedLBD, "PressedLBD");
	ui_main_add_function_by_id(g_main.ui_main, OnPtrEnter, "testOnPtrEnter");
	ui_main_add_function_by_id(g_main.ui_main, OnPtrExit, "testOnPtrExit");
	ui_main_add_function_by_id(g_main.ui_main, ui_el_event_set_default_texture,
		"ui_el_event_set_default_texture");
	ui_main_add_function_by_id(g_main.ui_main, ui_el_event_set_focused_texture,
		"ui_el_event_set_focused_texture");
	ui_main_add_function_by_id(g_main.ui_main, ui_el_event_set_active_texture,
		"ui_el_event_set_active_texture");
	ui_main_add_function_by_id(g_main.ui_main, ui_el_event_children_set_default,
		"ui_el_event_children_set_default");
	ui_main_add_function_by_id(g_main.ui_main, add_layer, "test_add_layer");
	ui_main_add_function_by_id(g_main.ui_main, del_layer, "test_del_layer");
	ui_main_add_function_by_id(g_main.ui_main, draw_color_rect,
		"draw_color_rect");
	ui_main_add_function_by_id(g_main.ui_main, scan_tool_position,
		"scan_tool_position");
	ui_main_add_function_by_id(g_main.ui_main, set_brush_texture_from_el,
		"set_brush_texture_from_el");
	ui_main_add_function_by_id(g_main.ui_main, switch_fill_mode,
		"switch_fill_mode");
	ui_main_add_function_by_id(g_main.ui_main, ui_save_image, "ui_save_image");
	ui_main_add_function_by_id(g_main.ui_main, ui_open_image, "ui_open_image");
	ui_main_add_function_by_id(g_main.ui_main,
		start_draw_with_selected_tool_pointer_up,
		"start_draw_with_selected_tool_pointer_up");

	ui_main_fill_default_fonts(g_main.ui_main);
	ui_main_set_font_params(g_main.ui_main, "Neco",
		(t_font_params){0, 0, 1, 0});

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


	t_ui_el	*el;


	el = ui_win_find_el_by_id(g_main.main_win, 3);

	g_main.layers.tmp_texture = ui_el_get_texture_by_id(el, "tmp_layer");

	el = ui_win_find_el_by_id(g_main.main_win, 63000);
	g_main.layers.current_layer = el;
	t_list	*tmp;
	tmp = ft_lstnew(NULL, 0);
	tmp->content = el->sdl_textures->content;
	tmp->content_size = 63;
	ft_lstadd(&(g_main.layers.layers), tmp);

	el = ui_win_find_el_by_id(g_main.tool_win, 31);
	el->data = ui_win_find_el_by_id(g_main.main_win, GM_MAIN_ID_DRAW);
	ui_event_add_listener(el->events->on_render, text_test);

	el = ui_win_find_el_by_id(g_main.tool_win, 32);
	ui_event_add_listener(el->events->on_pointer_left_button_pressed,
		clear_all_layers);

	el = ui_win_find_el_by_id(g_main.main_win, 63001);
	ui_event_add_listener(el->events->on_pointer_left_button_pressed,
		clear_layer);
	el->data = ui_el_get_texture_by_id(ui_win_find_el_by_id(g_main.main_win,
		63000), "default");

	el = ui_win_find_el_by_id(g_main.tool_win, 1000);
	el->data = ui_el_get_texture_by_id(
			ui_win_find_el_by_id(g_main.main_win, 3), "brush_circle");

	el = ui_win_find_el_by_id(g_main.tool_win, 1001);
	el->data = ui_el_get_texture_by_id(
			ui_win_find_el_by_id(g_main.main_win, 3), "brush_rect");

	el = ui_win_find_el_by_id(g_main.tool_win, 1002);
	el->data = ui_el_get_texture_by_id(
			ui_win_find_el_by_id(g_main.main_win, 3), "brush_cloud");

	el = ui_win_find_el_by_id(g_main.tool_win, 1003);
	el->data = ui_el_get_texture_by_id(
			ui_win_find_el_by_id(g_main.main_win, 3), "brush_star");

	el = ui_win_find_el_by_id(g_main.tool_win, 1004);
	el->data = ui_el_get_texture_by_id(
		ui_win_find_el_by_id(g_main.main_win, 3), "brush_boom");

	el = ui_win_find_el_by_id(g_main.tool_win, 1100);
	el->data = ui_el_get_texture_by_id(
			ui_win_find_el_by_id(g_main.main_win, 3), "sticker_frolov");

	el = ui_win_find_el_by_id(g_main.tool_win, 1101);
	el->data = ui_el_get_texture_by_id(
			ui_win_find_el_by_id(g_main.main_win, 3), "sticker_max");

	el = ui_win_find_el_by_id(g_main.tool_win, 1102);
	el->data = ui_el_get_texture_by_id(
			ui_win_find_el_by_id(g_main.main_win, 3), "sticker_petya");

	el = ui_win_find_el_by_id(g_main.tool_win, 1103);
	el->data = ui_el_get_texture_by_id(
			ui_win_find_el_by_id(g_main.main_win, 3), "sticker_jab");

	el = ui_win_find_el_by_id(g_main.tool_win, 1104);
	el->data = ui_el_get_texture_by_id(
			ui_win_find_el_by_id(g_main.main_win, 3), "sticker_poop");

	el = ui_win_find_el_by_id(g_main.tool_win, 1105);
	el->data = ui_el_get_texture_by_id(
			ui_win_find_el_by_id(g_main.main_win, 3), "sticker_jana");

	el = ui_win_find_el_by_id(ui_main_find_window_by_id(g_main.ui_main, 5), 2);
	el->data = ui_win_find_el_by_id(ui_main_find_window_by_id(g_main.ui_main, 5)
		, 5);
	ui_event_add_listener(el->events->on_pointer_left_button_pressed,
		ui_save_image);

	el = ui_win_find_el_by_id(ui_main_find_window_by_id(g_main.ui_main, 4), 2);
	el->data =  ui_win_find_el_by_id(ui_main_find_window_by_id(g_main.ui_main,
		4), 5);
	ui_event_add_listener(el->events->on_pointer_left_button_pressed,
		ui_open_image);
	ui_main_run_program(g_main.ui_main);
	return (0);
}
