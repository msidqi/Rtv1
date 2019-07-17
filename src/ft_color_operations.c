/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_color_operations.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msidqi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/17 15:26:31 by msidqi            #+#    #+#             */
/*   Updated: 2019/07/17 15:28:21 by msidqi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libgl.h"

unsigned	int	ft_color_rgb_scalar(unsigned int color, double r,
		double g, double b)
{
	unsigned char	*ptr;

	ptr = (unsigned char *)&color;
	ptr[0] = (ptr[0] * r) > 255 ? 255 : (ptr[0] * r);
	ptr[1] = (ptr[1] * g) > 255 ? 255 : (ptr[1] * g);
	ptr[2] = (ptr[2] * b) > 255 ? 255 : (ptr[2] * b);
	return (color);
}

int				ft_color_add(unsigned int color1, unsigned int color2)
{
	unsigned int r;
	unsigned int g;
	unsigned int b;

	r = ((color2 >> 16) & 0xff) + ((color1 >> 16) & 0xff);
	g = ((color2 >> 8) & 0xff) + ((color1 >> 8) & 0xff);
	b = (color2 & 0xff) + (color1 & 0xff);
	r = r > 255 ? 255 : r;
	g = g > 255 ? 255 : g;
	b = b > 255 ? 255 : b;
	return ((r << 16) | (g << 8) | b);
}
