/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rect.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbecker <sbecker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/10 15:52:59 by sbednar           #+#    #+#             */
/*   Updated: 2019/07/15 12:59:30 by sbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "guimp.h"

int	choose_rect(t_ui_main *main, void *el_v)
{
	t_guimp	*g;

	g = (t_guimp *)(main->data);
	(void)el_v;
	g->draw_tool.tool = GM_TOOL_RECT;
	g->draw_tool.state = GM_TOOL_STATE_NONE;
	return (1);
}

void	draw_rect(t_guimp *g, t_vec2 s, t_vec2 e)
{
	ui_sdl_render_fill_rect(g->main_win->sdl_renderer, &(t_rect){
			s.x,
			s.y,
			e.x - s.x,
			e.y - s.y});
}

void	draw_empty_rect(t_guimp *g, t_vec2 s, t_vec2 e)
{
	int px = ft_min(s.x, e.x);
	int py = ft_min(s.y, e.y);
	int cx = s.x + e.x - px;
	int cy = s.y + e.y - py;
	if ((Uint32)abs(s.x - e.x) < g->draw_tool.brush_size ||
		(Uint32)abs(s.y - e.y) < g->draw_tool.brush_size)
	{
		draw_rect(g, s, e);
		return ;
	}
	ui_sdl_render_fill_rect(g->main_win->sdl_renderer, &(t_rect) {
			px, py, g->draw_tool.brush_size, cy - py
	});
	ui_sdl_render_fill_rect(g->main_win->sdl_renderer, &(t_rect) {
			px, py, cx - px, g->draw_tool.brush_size
	});
	ui_sdl_render_fill_rect(g->main_win->sdl_renderer, &(t_rect) {
			px, cy - g->draw_tool.brush_size, cx - px,
			g->draw_tool.brush_size
	});
	ui_sdl_render_fill_rect(g->main_win->sdl_renderer, &(t_rect) {
			cx - g->draw_tool.brush_size, py, g->draw_tool.brush_size,
			cy - py
	});
}
