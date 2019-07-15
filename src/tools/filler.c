/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbecker <sbecker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/10 15:29:55 by sbednar           #+#    #+#             */
/*   Updated: 2019/07/15 16:45:46 by sbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "guimp.h"

static t_sur	*get_surface_and_fill(t_ui_win *w, t_texture *t, int **q,
		int **f)
{
	t_texture	*tt;
	t_sur		*r;
	int			s;

	s = w->size.x * w->size.y;
	*f = (char *)ft_memalloc(s);
	*q = (int *)ft_memalloc(s * sizeof(int));
	ui_sdl_set_render_draw_color(w->sdl_renderer, &(t_color){255, 255, 255, 0});
	ui_sdl_render_clear(w->sdl_renderer);
	tt = ui_sdl_create_texture(w->sdl_renderer, RGBA8888, STATIC, &w->size);
	ui_sdl_set_render_target(w->sdl_renderer, tt);
	ui_sdl_render_copy(w->sdl_renderer, t, NULL, NULL);
	r = ui_sdl_create_rgb_surface(&w->size);
	ui_sdl_renderer_read_pixels(w->sdl_renderer, r->format->format,
			r->pixels, r->pitch);
	ui_sdl_destroy_texture(tt);
	return (r);
}

static void		process2(t_filler *fl, t_vec2 *ci, t_vec2 *qi)
{
	if (ci->y - 1 >= 0 && !fl->f[(ci->y - 1) * fl->w->size.x + ci->x] &&
		ui_surface_get_pixel(fl->s, ci->x, ci->y - 1) == fl->c->color2)
	{
		fl->q[qi->y++] = ci->x * 10000 + ci->y - 1;
		fl->f[(ci->y - 1) * fl->w->size.x + ci->x] = '1';
	}
	if (ci->y + 1 < fl->w->size.y && !fl->f[(ci->y + 1) * fl->w->size.x + ci->x]
	&& ui_surface_get_pixel(fl->s, ci->x, ci->y + 1) == fl->c->color2)
	{
		fl->q[qi->y++] = ci->x * 10000 + ci->y + 1;
		fl->f[(ci->y + 1) * fl->w->size.x + ci->x] = '1';
	}
}

static void		process1(t_filler *fl, t_vec2 *ci, t_vec2 *qi)
{
	if (fl->f[ci->y * fl->w->size.x + ci->x] <= '2' &&
	ui_surface_get_pixel(fl->s, ci->x, ci->y) == fl->c->color2)
	{
		ui_surface_set_pixel(fl->s, ci->x, ci->y, fl->c->color1);
		fl->f[ci->y * fl->w->size.x + ci->x] = '2';
	}
	if (ci->x + 1 < fl->w->size.x && !fl->f[ci->y * fl->w->size.x + ci->x + 1]
	&& ui_surface_get_pixel(fl->s, ci->x + 1, ci->y) == fl->c->color2)
	{
		fl->q[qi->y++] = (ci->x + 1) * 10000 + ci->y;
		fl->f[ci->y * fl->w->size.x + ci->x + 1] = '1';
	}
	if (ci->x - 1 >= 0 && !fl->f[ci->y * fl->w->size.x + ci->x - 1] &&
		ui_surface_get_pixel(fl->s, ci->x - 1, ci->y) == fl->c->color2)
	{
		fl->q[qi->y++] = (ci->x - 1) * 10000 + ci->y;
		fl->f[ci->y * fl->w->size.x + ci->x - 1] = '1';
	}
}

void			tool_filler(t_ui_win *w, t_texture *texture, t_cvec2 color,
		t_vec2 coord)
{
	t_sur		*s;
	char		*f;
	int			*q;
	t_vec2		qi;
	t_texture	*tmp;

	s = get_surface_and_fill(w, texture, &q, &f);
	qi = (t_vec2){0, 1};
	q[0] = coord.x * 10000 + coord.y;
	while (qi.x < qi.y)
	{
		process1(&(t_filler){w, s, q, f, &color}, &(t_vec2){q[qi.x] / 10000,
			q[qi.x] % 10000}, &qi);
		process2(&(t_filler){w, s, q, f, &color}, &(t_vec2){q[qi.x] / 10000,
			q[qi.x++] % 10000}, &qi);
	}
	tmp = ui_sdl_create_texture_from_surface(w->sdl_renderer, s);
	ui_sdl_set_render_target(w->sdl_renderer, texture);
	ui_sdl_render_copy(w->sdl_renderer, tmp, NULL, NULL);
	ui_sdl_set_render_target(w->sdl_renderer, NULL);
	ui_sdl_destroy_texture(tmp);
	free(f);
	free(q);
	ui_sdl_free_surface(s);
}

int				choose_fill(t_ui_main *main, void *el_v)
{
	t_guimp	*g;

	g = (t_guimp *)(main->data);
	(void)el_v;
	g->draw_tool.tool = GM_TOOL_FILL;
	return (1);
}
