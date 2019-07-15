/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_sdl_set_render.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbecker <sbecker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/10 16:12:48 by sbednar           #+#    #+#             */
/*   Updated: 2019/07/13 14:01:06 by sbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libui.h"

void	ui_sdl_set_render_target(SDL_Renderer *r, SDL_Texture *t)
{
	SDL_SetRenderTarget(r, t);
}

void	ui_sdl_set_render_draw_color(SDL_Renderer *r, SDL_Color *c)
{
	SDL_SetRenderDrawColor(r, c->r, c->g, c->b, c->a);
}

void	ui_sdl_set_render_draw_blend_mode(SDL_Renderer *r, SDL_BlendMode b)
{
	SDL_SetRenderDrawBlendMode(r, b);
}