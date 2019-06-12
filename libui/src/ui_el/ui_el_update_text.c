/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_el_update_text.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbednar <sbednar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/23 05:38:20 by sbednar           #+#    #+#             */
/*   Updated: 2019/06/12 05:17:45 by sbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libui.h"

static int	get_surface_from_text(t_ui_el *el)
{
	if (el->text.params & TEXT_IS_SOLID)
	{
		if (!(el->sdl_surface = TTF_RenderText_Solid(el->text.font, el->text.text, el->text.text_color)))
			return (FUNCTION_FAILURE);
	}
	else if ((el->text.params & TEXT_IS_BLENDED) || el->text.params == 0)
	{
		if (!(el->sdl_surface = TTF_RenderText_Blended(el->text.font, el->text.text, el->text.text_color)))
			return (FUNCTION_FAILURE);
	}
	else
	{
		if (!(el->sdl_surface = TTF_RenderText_Shaded(el->text.font, el->text.text, el->text.text_color,
						el->text.bg_color)))
			return (FUNCTION_FAILURE);
	}
	return (FUNCTION_SUCCESS);
}

int	ui_el_update_text(t_ui_el *el, const char *text)
{
	t_list		*n;
	size_t		len;

	len = ft_strlen(text);
	if (el->text.text != NULL)
		free(el->text.text);
	if (el->text.max_text_size == 0 || len <= el->text.max_text_size)
		el->text.text = ft_strdup(text);
	else
	{
		if (el->text.text != NULL)
			return (FUNCTION_SUCCESS);
		else
			el->text.text = ft_strsub(text, 0, el->text.max_text_size);
	}
	if (get_surface_from_text(el) == FUNCTION_FAILURE || !(n = ft_lstnew(NULL, 0)))
		return (FUNCTION_FAILURE);
	n->content = ui_el_create_texture(el);
	n->content_size = ft_strhash("default");
	if (el->sdl_textures)
	{
		SDL_DestroyTexture((SDL_Texture *)el->sdl_textures->content);
		free(el->sdl_textures);
	}
	ft_lstadd(&(el->sdl_textures), n);
	return (FUNCTION_SUCCESS);
}
