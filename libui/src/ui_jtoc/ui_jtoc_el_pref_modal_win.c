/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_jtoc_el_pref_modal_win.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edraugr- <edraugr-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/12 06:56:23 by sbecker           #+#    #+#             */
/*   Updated: 2019/07/15 07:20:59 by edraugr-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libui.h"

static int	get_modal_text_params(t_ui_text *ui_text, t_jnode *n)
{
	int		hash;
	t_jnode *tmp;

	if ((tmp = jtoc_node_get_by_path(n, "text_area.string_len")) && tmp->type == number)
		ui_text->string_len = jtoc_get_int(tmp);
	if ((tmp = jtoc_node_get_by_path(n, "text_area.render_param")) && tmp->type == string)
	{
		hash = ft_strhash(jtoc_get_string(tmp));
		ui_text->render_param |= (hash == ft_strhash("TEXT_IS_SOLID") ? TEXT_IS_SOLID : 0);
		ui_text->render_param |= (hash == ft_strhash("TEXT_IS_SHADED") ? TEXT_IS_SHADED : 0);
		ui_text->render_param |= (hash == ft_strhash("TEXT_IS_BLENDED") ? TEXT_IS_BLENDED : 0);
	}
	else
		ui_text->render_param |= TEXT_IS_BLENDED;
	if ((tmp = jtoc_node_get_by_path(n, "text_area.params")))
	{
		tmp = tmp->down;
		while (tmp)
		{
			if (tmp->type != string)
				return (FUNCTION_FAILURE);
			hash = ft_strhash(jtoc_get_string(tmp));
			ui_text->params |= (hash == ft_strhash("TEXT_IS_CENTERED") ? TEXT_IS_CENTERED : 0);
			ui_text->params |= (hash == ft_strhash("TEXT_IS_INPUTTING") ? TEXT_IS_INPUTTING : 0);
			ui_text->params |= (hash == ft_strhash("TEXT_IS_REGULAR") ? TEXT_IS_REGULAR : 0);
			tmp = tmp->right;
		}
	}
	return (FUNCTION_SUCCESS);
}

static int	get_modal_font_color(t_ui_main *m, t_ui_text *ui_text, t_jnode *n)
{
	t_jnode *tmp;
	int     color;

	if ((tmp = jtoc_node_get_by_path(n, "text_area.font")) && tmp->type == string)
	{
		if (!(ui_text->font = ui_main_get_font_by_id(m, jtoc_get_string(tmp))))
			return (FUNCTION_FAILURE);
	}
	else
		return (FUNCTION_FAILURE);
	if ((tmp = jtoc_node_get_by_path(n, "text_area.color")) && tmp->type == string)
	{
		color = ft_atoi_base(jtoc_get_string(tmp), 16);
		ui_text->text_color = (SDL_Color){(Uint8)((color & 0xFF0000) >> 16),
			(Uint8)((color & 0x00FF00) >> 8), (Uint8)(color & 0x0000FF), 255};
	}
	else
		return (FUNCTION_FAILURE);
	if ((tmp = jtoc_node_get_by_path(n, "text_area.bg_color")) && tmp->type == string)
	{
		color = ft_atoi_base(jtoc_get_string(tmp), 16);
		ui_text->bg_color = (SDL_Color){(Uint8)((color & 0xFF0000) >> 16),
			(Uint8)((color & 0x00FF00) >> 8), (Uint8)(color & 0x0000FF), 255};
	}
	return (FUNCTION_SUCCESS);
}

static int	ui_el_pref_text_modal_win(t_ui_main *m, t_jnode *n, t_ui_text *ui_text)
{
	t_jnode		*tmp;

	if ((jtoc_node_get_by_path(n, "text_area")))
	{
		if (get_modal_font_color(m, ui_text, n) == FUNCTION_FAILURE)
			return (FUNCTION_FAILURE);
		if (get_modal_text_params(ui_text, n) == FUNCTION_FAILURE)
			return (FUNCTION_FAILURE);
		if ((tmp = jtoc_node_get_by_path(n, "text_area.text")) && tmp->type == string)
			ui_text->text = ft_strdup(jtoc_get_string(tmp));
		else
			return (FUNCTION_FAILURE);
		return (FUNCTION_SUCCESS);
	}
	return (FUNCTION_FAILURE);
}

static int	get_win_params(t_ui_win *w, t_jnode *n)
{
	int		type;
	t_jnode *tmp;

	if ((tmp = jtoc_node_get_by_path(n, "modal_win.type")) && tmp->type == string)
	{
		type = ft_strcmp(jtoc_get_string(tmp), "OK") ? 0 : 1;
		type = ft_strcmp(jtoc_get_string(tmp), "OK_CANCEL") ? type : 2;
	}
	if ((tmp = jtoc_node_get_by_path(n, "modal_win.win_id")) && tmp->type == number)
		w->id = jtoc_get_int(tmp);
	else
		return (0);
	if ((tmp = jtoc_node_get_by_path(n, "modal_win.title")) && tmp->type == string)
		w->title = ft_strdup(jtoc_get_string(tmp));
	else
		return (0);
	w->pos.x = SDL_WINDOWPOS_CENTERED;
	w->pos.y = SDL_WINDOWPOS_CENTERED;
	return (type);
}

int ui_jtoc_el_pref_modal_win(t_ui_main *m, t_ui_el *e, t_jnode *n)
{
	int			type;
	t_jnode		*tmp;
	t_ui_win	*w;
	t_ui_text	ui_text;

	(void)m;
	if ((tmp = jtoc_node_get_by_path(n, "modal_win")))
	{
		w = ui_win_init();
		if ((type = get_win_params(w, n)) == 0)
			return (FUNCTION_FAILURE);
		if (type == 1)
		{
			if (ui_el_pref_text_modal_win(m, tmp, &ui_text) == FUNCTION_FAILURE)
				return (FUNCTION_FAILURE);
			ui_jtoc_create_modal_ok(m, w, &ui_text);
		}
		else if (type == 2)
		{
			if (ui_el_pref_text_modal_win(m, tmp, &ui_text) == FUNCTION_FAILURE)
				return (FUNCTION_FAILURE);
		}
		e->modal_win = w;
		ui_event_add_listener(e->events->onPointerLeftButtonPressed, ui_el_event_show_window);
	}
	return (FUNCTION_SUCCESS);
}
