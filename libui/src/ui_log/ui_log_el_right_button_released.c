/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_log_el_right_button_released.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbecker <sbecker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 07:55:28 by sbednar           #+#    #+#             */
/*   Updated: 2019/07/12 11:08:23 by sbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libui.h"

void	ui_log_el_right_button_released(t_ui_main *m, void *a)
{
	t_ui_el		*el;

	(void)m;
	el = (t_ui_el *)a;
	SDL_Log("%s%-15s%sglobal = %3d;%-3d   local = %3d;%-3d   elementID = %-3d",   //windowID = %-3d\n",
		KRED,
		"RMB RELEASED",
		KNRM,
		m->ptr_pos.x,
		m->ptr_pos.y,
		el->ptr_rel_pos.x,
		el->ptr_rel_pos.y,
		el->id
//		m->raycaster->focused_win->id
	);
}
