/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_win_event_change_text_in_focused_el.c           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edraugr- <edraugr-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/19 19:18:31 by sbecker           #+#    #+#             */
/*   Updated: 2019/07/15 03:40:50 by edraugr-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libui.h"

static char	*circumcision(t_ui_el *el)
{
	char	*str;

	if (el->text_area->text == NULL || *el->text_area->text == '\0')
		return (ft_strnew(1));
	str = ft_strsub(el->text_area->text, 0, ft_strlen(el->text_area->text) - 1);
	return (str);
}

static char	*join_with_letter(t_ui_el *el, unsigned int keycode, Uint8 is_upper)
{
	char	*str;
	char	*str_letter;

	str_letter = ft_strnew(1);
	str_letter[0] = (char)(keycode + 93);
	if (is_upper)
		str_letter[0] = ft_toupper(str_letter[0]);
	if (el->text_area->text == NULL)
		return (str_letter);
	str = ft_strjoin(el->text_area->text, str_letter);
	free(str_letter);
	return(str);
}

static char	*join_with_number(t_ui_el *el, unsigned int keycode)
{
	char	*str_letter;
	char	*str;

	str_letter = ft_strnew(1);
	str_letter[0] = (char)(keycode + 19);
	if (el->text_area->text == NULL)
		return (str_letter);
	str = ft_strjoin(el->text_area->text, str_letter);
	free(str_letter);
	return(str);
}

static char	*join_with_other(t_ui_el *el, unsigned int keycode)
{
	char	*str_letter;
	char	*str;

	str_letter = ft_strnew(1);
	if (keycode == 56)
		str_letter[0] = '/';
	else if (keycode == 55)
		str_letter[0] = '.';
	else if (keycode == SDL_SCANCODE_SPACE)
		str_letter[0] = ' ';
	else if (keycode == 45)
		str_letter[0] = '-';
	else if (keycode == SDL_SCANCODE_0)
		str_letter[0] = '0';
	else if (el->text_area->text == NULL)
		return (str_letter);
	str = ft_strjoin(el->text_area->text, str_letter);
	free(str_letter);
	return(str);
}

int	ui_win_event_change_text_in_focused_el(t_ui_main *m, void *a)
{
	t_ui_win	*w;
	t_ui_el		*el;
	char		*new_text;

	w = (t_ui_win *)a;
	el = m->focused_el;
	if (!el || !(el->params & EL_IS_TEXT) || !(el->text_area->params & TEXT_IS_INPUTTING))
		return (1);
	if (m->cur_keycode >= SDL_SCANCODE_A && m->cur_keycode <= SDL_SCANCODE_Z)
	{
		new_text = join_with_letter(el, m->cur_keycode, m->is_upper);
		ui_el_update_text(el, new_text);
		if (new_text != NULL)
			free(new_text);
	}
	else if (m->cur_keycode >= SDL_SCANCODE_1 && m->cur_keycode <= SDL_SCANCODE_9)
	{
		new_text = join_with_number(el, m->cur_keycode);
		ui_el_update_text(el, new_text);
		if (new_text != NULL)
			free(new_text);
	}
	else if (m->cur_keycode == SDL_SCANCODE_BACKSPACE)
	{
		new_text = circumcision(el);
		ui_el_update_text(el, new_text);
		if (new_text != NULL)
			free(new_text);
	}
	else if (m->cur_keycode == 55 || m->cur_keycode == 56 || m->cur_keycode== SDL_SCANCODE_0 || m->cur_keycode == SDL_SCANCODE_SPACE || m->cur_keycode == 45)
	{
		new_text = join_with_other(el, m->cur_keycode);
		ui_el_update_text(el, new_text);
		if (new_text != NULL)
			free(new_text);
	}
	return (1);
}
