/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edraugr- <edraugr-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 16:09:10 by sbednar           #+#    #+#             */
/*   Updated: 2019/06/02 15:57:02 by edraugr-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "guimp.h"

// static void	testOnPtrStay(void *main, void *el_v)
// {
// 	main = NULL;
// 	t_ui_el *el = (t_ui_el *)el_v;
// 	static int dist = 1;
// 	static int dsize;

// 	if (main == NULL)
// 	{
// 		dsize += dist;
// 		if (dsize > 200 || dsize == 0)
// 			dist *= -1;
// 		el->rect.w += 2 * dist;
// 		el->rect.h += 2 * dist;
// 		el->rect.x -= dist;
// 		el->rect.y -= dist;
// 	}
// }

// static void	test(void *main, void *el_v)
// {
// 	main = NULL;
// 	t_ui_el *el = (t_ui_el *)el_v;
// 	t_ui_el *text = (t_ui_el *)el->data;
// 	ui_el_update_text(text, "FROM 7 ZALOOP");
// }

static void	test_add_layer(void *ui_main, void *el_v)
{
	t_ui_main	*m;
	t_ui_el		*el;
	t_ui_el		*layer_menu;
	t_ui_el		*tmp_el;
	t_guimp		*g;

	el = (t_ui_el *)el_v;
	m = (t_ui_main *)ui_main;
	layer_menu = (t_ui_el *)el->data;
	g = (t_guimp *)m->data;
	if (!(tmp_el = (t_ui_el *)malloc(sizeof(t_ui_el))))
	{
		printf("layer malloc error in scrollable menu in layer_win\n");
		return ;
	}
	ui_el_setup_default_scroll_menu_elem(tmp_el, layer_menu);
	tmp_el->id = gm_generate_surf_id(ID_GENERATOR_ADD);
	ui_el_set_pos(tmp_el, 0, 0, (t_fvec2){0.1, 0.27 * (float)gm_generator_get_surf_count()});
	ui_el_set_size(tmp_el, &(g->layer_win->canvas), SIZE_ABS, (t_fvec2){0.8, 0.25});
	tmp_el->sdl_renderer = g->layer_win->sdl_renderer;
	ui_el_add_texture_from_main_by_id(g->ui_main, tmp_el, "bl", "default");
}

int		main()
{
	t_guimp	g_main;
	t_ui_el	*tmp_el;
	t_ui_el	*tmp_el_p1;
	t_ui_el	*tmp_el_p2;



	/********/
	/* INIT */
	/********/
	ui_sdl_init();
	gm_init(&g_main);
	if (!(g_main.ui_main = (t_ui_main *)malloc(sizeof(t_ui_main))))
	{
		printf("ui_main malloc error in struct g_main\n");
		return (0);
	}
	ui_main_init(g_main.ui_main);
	ui_main_fill_default_surfaces(g_main.ui_main);
	g_main.ui_main->data = (void *)(&g_main);



	/************/
	/* MAIN_WIN */
	/************/
	if (!(g_main.main_win = (t_ui_win *)malloc(sizeof(t_ui_win))))
	{
		printf("main_win malloc error in struct g_main\n");
		return (0);
	}
	ui_win_init(g_main.main_win);
	g_main.main_win->title = ft_strdup("GUIMP");
	g_main.main_win->params = WIN_MAIN | WIN_RESIZABLE;
	g_main.main_win->size = (t_vec2){GM_MAIN_WIN_W, GM_MAIN_WIN_H};
	ui_win_setup_default(g_main.main_win);
	ui_win_create(g_main.main_win);
	ui_event_add_listener(&(g_main.main_win->events.onResize), &ui_win_update_size);
	ui_main_add_window(g_main.ui_main, g_main.main_win);
	g_main.main_win->canvas.id = 0;
	g_main.main_win->canvas.sdl_renderer = g_main.main_win->sdl_renderer;
	ui_el_add_texture_from_main_by_id(g_main.ui_main, &(g_main.main_win->canvas), "flower", "default");
	ui_el_add_empty_texture(
		&(g_main.main_win->canvas),
		g_main.main_win->canvas.rect.w,
		g_main.main_win->canvas.rect.h,
		TID_DRAW_TEXTURE);
	ui_event_add_listener(&(g_main.main_win->canvas.events.onRender), &draw_main_canvas_event);
	ui_event_add_listener(&(g_main.main_win->canvas.events.onPointerLeftButtonHold), &draw_dot);

	/*MAIN ELEM*/
		if (!(tmp_el = (t_ui_el *)malloc(sizeof(t_ui_el))))
		{
			printf("main_elem malloc error in canvas in main_win\n");
			return (0);
		}
		ui_el_init(tmp_el);
		ui_el_setup_default(tmp_el);
		ui_event_add_listener(&(tmp_el->events.onRender), &ui_el_draw_event);
		ui_el_add_child(&(g_main.main_win->canvas), tmp_el);
		ui_el_set_pos(tmp_el, 0, 0, (t_fvec2){0.05, 0.05});
		ui_el_set_size(tmp_el, 0, 0, (t_fvec2){0.9, 0.9});
		tmp_el->id = GM_MAIN_ID_DRAW;
		tmp_el->sdl_renderer = g_main.main_win->sdl_renderer;
		tmp_el->params |= EL_DYNAMIC_SIZE;
		ui_el_add_texture_from_main_by_id(g_main.ui_main, tmp_el, "bl", "default");



	/************/
	/* TOOL_WIN */
	/************/
	if (!(g_main.tool_win = (t_ui_win *)malloc(sizeof(t_ui_win))))
	{
		printf("tool_win malloc error in struct g_main\n");
		return (0);
	}
	ui_win_init(g_main.tool_win);
	g_main.tool_win->title = ft_strdup("TOOLS");
	g_main.tool_win->params = 0;
	g_main.tool_win->size = (t_vec2){GM_TOOL_WIN_W, GM_TOOL_WIN_H};
	ui_win_setup_default(g_main.tool_win);
	ui_win_create(g_main.tool_win);
	ui_main_add_window(g_main.ui_main, g_main.tool_win);
	g_main.tool_win->canvas.id = 0;
	g_main.tool_win->canvas.sdl_renderer = g_main.tool_win->sdl_renderer;
	ui_el_add_texture_from_main_by_id(g_main.ui_main, &(g_main.tool_win->canvas), "flower", "default");
	ui_event_add_listener(&(g_main.tool_win->canvas.events.onRender), &draw_main_canvas_event);

	/*DRAW BUTTONS SCROLLABLE MENU*/
		if (!(tmp_el_p1 = (t_ui_el *)malloc(sizeof(t_ui_el))))
		{
			printf("scrollable menu malloc error in canvas in tool_win\n");
			return (0);
		}
		ui_el_setup_default_scroll_menu(tmp_el_p1);
		ui_el_add_child(&(g_main.tool_win->canvas), tmp_el_p1);
		ui_el_set_pos(tmp_el_p1, 0, 0, (t_fvec2){0.01, 0.01});
		ui_el_set_size(tmp_el_p1, 0, 0, (t_fvec2){0.98, 0.59});
		tmp_el_p1->id = GM_TOOL_ID_BUT_MENU;
		tmp_el_p1->sdl_renderer = g_main.tool_win->sdl_renderer;
		ui_el_add_texture_from_main_by_id(g_main.ui_main, tmp_el_p1, "priso", "default");

	/*SELECT BRUSH BUTTON*/
			if (!(tmp_el = (t_ui_el *)malloc(sizeof(t_ui_el))))
			{
				printf("draw_brush malloc error in scrollable menu in tool_win\n");
				return (0);
			}
			ui_el_setup_default_scroll_menu_elem(tmp_el, tmp_el_p1);
			ui_el_set_pos(tmp_el, 0, 0, (t_fvec2){0.1, 0.05});
			ui_el_set_size(tmp_el, 0, SIZE_PIXEL, (t_fvec2){GM_TOOL_WIN_W * 0.35, GM_TOOL_WIN_W * 0.35});
			tmp_el->id = GM_TOOL_ID_BRUSH;
			tmp_el->sdl_renderer = g_main.tool_win->sdl_renderer;
			ui_el_add_texture_from_main_by_id(g_main.ui_main, tmp_el, "bl", "default");

	/*ERASER BUTTON*/
			if (!(tmp_el = (t_ui_el *)malloc(sizeof(t_ui_el))))
			{
				printf("eraser_brush malloc error in scrollable menu in tool_win\n");
				return (0);
			}
			ui_el_setup_default_scroll_menu_elem(tmp_el, tmp_el_p1);
			ui_el_set_pos(tmp_el, 0, 0, (t_fvec2){0.55, 0.05});
			ui_el_set_size(tmp_el,  0, SIZE_PIXEL, (t_fvec2){GM_TOOL_WIN_W * 0.35, GM_TOOL_WIN_W * 0.35});
			tmp_el->id = GM_TOOL_ID_ERASER;
			tmp_el->sdl_renderer = g_main.tool_win->sdl_renderer;
			ui_el_add_texture_from_main_by_id(g_main.ui_main, tmp_el, "bl", "default");

	/*SETTINGS MENU*/
		if (!(tmp_el_p1 = (t_ui_el *)malloc(sizeof(t_ui_el))))
		{
			printf("settings menu malloc error in canvas in tool_win\n");
			return (0);
		}
		ui_el_setup_default(tmp_el_p1);
		ui_el_add_child(&(g_main.tool_win->canvas), tmp_el_p1);
		ui_el_set_pos(tmp_el_p1, 0, 0, (t_fvec2){0.01, 0.61});
		ui_el_set_size(tmp_el_p1, 0, 0, (t_fvec2){0.98, 0.38});
		tmp_el_p1->id = GM_TOOL_ID_SET_MENU;
		tmp_el_p1->sdl_renderer = g_main.tool_win->sdl_renderer;
		ui_el_add_texture_from_main_by_id(g_main.ui_main, tmp_el_p1, "frolushka", "default");

	/*SLIDER ROOT*/
			if (!(tmp_el = (t_ui_el *)malloc(sizeof(t_ui_el))))
			{
				printf("eraser_brush malloc error in scrollable menu in tool_win\n");
				return (0);
			}
			ui_el_setup_default(tmp_el);
			ui_el_add_child(tmp_el_p1, tmp_el);
			ui_el_set_pos(tmp_el, 0, 0, (t_fvec2){0.1, 0.49});
			ui_el_set_size(tmp_el, 0, 0, (t_fvec2){0.8, 0.02});
			tmp_el->id = GM_TOOL_ID_SLIDER_ROOT;
			tmp_el->sdl_renderer = g_main.tool_win->sdl_renderer;
			ui_el_add_texture_from_main_by_id(g_main.ui_main, tmp_el, "bl", "default");

	/*SLIDER HEAD*/
				if (!(tmp_el_p2 = (t_ui_el *)malloc(sizeof(t_ui_el))))
				{
					printf("eraser_brush malloc error in scrollable menu in tool_win\n");
					return (0);
				}
				ui_el_setup_default(tmp_el_p2);
				ui_el_add_child(tmp_el, tmp_el_p2);
				ui_el_set_pos(tmp_el_p2, 0, 0, (t_fvec2){0.5, -4.5});
				ui_el_set_size(tmp_el_p2, 0, 0, (t_fvec2){0.04, 10});
				tmp_el_p2->id = GM_TOOL_ID_SLIDER_HEAD;
				tmp_el_p2->sdl_renderer = g_main.tool_win->sdl_renderer;
				ui_el_add_texture_from_main_by_id(g_main.ui_main, tmp_el_p2, "test", "default");
				ui_el_setup_hor_draggable(tmp_el_p2);



	/*************/
	/* LAYER_WIN */
	/*************/
	if (!(g_main.layer_win = (t_ui_win *)malloc(sizeof(t_ui_win))))
	{
		printf("layer_win malloc error in struct g_main\n");
		return (0);
	}
	ui_win_init(g_main.layer_win);
	g_main.layer_win->title = ft_strdup("LAYERS");
	g_main.layer_win->params = 0;
	g_main.layer_win->size = (t_vec2){GM_LAYER_WIN_W, GM_LAYER_WIN_H};
	ui_win_setup_default(g_main.layer_win);
	ui_win_create(g_main.layer_win);
	ui_main_add_window(g_main.ui_main, g_main.layer_win);
	g_main.layer_win->canvas.id = 0;
	g_main.layer_win->canvas.sdl_renderer = g_main.layer_win->sdl_renderer;
	ui_el_add_texture_from_main_by_id(g_main.ui_main, &(g_main.layer_win->canvas), "flower", "default");
	ui_event_add_listener(&(g_main.layer_win->canvas.events.onRender), &draw_main_canvas_event);

	/*LAYERS SCROLLABLE MENU*/
		if (!(tmp_el_p2 = (t_ui_el *)malloc(sizeof(t_ui_el))))
		{
			printf("scrollable menu malloc error in canvas in layer_win\n");
			return (0);
		}
		ui_el_setup_default_scroll_menu(tmp_el_p2);
		ui_el_add_child(&(g_main.layer_win->canvas), tmp_el_p2);
		ui_el_set_pos(tmp_el_p2, 0, 0, (t_fvec2){0.01, 0.01});
		ui_el_set_size(tmp_el_p2, 0, 0, (t_fvec2){0.98, 0.89});
		tmp_el_p2->id = GM_LAYER_ID_MENU;
		tmp_el_p2->sdl_renderer = g_main.layer_win->sdl_renderer;
		ui_el_add_texture_from_main_by_id(g_main.ui_main, tmp_el_p2, "priso", "default");

	/*DEFAULT LAYER*/
			if (!(tmp_el = (t_ui_el *)malloc(sizeof(t_ui_el))))
			{
				printf("default layer malloc error in scrollable menu in layer_win\n");
				return (0);
			}
			ui_el_setup_default_scroll_menu_elem(tmp_el, tmp_el_p2);
			ui_el_set_pos(tmp_el, 0, 0, (t_fvec2){0.1, 0.05});
			ui_el_set_size(tmp_el, &(g_main.layer_win->canvas), SIZE_ABS, (t_fvec2){0.8, 0.25});
			tmp_el->id = 23456;//GM_LAYER_ID_DEF_LAYER;
			tmp_el->sdl_renderer = g_main.layer_win->sdl_renderer;
			ui_el_add_texture_from_main_by_id(g_main.ui_main, tmp_el, "bl", "default");

	/*ADD BUTTON*/
		if (!(tmp_el_p1 = (t_ui_el *)malloc(sizeof(t_ui_el))))
		{
			printf("add button malloc error in canvas in layer_win\n");
			return (0);
		}
		ui_el_setup_default(tmp_el_p1);
		ui_el_add_child(&(g_main.layer_win->canvas), tmp_el_p1);
		ui_el_set_pos(tmp_el_p1, 0, 0, (t_fvec2){0.01, 0.91});
		ui_el_set_size(tmp_el_p1, 0, 0, (t_fvec2){0.485, 0.08});
		tmp_el_p1->id = GM_LAYER_ID_ADD;
		tmp_el_p1->sdl_renderer = g_main.layer_win->sdl_renderer;
		ui_el_add_texture_from_main_by_id(g_main.ui_main, tmp_el_p1, "priso", "default");
		tmp_el_p1->data = (void *)tmp_el_p2;
		ui_event_add_listener(&(tmp_el_p1->events.onPointerLeftButtonPressed), &test_add_layer);

	/*DEL BUTTON*/
		if (!(tmp_el_p1 = (t_ui_el *)malloc(sizeof(t_ui_el))))
		{
			printf("del button malloc error in canvas in layer_win\n");
			return (0);
		}
		ui_el_setup_default(tmp_el_p1);
		ui_el_add_child(&(g_main.layer_win->canvas), tmp_el_p1);
		ui_el_set_pos(tmp_el_p1, 0, 0, (t_fvec2){0.505, 0.91});
		ui_el_set_size(tmp_el_p1, 0, 0, (t_fvec2){0.485, 0.08});
		tmp_el_p1->id = GM_LAYER_ID_DEL;
		tmp_el_p1->sdl_renderer = g_main.layer_win->sdl_renderer;
		ui_el_add_texture_from_main_by_id(g_main.ui_main, tmp_el_p1, "priso", "default");
		tmp_el_p1->data = (void *)tmp_el_p2;

	/*************/
	/* MAIN_LOOP */
	/*************/
	ui_main_loop(g_main.ui_main);
	return (0);
}
