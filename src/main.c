/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbecker <sbecker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 16:09:10 by sbednar           #+#    #+#             */
/*   Updated: 2019/07/14 09:20:35 by sbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "guimp.h"

int move_windows(t_ui_main *m, void *a)
{
	t_ui_win    *w;
	t_list      *list;
	t_ui_win    *cur_w;
	t_vec2      pos;

	w = (t_ui_win *)a;
	if (w != NULL)
	{
		list = m->windows;
		while (list)
		{
			cur_w = (t_ui_win *)list->content;
			if (cur_w->id >= 2 || cur_w->id == w->id)
			{
				list = list->next;
				continue;
			}
			SDL_GetWindowPosition(w->sdl_window, &pos.x, &pos.y);
			if (cur_w->id == 0)
				pos.x = pos.x + GM_TOOL_WIN_W + 5;
			else if (cur_w->id == 1)
				pos.x = pos.x - GM_TOOL_WIN_W - 5;
			SDL_SetWindowPosition(cur_w->sdl_window, pos.x, pos.y);
			cur_w->pos.x = pos.x;
			cur_w->pos.y = pos.y;
			list = list->next;
		}
	}
	return (1);
}

static int	testOnPtrEnter(t_ui_main *main, void *el_v)
{
	(void)main;
	t_ui_el *el = (t_ui_el *)el_v;
	if (el->current_texture != (size_t)ft_strhash("onActive"))
		ui_el_set_current_texture_by_id(el, "onFocus");
	return (1);
}

static int	testOnPtrExit(t_ui_main *main, void *el_v)
{
	(void)main;
	t_ui_el *el = (t_ui_el *)el_v;
	if (el->current_texture != (size_t)ft_strhash("onActive"))
		ui_el_set_current_texture_by_id(el, "default");
	return (1);
}

static int	PressedLBD(t_ui_main *main, void *el_v)
{
	(void)main;
	t_ui_el *el = (t_ui_el *)el_v;
	if (el->current_texture != (size_t)ft_strhash("onActive"))
		ui_el_set_current_texture_by_id(el, "onPressedLBM");
	return (1);
}

static int	testOnPtrLBD(t_ui_main *main, void *el_v)
{
	t_list	*layer_elems;
	t_guimp	*g;

	g = (t_guimp *)(main->data);
	t_ui_el *el = (t_ui_el *)el_v;
	layer_elems = el->parent->children;
	if (el->current_texture != (size_t)ft_strhash("onActive"))
	{
		while (layer_elems)
		{
			if (((t_ui_el *)layer_elems->content)->current_texture == (size_t)ft_strhash("onActive"))
				ui_el_set_current_texture_by_id(((t_ui_el *)layer_elems->content), "default");
			layer_elems = layer_elems->next;
		}
		ui_el_set_current_texture_by_id(el, "onActive");
		g->layers.current_layer = (t_ui_el *)(el->children->content);
	}
	return (1);
}

static int	clear_layer(t_ui_main *main, void *el_v)
{
	SDL_Texture	*t;
	t_guimp		*g;

	g = (t_guimp *)(main->data);
	t = (t_texture *)((t_ui_el *)el_v)->data;
	SDL_SetRenderTarget(g->main_win->sdl_renderer, t);
	SDL_SetRenderDrawBlendMode(g->main_win->sdl_renderer, SDL_BLENDMODE_NONE);
	SDL_SetRenderDrawColor(g->main_win->sdl_renderer, 255, 255, 255, 0);
	SDL_RenderFillRect(g->main_win->sdl_renderer, NULL);
	SDL_SetRenderTarget(g->main_win->sdl_renderer, NULL);
	return (1);
}

static int	clear_all_layers(t_ui_main *main, void *el_v)
{
	SDL_Texture	*t;
	t_list		*l;
	t_guimp		*g;

	g = (t_guimp *)(main->data);
	(void)el_v;
	l = g->layers.layers;
	while (l)
	{
		t = (t_texture *)l->content;
		SDL_SetRenderTarget(g->main_win->sdl_renderer, t);
		SDL_SetRenderDrawBlendMode(g->main_win->sdl_renderer, SDL_BLENDMODE_NONE);
		SDL_SetRenderDrawColor(g->main_win->sdl_renderer, 255, 255, 255, 0);
		SDL_RenderFillRect(g->main_win->sdl_renderer, NULL);
		l = l->next;
	}
	SDL_SetRenderTarget(g->main_win->sdl_renderer, NULL);
	return (1);
}

static int	test_add_layer(t_ui_main *m, void *el_v)
{
	t_ui_el		*el;
	t_ui_el		*tmp2;
	t_ui_el		*layer_menu;
	t_ui_el		*tmp_el;
	t_guimp		*g;

	el = (t_ui_el *)el_v;
	g = (t_guimp *)m->data;
	layer_menu = ui_win_find_el_by_id(g->main_win, GM_LAYER_ID_MENU);
	if (!(tmp_el = ui_el_init()))
	{
		printf("layer malloc error in scrollable menu in layer_win\n");
		return (1);
	}
	ui_el_setup_default(tmp_el);
	ui_el_setup_default_scroll_menu_elem(tmp_el);
	ui_el_add_child(layer_menu, tmp_el);
	tmp_el->id = gm_generate_surf_id(ID_GENERATOR_ADD);
	ui_el_set_new_pos(tmp_el, 0, 0,
		(t_fvec2){0.0,
			((t_ui_el *)layer_menu->children->content)->rrect.y + 0.25f * (float)gm_generator_get_surf_count()});// * layer_menu->crect.x / g->main_win->size.y * (float)gm_generator_get_surf_count()});
	ui_el_set_size(tmp_el, 0, (t_fvec2){1, 0.25});
	tmp_el->sdl_renderer = g->main_win->sdl_renderer;
	ui_el_add_color_texture(tmp_el, (t_vec2){1704, 800}, 0x888888, "default");
	ui_el_add_color_texture(tmp_el, (t_vec2){1704, 800}, 0xFF5050, "onActive");
	ui_el_add_color_texture(tmp_el, (t_vec2){1704, 800}, 0x5050FF, "onFocus");
	ui_event_add_listener(tmp_el->events->onPointerLeftButtonPressed, testOnPtrLBD);
	ui_event_add_listener(tmp_el->events->onPointerEnter, testOnPtrEnter);
	ui_event_add_listener(tmp_el->events->onPointerLeftButtonPressed, PressedLBD);
	ui_event_add_listener(tmp_el->events->onPointerExit, testOnPtrExit);

	if (!(el = ui_el_init()))
	{
		printf("layer texture malloc error in scrollable menu in layer_win\n");
		return (1);
	}
	ui_el_setup_default(el);
	ui_el_add_child(tmp_el, el);
	ui_el_set_pos(el, 0, (t_fvec2){0.04, 0.05});
	ui_el_set_size(el, 0, (t_fvec2){0.92, 0.782});
	el->id = tmp_el->id * 1000;
	el->params |= EL_IGNOR_RAYCAST | EL_IS_DEPENDENT;
	el->sdl_renderer = g->main_win->sdl_renderer;
	ui_el_add_empty_texture(el, GM_IMAGE_SIZE_X, GM_IMAGE_SIZE_Y, "default");

	t_list	*tmp;
	tmp = ft_lstnew(NULL, 0);
	tmp->content = el->sdl_textures->content;
	tmp->content_size = tmp_el->id;
	ft_lstadd_back(&(g->layers.layers), tmp);

	tmp2 = el;

	if (!(el = ui_el_init()))
	{
		printf("layer texture malloc error in scrollable menu in layer_win\n");
		return (1);
	}

	ui_el_setup_default(el);
	el->params |= EL_IS_DEPENDENT;
	ui_el_add_child(tmp_el, el);
	ui_el_set_pos(el, 0, (t_fvec2){0.04, 0.85});
	ui_el_set_size(el, 0, (t_fvec2){0.45, 0.1});
	el->id = tmp_el->id * 1000 + 1;
	ui_el_add_color_texture(el, (t_vec2){GM_IMAGE_SIZE_X, GM_IMAGE_SIZE_Y}, 0x00FF00, "default");
	ui_event_add_listener(el->events->onPointerLeftButtonPressed, clear_layer);
	el->data = ui_el_get_texture_by_id(tmp2, "default");

	if (!(el = ui_el_init()))
	{
		printf("layer texture malloc error in scrollable menu in layer_win\n");
		return (1);
	}

	ui_el_setup_default(el);
	el->params |= EL_IS_DEPENDENT;
	ui_el_add_child(tmp_el, el);
	ui_el_set_pos(el, 0, (t_fvec2){0.51, 0.85});
	ui_el_set_size(el, 0, (t_fvec2){0.45, 0.1});
	el->id = tmp_el->id * 1000 + 2;
	ui_el_add_white_texture(el, GM_IMAGE_SIZE_X, GM_IMAGE_SIZE_Y, "default");
	el->data = ui_el_get_texture_by_id(tmp2, "default");
	ui_event_add_listener(el->events->onPointerLeftButtonPressed, clear_layer);
	return (1);
}

static int	test_del_layer(t_ui_main *main, void *el_v)
{
	t_guimp	*g;
	t_ui_el	*el;
	t_ui_el	*next_active;
	t_list	*tmp;
	t_list	*prev;

	g = (t_guimp *)(main->data);
	el = g->layers.current_layer->parent;
	(void)el_v;
	if (gm_generator_get_surf_count() == 0 || el->id == GM_LAYER_ID_DEF_LAYER)
		return (1);
	if (!(next_active = ui_win_find_el_by_id(g->main_win, el->id + 1)))
		next_active = ui_win_find_el_by_id(g->main_win, el->id - 1);
	ui_el_set_current_texture_by_id(next_active, "onActive");
	g->layers.current_layer = (t_ui_el *)(next_active->children->content);
	tmp = el->parent->children;
	prev = tmp;
	t_list *tmp2;
	while (tmp)
	{
		next_active = (t_ui_el *)(tmp->content);
		if (next_active->id == el->id)
		{
			ui_el_destroy(next_active);
			tmp2 = tmp;
			prev->next = tmp->next;
			free(tmp2);
		}
		else if (next_active->id > el->id)
		{
			next_active->id--;
			ui_el_change_pos(next_active, 0, 0, (t_fvec2){0, -0.25f});
		}
		prev = tmp;
		tmp = tmp->next;
	}

	tmp = g->layers.layers;
	prev = tmp;
	while (tmp)
	{
		if ((Uint32)(tmp->content_size) == el->id)
		{
			SDL_DestroyTexture(tmp->content);
			tmp2 = tmp;
			prev->next = tmp->next;
			tmp = tmp->next;
			free(tmp2);
			continue ;
		}
		else if ((Uint32)(tmp->content_size) > el->id)
			tmp->content_size--;
		prev = tmp;
		tmp = tmp->next;
	}

	//del el
	//del texture
	gm_generate_surf_id(ID_GENERATOR_DEL);
	return (1);
}

static int	ui_save_test(t_ui_main *main, void *el_v)
{
	t_guimp		*g;
	t_texture	*t;

	g = (t_guimp *)(main->data);
	(void)el_v;
	t = ui_main_merge_layers(g->main_win->sdl_renderer, g->layers.layers);
	ui_main_save_texture(g->main_win, t, "/Users/sbednar/Desktop/test.jpg", IMG_TYPE_JPG);
	return (1);
}

static int	ui_open_test(t_ui_main *main, void *el_v)
{
	t_guimp		*g;

	g = (t_guimp *)(((t_ui_main *)main)->data);
	(void)el_v;
	ui_main_open_texture(g->main_win->sdl_renderer, g->layers.current_layer, "/Users/sbednar/Desktop/test.png");
	return (1);
}

static int	draw_canvas_renderer(t_ui_main *main, void *el_v)
{
	t_guimp	*g;
	t_ui_el	*el;
	t_list	*layer;
	int		tmp_flag;

	g = (t_guimp *)(main->data);
	el = (t_ui_el *)el_v;
	layer = g->layers.layers;
	tmp_flag = 1;
	process_tmp_layer(g);
	while (layer)
	{
		SDL_RenderCopy(el->sdl_renderer, (t_texture *)(layer->content), &g->zoom_rect, &el->rect);
		if (tmp_flag && layer->content_size == g->layers.current_layer->parent->id)
		{
			tmp_flag = 0;
			SDL_RenderCopy(el->sdl_renderer, g->layers.tmp_texture, &g->zoom_rect, &el->rect);
		}
		layer = layer->next;
	}
	return (1);
}

static int	start_draw_with_selected_tool(t_ui_main *main, void *el_v)
{
	t_guimp	*g;
	t_ui_el	*el;
	int		x;
	int		y;

	g = (t_guimp *)(main->data);
	el = (t_ui_el *)el_v;
	x = ((float)el->ptr_rel_pos.x / (float)el->rect.w) * g->zoom_rect.w + g->zoom_rect.x;
	y = ((float)el->ptr_rel_pos.y / (float)el->rect.h) * g->zoom_rect.h + g->zoom_rect.y;
	if ((g->draw_tool.tool < (GM_TOOL_LINE)) || (g->draw_tool.state == GM_TOOL_STATE_NONE && g->draw_tool.tool >= (GM_TOOL_LINE)))
		g->draw_tool.prew_point = (t_vec2){x, y};
	if (g->draw_tool.tool == GM_TOOL_ZOOM && g->draw_tool.zoom < GM_ZOOM_MAX_SIZE)
		tool_zoom_in(g, x, y);
	if (g->draw_tool.tool >= (GM_TOOL_LINE))
	{
		// printf("from start_draw_with_selected_tool in>>>>>>>>> %d\n", g->draw_tool.state);
		if (g->draw_tool.state == GM_TOOL_STATE_DRAW)
			g->draw_tool.state = GM_TOOL_STATE_END;
		else if (g->draw_tool.state == GM_TOOL_STATE_NONE)
			g->draw_tool.state = GM_TOOL_STATE_START;
	}
	if (g->draw_tool.tool == GM_TOOL_FILL)
	{
		Uint32 color1 = (g->draw_tool.r << 16) + (g->draw_tool.g << 8) + g->draw_tool.b;
		Uint32 color2 = ui_util_get_pixel_color_from_texture(el->sdl_renderer,
			(t_texture *)g->layers.current_layer->sdl_textures->content,
			(t_vec2){x, y});
		if (color1 != color2)
			tool_filler(g->main_win,
				(t_texture *)g->layers.current_layer->sdl_textures->content,
				(t_cvec2){color1, color2},
				(t_vec2){(int)(x * 1.0f / GM_IMAGE_SIZE_X * g->main_win->size.x), (int)(y * 1.0f / GM_IMAGE_SIZE_Y * g->main_win->size.y)});
	}
	return (1);
}

void	update_color_rect(t_guimp *gm, int r, int g, int b)
{
	t_ui_el	*el;

	el = ui_win_find_el_by_id(gm->tool_win, GM_TOOL_ID_COLOR_RECT);
	SDL_Texture *t = (SDL_Texture *)el->sdl_textures->content;
	SDL_DestroyTexture(t);
	free(el->sdl_textures);
	el->sdl_textures = NULL;
	ui_el_add_color_texture(el, (t_vec2){100, 20}, (r << 16) | (g << 8) | b, "default");
//	el = ui_win_find_el_by_id(gm->tool_win, GM_TOOL_ID_COLOR_TEXT);
}

static int	scan_tool_position(t_ui_main *main, void *el_v)
{
	t_guimp	*g;
	t_ui_el	*el;
	int		x;
	int		y;

	g = (t_guimp *)(main->data);
	el = (t_ui_el *)el_v;
	x = ((float)el->ptr_rel_pos.x / (float)el->rect.w) * g->zoom_rect.w + g->zoom_rect.x;
	y = ((float)el->ptr_rel_pos.y / (float)el->rect.h) * g->zoom_rect.h + g->zoom_rect.y;
	g->draw_tool.cur_point = (t_vec2){x, y};
	// printf(">>>>>>>>>>>>>>%d>>>>>>>>>>>>>>%d\n", g->draw_tool.cur_point.x, g->draw_tool.cur_point.y);
	return (1);
}

static int	start_draw_with_selected_tool_pointer_up(t_ui_main *main, void *el_v)
{
	t_guimp	*g;

	g = (t_guimp *)(main->data);
	(void)el_v;
	// printf("from start_draw_with_selected_tool_pointer_up in>>>>>>>>> %d\n", g->draw_tool.state);
	if (g->draw_tool.tool >= GM_TOOL_LINE)
		if (g->draw_tool.state == GM_TOOL_STATE_START)
			g->draw_tool.state = GM_TOOL_STATE_DRAW;
	// printf("from start_draw_with_selected_tool_pointer_up out>>>>>>>>> %d\n", g->draw_tool.state);
	return (1);
}

static int	start_alt_with_selected_tool(t_ui_main *main, void *el_v)
{
	t_guimp	*g;
	t_ui_el	*el;
	int		x;
	int		y;

	g = (t_guimp *)(main->data);
	el = (t_ui_el *)el_v;
	x = ((float)el->ptr_rel_pos.x / (float)el->rect.w) * g->zoom_rect.w + g->zoom_rect.x;
	y = ((float)el->ptr_rel_pos.y / (float)el->rect.h) * g->zoom_rect.h + g->zoom_rect.y;
	g->draw_tool.prew_point = (t_vec2){x, y};
	if (g->draw_tool.tool == GM_TOOL_ZOOM && g->draw_tool.zoom > 1)
		tool_zoom_out(g, x, y);
	return (1);
}

//static void	choose_color(void *main, void *el_v)
//{
//	t_guimp	*g;
//	t_ui_el	*el;
//	t_ui_el	*chil;
//	int		res;
//	int		max;
//
//	g = (t_guimp *)(((t_ui_main *)main)->data);
//	el = (t_ui_el *)el_v;
//	chil = ((t_ui_el *)el->children->content);
//	max = (el->id == GM_TOOL_ID_SL_HEAD_SZ) ? GM_BRUSH_MAX_SIZE : 255;
//	res = el->ptr_rel_pos.x - chil->rect.w / 2;
//	ui_el_set_new_pos(chil, 0, PIXEL, (t_fvec2){res, 0});
//	res = ((float)(el->ptr_rel_pos.x) / (float)el->rect.w) * (float)max;
//	if (chil->id == GM_TOOL_ID_SL_HEAD_RED)
//		g->draw_tool.r = res;
//	else if (chil->id == GM_TOOL_ID_SL_HEAD_GR)
//		g->draw_tool.g = res;
//	else if (chil->id == GM_TOOL_ID_SL_HEAD_BL)
//		g->draw_tool.b = res;
//	else if (chil->id == GM_TOOL_ID_SL_HEAD_SZ)
//		g->draw_tool.brush_size = res;
//}

static int	move_draw_canvas_with_zoom(t_ui_main *main, void *el_v)
{
	t_guimp	*g;
	t_ui_el	*el;
	float	x;
	float	y;

	g = (t_guimp *)(main->data);
	el = (t_ui_el *)el_v;
	x = 0;
	y = 0;
	if (g->draw_tool.tool == GM_TOOL_ZOOM)
	{
		if (el->ptr_rel_pos.x > el->rect.w * (1.0 - GM_ZOOM_MOVE_ZONE))
			x = ((float)el->ptr_rel_pos.x / (float)el->rect.w - (1.0 - GM_ZOOM_MOVE_ZONE)) / (GM_ZOOM_MOVE_ZONE);
		if (el->ptr_rel_pos.x < el->rect.w * GM_ZOOM_MOVE_ZONE)
			x = -(GM_ZOOM_MOVE_ZONE - (float)el->ptr_rel_pos.x / (float)el->rect.w) / GM_ZOOM_MOVE_ZONE;
		if (el->ptr_rel_pos.y > el->rect.h * (1.0 - GM_ZOOM_MOVE_ZONE))
			y = ((float)el->ptr_rel_pos.y / (float)el->rect.h - (1.0 - GM_ZOOM_MOVE_ZONE)) / (GM_ZOOM_MOVE_ZONE);
		if (el->ptr_rel_pos.y < el->rect.h * GM_ZOOM_MOVE_ZONE)
			y = -(GM_ZOOM_MOVE_ZONE - (float)el->ptr_rel_pos.y / (float)el->rect.h) / GM_ZOOM_MOVE_ZONE;
		g->zoom_rect.x += x * (GM_ZOOM_MOVE_SPEED / g->draw_tool.zoom);
		g->zoom_rect.y += y * (GM_ZOOM_MOVE_SPEED / g->draw_tool.zoom);
		g->zoom_rect.x = g->zoom_rect.x < 0 ? 0 : g->zoom_rect.x;
		g->zoom_rect.x = g->zoom_rect.x + g->zoom_rect.w > GM_IMAGE_SIZE_X ? GM_IMAGE_SIZE_X - g->zoom_rect.w : g->zoom_rect.x;
		g->zoom_rect.y = g->zoom_rect.y < 0 ? 0 : g->zoom_rect.y;
		g->zoom_rect.y = g->zoom_rect.y + g->zoom_rect.h > GM_IMAGE_SIZE_Y ? GM_IMAGE_SIZE_Y - g->zoom_rect.h : g->zoom_rect.y;
	}
	return (1);
}

static int	draw_color_rect(t_ui_main *main, void *el_v)
{
	t_guimp	*g;
	t_ui_el	*el;

	g = (t_guimp *)(main->data);
	el = (t_ui_el *)el_v;
	SDL_SetRenderTarget(el->sdl_renderer, ui_el_get_current_texture(el));
	SDL_SetRenderDrawColor(el->sdl_renderer, g->draw_tool.r, g->draw_tool.g, g->draw_tool.b, 255);
	SDL_RenderFillRect(el->sdl_renderer, NULL);
	SDL_SetRenderTarget(el->sdl_renderer, NULL);
	SDL_RenderCopy(el->sdl_renderer, ui_el_get_current_texture(el), NULL, &el->rect);
	return (1);
}

static void	ft_strjoin_free(char **to, char *what)
{
	char	*tmp;

	tmp = *to;
	*to = ft_strjoin(*to, what);
	free(tmp);
	free(what);
}

static int text_test(t_ui_main *m, void *a)
{
	t_ui_el	*el;
	t_ui_el	*dr;

	(void)m;
	el = (t_ui_el *)a;
	dr = (t_ui_el *)el->data;
	if (dr->params & EL_IS_PTR_INSIDE)
	{
		char *res = ft_strdup("(");
		ft_strjoin_free(&res, ft_itoa(dr->ptr_rel_pos.x));
		ft_strjoin_free(&res, ft_strdup(";"));
		ft_strjoin_free(&res, ft_itoa(dr->ptr_rel_pos.y));
		ft_strjoin_free(&res, ft_strdup(")"));
		ui_el_update_text(el, res);
		free(res);
	}
	else
		ui_el_update_text(el, " ");
	return (1);
}

int		main()
{
	t_guimp	g_main;

	ui_sdl_init();
	gm_init(&g_main);
	if (!(g_main.ui_main = ui_main_init()))
	{
		printf("ui_main malloc error in struct g_main\n");
		return (0);
	}
	ui_main_fill_default_surfaces(g_main.ui_main);
	ui_main_fill_default_functions(g_main.ui_main);
	ui_main_add_function_by_id(g_main.ui_main, ui_el_event_show_child, "ui_el_event_show_child");
	ui_main_add_function_by_id(g_main.ui_main, ui_el_event_default_draw, "ui_el_event_default_draw");
	ui_main_add_function_by_id(g_main.ui_main, draw_canvas_renderer, "draw_canvas_renderer");
	ui_main_add_function_by_id(g_main.ui_main, draw_with_selected_tool, "draw_with_selected_tool");
	ui_main_add_function_by_id(g_main.ui_main, start_draw_with_selected_tool, "start_draw_with_selected_tool");
	ui_main_add_function_by_id(g_main.ui_main, start_alt_with_selected_tool, "start_alt_with_selected_tool");
	ui_main_add_function_by_id(g_main.ui_main, move_draw_canvas_with_zoom, "move_draw_canvas_with_zoom");
	ui_main_add_function_by_id(g_main.ui_main, testOnPtrLBD, "testOnPtrLBD");
	ui_main_add_function_by_id(g_main.ui_main, PressedLBD, "PressedLBD");
	ui_main_add_function_by_id(g_main.ui_main, testOnPtrEnter, "testOnPtrEnter");
	ui_main_add_function_by_id(g_main.ui_main, testOnPtrExit, "testOnPtrExit");
	ui_main_add_function_by_id(g_main.ui_main, ui_el_event_set_default_texture, "ui_el_event_set_default_texture");
	ui_main_add_function_by_id(g_main.ui_main, ui_el_event_set_focused_texture, "ui_el_event_set_focused_texture");
	ui_main_add_function_by_id(g_main.ui_main, ui_el_event_set_active_texture, "ui_el_event_set_active_texture");
	ui_main_add_function_by_id(g_main.ui_main, ui_el_event_children_set_default, "ui_el_event_children_set_default");
	ui_main_add_function_by_id(g_main.ui_main, test_add_layer, "test_add_layer");
	ui_main_add_function_by_id(g_main.ui_main, test_del_layer, "test_del_layer");
	ui_main_add_function_by_id(g_main.ui_main, draw_color_rect, "draw_color_rect");
	ui_main_add_function_by_id(g_main.ui_main, scan_tool_position, "scan_tool_position");

	ui_main_add_function_by_id(g_main.ui_main, set_brush_texture_from_el, "set_brush_texture_from_el");
	ui_main_add_function_by_id(g_main.ui_main, switch_fill_mode, "switch_fill_mode");


	ui_main_add_function_by_id(g_main.ui_main, ui_save_test, "ui_save_test");
	ui_main_add_function_by_id(g_main.ui_main, ui_open_test, "ui_open_test");
	ui_main_add_function_by_id(g_main.ui_main, start_draw_with_selected_tool_pointer_up, "start_draw_with_selected_tool_pointer_up");
	ui_main_fill_default_fonts(g_main.ui_main);
	ui_main_set_font_params(g_main.ui_main, "Neco", (t_font_params){0, 0, 1, 0});
	g_main.ui_main->data = (void *)(&g_main);
	g_main.draw_tool.brush_size = GM_BRUSH_DEF_SIZE;
	g_main.draw_tool.tool_mode = GM_TOOL_MODE_EMPTY;
	g_main.draw_tool.a = 255;
	g_main.draw_tool.zoom = 1;
	g_main.draw_tool.state = GM_TOOL_STATE_NONE;
	g_main.draw_tool.tool = GM_TOOL_BRUSH;
	g_main.zoom_rect.x = 0;
	g_main.zoom_rect.y = 0;
	g_main.zoom_rect.w = GM_IMAGE_SIZE_X;
	g_main.zoom_rect.h = GM_IMAGE_SIZE_Y;

	if (ui_jtoc_main_from_json(g_main.ui_main, "./json/main_new.json"))
		return (0);

	 g_main.main_win = ui_main_find_window_by_id(g_main.ui_main, 0);
	 g_main.tool_win = ui_main_find_window_by_id(g_main.ui_main, 1);
	SDL_RaiseWindow(g_main.main_win->sdl_window);   //TODO SDL FUNCTIONS FORBIDDEN


	t_ui_el	*cur_el;
//	cur_el = ui_win_find_el_by_id((t_ui_win *)g_main.ui_main->windows->content, 30);


	cur_el = ui_win_find_el_by_id(g_main.main_win, 3);

	g_main.layers.tmp_texture = ui_el_get_texture_by_id(cur_el, "tmp_layer");

	cur_el = ui_win_find_el_by_id(g_main.main_win, 63000);
	g_main.layers.current_layer = cur_el;
	t_list	*tmp;
	tmp = ft_lstnew(NULL, 0);
	tmp->content = cur_el->sdl_textures->content;
	tmp->content_size = 63;
	ft_lstadd(&(g_main.layers.layers), tmp);

 	cur_el = ui_win_find_el_by_id(g_main.tool_win, 31);
	cur_el->data = ui_win_find_el_by_id(g_main.main_win, GM_MAIN_ID_DRAW);
	ui_event_add_listener(cur_el->events->onRender, text_test);

	cur_el = ui_win_find_el_by_id(g_main.tool_win, 32);
	ui_event_add_listener(cur_el->events->onPointerLeftButtonPressed, clear_all_layers);

	cur_el = ui_win_find_el_by_id(g_main.main_win, 63001);
	ui_event_add_listener(cur_el->events->onPointerLeftButtonPressed, clear_layer);
	cur_el->data = ui_el_get_texture_by_id(ui_win_find_el_by_id(g_main.main_win, 63000), "default");

	cur_el = ui_win_find_el_by_id(g_main.tool_win, 1000);
	cur_el->data = ui_el_get_texture_by_id(
			ui_win_find_el_by_id(g_main.main_win, 3), "brush_circle");

	cur_el = ui_win_find_el_by_id(g_main.tool_win, 1001);
	cur_el->data = ui_el_get_texture_by_id(
			ui_win_find_el_by_id(g_main.main_win, 3), "brush_rect");

	cur_el = ui_win_find_el_by_id(g_main.tool_win, 1002);
	cur_el->data = ui_el_get_texture_by_id(
			ui_win_find_el_by_id(g_main.main_win, 3), "brush_cloud");

	cur_el = ui_win_find_el_by_id(g_main.tool_win, 1003);
	cur_el->data = ui_el_get_texture_by_id(
			ui_win_find_el_by_id(g_main.main_win, 3), "brush_star");

    cur_el = ui_win_find_el_by_id(g_main.tool_win, 1004);
    cur_el->data = ui_el_get_texture_by_id(
            ui_win_find_el_by_id(g_main.main_win, 3), "brush_boom");

	cur_el = ui_win_find_el_by_id(g_main.tool_win, 1100);
	cur_el->data = ui_el_get_texture_by_id(
			ui_win_find_el_by_id(g_main.main_win, 3), "sticker_frolov");

//	t_ui_win *w = ui_main_find_window_by_id(g_main.ui_main, 4);
//	t_ui_el *el = ui_el_init();
//	el->id = 100;
//	ui_el_add_child(w->canvas, el);
//	ui_el_set_pos(el, PIXEL, (t_fvec2){10, 10});
//	ui_el_set_size(el, PIXEL, (t_fvec2){100, 100});
//	ui_el_setup_default(el);
//	el->modal_win = w;
//	ui_event_add_listener(el->events->onPointerLeftButtonPressed, ui_el_event_close_window);
//	t_ui_text *t = ui_main_get_font_by_id(g_main.ui_main, "SansSerif");
//	ui_el_set_text(el, t->font,
//				   (t_text_params){(SDL_Color){0, 0, 0, 0}, (SDL_Color){170, 170, 170, 0},
//								   0, TEXT_IS_REGULAR | TEXT_IS_INPUTTING | t->params, TEXT_IS_SOLID});
//	ui_el_update_text(el, "KEEEK");


	//SDL_DisplayMode DM;
	//SDL_GetCurrentDisplayMode(0, &DM);
	//if (DM.w - g_main.tool_win->size.x < g_main.main_win->size.x)
	//{
	//	g_main.tool_win->pos = (t_vec2){0, (DM.h - g_main.tool_win->size.y) / 2};
	//	SDL_SetWindowPosition(g_main.tool_win->sdl_window, g_main.tool_win->pos.x, g_main.tool_win->pos.y);
	//	g_main.main_win->pos = (t_vec2){g_main.tool_win->size.x + 10, g_main.tool_win->pos.y};
	//	SDL_SetWindowPosition(g_main.main_win->sdl_window, g_main.main_win->pos.x, g_main.main_win->pos.y);
	//	int size_x = DM.w - g_main.tool_win->size.x;
	//	g_main.main_win->size = (t_vec2){size_x, size_x / 2.13f};
	//	SDL_SetWindowSize(g_main.main_win->sdl_window, g_main.main_win->size.x, g_main.main_win->size.y);
	//	g_main.main_win->canvas->rect.w = g_main.main_win->size.x;
	//	g_main.main_win->canvas->rect.h = g_main.main_win->size.y;
	//	g_main.main_win->canvas->crect = g_main.main_win->canvas->rect;
	//	bfs_for_resize(g_main.main_win->canvas, &g_main);
	//}

	// ui_set_pixel_color_to_texture(
	// 		g_main.main_win->sdl_renderer,
	// 		(t_texture *)g_main.layers.current_layer->sdl_textures->content,
	// 		(t_vec2){10, 10}, (SDL_Color){0, 0, 255, 155});

//	 cur_el = ui_win_find_el_by_id(g_main.tool_win, 12);
//	 cur_el->sdl_renderer = g_main.tool_win->sdl_renderer;
//	 cur_el->data = (void *)(&(t_cursor){ui_main_get_surface_by_id(g_main.ui_main, "brush"), 100, 100});
//	 ui_event_add_listener(cur_el->events->onPointerLeftButtonPressed, ui_cursor_from_el_data);
//
//	 cur_el = ui_win_find_el_by_id(g_main.tool_win, 14);
//	 ui_event_add_listener(cur_el->events->onPointerLeftButtonPressed, ui_cursor_to_default);
//
//	 ui_el_add_texture_from_file(cur_el, "/home_sbednar/21school/guimp_json/images/bl.png", "default");
//	 ui_el_add_texture_from_file_dialog(cur_el);

	ui_main_run_program(g_main.ui_main);
	return (0);
}
