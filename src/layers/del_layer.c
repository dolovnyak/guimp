/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_layer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbecker <sbecker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/15 17:00:42 by sbecker           #+#    #+#             */
/*   Updated: 2019/07/15 17:01:54 by sbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "guimp.h"

static void	process1(t_list *tmp, t_ui_el *next_active, t_ui_el *el)
{
	t_list	*prev;
	t_list	*tmp2;

	prev = tmp;
	while (tmp)
	{
		next_active = (t_ui_el *)(tmp->content);
		if (next_active->id == el->id)
		{
			ui_el_destroy(next_active);
			tmp2 = tmp;
			prev->next = tmp->next;
			free(tmp2);
		}
		else if (next_active->id > el->id)
		{
			next_active->id--;
			ui_el_change_pos(next_active, 0, 0, (t_fvec2){0, -0.25f});
		}
		prev = tmp;
		tmp = tmp->next;
	}
}

static void	process2(t_list *tmp, t_ui_el *el)
{
	t_list	*prev;
	t_list	*tmp2;

	prev = tmp;
	while (tmp)
	{
		if ((Uint32)(tmp->content_size) == el->id)
		{
			ui_sdl_destroy_texture(tmp->content);
			tmp2 = tmp;
			prev->next = tmp->next;
			tmp = tmp->next;
			free(tmp2);
			continue ;
		}
		else if ((Uint32)(tmp->content_size) > el->id)
			tmp->content_size--;
		prev = tmp;
		tmp = tmp->next;
	}
}

int			del_layer(t_ui_main *main, void *el_v)
{
	t_guimp	*g;
	t_ui_el	*el;
	t_ui_el	*next_active;
	t_list	*tmp;
	t_list	*prev;

	g = (t_guimp *)(main->data);
	el = g->layers.current_layer->parent;
	(void)el_v;
	if (gm_generator_get_surf_count() == 0 || el->id == GM_LAYER_ID_DEF_LAYER)
		return (1);
	if (!(next_active = ui_win_find_el_by_id(g->main_win, el->id + 1)))
		next_active = ui_win_find_el_by_id(g->main_win, el->id - 1);
	ui_el_set_current_texture_by_id(next_active, "onActive");
	g->layers.current_layer = (t_ui_el *)(next_active->children->content);
	tmp = el->parent->children;
	process1(tmp, next_active, el);
	tmp = g->layers.layers;
	process2(tmp, el);
	gm_generate_surf_id(ID_GENERATOR_DEL);
	return (1);
}
