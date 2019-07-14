/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_texture_id.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edraugr- <edraugr-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 04:27:11 by edraugr-          #+#    #+#             */
/*   Updated: 2019/07/09 18:46:25 by edraugr-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libui.h"

int	ctid(t_list_texture *lst, int tid)
{
	while (lst)
	{
		if (lst->content_size == (size_t)tid)
			ui_sdl_deinit(228);
		lst = lst->next;
	}
	return (FUNCTION_SUCCESS);
}