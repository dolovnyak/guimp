/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbecker <sbecker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/10 15:29:55 by sbednar           #+#    #+#             */
/*   Updated: 2019/07/13 10:14:01 by sbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "guimp.h"

static Uint32	getpixel(t_sur *surface, int x, int y)
{
	int		bpp;
	Uint8	*p;

	bpp = surface->format->BytesPerPixel;
	p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;
	return (*(Uint32 *)p);
}

static void		putpixel(t_sur *surface, int x, int y, Uint32 pixel)
{
	int bpp;
	Uint8 *p;

	bpp = surface->format->BytesPerPixel;
	p = (Uint8 *) surface->pixels + y * surface->pitch + x * bpp;
	*(Uint32 *) p = pixel;
}

void			tool_filler(t_ui_win *w, t_texture *texture, t_cvec2 color, t_vec2 coord)
{
	char 	*field;
	int f = 0;
	int l = 0;
	int *queue;
	int x, y;

	x = w->size.x * w->size.y;
	field = (char *)malloc(x);
	for (int i = 0; i < x; i++)
		field[i] = 0;
	queue = (int *)malloc(x * sizeof(int));
	ui_sdl_set_render_draw_color(w->sdl_renderer, &(t_color){255, 255, 255, 0});
	ui_sdl_render_clear(w->sdl_renderer);
	t_texture *t = ui_sdl_create_texture(w->sdl_renderer, RGBA8888, STATIC, &w->size);
	ui_sdl_set_render_target(w->sdl_renderer, t);
	ui_sdl_render_copy(w->sdl_renderer, texture, NULL, NULL);
	t_sur *s = ui_sdl_create_rgb_surface(&w->size);
	ui_sdl_renderer_read_pixels(w->sdl_renderer, s->format->format, s->pixels, s->pitch);
	for (int i = 0; i < x; i++)
		queue[i] = 0;
	queue[l++] = coord.x * 10000 + coord.y;
	while (f < l)
	{
		x = queue[f] / 10000;
		y = queue[f++] % 10000;
		if (field[y * w->size.x + x] <= '2' && getpixel(s, x, y) == color.color2)
		{
			putpixel(s, x, y, color.color1);
			field[y * w->size.x + x] = '2';
		}
		if (x + 1 < w->size.x && !field[y * w->size.x + x + 1] && getpixel(s, x + 1, y) == color.color2)
		{
			queue[l++] = (x + 1) * 10000 + y;
			field[y * w->size.x + x + 1] = '1';
		}
		if (x - 1 >= 0 && !field[y * w->size.x + x - 1] && getpixel(s, x - 1, y) == color.color2)
		{
			queue[l++] = (x - 1) * 10000 + y;
			field[y * w->size.x + x - 1] = '1';
		}
		if (y - 1 >= 0 && !field[(y - 1) * w->size.x + x] && getpixel(s, x, y - 1) == color.color2)
		{
			queue[l++] = x * 10000 + y - 1;
			field[(y - 1) * w->size.x + x] = '1';
		}
		if (y + 1 < w->size.y && !field[(y + 1) * w->size.x + x] && getpixel(s, x, y + 1) == color.color2)
		{
			queue[l++] = x * 10000 + y + 1;
			field[(y + 1) * w->size.x + x] = '1';
		}
	}
	t_texture *tmp = ui_sdl_create_texture_from_surface(w->sdl_renderer, s);
	ui_sdl_set_render_target(w->sdl_renderer, texture);
	ui_sdl_render_copy(w->sdl_renderer, tmp, NULL, NULL);
	ui_sdl_set_render_target(w->sdl_renderer, NULL);
	free(field);
	free(queue);
	ui_sdl_destroy_texture(tmp);
	ui_sdl_destroy_texture(t);
	ui_sdl_free_surface(s);
}

int		choose_fill(t_ui_main *main, void *el_v)
{
	t_guimp	*g;

	g = (t_guimp *)(main->data);
	(void)el_v;
	g->draw_tool.tool = GM_TOOL_FILL;
	return (1);
}
