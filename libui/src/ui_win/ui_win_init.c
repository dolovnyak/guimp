/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_win_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbednar <sbednar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/29 20:57:36 by sbednar           #+#    #+#             */
/*   Updated: 2019/06/18 20:35:48 by sbednar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libui.h"

t_ui_win	*ui_win_init(void)
{
	t_ui_win	*win;

	if (!(win = (t_ui_win *)malloc(sizeof(t_ui_win))))
		return (NULL);
	ft_bzero(win, sizeof(t_ui_win));
	return (win);
}
