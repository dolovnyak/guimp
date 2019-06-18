/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_win_from_json.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbednar <sbednar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/03 18:19:27 by sbednar           #+#    #+#             */
/*   Updated: 2019/06/18 20:42:23 by sbednar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libui.h"

static int	ui_get_win_param_from_string(const char *str)
{
	int	i;

	i = 0;
	i |= (ft_strcmp(str, "WIN_MAIN") ? WIN_MAIN : 0);
	i |= (ft_strcmp(str, "WIN_RESIZABLE") ? WIN_RESIZABLE : 0);
	return (i);
}

static int	ui_win_from_json2(t_ui_main *m, t_ui_win *w, t_jnode *n)
{
	t_jnode	*tmp;

	if (!(tmp = jtoc_node_get_by_path(n, "size.x")) || tmp->type != number)
		return (FUNCTION_FAILURE);
	w->size.x = jtoc_get_int(tmp);
	if (!(tmp = jtoc_node_get_by_path(n, "size.y")) || tmp->type != number)
		return (FUNCTION_FAILURE);
	w->size.y = jtoc_get_int(tmp);
	ui_win_setup_default(w);
	ui_win_create(w);
	if (!(tmp = jtoc_node_get_by_path(n, "elements")))
		return (FUNCTION_FAILURE);
	tmp = tmp->down;
	while (tmp)
	{
		if (ui_el_from_json(m, w, tmp))
			return (FUNCTION_FAILURE);
		tmp = tmp->right;
	}
	return (FUNCTION_SUCCESS);
}

int			ui_win_from_json(t_ui_main *m, t_jnode *n)
{
	t_ui_win	*w;
	t_jnode		*tmp;

	if (!(w = ui_win_init()) ||
		!(tmp = jtoc_node_get_by_path(n, "title")) || tmp->type != string ||
			!(w->title = ft_strdup(jtoc_get_string(tmp))))
		return (FUNCTION_FAILURE);
	if ((tmp = jtoc_node_get_by_path(n, "params")) &&
		(tmp = tmp->down))
		while (tmp)
		{
			if (tmp->type != string)
				return (FUNCTION_FAILURE);
			w->params |= ui_get_win_param_from_string(jtoc_get_string(tmp));
			tmp = tmp->right;
		}
	if (ui_win_from_json2(m, w, n))
		return (FUNCTION_FAILURE);
	ui_main_add_window(m, w);
	return (FUNCTION_SUCCESS);
}
