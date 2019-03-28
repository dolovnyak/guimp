/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edraugr- <edraugr-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 16:09:10 by sbednar           #+#    #+#             */
/*   Updated: 2019/03/28 10:45:13 by edraugr-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "guimp.h"

void	test(t_env *e)
{
	for (int i = 0; i < e->w; i += 6)
	{
		for (int j = 0; j < e->h; j += 6)
		{
			ui_set_pixel(e, i, j, 0xFF00FFFE);
		}
	}
}
void	test2(t_env *e)
{
	for (int i = 0; i < e->w; i += 6)
	{
		for (int j = 0; j < e->h; j += 6)
		{
			ui_set_pixel(e, i, j, 0xFFFF00FF);
		}
	}
}

int		events(t_env *e)
{
	if (e->state[SDL_SCANCODE_ESCAPE])
		ui_exit(e);
	else if (e->sdl.evt.type == SDL_QUIT)
		ui_exit(e);
	return (1);
}

// void	ui_loop22(t_env *e1, t_env *e2)
// {
// 	ui_create_frame(e1);
// 	ui_create_frame(e2);
// 	while (1)
// 	{
// 		if (ui_get_events(e1))
// 			ui_create_frame(e1);if (ui_get_events(e1))
// 			ui_create_frame(e1);
// 	}
// }

int	ui_perframe(void *ev)
{
	t_env	*e;

	e = (t_env *)ev;
	ui_create_frame(e);
	if (e->events)
		ui_create_frame(e);
	return (0);
}

int		main(int argc, char *argv[])
{
	// (void)argc;
	// (void)argv;
	// t_env	e1;
	// t_env	e2;


    // SDL_Thread *thread1;
	// SDL_Thread *thread2;
    // int         threadReturnValue1;
    // int         threadReturnValue2;
	// int			i_events1;
	// int			i_events2;

	// ft_putchar('a');
	// ui_create_env(&e1, WIN_W, WIN_H);
	// ui_create_win(&e1, "kek1");

	// ui_create_env(&e2, 400, 300);
	// ui_create_win(&e2, "kek2");

	// e1.event = &events;
	// e1.frame = &test;

	// e2.event = &events;
	// e2.frame = &test2;

	// SDL_SetWindowResizable(e1.sdl.win, 1);
	// SDL_SetWindowResizable(e2.sdl.win, 1);
	// while (1)
	// {
	// 	i_events1 = ui_get_events(&e1);
	// 	i_events2 = ui_get_events(&e2);
	// 	e1.events = i_events1;
	// 	e2.events = i_events2;

	// 	thread1 = SDL_CreateThread(ui_perframe, "TestThread1", (void *)&e1);
	// 	thread2 = SDL_CreateThread(ui_perframe, "TestThread2", (void *)&e2);

	// 	SDL_WaitThread(thread1, &threadReturnValue1);
	// 	SDL_WaitThread(thread2, &threadReturnValue2);
	// }
	// exit(EXIT_SUCCESS);

	return (0);
}
