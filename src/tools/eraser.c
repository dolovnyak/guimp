/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eraser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbecker <sbecker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/10 15:36:26 by sbednar           #+#    #+#             */
/*   Updated: 2019/07/13 10:12:40 by sbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "guimp.h"

int		choose_eraser(t_ui_main *main, void *el_v)
{
	t_guimp	*g;

	g = (t_guimp *)(main->data);
	(void)el_v;
	g->draw_tool.tool = GM_TOOL_ERASER;
	return (1);
}

void	tool_eraser(t_ui_el *el, t_guimp *g, int x, int y)
{
	SDL_BlendMode	bm;
	int				s;

	s = g->draw_tool.brush_size;
	ui_sdl_set_render_target(el->sdl_renderer,
			(SDL_Texture *)(g->layers.current_layer->sdl_textures->content));
//	SDL_GetRenderDrawBlendMode(el->sdl_renderer, &bm);
	ui_sdl_set_render_draw_blend_mode(el->sdl_renderer, SDL_BLENDMODE_NONE);
	ui_sdl_set_render_draw_color(el->sdl_renderer, &(t_color){255, 255, 255, 0});
	ui_sdl_render_fill_rect(el->sdl_renderer, &(t_rect){x - s, y - s, 2 * s, 2 * s});
	ui_sdl_set_render_target(el->sdl_renderer, NULL);
//	SDL_SetRenderDrawBlendMode(el->sdl_renderer, bm);
}

