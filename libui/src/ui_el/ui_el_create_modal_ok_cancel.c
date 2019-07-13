/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_el_create_modal_ok_cancel.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/11 20:30:59 by sbecker           #+#    #+#             */
/*   Updated: 2019/07/11 21:01:41 by sbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libui.h"

void    ui_el_create_modal_ok_cancel(void *a1, void *a2)
{
	t_ui_main   *m;
	t_ui_el     *el;
	t_ui_win    *w;

	m = (t_ui_main *)a1;
	el = (t_ui_el *)a2;
	if (ui_main_find_window_by_id(m, el->modal_win->w_id))
		return ;
	w = ui_win_create_modal_win(el->modal_win);
	ui_main_add_window(m, w);
}
