/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ellipse.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbecker <sbecker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/10 15:53:23 by sbednar           #+#    #+#             */
/*   Updated: 2019/07/15 16:33:13 by sbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "guimp.h"

int				choose_ellipse(t_ui_main *main, void *el_v)
{
	t_guimp	*g;

	g = (t_guimp *)(main->data);
	(void)el_v;
	g->draw_tool.tool = GM_TOOL_ELLIPSE;
	g->draw_tool.state = GM_TOOL_STATE_NONE;
	return (1);
}

static int		util_for_draw(t_vec2 *s, t_vec2 *e, t_vec2 (*d)[6])
{
	float	k;

	k = 0;
	if ((*s).y > (*e).y)
	{
		(*d)[0] = *s;
		*s = *e;
		*e = (*d)[0];
	}
	(*d)[0] = (t_vec2){(*s).x, (*s).y + ((*e).y - (*s).y) / 2};
	(*d)[1] = *s;
	(*d)[2] = (t_vec2){(*e).x, (*s).y};
	(*d)[3] = (t_vec2){(*e).x, (*d)[0].y};
	if ((*s).x == (*e).x || (*s).y == (*e).y)
		return (0);
	(*d)[4] = calc_el_dot(*d, k);
	return (1);
}

static void		draw_line_for_ellipse(t_guimp *g, t_vec2 d[6],
		t_vec2 s, t_vec2 e)
{
	ui_sdl_render_draw_line(g->main_win->sdl_renderer,
			&(t_vec2){d[4].x, d[4].y}, &(t_vec2){s.x + e.x - d[4].x, d[4].y});
	ui_sdl_render_draw_line(g->main_win->sdl_renderer,
			&(t_vec2){d[4].x, s.y + e.y - d[4].y},
			&(t_vec2){s.x + e.x - d[4].x, s.y + e.y - d[4].y});
}

void			draw_ellipse(t_guimp *g, t_vec2 s, t_vec2 e)
{
	t_vec2	d[6];
	float	k;
	float	step;

	if (!(util_for_draw(&s, &e, &d)))
		return ;
	step = 1.0 / (float)((float)(e.y - s.y) / 2.0);
	k = 0;
	while (k <= 1)
	{
		d[5] = calc_el_dot(d, k + step);
		if (d[4].y == d[5].y)
			draw_line_for_ellipse(g, d, s, e);
		else
			while (d[4].y != d[5].y)
			{
				draw_line_for_ellipse(g, d, s, e);
				d[4].y = d[4].y > d[5].y ? d[4].y - 1 : d[4].y + 1;
			}
		k += step;
		d[4] = d[5];
	}
}

void			draw_empty_ellipse(t_guimp *g, t_vec2 s, t_vec2 e)
{
	t_vec2	d;

	if (s.y > e.y)
	{
		d = s;
		s = e;
		e = d;
	}
	if (s.x > e.x)
	{
		d.x = s.x;
		s.x = e.x;
		e.x = d.x;
	}
	draw_ellipse(g, s, e);
	if (g->draw_tool.brush_size >= (Uint32)abs(e.x - s.x) / 2 ||
			g->draw_tool.brush_size >= (Uint32)abs(e.y - s.y) / 2)
		return ;
	s = (t_vec2){s.x + g->draw_tool.brush_size, s.y + g->draw_tool.brush_size};
	e = (t_vec2){e.x - g->draw_tool.brush_size, e.y - g->draw_tool.brush_size};
	ui_sdl_set_render_draw_color(g->main_win->sdl_renderer,
			&(t_color){0, 0, 0, 0});
	ui_sdl_set_render_draw_blend_mode(g->main_win->sdl_renderer, NONE);
	draw_ellipse(g, s, e);
}
