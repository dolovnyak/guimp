/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_log_el_left_button_released.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbednar <sbednar@student.fr.42>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 05:30:35 by sbednar           #+#    #+#             */
/*   Updated: 2019/06/22 18:29:06 by sbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libui.h"

void	ui_log_el_left_button_released(void *a1, void *a2)
{
	t_ui_main	*m;
	t_ui_el		*el;

	m = (t_ui_main *)a1;
	el = (t_ui_el *)a2;
	SDL_Log("%s%-15s%sglobal = %3d;%-3d   local = %3d;%-3d   elementID = %-3d   windowID = %-3d\n",
		KRED,
		"LMB RELEASED",
		KNRM,
		m->ptr_pos.x,
		m->ptr_pos.y,
		el->ptr_rel_pos.x,
		el->ptr_rel_pos.y,
		el->id,
		m->raycaster->selected_win->id
	);
}
