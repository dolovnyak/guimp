/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_log_el_pointer_enter.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbecker <sbecker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 04:10:01 by sbednar           #+#    #+#             */
/*   Updated: 2019/07/13 09:25:08 by sbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libui.h"

int	ui_log_el_pointer_enter(t_ui_main *m, void *a)
{
	t_ui_el		*el;

	el = (t_ui_el *)a;
	SDL_Log("%s%-15s%sglobal = %3d;%-3d   local = %3d;%-3d   elementID = %-3d",   //windowID = %-3d\n",
		KGRN,
		"POINTER ENTER",
		KNRM,
		m->ptr_pos.x,
		m->ptr_pos.y,
		el->ptr_rel_pos.x,
		el->ptr_rel_pos.y,
		el->id
//		m->raycaster->focused_win->id
	);
	return (1);
}
