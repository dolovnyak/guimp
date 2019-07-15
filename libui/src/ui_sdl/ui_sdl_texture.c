/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_sdl_texture.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbecker <sbecker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/10 16:12:48 by sbednar           #+#    #+#             */
/*   Updated: 2019/07/13 14:01:06 by sbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libui.h"

void		ui_sdl_destroy_texture(SDL_Texture *t)
{
	SDL_DestroyTexture(t);
}

SDL_Texture	*ui_sdl_create_texture_from_surface(SDL_Renderer *r, SDL_Surface *s)
{
	return (SDL_CreateTextureFromSurface(r, s));
}