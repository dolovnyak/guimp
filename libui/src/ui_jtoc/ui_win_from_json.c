/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_win_from_json.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbednar <sbednar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/03 18:19:27 by sbednar           #+#    #+#             */
/*   Updated: 2019/06/19 20:23:32 by sbednar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libui.h"

static int	ui_win_from_json_events(t_ui_main *m, t_ui_win *w, t_jnode *n)
{
	char		*event_name;
	char		*func_name;
	t_ui_event	*e;
	func_ptr	f;
	t_jnode		*tmp;

	n = n->down;
	while (n)
	{
		if (n->type != object ||
			!(tmp = jtoc_node_get_by_path(n, "event_name")) ||
			tmp->type != string ||
			!(event_name  = jtoc_get_string(tmp)) ||
			!(e = ui_win_from_json_get_event_by_name(w, event_name)) ||
			!(tmp = jtoc_node_get_by_path(n, "func_name")) ||
			tmp->type != string ||
			!(func_name  = jtoc_get_string(tmp)) ||
			!(f = ui_main_get_function_by_id(m, func_name)))
			return (ui_sdl_log_error("WIN: PARSING EVENT"));
		ui_event_add_listener(e, f);
		n = n->right;
	}
	return (FUNCTION_SUCCESS);
}

static int	ui_win_from_json_size(t_ui_main *m, t_ui_win *w, t_jnode *n)
{
	t_jnode	*tmp;

	if (!(tmp = jtoc_node_get_by_path(n, "size.x")) || tmp->type != number)
		return (ui_sdl_log_error("WIN: SIZE.X"));
	w->size.x = jtoc_get_int(tmp);
	if (!(tmp = jtoc_node_get_by_path(n, "size.y")) || tmp->type != number)
		return (ui_sdl_log_error("WIN: SIZE.Y"));
	w->size.y = jtoc_get_int(tmp);
	ui_win_setup_default(w);
	ui_win_create(w);
	if (!(tmp = jtoc_node_get_by_path(n, "elements")))
		return (ui_sdl_log_error("WIN: NO ELEMENTS"));
	tmp = tmp->down;
	while (tmp)
	{
		if (ui_el_from_json(m, w, tmp))
			return (ui_sdl_log_error("WIN: PARSING ELEMENT"));
		tmp = tmp->right;
	}
	if ((tmp = jtoc_node_get_by_path(n, "events")))
	{
		if (tmp->type != array || ui_win_from_json_events(m, w, tmp))
			return (ui_sdl_log_error("WIN: PARSING EVENTS"));
	}
	return (FUNCTION_SUCCESS);
}

static int	ui_win_from_json_pos(t_ui_main *m, t_ui_win *w, t_jnode *n)
{
	t_jnode	*tmp;

	if (!(tmp = jtoc_node_get_by_path(n, "pos.x")) || tmp->type != number)
		return (ui_sdl_log_error("WIN: POS.X"));
	w->pos.x = jtoc_get_int(tmp);
	if (!(tmp = jtoc_node_get_by_path(n, "pos.y")))
		w->pos.y = SDL_WINDOWPOS_CENTERED;
	else
	{
		if (tmp->type != number)
			return (ui_sdl_log_error("WIN: POS.Y/TYPE"));
		w->pos.y = jtoc_get_int(tmp);
	}
	return (ui_win_from_json_size(m, w, n));
}

int			ui_win_from_json(t_ui_main *m, t_jnode *n)
{
	t_ui_win	*w;
	t_jnode		*tmp;

	if (!(w = ui_win_init()) ||
		!(tmp = jtoc_node_get_by_path(n, "title")) || tmp->type != string ||
			!(w->title = ft_strdup(jtoc_get_string(tmp))))
		return (ui_sdl_log_error("WIN: INIT/TITLE/TYPE"));
	if ((tmp = jtoc_node_get_by_path(n, "params")) &&
		(tmp = tmp->down))
		while (tmp)
		{
			if (tmp->type != string)
				return (ui_sdl_log_error("WIN: PARAMs TYPE"));
			w->params |= ui_get_win_param_from_string(jtoc_get_string(tmp));
			tmp = tmp->right;
		}
	if (ui_win_from_json_pos(m, w, n))
		return (ui_sdl_log_error("WIN: PARSING POS"));
	ui_main_add_window(m, w);
	return (FUNCTION_SUCCESS);
}