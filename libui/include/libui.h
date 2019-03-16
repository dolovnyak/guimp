/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libui.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbednar <sbednar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/10 19:09:04 by sbednar           #+#    #+#             */
/*   Updated: 2019/03/16 23:54:59 by sbednar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBUI_H
# define LIBUI_H

# include <SDL2/SDL.h>
# include <SDL2/SDL_ttf.h>
# include <SDL2/SDL_image.h>
# include "libft.h"

# define WIN_W		640
# define WIN_H		480

typedef struct		s_sdl
{
	SDL_Event		*evt;
	SDL_Window		*win;
	SDL_Renderer	*ren;
}					t_sdl;

typedef struct		s_env
{
	int				w;
	int				h;
	int				m_pos[2];
	t_sdl			sdl;
	SDL_Surface		*sur;
	SDL_Texture		*tex;
	Uint8			*state;
}					t_env;

void				ui_create_env(t_env *e, const int w, const int h);
void				ui_create_win(t_env *e, const char *name);
SDL_Surface			*ui_create_sur(const int w, const int h);
void				ui_create_frame(void (*frame)(t_env *e), t_env *e);

int					ui_get_events(int (*event)(t_env *e), t_env *e);

void				ui_set_pixel(t_env *e, const int x, const int y,
const Uint32 c);

void				ui_exit_with_msg(t_env *e, const char *msg);
void				ui_exit(t_env *e);

#endif
