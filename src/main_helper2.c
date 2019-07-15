/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_helper2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edraugr- <edraugr-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/15 17:53:45 by edraugr-          #+#    #+#             */
/*   Updated: 2019/07/15 18:18:18 by edraugr-         ###   ########.fr       */
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
