/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_with_selected_tool.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbecker <sbecker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/26 00:41:52 by sbecker           #+#    #+#             */
/*   Updated: 2019/07/13 10:17:41 by sbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "guimp.h"

int	draw_with_selected_tool(t_ui_main *main, void *el_v)
{
	t_guimp	*g;
	t_ui_el	*el;
	int		x;
	int		y;

	g = (t_guimp *)(main->data);
	el = (t_ui_el *)el_v;
	x = ((float)el->ptr_rel_pos.x / (float)el->rect.w) *
			g->zoom_rect.w + g->zoom_rect.x;
	y = ((float)el->ptr_rel_pos.y / (float)el->rect.h) *
			g->zoom_rect.h + g->zoom_rect.y;
	g->draw_tool.cur_point = (t_vec2){x, y};
	if (g->draw_tool.tool == GM_TOOL_BRUSH)
		tool_brush(el, g, x, y);
	else if (g->draw_tool.tool == GM_TOOL_HAND)
		tool_hand(g);
	else if (g->draw_tool.tool == GM_TOOL_PIPETTE)
		tool_pipette(g, el);
	else if (g->draw_tool.tool == GM_TOOL_ERASER)
		tool_eraser(el, g, x, y);
	return (1);
}
