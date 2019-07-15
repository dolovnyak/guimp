/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gm_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edraugr- <edraugr-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/23 05:20:03 by edraugr-          #+#    #+#             */
/*   Updated: 2019/05/23 05:33:21 by edraugr-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "guimp.h"

void	gm_init(t_guimp *g_main)
{
	ft_bzero((void *)g_main, sizeof(t_guimp));
}

void	gm_setup_default(t_guimp *g_main)
{
	g_main->ui_main->data = (void *)g_main;
	g_main->draw_tool.brush_size = GM_BRUSH_DEF_SIZE;
	g_main->draw_tool.tool_mode = GM_TOOL_MODE_EMPTY;
	g_main->draw_tool.a = 255;
	g_main->draw_tool.zoom = 1;
	g_main->draw_tool.state = GM_TOOL_STATE_NONE;
	g_main->draw_tool.tool = GM_TOOL_BRUSH;
	g_main->zoom_rect.x = 0;
	g_main->zoom_rect.y = 0;
	g_main->zoom_rect.w = GM_IMAGE_SIZE_X;
	g_main->zoom_rect.h = GM_IMAGE_SIZE_Y;
}
