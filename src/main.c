/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msidqi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 12:48:35 by msidqi            #+#    #+#             */
/*   Updated: 2019/05/14 12:48:36 by msidqi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libgl.h"

#define HEIGHT 800
#define WIDTH 800
double ft_map(int x, double size)
{
	return ((x * size) / 800 - (size / 2));
}
void ft_explane()
{
	int x;
	int y;
	double xm;
	double ym;
	double size = 1;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			xm = ft_map(x, size);
			ym = ft_map(y, size);
			printf("x: %d , y: %d ,, ,, xm: %f , ym: %f\n", x, y, xm, ym);
			//sleep(1);
			x++;
		}
		y++;
	}
}
int		main(void)
{
	t_data  data;
	int i;
	int j;
	t_vector2	a;
	t_vector2	b;
	t_vector2	x_axis;
	t_vector2	y_axis;

	vec2_init(&x_axis, 1, 0);
	vec2_init(&y_axis, 0, 1);
	vec2_init(&a, 400, 400);
	vec2_init(&b, 460, 350);
	data.movex = 90;
	j = -1;
	i = -1;
	ft_window_setup(&data, "ReTweet", 800, 800);
	ft_image_setup(&data);
	data.zoom = 1;
	ft_explane();
	data.worldpos.x = ft_get_world_pos(i, data.winwidth, data.zoom);
	data.worldpos.y = ft_get_world_pos(i, data.winheight, data.zoom);
	while (++i < data.winwidth)
		ft_image_fill(&data, i , data.winwidth / 2, 0xdd0011);
	while (++j < data.winheight)
		ft_image_fill(&data, data.winheight / 2, j, 0xdd0011);
	
	connect_dots(&data, a, b, 0x00AA11);
	a = vec2_rotate_byangle(a, data.movex * M_PI/180);
	b = vec2_rotate_byangle(b, data.movex * M_PI/180);
	connect_dots(&data, a, b, 0xAAAA11);

	x_axis = vec2_rotate_byangle(x_axis, 49 * M_PI/180);
	y_axis = vec2_rotate_byangle(y_axis, 49 * M_PI/180);
	printf("x_axis x == %f\nx_axis y == %f\n", x_axis.x,x_axis.y);
	a = vec2_rotate_byaxis(a, x_axis, y_axis);
	b = vec2_rotate_byaxis(a, x_axis, y_axis);
	connect_dots(&data, a, b, 0xAAAA11);

	mlx_put_image_to_window(data.mlx, data.win, data.img_ptr, 0, 0);
	ft_mlx_hooks(&data, true);
	return (0);
}