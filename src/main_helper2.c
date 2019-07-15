/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_helper2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edraugr- <edraugr-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/15 17:53:45 by edraugr-          #+#    #+#             */
/*   Updated: 2019/07/15 18:13:47 by edraugr-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "guimp.h"

int	scan_tool_position(t_ui_main *main, void *el_v)
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
	g->draw_tool.cur_point = (t_vec2){x, y};
	return (1);
}

int	start_draw_with_selected_tool_pointer_up(t_ui_main *main,
				void *el_v)
{
	t_guimp	*g;

	g = (t_guimp *)(main->data);
	(void)el_v;
	if (g->draw_tool.tool >= GM_TOOL_LINE)
		if (g->draw_tool.state == GM_TOOL_STATE_START)
			g->draw_tool.state = GM_TOOL_STATE_DRAW;
	return (1);
}

int	start_alt_with_selected_tool(t_ui_main *main, void *el_v)
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
	g->draw_tool.prew_point = (t_vec2){x, y};
	if (g->draw_tool.tool == GM_TOOL_ZOOM && g->draw_tool.zoom > 1)
		tool_zoom_out(g, x, y);
	return (1);
}

int	move_draw_canvas_with_zoom(t_ui_main *main, void *el_v)
{
	t_guimp	*g;
	t_ui_el	*el;
	float	x;
	float	y;

	g = (t_guimp *)(main->data);
	el = (t_ui_el *)el_v;
	x = 0;
	y = 0;
	if (g->draw_tool.tool == GM_TOOL_ZOOM)
	{
		if (el->ptr_rel_pos.x > el->rect.w * (1.0 - GM_ZOOM_MOVE_ZONE))
			x = ((float)el->ptr_rel_pos.x / (float)el->rect.w - (1.0 -
				GM_ZOOM_MOVE_ZONE)) / (GM_ZOOM_MOVE_ZONE);
		if (el->ptr_rel_pos.x < el->rect.w * GM_ZOOM_MOVE_ZONE)
			x = -(GM_ZOOM_MOVE_ZONE - (float)el->ptr_rel_pos.x /
				(float)el->rect.w) / GM_ZOOM_MOVE_ZONE;
		if (el->ptr_rel_pos.y > el->rect.h * (1.0 - GM_ZOOM_MOVE_ZONE))
			y = ((float)el->ptr_rel_pos.y / (float)el->rect.h -
				(1.0 - GM_ZOOM_MOVE_ZONE)) / (GM_ZOOM_MOVE_ZONE);
		if (el->ptr_rel_pos.y < el->rect.h * GM_ZOOM_MOVE_ZONE)
			y = -(GM_ZOOM_MOVE_ZONE - (float)el->ptr_rel_pos.y /
				(float)el->rect.h) / GM_ZOOM_MOVE_ZONE;
		g->zoom_rect.x += x * (GM_ZOOM_MOVE_SPEED / g->draw_tool.zoom);
		g->zoom_rect.y += y * (GM_ZOOM_MOVE_SPEED / g->draw_tool.zoom);
		g->zoom_rect.x = g->zoom_rect.x < 0 ? 0 : g->zoom_rect.x;
		g->zoom_rect.x = g->zoom_rect.x + g->zoom_rect.w > GM_IMAGE_SIZE_X ?
			GM_IMAGE_SIZE_X - g->zoom_rect.w : g->zoom_rect.x;
		g->zoom_rect.y = g->zoom_rect.y < 0 ? 0 : g->zoom_rect.y;
		g->zoom_rect.y = g->zoom_rect.y + g->zoom_rect.h > GM_IMAGE_SIZE_Y ?
			GM_IMAGE_SIZE_Y - g->zoom_rect.h : g->zoom_rect.y;
	}
	return (1);
}

int	draw_color_rect(t_ui_main *main, void *el_v)
{
	t_guimp	*g;
	t_ui_el	*el;

	g = (t_guimp *)(main->data);
	el = (t_ui_el *)el_v;
	ui_sdl_set_render_target(el->sdl_renderer, ui_el_get_current_texture(el));
	ui_sdl_set_render_draw_color(el->sdl_renderer, &(t_color){g->draw_tool.r,
		g->draw_tool.g, g->draw_tool.b, 255});
	ui_sdl_render_fill_rect(el->sdl_renderer, NULL);
	ui_sdl_set_render_target(el->sdl_renderer, NULL);
	ui_sdl_render_copy(el->sdl_renderer, ui_el_get_current_texture(el), NULL,
		&el->rect);
	return (1);
}

void	ft_strjoin_free(char **to, char *what)
{
	char	*tmp;

	tmp = *to;
	*to = ft_strjoin(*to, what);
	free(tmp);
	free(what);
}

int	text_test(t_ui_main *m, void *a)
{
	t_ui_el	*el;
	t_ui_el	*dr;
	char	*res;

	(void)m;
	el = (t_ui_el *)a;
	dr = (t_ui_el *)el->data;
	if (dr->params & EL_IS_PTR_INSIDE)
	{
		res = ft_strdup("(");
		ft_strjoin_free(&res, ft_itoa(dr->ptr_rel_pos.x));
		ft_strjoin_free(&res, ft_strdup(";"));
		ft_strjoin_free(&res, ft_itoa(dr->ptr_rel_pos.y));
		ft_strjoin_free(&res, ft_strdup(")"));
		ui_el_update_text(el, res);
		free(res);
	}
	else
		ui_el_update_text(el, " ");
	return (1);
}
