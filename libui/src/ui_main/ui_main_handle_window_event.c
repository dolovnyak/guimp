/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_main_handle_window_event.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbednar <sbednar@student.fr.42>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/31 02:19:12 by sbednar           #+#    #+#             */
/*   Updated: 2019/03/31 14:56:18 by sbednar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libui.h"

void	ui_main_handle_window_event(t_ui_main *m)
{
	Uint32		windowID;
	t_ui_win	*win;
	t_ui_event	*event;

	windowID = m->sdl_event.window.windowID;
	if ((win = ui_main_find_window_by_id(m, windowID)) == NULL)
	{
		// SDL_Log("Window with id %d is not presented in main\n", windowID);
		// ui_sdl_deinit();
		// exit(EXIT_FAILURE);
		return ; // TODO: FIX
	}
	event = NULL;
	if (m->sdl_event.window.event == SDL_WINDOWEVENT_RESIZED)
		event = &(win->events.onResize);
	else if (m->sdl_event.window.event == SDL_WINDOWEVENT_FOCUS_GAINED)
		event = &(win->events.onFocusGained);
	else if (m->sdl_event.window.event == SDL_WINDOWEVENT_FOCUS_GAINED)
		event = &(win->events.onFocusLost);
	else if (m->sdl_event.window.event == SDL_WINDOWEVENT_CLOSE)
		event = &(win->events.onClose);
	if (event != NULL)
		ui_event_invoke(event, m, &windowID);
}