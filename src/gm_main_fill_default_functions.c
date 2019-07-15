/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gm_main_fill_default_surfaces.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbecker <sbecker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/23 05:03:28 by sbednar           #+#    #+#             */
/*   Updated: 2019/07/15 12:20:39 by sbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "guimp.h"

static void	gm_main_fill_default_functions2(t_ui_main *m)
{
	ui_main_add_function_by_id(m, ui_el_event_set_focused_texture,
		"ui_el_event_set_focused_texture");
	ui_main_add_function_by_id(m, ui_el_event_set_active_texture,
		"ui_el_event_set_active_texture");
	ui_main_add_function_by_id(m, ui_el_event_children_set_default,
		"ui_el_event_children_set_default");
	ui_main_add_function_by_id(m, add_layer, "test_add_layer");
	ui_main_add_function_by_id(m, del_layer, "test_del_layer");
	ui_main_add_function_by_id(m, draw_color_rect,
		"draw_color_rect");
	ui_main_add_function_by_id(m, scan_tool_position,
		"scan_tool_position");
	ui_main_add_function_by_id(m, set_brush_texture_from_el,
		"set_brush_texture_from_el");
	ui_main_add_function_by_id(m, switch_fill_mode,
		"switch_fill_mode");
	ui_main_add_function_by_id(m, ui_save_image, "ui_save_image");
	ui_main_add_function_by_id(m, ui_open_image, "ui_open_image");
	ui_main_add_function_by_id(m,
		start_draw_with_selected_tool_pointer_up,
		"start_draw_with_selected_tool_pointer_up");
}

void		gm_main_fill_default_functions(t_ui_main *m)
{
	ui_main_add_function_by_id(m, ui_el_event_show_child,
		"ui_el_event_show_child");
	ui_main_add_function_by_id(m, ui_el_event_default_draw,
		"ui_el_event_default_draw");
	ui_main_add_function_by_id(m, draw_canvas_renderer,
		"draw_canvas_renderer");
	ui_main_add_function_by_id(m, draw_with_selected_tool,
		"draw_with_selected_tool");
	ui_main_add_function_by_id(m, start_draw_with_selected_tool,
		"start_draw_with_selected_tool");
	ui_main_add_function_by_id(m, start_alt_with_selected_tool,
		"start_alt_with_selected_tool");
	ui_main_add_function_by_id(m, move_draw_canvas_with_zoom,
		"move_draw_canvas_with_zoom");
	ui_main_add_function_by_id(m, on_ptr_lbd, "testOnPtrLBD");
	ui_main_add_function_by_id(m, pressed_lbd, "PressedLBD");
	ui_main_add_function_by_id(m, on_ptr_enter, "testOnPtrEnter");
	ui_main_add_function_by_id(m, on_ptr_exit, "testOnPtrExit");
	ui_main_add_function_by_id(m, ui_el_event_set_default_texture,
		"ui_el_event_set_default_texture");
	gm_main_fill_default_functions2(m);
}
