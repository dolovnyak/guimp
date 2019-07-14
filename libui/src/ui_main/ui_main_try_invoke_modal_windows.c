/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_main_try_invoke_modal_windows.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/14 15:11:08 by sbecker           #+#    #+#             */
/*   Updated: 2019/07/14 15:49:24 by sbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libui.h"

int	ui_main_try_invoke_modal_windows(t_ui_main *m)
{
	t_list		*node;
	t_ui_win	*w;

	node = m->windows;
	while (node)
	{
		w = (t_ui_win *)node->content;
		if (w->params & WIN_IS_SHOWN)
		{
			SDL_LockMutex(m->mutex);
			SDL_ShowWindow(w->sdl_window);
			SDL_RaiseWindow(w->sdl_window);
			w->params &= ~WIN_IS_SHOWN;
			SDL_UnlockMutex(m->mutex);
			return (0);
		}
		if (w->params & WIN_IS_HIDDEN)
		{
			SDL_LockMutex(m->mutex);
			SDL_HideWindow(w->sdl_window);
			SDL_UnlockMutex(m->mutex);
			w->params &= ~WIN_IS_HIDDEN;
			return (0);
		}
		node = node->next;
	}
	return (1);
}
