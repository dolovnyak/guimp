/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_event_add.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edraugr- <edraugr-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/27 17:16:15 by sbednar           #+#    #+#             */
/*   Updated: 2019/03/28 14:02:26 by edraugr-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libui.h"

int	ui_event_add(t_ui_event *e, void(*f)(const void *i))
{
	t_list	*node;

	if (e->events == NULL)
	{
		if ((e->events = ft_lstnew(f, sizeof(*f))) == NULL)
			return (1);
		return (0);
	}
	else
	{
		if ((node = ft_lstnew(f, sizeof(*f))) == NULL)
			return (1);
		ft_lstadd_back(&(e->events), node);
		return (0);
	}
}
