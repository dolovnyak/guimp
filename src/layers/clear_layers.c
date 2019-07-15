/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_layers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbecker <sbecker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/15 16:53:12 by sbecker           #+#    #+#             */
/*   Updated: 2019/07/15 17:19:22 by sbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "guimp.h"

int	clear_layer(t_ui_main *main, void *el_v)
{
	t_texture	*t;
	t_guimp		*g;

	g = (t_guimp *)(main->data);
	t = (t_texture *)((t_ui_el *)el_v)->data;
	ui_sdl_set_render_target(g->main_win->sdl_renderer, t);
	ui_sdl_set_render_draw_blend_mode(g->main_win->sdl_renderer, NONE);
	ui_sdl_set_render_draw_color(g->main_win->sdl_renderer,
			&(t_color){255, 255, 255, 0});
	ui_sdl_render_fill_rect(g->main_win->sdl_renderer, NULL);
	ui_sdl_set_render_target(g->main_win->sdl_renderer, NULL);
	return (1);
}

int	clear_all_layers(t_ui_main *main, void *el_v)
{
	t_texture	*t;
	t_list		*l;
	t_guimp		*g;

	g = (t_guimp *)(main->data);
	(void)el_v;
	l = g->layers.layers;
	while (l)
	{
		t = (t_texture *)l->content;
		ui_sdl_set_render_target(g->main_win->sdl_renderer, t);
		ui_sdl_set_render_draw_blend_mode(g->main_win->sdl_renderer, NONE);
		ui_sdl_set_render_draw_color(g->main_win->sdl_renderer,
				&(t_color){255, 255, 255, 0});
		ui_sdl_render_fill_rect(g->main_win->sdl_renderer, NULL);
		l = l->next;
	}
	ui_sdl_set_render_target(g->main_win->sdl_renderer, NULL);
	return (1);
}
