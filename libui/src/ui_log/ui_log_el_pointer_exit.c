/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_log_el_pointer_exit.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbecker <sbecker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 04:14:00 by sbednar           #+#    #+#             */
/*   Updated: 2019/07/12 03:30:49 by sbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libui.h"

void	ui_log_el_pointer_exit(t_ui_main *m, void *a)
{
	t_ui_el		*el;

	el = (t_ui_el *)a;
	SDL_Log("%s%-15s%sglobal = %3d;%-3d   local = %3d;%-3d   elementID = %-3d",   //windowID = %-3d\n",
		KRED,
		"POINTER EXIT",
		KNRM,
		m->ptr_pos.x,
		m->ptr_pos.y,
		el->ptr_rel_pos.x,
		el->ptr_rel_pos.y,
		el->id
//		m->raycaster->focused_win->id
	);
}
