/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbecker <sbecker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 16:09:10 by sbednar           #+#    #+#             */
/*   Updated: 2019/07/15 18:24:56 by sbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "guimp.h"

int		main(void)
{
	t_guimp	g_main;

	ui_sdl_init();
	gm_init(&g_main);
	if (!(g_main.ui_main = ui_main_init()))
		return (0);
	ui_main_fill_default_surfaces(g_main.ui_main);
	ui_main_fill_default_functions(g_main.ui_main);
	gm_main_fill_default_functions(g_main.ui_main);
	ui_main_fill_default_fonts(g_main.ui_main);
	gm_setup_default(&g_main);
	if (ui_jtoc_main_from_json(g_main.ui_main, "./json/main_new.json"))
		ui_sdl_deinit(228);
	g_main.main_win = ui_main_find_window_by_id(g_main.ui_main, 0);
	g_main.tool_win = ui_main_find_window_by_id(g_main.ui_main, 1);
	ui_sdl_raise_window(g_main.main_win->sdl_window);
	gm_fill(&g_main);
	ui_main_run_program(g_main.ui_main);
	return (0);
}
