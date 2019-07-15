/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zoom.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbecker <sbecker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/10 15:40:37 by sbednar           #+#    #+#             */
/*   Updated: 2019/07/15 15:39:15 by sbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "guimp.h"

int		choose_zoom(t_ui_main *main, void *el_v)
{
	t_guimp	*g;

	g = (t_guimp *)(main->data);
	(void)el_v;
	g->draw_tool.tool = GM_TOOL_ZOOM;
	return (1);
}

void	tool_zoom_in(t_guimp *g, int x, int y)
{
	g->draw_tool.zoom++;
	g->zoom_rect.w = GM_IMAGE_SIZE_X / g->draw_tool.zoom;
	g->zoom_rect.h = GM_IMAGE_SIZE_Y / g->draw_tool.zoom;
	x = x - g->zoom_rect.w / 2;
	y = y - g->zoom_rect.h / 2;
	x = (x + g->zoom_rect.w > GM_IMAGE_SIZE_X) ?
		GM_IMAGE_SIZE_X - g->zoom_rect.w : x;
	y = (y + g->zoom_rect.h > GM_IMAGE_SIZE_Y) ?
		GM_IMAGE_SIZE_Y - g->zoom_rect.h : y;
	g->zoom_rect.x = x < 0 ? 0 : x;
	g->zoom_rect.y = y < 0 ? 0 : y;
}

void	tool_zoom_out(t_guimp *g, int x, int y)
{
	g->draw_tool.zoom--;
	g->zoom_rect.w = GM_IMAGE_SIZE_X / g->draw_tool.zoom;
	g->zoom_rect.h = GM_IMAGE_SIZE_Y / g->draw_tool.zoom;
	x = x - g->zoom_rect.w / 2;
	y = y - g->zoom_rect.h / 2;
	x = (x + g->zoom_rect.w > GM_IMAGE_SIZE_X) ?
		GM_IMAGE_SIZE_X - g->zoom_rect.w : x;
	y = (y + g->zoom_rect.h > GM_IMAGE_SIZE_Y) ?
		GM_IMAGE_SIZE_Y - g->zoom_rect.h : y;
	g->zoom_rect.x = x < 0 || g->draw_tool.zoom == 1 ? 0 : x;
	g->zoom_rect.y = y < 0 || g->draw_tool.zoom == 1 ? 0 : y;
}
