/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_main_canvas_event.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edraugr- <edraugr-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 04:59:41 by edraugr-          #+#    #+#             */
/*   Updated: 2019/07/15 04:41:49 by edraugr-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "guimp.h"

void	draw_main_canvas_event(void *el_v, void *arg)
{
	t_ui_el	*el;

	el = (t_ui_el *)el_v;
	arg = NULL;
	if (arg == NULL)
	{
		ui_sdl_render_copy(el->sdl_renderer, ui_el_get_current_texture(el),
				NULL, &el->rect);
		ui_sdl_render_copy(el->sdl_renderer,
				ui_el_get_texture_by_id(el, "draw_texture"), NULL, &el->rect);
	}
}
