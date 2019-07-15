/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   brush.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbecker <sbecker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/10 16:12:48 by sbednar           #+#    #+#             */
/*   Updated: 2019/07/15 15:38:27 by sbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "guimp.h"

int		choose_brush(t_ui_main *main, void *el_v)
{
	t_guimp	*g;

	g = (t_guimp *)(((t_ui_main *)main)->data);
	(void)el_v;
	g->draw_tool.tool = GM_TOOL_BRUSH;
	return (1);
}

int		set_brush_texture_from_el(t_ui_main *main, void *el_v)
{
	t_guimp	*g;
	t_ui_el	*el;

	g = (t_guimp *)(((t_ui_main *)main)->data);
	el = (t_ui_el *)el_v;
	g->draw_tool.brush = (t_texture *)el->data;
	return (1);
}

void	tool_brush(t_ui_el *el, t_guimp *g, int x, int y)
{
	ui_sdl_set_render_target(el->sdl_renderer,
			(t_texture *)(g->layers.current_layer->sdl_textures->content));
	ui_sdl_set_texture_color_mode(g->draw_tool.brush, g->draw_tool.r,
			g->draw_tool.g, g->draw_tool.b);
	ui_sdl_set_texture_alpha_mode(g->draw_tool.brush, g->draw_tool.a);
	ui_sdl_render_copy(el->sdl_renderer, g->draw_tool.brush, NULL,
			&((t_rect){x - g->draw_tool.brush_size / 2,
				y - g->draw_tool.brush_size / 2,
				g->draw_tool.brush_size, g->draw_tool.brush_size}));
	ui_sdl_set_render_target(el->sdl_renderer, NULL);
}
