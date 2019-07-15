/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_sdl_render_draw.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbecker <sbecker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/10 16:12:48 by sbednar           #+#    #+#             */
/*   Updated: 2019/07/13 14:01:06 by sbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libui.h"

void	ui_sdl_render_draw_line(SDL_Renderer *r, t_vec2 *v1, t_vec2 *v2)
{
	SDL_RenderDrawLine(r, v1->x, v1->y, v2->x, v2->y);
}

void	ui_sdl_render_fill_rect(SDL_Renderer *r, SDL_Rect *rect)
{
	SDL_RenderFillRect(r, rect);
}