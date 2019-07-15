/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_sliders.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbecker <sbecker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/10 16:05:33 by sbednar           #+#    #+#             */
/*   Updated: 2019/07/15 15:34:57 by sbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "guimp.h"

int	choose_red_color(t_ui_main *main, void *el_v)
{
	t_guimp	*g;
	t_ui_el	*el;
	t_ui_el	*chil;

	g = (t_guimp *)(main->data);
	el = (t_ui_el *)el_v;
	chil = ((t_ui_el *)el->children->content);
	g->draw_tool.r = get_value_from_slider(el, chil);
	update_color_rect(g, g->draw_tool.r, g->draw_tool.g, g->draw_tool.b);
	return (1);
}

int	choose_green_color(t_ui_main *main, void *el_v)
{
	t_guimp	*g;
	t_ui_el	*el;
	t_ui_el	*chil;

	g = (t_guimp *)(main->data);
	el = (t_ui_el *)el_v;
	chil = ((t_ui_el *)el->children->content);
	g->draw_tool.g = get_value_from_slider(el, chil);
	update_color_rect(g, g->draw_tool.r, g->draw_tool.g, g->draw_tool.b);
	return (1);
}

int	choose_blue_color(t_ui_main *main, void *el_v)
{
	t_guimp	*g;
	t_ui_el	*el;
	t_ui_el	*chil;

	g = (t_guimp *)(main->data);
	el = (t_ui_el *)el_v;
	chil = ((t_ui_el *)el->children->content);
	g->draw_tool.b = get_value_from_slider(el, chil);
	update_color_rect(g, g->draw_tool.r, g->draw_tool.g, g->draw_tool.b);
	return (1);
}

int	choose_size(t_ui_main *main, void *el_v)
{
	t_guimp	*g;
	t_ui_el	*el;
	t_ui_el	*chil;

	g = (t_guimp *)(main->data);
	el = (t_ui_el *)el_v;
	chil = ((t_ui_el *)el->children->content);
	g->draw_tool.brush_size = get_value_from_slider(el, chil);
	return (1);
}

int	choose_alpha(t_ui_main *main, void *el_v)
{
	t_guimp	*g;
	t_ui_el	*el;
	t_ui_el	*chil;

	g = (t_guimp *)(main->data);
	el = (t_ui_el *)el_v;
	chil = ((t_ui_el *)el->children->content);
	g->draw_tool.a = get_value_from_slider(el, chil);
	return (1);
}
