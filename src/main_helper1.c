/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_helper1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edraugr- <edraugr-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/15 17:53:20 by edraugr-          #+#    #+#             */
/*   Updated: 2019/07/15 18:04:31 by edraugr-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "guimp.h"

int			move_windows(t_ui_main *m, void *a)
{
	t_ui_win	*w;
	t_list		*list;
	t_ui_win	*cur_w;
	t_vec2		pos;

	w = (t_ui_win *)a;
	list = m->windows;
	if (w != NULL)
		while (list)
		{
			cur_w = (t_ui_win *)list->content;
			if (!(cur_w->id >= 2 || cur_w->id == w->id))
			{
				ui_sdl_get_window_position(w->sdl_window, &pos.x, &pos.y);
				if (cur_w->id == 0)
					pos.x = pos.x + GM_TOOL_WIN_W + 5;
				else if (cur_w->id == 1)
					pos.x = pos.x - GM_TOOL_WIN_W - 5;
				ui_sdl_set_window_position(cur_w->sdl_window, pos.x, pos.y);
				cur_w->pos = pos;
			}
			list = list->next;
		}
	return (1);
}

int			draw_canvas_renderer(t_ui_main *main, void *el_v)
{
	t_guimp	*g;
	t_ui_el	*el;
	t_list	*layer;
	int		tmp_flag;

	g = (t_guimp *)(main->data);
	el = (t_ui_el *)el_v;
	layer = g->layers.layers;
	tmp_flag = 1;
	process_tmp_layer(g);
	while (layer)
	{
		ui_sdl_render_copy(el->sdl_renderer, (t_texture *)(layer->content),
			&g->zoom_rect, &el->rect);
		if (tmp_flag && layer->content_size ==
			g->layers.current_layer->parent->id)
		{
			tmp_flag = 0;
			ui_sdl_render_copy(el->sdl_renderer, g->layers.tmp_texture,
				&g->zoom_rect, &el->rect);
		}
		layer = layer->next;
	}
	return (1);
}

static int	prepare_fill(int x, int y, t_guimp *g, t_ui_el *el)
{
	Uint32	c[2];

	if (g->draw_tool.tool == GM_TOOL_FILL)
	{
		c[0] = (g->draw_tool.r << 16) + (g->draw_tool.g << 8) + g->draw_tool.b;
		c[1] = ui_util_get_pixel_color_from_texture(el->sdl_renderer,
			(t_texture *)g->layers.current_layer->sdl_textures->content,
			(t_vec2){x, y});
		if (c[0] != c[1])
			tool_filler(g->main_win,
				(t_texture *)g->layers.current_layer->sdl_textures->content,
				(t_cvec2){c[0], c[1]},
				(t_vec2){(int)(x * 1.0f / GM_IMAGE_SIZE_X *
				g->main_win->size.x), (int)(y * 1.0f / GM_IMAGE_SIZE_Y *
				g->main_win->size.y)});
	}
	return (1);
}

int			start_draw_with_selected_tool(t_ui_main *main, void *el_v)
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
	if ((g->draw_tool.tool < (GM_TOOL_LINE)) || (g->draw_tool.state ==
		GM_TOOL_STATE_NONE && g->draw_tool.tool >= (GM_TOOL_LINE)))
		g->draw_tool.prew_point = (t_vec2){x, y};
	if (g->draw_tool.tool == GM_TOOL_ZOOM && g->draw_tool.zoom <
		GM_ZOOM_MAX_SIZE)
		tool_zoom_in(g, x, y);
	if (g->draw_tool.tool >= (GM_TOOL_LINE))
	{
		if (g->draw_tool.state == GM_TOOL_STATE_DRAW)
			g->draw_tool.state = GM_TOOL_STATE_END;
		else if (g->draw_tool.state == GM_TOOL_STATE_NONE)
			g->draw_tool.state = GM_TOOL_STATE_START;
	}
	return (prepare_fill(x, y, g, el));
}

void		update_color_rect(t_guimp *gm, int r, int g, int b)
{
	t_ui_el		*el;
	t_texture	*t;

	el = ui_win_find_el_by_id(gm->tool_win, GM_TOOL_ID_COLOR_RECT);
	t = (t_texture *)el->sdl_textures->content;
	ui_sdl_destroy_texture(t);
	free(el->sdl_textures);
	el->sdl_textures = NULL;
	ui_el_add_color_texture(el, (t_vec2){100, 20}, (r << 16) | (g << 8) | b,
		"default");
}
