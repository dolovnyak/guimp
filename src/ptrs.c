/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ptrs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbecker <sbecker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/15 17:04:03 by sbecker           #+#    #+#             */
/*   Updated: 2019/07/15 18:05:31 by sbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "guimp.h"

int	on_ptr_enter(t_ui_main *main, void *el_v)
{
	t_ui_el	*el;

	(void)main;
	el = (t_ui_el *)el_v;
	if (el->current_texture != (size_t)ft_strhash("onActive"))
		ui_el_set_current_texture_by_id(el, "onFocus");
	return (1);
}

int	on_ptr_exit(t_ui_main *main, void *el_v)
{
	t_ui_el	*el;

	(void)main;
	el = (t_ui_el *)el_v;
	if (el->current_texture != (size_t)ft_strhash("onActive"))
		ui_el_set_current_texture_by_id(el, "default");
	return (1);
}

int	pressed_lbd(t_ui_main *main, void *el_v)
{
	t_ui_el	*el;

	(void)main;
	el = (t_ui_el *)el_v;
	if (el->current_texture != (size_t)ft_strhash("onActive"))
		ui_el_set_current_texture_by_id(el, "onPressedLBM");
	return (1);
}

int	on_ptr_lbd(t_ui_main *main, void *el_v)
{
	t_list	*layer_elems;
	t_guimp	*g;
	t_ui_el	*el;

	g = (t_guimp *)(main->data);
	el = (t_ui_el *)el_v;
	layer_elems = el->parent->children;
	if (el->current_texture != (size_t)ft_strhash("onActive"))
	{
		while (layer_elems)
		{
			if (((t_ui_el *)layer_elems->content)->current_texture ==
					(size_t)ft_strhash("onActive"))
				ui_el_set_current_texture_by_id(
						((t_ui_el *)layer_elems->content), "default");
			layer_elems = layer_elems->next;
		}
		ui_el_set_current_texture_by_id(el, "onActive");
		g->layers.current_layer = (t_ui_el *)(el->children->content);
	}
	return (1);
}
