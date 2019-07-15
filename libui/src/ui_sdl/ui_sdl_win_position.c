/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_sdl_win_position                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbecker <sbecker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/10 19:09:04 by sbednar           #+#    #+#             */
/*   Updated: 2019/07/14 16:33:03 by sbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libui.h"

void	ui_sdl_set_window_position(SDL_Window *w, int x, int y)
{
	SDL_SetWindowPosition(w, x, y);
}

void	ui_sdl_get_window_position(SDL_Window *w, int *x, int *y)
{
	SDL_GetWindowPosition(w, x, y);
}

void	ui_sdl_raise_window(SDL_Window *w)
{
	SDL_RaiseWindow(w);
}