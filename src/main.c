/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbecker <sbecker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 16:09:10 by sbednar           #+#    #+#             */
/*   Updated: 2019/07/15 18:24:56 by sbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "guimp.h"

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
	ui_main_add_function_by_id(g_main.ui_main, on_ptr_lbd, "testOnPtrLBD");
	ui_main_add_function_by_id(g_main.ui_main, pressed_lbd, "PressedLBD");
	ui_main_add_function_by_id(g_main.ui_main, on_ptr_enter, "testOnPtrEnter");
	ui_main_add_function_by_id(g_main.ui_main, on_ptr_exit, "testOnPtrExit");
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

	el = ui_win_find_el_by_id(g_main.tool_win, 1106);
	el->data = ui_el_get_texture_by_id(
			ui_win_find_el_by_id(g_main.main_win, 3), "sticker_saley");

	el = ui_win_find_el_by_id(g_main.tool_win, 1107);
	el->data = ui_el_get_texture_by_id(
			ui_win_find_el_by_id(g_main.main_win, 3), "sticker_dasha");

	el = ui_win_find_el_by_id(g_main.tool_win, 1108);
	el->data = ui_el_get_texture_by_id(
			ui_win_find_el_by_id(g_main.main_win, 3), "sticker_semen");

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
