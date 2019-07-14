/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_main_run_program.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbecker <sbecker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/14 09:15:04 by sbecker           #+#    #+#             */
/*   Updated: 2019/07/14 16:29:45 by sbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libui.h"

void	ui_main_run_program(t_ui_main *m)
{
	//TUT POKA CHTO HUITA
    SDL_SetWindowModalFor(ui_main_find_window_by_id(m, 3)->sdl_window, ui_main_find_window_by_id(m, 0)->sdl_window); //TODO it's just check;
	SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "AAAAAAAAAAAAA",
			"CUKA BLYAT NENAVIJUU EBANII SDL AAAAAAAAAAAAAAAAAA",
			ui_main_find_window_by_id(m, 0)->sdl_window);
	ui_main_loop(m);
}
