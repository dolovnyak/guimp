/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_layer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbecker <sbecker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/15 16:58:19 by sbecker           #+#    #+#             */
/*   Updated: 2019/07/15 17:13:06 by sbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "guimp.h"

int add_layer(t_ui_main *m, void *el_v)
{
	t_ui_el		*el;
	t_ui_el		*tmp2;
	t_ui_el		*layer_menu;
	t_ui_el		*tmp_el;
	t_guimp		*g;

	el = (t_ui_el *)el_v;
	g = (t_guimp *)m->data;
	if (gm_generator_get_surf_count() > 20)
		return (1);
	layer_menu = ui_win_find_el_by_id(g->main_win, GM_LAYER_ID_MENU);
	if (!(tmp_el = ui_el_init()))
	{
		printf("layer malloc error in scrollable menu in layer_win\n");
		return (1);
	}
	ui_el_setup_default(tmp_el);
	ui_el_setup_default_scroll_menu_elem(tmp_el);
	ui_el_add_child(layer_menu, tmp_el);
	tmp_el->id = gm_generate_surf_id(ID_GENERATOR_ADD);
	ui_el_set_new_pos(tmp_el, 0, 0,
		(t_fvec2){0.0,
			((t_ui_el *)layer_menu->children->content)->rrect.y + 0.25f * (float)gm_generator_get_surf_count()});// * layer_menu->crect.x / g->main_win->size.y * (float)gm_generator_get_surf_count()});
	ui_el_set_size(tmp_el, 0, (t_fvec2){1, 0.25});
	tmp_el->sdl_renderer = g->main_win->sdl_renderer;
	ui_el_add_color_texture(tmp_el, (t_vec2){1704, 800}, tmp_el->id % 2 ? 0x88AA88 : 0x669966, "default");
	ui_el_add_color_texture(tmp_el, (t_vec2){1704, 800}, 0xFF5050, "onActive");
	ui_el_add_color_texture(tmp_el, (t_vec2){1704, 800}, 0x5050FF, "onFocus");
	ui_event_add_listener(tmp_el->events->on_pointer_left_button_pressed, OnPtrLBD);
	ui_event_add_listener(tmp_el->events->on_pointer_enter, OnPtrEnter);
	ui_event_add_listener(tmp_el->events->on_pointer_left_button_pressed, PressedLBD);
	ui_event_add_listener(tmp_el->events->on_pointer_exit, OnPtrExit);

	if (!(el = ui_el_init()))
	{
		printf("layer texture malloc error in scrollable menu in layer_win\n");
		return (1);
	}
	ui_el_setup_default(el);
	ui_el_add_child(tmp_el, el);
	ui_el_set_pos(el, 0, (t_fvec2){0.04, 0.05});
	ui_el_set_size(el, 0, (t_fvec2){0.92, 0.782});
	el->id = tmp_el->id * 1000;
	el->params |= EL_IGNOR_RAYCAST | EL_IS_DEPENDENT;
	el->sdl_renderer = g->main_win->sdl_renderer;
	ui_el_add_empty_texture(el, GM_IMAGE_SIZE_X, GM_IMAGE_SIZE_Y, "default");

	t_list	*tmp;
	tmp = ft_lstnew(NULL, 0);
	tmp->content = el->sdl_textures->content;
	tmp->content_size = tmp_el->id;
	ft_lstadd_back(&(g->layers.layers), tmp);

	tmp2 = el;

	if (!(el = ui_el_init()))
	{
		printf("layer texture malloc error in scrollable menu in layer_win\n");
		return (1);
	}

	ui_el_setup_default(el);
	el->params |= EL_IS_DEPENDENT;
	ui_el_add_child(tmp_el, el);
	ui_el_set_pos(el, 0, (t_fvec2){0.04, 0.85});
	ui_el_set_size(el, 0, (t_fvec2){0.45, 0.1});
	el->id = tmp_el->id * 1000 + 1;
		ui_el_set_text(el, ui_main_get_font_by_id(m, "SansSerif"),
				   (t_text_params){(t_color){0, 0, 0, 0}, (t_color){0, 0, 0, 0},
								   0, TEXT_IS_REGULAR, TEXT_IS_SOLID});
		ui_el_update_text(el, "CLEAR");
	ui_event_add_listener(el->events->on_pointer_left_button_pressed, clear_layer);
	el->data = ui_el_get_texture_by_id(tmp2, "default");
	return (1);
}