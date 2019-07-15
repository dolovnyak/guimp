/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_main_handle_mouse_event.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbecker <sbecker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 00:47:51 by sbednar           #+#    #+#             */
/*   Updated: 2019/07/15 15:04:05 by sbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libui.h"

static void	check_mousewheel(t_ui_main *m, t_ui_event *event, t_ui_win *win)
{
	if (m->sdl_event->wheel.y < 0)
		event = win->events->on_scroll_up;
	else if (m->sdl_event->wheel.y > 0)
		event = win->events->on_scroll_down;
}

void		ui_main_handle_mouse_event(t_ui_main *m)
{
	t_ui_win	*win;
	t_ui_event	*event;

	if ((win = ui_main_find_window_by_sdl_id(m,
			m->sdl_event->window.windowID)) == NULL)
		return ;
	event = NULL;
	if (m->sdl_event->type == SDL_MOUSEMOTION)
		event = win->events->on_pointer_moved;
	else if (m->sdl_event->type == SDL_MOUSEBUTTONDOWN &&
			m->sdl_event->button.button == SDL_BUTTON_LEFT)
		event = win->events->on_pointer_left_button_pressed;
	else if (m->sdl_event->type == SDL_MOUSEBUTTONDOWN &&
			m->sdl_event->button.button == SDL_BUTTON_RIGHT)
		event = win->events->on_pointer_right_button_pressed;
	else if (m->sdl_event->type == SDL_MOUSEBUTTONUP &&
			m->sdl_event->button.button == SDL_BUTTON_LEFT)
		event = win->events->on_pointer_left_button_released;
	else if (m->sdl_event->type == SDL_MOUSEBUTTONUP &&
			m->sdl_event->button.button == SDL_BUTTON_RIGHT)
		event = win->events->on_pointer_right_button_released;
	else if (m->sdl_event->type == SDL_MOUSEWHEEL)
		check_mousewheel(m, event, win);
	if (event != NULL)
		ui_event_invoke(event, m, win);
}
