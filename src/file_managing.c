/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_managing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edraugr- <edraugr-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/23 05:38:20 by sbednar           #+#    #+#             */
/*   Updated: 2019/07/15 03:41:23 by edraugr-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "guimp.h"

static int	get_image_type(const char *p)
{
	size_t	l;

	l = ft_strlen(p);
	if (l < 4)
		return (-1);
	if ((l > 4 && !ft_strcmp(&p[l - 5], ".jpeg")) ||
		!ft_strcmp(&p[l - 4], ".jpg"))
		return (IMG_TYPE_JPG);
	if (!ft_strcmp(&p[l - 4], ".png"))
		return (IMG_TYPE_PNG);
	return (-1);
}

int	ui_save_image(t_ui_main *main, void *el_v)
{
	char 		*p;
	t_guimp		*g;
	t_texture	*t;
	t_ui_el		*el;

	g = (t_guimp *)(main->data);
	el = (t_ui_el *)el_v;
	t = ui_main_merge_layers(g->main_win->sdl_renderer, g->layers.layers);
	p = ((t_ui_el *)el->data)->text_area->text;
	ui_main_save_texture(g->main_win, t, p, get_image_type(p));
	return (1);
}

int	ui_open_image(t_ui_main *main, void *el_v)
{
	t_guimp		*g;
	t_ui_el		*el;

	g = (t_guimp *)(((t_ui_main *)main)->data);
	el = (t_ui_el *)el_v;
	ui_main_open_texture(g->main_win->sdl_renderer, g->layers.current_layer,
			((t_ui_el *)el->data)->text_area->text);
	return (1);
}
