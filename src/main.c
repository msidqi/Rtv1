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

double		ft_map(int x_or_y, double size, int width_or_height)
{
	return ((x_or_y * size) / width_or_height - (size / 2));
}
void		ft_explane(t_data *data)
{
	int x;
	int y;
	double xm;
	double ym;
	double size = 1;
	// double	fow;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			xm = ft_map(x, size, WIDTH);
			ym = ft_map(y, size, HEIGHT);
			t_vector4 camera_pos = ft_create_vector4(0, 0, -10, 1);
			t_vector4 sub = ft_create_vector4(xm, ym, 0, 1);
			t_ray ray;
			t_vector4 k = ft_vec4_sub(&sub, &camera_pos);
			ray.dir = ft_vec4_normalize(&k);//ft_create_vector4(xm - camera_pos.v[X], ym - camera_pos.v[Y], 0 - camera_pos.v[Z], 0);
			ray.origin = ft_create_vector4(0, 0, -10, 0);
			if (ft_sphere_intersection(&ray))
				ft_image_fill(data, x, y, 0xFF0000);

			// ft_printvector4(&ray);
			// printf("mag == %.14f\n", ft_vec4_magnitude(&ray));
			// printf("x: %d , y: %d | xm: %f , ym: %f\n", x, y, xm, ym);
			// usleep(10000);
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
	// t_vector2	a;
	// t_vector2	b;
	// t_vector2	x_axis;
	// t_vector2	y_axis;

	// vec2_init(&x_axis, 1, 0);
	// vec2_init(&y_axis, 0, 1);
	// vec2_init(&a, 400, 400);
	// vec2_init(&b, 460, 350);
	data.movex = 90;
	j = -1;
	i = -1;
	ft_window_setup(&data, "ReTweet", 800, 800);
	ft_image_setup(&data);
	data.zoom = 1;
	data.worldpos.v[X] = ft_get_world_pos(i, data.winwidth, data.zoom);
	data.worldpos.v[Y] = ft_get_world_pos(i, data.winheight, data.zoom);
	while (++i < data.winwidth)
		ft_image_fill(&data, i , data.winwidth / 2, 0xdd0011);
	while (++j < data.winheight)
		ft_image_fill(&data, data.winheight / 2, j, 0xdd0011);
	
	// connect_dots(&data, a, b, 0x00AA11);
	// a = vec2_rotate_byangle(a, data.movex * M_PI/180);
	// b = vec2_rotate_byangle(b, data.movex * M_PI/180);
	// connect_dots(&data, a, b, 0xAAAA11);

	// x_axis = vec2_rotate_byangle(x_axis, 49 * M_PI/180);
	// y_axis = vec2_rotate_byangle(y_axis, 49 * M_PI/180);
	//printf("x_axis x == %f\nx_axis y == %f\n", x_axis.x,x_axis.y);
	// a = vec2_rotate_byaxis(a, x_axis, y_axis);
	// b = vec2_rotate_byaxis(a, x_axis, y_axis);
	// connect_dots(&data, a, b, 0xAAAA11);

	ft_explane(&data);

	t_matrix4 mat;
	t_matrix4 trans;
	mat = ft_create_matrix4();
	ft_putmatrix4(&mat);
	trans = ft_get_translation_matrix4(10, 10, 10);
	ft_putmatrix4(&trans);
	
	
	t_vector4 vec = ft_create_vector4(10 , 11, 12, 1);
	ft_putvector4(&vec);
	vec = ft_matrix_x_vector(&trans, &vec);
	ft_putvector4(&vec);

/*
	macro up : 1;
	macro down  : 2;
	macro left : 4;
	macro right  : 8;
	(left | up | left | right )
*/



	mlx_put_image_to_window(data.mlx, data.win, data.img_ptr, 0, 0);
	ft_mlx_hooks(&data, false);
	return (0);
}




/*

Vec P(x,y,z,w) , Vec C(5,5,5,1)

|P - C|² = r²
P - C² = r²








*/