/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_el_event_close_window.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/12 05:12:51 by sbecker           #+#    #+#             */
/*   Updated: 2019/07/13 11:32:45 by sbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libui.h"

int	ui_el_event_close_window(t_ui_main *m, void *a)
{
	t_ui_el		*el;
	t_ui_win	*cur_w;
	t_list		*cur;
	t_list		*prev;

	SDL_LockMutex(m->mutex);
	el = (t_ui_el *)a;
	prev = NULL;
	cur = m->windows;
	while (cur)
	{
		cur_w = (t_ui_win *)(cur->content);
		if (el->id == cur_w->id)
		{
			ui_win_destroy(cur_w);
			if (prev == NULL)
				m->windows = cur->next;
			else
				prev->next = cur->next;
			free(cur);
//			ft_lstdelones_without_cont(&cur);
			m->params |= HUITA;
			if (m->raycaster->focused_win && m->raycaster->focused_win->id == cur_w->id)
			{
				m->raycaster->focused_win = NULL;
				m->raycaster->selected = NULL;
			}
			SDL_UnlockMutex(m->mutex);
			return (0);
		}
		prev = cur;
		cur = cur->next;
	}
	SDL_UnlockMutex(m->mutex);
	return (1);
}