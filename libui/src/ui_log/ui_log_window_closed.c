/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_log_window_closed.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbecker <sbecker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 00:51:02 by sbednar           #+#    #+#             */
/*   Updated: 2019/07/13 09:32:31 by sbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libui.h"

int	ui_log_window_closed(t_ui_main *m, void *a)
{
	t_ui_win	*w;

	(void)m;
	w = (t_ui_win *)a;
	if (w != NULL)
	{
		SDL_Log("%s%-15s%swindowID = %d\n",
			KYEL,
			"WIN CLOSED",
			KNRM,
			w->id
		);
	}
	return (1);
}
