/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   square.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbecker <sbecker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/10 15:53:21 by sbednar           #+#    #+#             */
/*   Updated: 2019/07/13 10:09:13 by sbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "guimp.h"

int	choose_square(t_ui_main *main, void *el_v)
{
	t_guimp	*g;

	g = (t_guimp *)(main->data);
	(void)el_v;
	g->draw_tool.tool = GM_TOOL_SQUARE;
	g->draw_tool.state = GM_TOOL_STATE_NONE;
	return (1);
}

void	draw_square(t_guimp *g, t_vec2 s, t_vec2 e)
{
	int sx;
	int sy;
	int	d;

	sx = (e.x - s.x > 0 ? 1 : -1);
	sy = (e.y - s.y > 0 ? 1 : -1);
	d = ft_max(abs(s.x - e.x), abs(s.y - e.y));
	draw_rect(g, s, (t_vec2){s.x + d * sx, s.y + d * sy});
}

void	draw_empty_square(t_guimp *g, t_vec2 s, t_vec2 e)
{
	int sx;
	int sy;
	int	d;

	sx = (e.x - s.x > 0 ? 1 : -1);
	sy = (e.y - s.y > 0 ? 1 : -1);
	d = ft_max(abs(s.x - e.x), abs(s.y - e.y));
	draw_empty_rect(g, s, (t_vec2){s.x + d * sx, s.y + d * sy});
}