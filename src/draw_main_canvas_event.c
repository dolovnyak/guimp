/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_main_canvas_event.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edraugr- <edraugr-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 04:59:41 by edraugr-          #+#    #+#             */
/*   Updated: 2019/06/04 20:43:06 by edraugr-         ###   ########.fr       */
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
		SDL_RenderCopy(el->sdl_renderer, ui_el_get_current_texture(el), NULL, &el->rect);
		SDL_RenderCopy(el->sdl_renderer, ui_el_get_texture_by_id(el, "draw_texture"), NULL, &el->rect);
	}
}
