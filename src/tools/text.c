/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   text.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edraugr- <edraugr-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/12 17:49:44 by edraugr-          #+#    #+#             */
/*   Updated: 2019/07/15 01:10:55 by edraugr-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "guimp.h"

int	choose_text(t_ui_main *main, void *el_v)
{
	t_guimp	*g;

	g = (t_guimp *)(main->data);
	(void)el_v;
	g->draw_tool.tool = GM_TOOL_TEXT;
	g->draw_tool.state = GM_TOOL_STATE_NONE;
	return (1);
}

int	choose_font(t_ui_main *main, void *el_v)
{
	t_guimp	*g;
	t_ui_el	*el;
	t_ui_el	*el_target;

	g = (t_guimp *)(main->data);
	el = (t_ui_el *)el_v;
	el_target = ui_win_find_el_by_id(g->tool_win, 121210);
	el = (t_ui_el *)el->children->content;
	el_target->text_area->font = el->text_area->font;
	ui_el_update_text(el_target, el_target->text_area->text);
	return (1);
}

int	update_text_color(t_ui_main *main, void *el_v)
{
	t_guimp	*g;
	t_ui_el	*el;

	g = (t_guimp *)(main->data);
	el = (t_ui_el *)el_v;
	el->text_area->text_color = (t_color){g->draw_tool.r,
		g->draw_tool.g, g->draw_tool.b, g->draw_tool.a};
	ui_el_update_text(el, el->text_area->text);
	return (1);
}

void	draw_text(t_guimp *g, t_vec2 s, t_vec2 e, t_ui_el *el)
{
	t_texture	*t;

	t = ui_sdl_create_texture_from_surface(g->main_win->sdl_renderer, el->sdl_surface);
	ui_sdl_render_copy(g->main_win->sdl_renderer, t, NULL, &(t_rect){s.x, s.y, e.x - s.x, e.y - s.y});
	ui_sdl_destroy_texture(t);
}
