/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_sdl_surface.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbecker <sbecker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/10 16:12:48 by sbednar           #+#    #+#             */
/*   Updated: 2019/07/13 14:01:06 by sbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libui.h"

void		ui_sdl_free_surface(SDL_Surface *s)
{
	SDL_FreeSurface(s);
}

SDL_Surface	*ui_sdl_create_rgb_surface(t_vec2 *s)
{
	return (SDL_CreateRGBSurface(0, s->x, s->y, 32, 0, 0, 0, 1));
}