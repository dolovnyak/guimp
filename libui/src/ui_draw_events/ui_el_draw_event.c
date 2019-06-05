/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_el_draw_event.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbednar <sbednar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 18:23:17 by sbednar           #+#    #+#             */
/*   Updated: 2019/06/05 04:41:22 by sbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libui.h"

static void	get_texture_params(SDL_Texture *texture, t_rect *srect,
		int *width, int *height)
{
	SDL_QueryTexture(texture, NULL, NULL, width, height);
	srect->x = 0;
	srect->y = 0;
	srect->w = *width;
	srect->h = *height;
}

static void	get_texture_x_and_width(t_ui_el *el, t_rect *srect, t_rect *tmp_rect, int width)
{
	if (el->rect.x < el->parent->cut_rect.x &&
			el->rect.x + el->rect.w > el->parent->cut_rect.x + el->parent->cut_rect.w)
	{
		srect->x = roundf((float)(el->parent->cut_rect.x - el->rect.x) * ((float)width / (float)el->rect.w));
		srect->w = roundf((float)el->parent->cut_rect.w * ((float)width / (float)el->rect.w));
		tmp_rect->x = el->parent->cut_rect.x;
		tmp_rect->w = el->parent->cut_rect.w;
	}
	else if (el->rect.x < el->parent->cut_rect.x)
	{
		tmp_rect->x = el->parent->cut_rect.x;
		tmp_rect->w = el->rect.w - (el->parent->cut_rect.x - el->rect.x);
		srect->x = roundf((float)(el->parent->cut_rect.x - el->rect.x) * ((float)width / (float)el->rect.w));
		srect->w = roundf((float)tmp_rect->w * ((float)width / (float)el->rect.w));
	}
	else if (el->rect.x + el->rect.w > el->parent->cut_rect.x + el->parent->cut_rect.w)
	{
		srect->x = 0;
		tmp_rect->w = el->parent->cut_rect.x + el->parent->cut_rect.w - el->rect.x;
		srect->w = roundf((float)tmp_rect->w * ((float)width / (float)el->rect.w));
		tmp_rect->x = el->rect.x;
	}
}

static void	get_texture_y_and_height(t_ui_el *el, t_rect *srect, t_rect *tmp_rect, int height)
{
	if (el->rect.y < el->parent->cut_rect.y &&
			el->rect.y + el->rect.h > el->parent->cut_rect.y + el->parent->cut_rect.h)
	{
		srect->y = roundf((float)(el->parent->cut_rect.y - el->rect.y) * ((float)height / (float)el->rect.h));
		srect->h = roundf((float)el->parent->cut_rect.h * ((float)height / (float)el->rect.h));
		tmp_rect->y = el->parent->cut_rect.y;
		tmp_rect->h = el->parent->cut_rect.h;
	}
	else if (el->rect.y < el->parent->cut_rect.y)
	{
		tmp_rect->y = el->parent->cut_rect.y;
		tmp_rect->h = el->rect.h - (el->parent->cut_rect.y - el->rect.y);
		srect->y = roundf((float)(el->parent->cut_rect.y - el->rect.y) * ((float)height / (float)el->rect.h));
		srect->h = roundf((float)tmp_rect->h * ((float)height / (float)el->rect.h));
	}
	else if (el->rect.y + el->rect.h > el->parent->cut_rect.y + el->parent->cut_rect.h)
	{
		srect->y = 0;
		tmp_rect->h = el->parent->cut_rect.y + el->parent->cut_rect.h - el->rect.y;
		srect->h = roundf((float)tmp_rect->h * ((float)height / (float)el->rect.h));
		tmp_rect->y = el->rect.y;
	}
}

static void	cutting_texture_and_draw(t_ui_el *el, SDL_Texture *texture)
{
	t_rect		tmp_rect;
	t_rect		srect;
	int			width;
	int			height;

	tmp_rect = el->rect;
	get_texture_params(texture, &srect, &width, &height);
	get_texture_x_and_width(el, &srect, &tmp_rect, width);
	get_texture_y_and_height(el, &srect, &tmp_rect, height);
	el->cut_rect = tmp_rect;
	SDL_RenderCopy(el->sdl_renderer, texture, &srect, &tmp_rect);
}

void	ui_el_draw_event(void *el_v, void *arg)
{
	t_ui_el		*el;
	SDL_Texture	*texture;

	arg = NULL;
	el = (t_ui_el *)el_v;
	texture = ui_el_get_current_texture(el);
	if (el->params & EL_IS_DEPENDENT)
	{
		cutting_texture_and_draw(el, texture);
		return ;
	}
	SDL_RenderCopy(el->sdl_renderer, texture, NULL, &el->rect);
}
