/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_tmp_layer.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edraugr- <edraugr-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/10 16:09:45 by sbednar           #+#    #+#             */
/*   Updated: 2019/07/15 18:49:33 by edraugr-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "guimp.h"

static void	process_draw(t_guimp *g)
{
	if (g->draw_tool.tool == GM_TOOL_RECT)
		(g->draw_tool.tool_mode == GM_TOOL_MODE_FILL ?
		draw_rect(g, g->draw_tool.prew_point, g->draw_tool.cur_point) :
		draw_empty_rect(g, g->draw_tool.prew_point, g->draw_tool.cur_point));
	else if (g->draw_tool.tool == GM_TOOL_SQUARE)
		(g->draw_tool.tool_mode == GM_TOOL_MODE_FILL ?
		draw_square(g, g->draw_tool.prew_point, g->draw_tool.cur_point) :
		draw_empty_square(g, g->draw_tool.prew_point,
				g->draw_tool.cur_point));
	else if (g->draw_tool.tool == GM_TOOL_ELLIPSE)
		(g->draw_tool.tool_mode == GM_TOOL_MODE_FILL ?
		draw_ellipse(g, g->draw_tool.prew_point, g->draw_tool.cur_point) :
		draw_empty_ellipse(g, g->draw_tool.prew_point,
				g->draw_tool.cur_point));
	else if (g->draw_tool.tool == GM_TOOL_LINE)
		draw_line(g, g->draw_tool.prew_point, g->draw_tool.cur_point);
	else if (g->draw_tool.tool == GM_TOOL_TEXT)
		draw_text(g, g->draw_tool.prew_point, g->draw_tool.cur_point,
				ui_win_find_el_by_id(g->tool_win, 121210));
}

static void	process_tool_state_draw(t_guimp *g)
{
	ui_sdl_set_render_draw_color(g->main_win->sdl_renderer, &(t_color){
		g->draw_tool.r, g->draw_tool.g, g->draw_tool.b, 255});
	process_draw(g);
}

static void	process_tool_state_end(t_guimp *g)
{
	ui_sdl_set_render_draw_color(g->main_win->sdl_renderer,
			&(t_color){g->draw_tool.r, g->draw_tool.g, g->draw_tool.b, 255});
	process_draw(g);
	g->draw_tool.state = GM_TOOL_STATE_NONE;
	ui_sdl_set_render_target(g->main_win->sdl_renderer,
			(t_texture *)(g->layers.current_layer->sdl_textures->content));
	ui_sdl_render_copy(g->main_win->sdl_renderer, g->layers.tmp_texture, 0, 0);
}

void		process_tmp_layer(t_guimp *g)
{
	ui_sdl_set_render_target(g->main_win->sdl_renderer, g->layers.tmp_texture);
	ui_sdl_set_render_draw_color(g->main_win->sdl_renderer, &(t_color){0, 0, 0,
		0});
	ui_sdl_render_clear(g->main_win->sdl_renderer);
	if (g->draw_tool.state == GM_TOOL_STATE_DRAW)
		process_tool_state_draw(g);
	if (g->draw_tool.state == GM_TOOL_STATE_END)
		process_tool_state_end(g);
	ui_sdl_set_render_target(g->main_win->sdl_renderer, NULL);
}
