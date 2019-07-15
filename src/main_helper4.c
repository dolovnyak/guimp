/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_helper4.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edraugr- <edraugr-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/15 18:18:46 by edraugr-          #+#    #+#             */
/*   Updated: 2019/07/15 18:23:35 by edraugr-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "guimp.h"

static void	gm_fill4(t_guimp *g)
{
	t_ui_el	*el;

	el = ui_win_find_el_by_id(ui_main_find_window_by_id(g->ui_main, 5), 2);
	el->data = ui_win_find_el_by_id(ui_main_find_window_by_id(g->ui_main, 5),
			5);
	ui_event_add_listener(el->events->on_pointer_left_button_pressed,
			ui_save_image);
	el = ui_win_find_el_by_id(ui_main_find_window_by_id(g->ui_main, 4), 2);
	el->data = ui_win_find_el_by_id(ui_main_find_window_by_id(g->ui_main,
			4), 5);
	ui_event_add_listener(el->events->on_pointer_left_button_pressed,
			ui_open_image);
}

static void	gm_fill3(t_guimp *g)
{
	t_ui_el	*el;

	el = ui_win_find_el_by_id(g->tool_win, 1102);
	el->data = ui_el_get_texture_by_id(
			ui_win_find_el_by_id(g->main_win, 3), "sticker_petya");
	el = ui_win_find_el_by_id(g->tool_win, 1103);
	el->data = ui_el_get_texture_by_id(
			ui_win_find_el_by_id(g->main_win, 3), "sticker_jab");
	el = ui_win_find_el_by_id(g->tool_win, 1104);
	el->data = ui_el_get_texture_by_id(
			ui_win_find_el_by_id(g->main_win, 3), "sticker_poop");
	el = ui_win_find_el_by_id(g->tool_win, 1105);
	el->data = ui_el_get_texture_by_id(
			ui_win_find_el_by_id(g->main_win, 3), "sticker_jana");
	el = ui_win_find_el_by_id(g->tool_win, 1106);
	el->data = ui_el_get_texture_by_id(
			ui_win_find_el_by_id(g->main_win, 3), "sticker_saley");
	el = ui_win_find_el_by_id(g->tool_win, 1107);
	el->data = ui_el_get_texture_by_id(
			ui_win_find_el_by_id(g->main_win, 3), "sticker_dasha");
	el = ui_win_find_el_by_id(g->tool_win, 1108);
	el->data = ui_el_get_texture_by_id(
			ui_win_find_el_by_id(g->main_win, 3), "sticker_semen");
	gm_fill4(g);
}

static void	gm_fill2(t_guimp *g)
{
	t_ui_el	*el;

	el = ui_win_find_el_by_id(g->tool_win, 1000);
	el->data = ui_el_get_texture_by_id(
			ui_win_find_el_by_id(g->main_win, 3), "brush_circle");
	el = ui_win_find_el_by_id(g->tool_win, 1001);
	el->data = ui_el_get_texture_by_id(
			ui_win_find_el_by_id(g->main_win, 3), "brush_rect");
	el = ui_win_find_el_by_id(g->tool_win, 1002);
	el->data = ui_el_get_texture_by_id(
			ui_win_find_el_by_id(g->main_win, 3), "brush_cloud");
	el = ui_win_find_el_by_id(g->tool_win, 1003);
	el->data = ui_el_get_texture_by_id(
			ui_win_find_el_by_id(g->main_win, 3), "brush_star");
	el = ui_win_find_el_by_id(g->tool_win, 1004);
	el->data = ui_el_get_texture_by_id(
			ui_win_find_el_by_id(g->main_win, 3), "brush_boom");
	el = ui_win_find_el_by_id(g->tool_win, 1100);
	el->data = ui_el_get_texture_by_id(
			ui_win_find_el_by_id(g->main_win, 3), "sticker_frolov");
	el = ui_win_find_el_by_id(g->tool_win, 1101);
	el->data = ui_el_get_texture_by_id(
			ui_win_find_el_by_id(g->main_win, 3), "sticker_max");
	gm_fill3(g);
}

void		gm_fill(t_guimp *g)
{
	t_ui_el	*el;
	t_list	*tmp;

	el = ui_win_find_el_by_id(g->main_win, 3);
	g->layers.tmp_texture = ui_el_get_texture_by_id(el, "tmp_layer");
	el = ui_win_find_el_by_id(g->main_win, 63000);
	g->layers.current_layer = el;
	tmp = ft_lstnew(NULL, 0);
	tmp->content = el->sdl_textures->content;
	tmp->content_size = 63;
	ft_lstadd(&(g->layers.layers), tmp);
	el = ui_win_find_el_by_id(g->tool_win, 31);
	el->data = ui_win_find_el_by_id(g->main_win, GM_MAIN_ID_DRAW);
	ui_event_add_listener(el->events->on_render, text_test);
	el = ui_win_find_el_by_id(g->tool_win, 32);
	ui_event_add_listener(el->events->on_pointer_left_button_pressed,
		clear_all_layers);
	el = ui_win_find_el_by_id(g->main_win, 63001);
	ui_event_add_listener(el->events->on_pointer_left_button_pressed,
		clear_layer);
	el->data = ui_el_get_texture_by_id(ui_win_find_el_by_id(g->main_win,
		63000), "default");
	gm_fill2(g);
}
