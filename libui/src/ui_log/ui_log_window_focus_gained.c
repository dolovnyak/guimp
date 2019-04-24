/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_log_window_focus_gained.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbednar <sbednar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 00:44:42 by sbednar           #+#    #+#             */
/*   Updated: 2019/04/24 13:56:24 by sbednar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libui.h"

void	ui_log_window_focus_gained(void *a1, void *a2)
{
	t_ui_main	*m;
	t_ui_win	*w;
	Uint32		windowID;

	m = (t_ui_main *)a1;
	windowID = *((Uint32 *)a2);
	w = ui_main_find_window_by_id(m, windowID);
	if (w != NULL)
	{
		SDL_Log("%s%-15s%swindowID=%d\n",
			KYEL,
			"WIN FOCUSED",
			KNRM,
			m->sdl_event.window.windowID
		);
	}
}
