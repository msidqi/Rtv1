/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_filters.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msidqi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 21:53:05 by msidqi            #+#    #+#             */
/*   Updated: 2019/09/24 21:53:07 by msidqi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libgl.h"

static void ft_black_white_filter(unsigned char *rgb)//double rgb[2], double rgb[1], double rgb[0])
{
    int avg;

    avg = (int)((rgb[2] + rgb[1] + rgb[0]) / 3);
    rgb[2] = avg;
    rgb[1] = avg;
    rgb[0] = avg;
}

static void ft_negative_filter(unsigned char *rgb)
{
	rgb[2] = 255 - rgb[2];
	rgb[1] = 255 - rgb[1];
	rgb[0] = 255 - rgb[0];
}

static void ft_sepia_filter(unsigned char *rgb)
{
    int tr = (int)(0.393 * rgb[2] + 0.769 * rgb[1] + 0.189 * rgb[0]);
    int tg = (int)(0.349 * rgb[2] + 0.686 * rgb[1] + 0.168 * rgb[0]);
    int tb = (int)(0.272 * rgb[2] + 0.534 * rgb[1] + 0.131 * rgb[0]);
    if(tr > 255)
        rgb[2] = 255;
    else
        rgb[2] = tr;
    if(tg > 255)
        rgb[1] = 255;
    else
        rgb[1] = tg;
    if(tb > 255)
        rgb[0] = 255;
    else
        rgb[0] = tb;
}

void ft_filters(t_data *data, int x, int y, int color)
{
	unsigned char	*ptr;

    if (data->filter == 1)
        ft_negative_filter((unsigned char *)&color);
    else if (data->filter == 2)
        ft_black_white_filter((unsigned char *)&color);
    else if (data->filter == 3)
        ft_sepia_filter((unsigned char *)&color);
	ft_image_fill(data, x, y, color);
}

int ft_filters_aa(t_data *data, int x, int y, int color)
{
	unsigned char	*ptr;(void)x;(void)y;

    if (data->filter == 1)
        ft_negative_filter((unsigned char *)&color);
    else if (data->filter == 2)
        ft_black_white_filter((unsigned char *)&color);
    else if (data->filter == 3)
        ft_sepia_filter((unsigned char *)&color);
    return (color);
}