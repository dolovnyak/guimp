/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_for_ellipse.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/15 15:43:30 by sbecker           #+#    #+#             */
/*   Updated: 2019/07/15 16:33:41 by sbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "guimp.h"

t_vec2	lerp(t_vec2 p1, t_vec2 p2, float k)
{
	t_vec2	res;

	res.x = p1.x + roundf((float)(p2.x - p1.x) * k);
	res.y = p1.y + roundf((float)(p2.y - p1.y) * k);
	return (res);
}

t_vec2	calc_el_dot(t_vec2 *d, float k)
{
	t_vec2	res;

	res = lerp(
			lerp(
				lerp(d[0], d[1], k),
				lerp(d[1], d[2], k),
				k),
			lerp(
				lerp(d[1], d[2], k),
				lerp(d[2], d[3], k),
				k),
			k);
	return (res);
}
