/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   connect.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msidqi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 15:46:27 by msidqi            #+#    #+#             */
/*   Updated: 2019/05/14 15:46:28 by msidqi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libgl.h"

static void		plotLineLow(t_data *data, t_vector2 a, t_vector2 b, int color)
{
	int			D;
	int			dx;
	int			dy;
	int			yi;
    t_vector2	tmp;

	dx = b.x - a.x;
	dy = b.y - a.y;
	yi = 1;
	if (dy < 0)
	{
		yi = -1;
		dy = -dy;
	}
	D = 2*dy - dx;
	tmp.y = a.y;
	tmp.x = a.x;
	while (tmp.x <= b.x)
	{
		ft_image_fill(data, tmp.x, tmp.y, color);
		if (D > 0)
		{
			tmp.y = tmp.y + yi;
			D = D - 2*dx;
		}
		D = D + 2*dy;
		tmp.x++;
	}
}

static void		plotLineHigh(t_data *data, t_vector2 a, t_vector2 b, int color)
{
	int			D;
	int			dx;
	int			dy;
	int			xi;
    t_vector2	tmp;

	dx = b.x - a.x;
	dy = b.y - a.y;
	xi = 1;
	if (dx < 0)
	{
		xi = -1;
		dx = -dx;
	}
	D = 2*dx - dy;
	tmp.x = a.x;
	tmp.y = a.y;
	while (tmp.y <= b.y)
	{
		ft_image_fill(data, tmp.x, tmp.y, color);
		if (D > 0)
		{
			tmp.x = tmp.x + xi;
			D = D - 2*dy;
		}
		D = D + 2*dx;
		tmp.y++;
	}
}

void			connect_dots(t_data *data, t_vector2 a, t_vector2 b, int color)
{
	if (fabs(b.y - a.y) < fabs(b.x - a.x))
	{
		if (a.x > b.x)
			plotLineLow(data, b, a, color);
		else
			plotLineLow(data, a, b, color);
	}
	else
	{
		if (a.y > b.y)
			plotLineHigh(data, b, a, color);
		else
			plotLineHigh(data, a, b, color);
	}
}