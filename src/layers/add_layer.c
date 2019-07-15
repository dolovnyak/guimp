/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_layer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbecker <sbecker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/15 16:58:19 by sbecker           #+#    #+#             */
/*   Updated: 2019/07/15 18:08:14 by sbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "guimp.h"

static t_ui_el	*create_tmp_el(t_guimp *g, t_ui_el *layer_menu)
{
	t_ui_el		*tmp_el;

	tmp_el = ui_el_init();
	ui_el_setup_default(tmp_el);
	ui_el_setup_default_scroll_menu_elem(tmp_el);
	ui_el_add_child(layer_menu, tmp_el);
	tmp_el->id = gm_generate_surf_id(ID_GENERATOR_ADD);
	ui_el_set_new_pos(tmp_el, 0, 0,
		(t_fvec2){0.0, ((t_ui_el *)layer_menu->children->content)->rrect.y
		+ 0.25f * (float)gm_generator_get_surf_count()});
	ui_el_set_size(tmp_el, 0, (t_fvec2){1, 0.25});
	tmp_el->sdl_renderer = g->main_win->sdl_renderer;
	ui_el_add_color_texture(tmp_el, (t_vec2){1704, 800},
			tmp_el->id % 2 ? 0x88AA88 : 0x669966, "default");
	ui_el_add_color_texture(tmp_el, (t_vec2){1704, 800}, 0xFF5050, "onActive");
	ui_el_add_color_texture(tmp_el, (t_vec2){1704, 800}, 0x5050FF, "onFocus");
	ui_event_add_listener(tmp_el->events->on_pointer_left_button_pressed,
			on_ptr_lbd);
	ui_event_add_listener(tmp_el->events->on_pointer_enter,
			on_ptr_enter);
	ui_event_add_listener(tmp_el->events->on_pointer_left_button_pressed,
			pressed_lbd);
	ui_event_add_listener(tmp_el->events->on_pointer_exit, on_ptr_exit);
	return (tmp_el);
}

static t_ui_el	*create_el(t_guimp *g, t_ui_el *tmp_el)
{
	t_ui_el	*el;

	el = ui_el_init();
	ui_el_setup_default(el);
	ui_el_add_child(tmp_el, el);
	ui_el_set_pos(el, 0, (t_fvec2){0.04, 0.05});
	ui_el_set_size(el, 0, (t_fvec2){0.92, 0.782});
	el->id = tmp_el->id * 1000;
	el->params |= EL_IGNOR_RAYCAST | EL_IS_DEPENDENT;
	el->sdl_renderer = g->main_win->sdl_renderer;
	ui_el_add_empty_texture(el, GM_IMAGE_SIZE_X, GM_IMAGE_SIZE_Y, "default");
	return (el);
}

static void		add_to_layers(t_ui_el *el, t_guimp *g, t_ui_el *tmp_el)
{
	t_list	*tmp;

	tmp = ft_lstnew(NULL, 0);
	tmp->content = el->sdl_textures->content;
	tmp->content_size = tmp_el->id;
	ft_lstadd_back(&(g->layers.layers), tmp);
}

static void		process(t_ui_el *el, t_ui_main *m, t_ui_el *tmp_el)
{
	t_ui_el	*tmp2;

	tmp2 = el;
	el = ui_el_init();
	ui_el_setup_default(el);
	ui_el_setup_default_scroll_menu_elem(el);
	el->params |= EL_IS_DEPENDENT;
	ui_el_add_child(tmp_el, el);
	ui_el_set_pos(el, 0, (t_fvec2){0.04, 0.85});
	ui_el_set_size(el, 0, (t_fvec2){0.45, 0.1});
	el->id = tmp_el->id * 1000 + 1;
	ui_el_set_text(el, ui_main_get_font_by_id(m, "SansSerif"),
		(t_text_params){(t_color){0, 0, 0, 0}, (t_color){0, 0, 0, 0},
		0, TEXT_IS_REGULAR, TEXT_IS_SOLID});
	ui_el_update_text(el, "CLEAR");
	ui_event_add_listener(el->events->on_pointer_left_button_pressed,
			clear_layer);
	el->data = ui_el_get_texture_by_id(tmp2, "default");
}

int				add_layer(t_ui_main *m, void *el_v)
{
	t_ui_el		*el;
	t_ui_el		*layer_menu;
	t_ui_el		*tmp_el;
	t_guimp		*g;

	el = (t_ui_el *)el_v;
	g = (t_guimp *)m->data;
	if (gm_generator_get_surf_count() > 30)
		return (1);
	layer_menu = ui_win_find_el_by_id(g->main_win, GM_LAYER_ID_MENU);
	tmp_el = create_tmp_el(g, layer_menu);
	el = create_el(g, tmp_el);
	add_to_layers(el, g, tmp_el);
	process(el, m, tmp_el);
	return (1);
}
