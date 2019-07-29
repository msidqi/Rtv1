/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_plane_functions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msidqi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/17 15:09:59 by msidqi            #+#    #+#             */
/*   Updated: 2019/07/24 18:15:15 by kdaou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libgl.h"
#define MAX_ITER 30

void			ft_init_fractal(t_data *data)
{
	data->set = 'm';
	data->movex = 0;
	data->movey = 0;
	data->zoom = 3;
}

int			mandelbrot_set(double c_x, double c_y)
{
	double	real;
	double	imaginary;
	double	tmpreal;
	int		i;

	i = 0;
	imaginary = 0;
	real = 0;
	while (i < MAX_ITER)
	{
		tmpreal = real * real - imaginary * imaginary + c_x;
		imaginary = 2 * real * imaginary + c_y;
		real = tmpreal;
		if (real * real + imaginary * imaginary > 4)
			return (i);
		i++;
	}
	return (0);
}

int	ft_checkif_in_set(t_data *data, double a, double b)
{
	if (data->set == 'm')
		return (mandelbrot_set(a / data->zoom,b / data->zoom));
	return (0);
}

void	ft_color_change(int *col)
{
	int				tmp;
	unsigned char	*ptr;

	tmp = *col;
	ptr = (unsigned char*)col;
	ptr[0] = 0 * (tmp) / MAX_ITER;
	ptr[1] = 255 * (tmp) / MAX_ITER;
	ptr[2] = 0 * (tmp) / MAX_ITER;
}

/*
** a plane is defined by a normal and a point1.
** if dot product between the vector(point1 - point2)
** and the normal == 0 then that point2 is part of the plane.
** (p1 − p2)⋅n=0
**
** if we assume that a ray and the plane intersects in point2
** ((origin + t * dir) − p2)⋅n = 0
** and calculate t(the distance from the ray's origin and point2)
** we can calculate t for point2.
** t = (p0 − origin)⋅n / (dir⋅n)
*/

int				ft_plane_inter(t_ray *ray, t_plane *plane)
{
	t_vec4	k;
	double	t0;
	double	dot;

	dot = ft_vec4_dot_product(ray->dir, plane->normal);
	if (dot == 0)
		return (0);
	k = ft_vec4_sub(plane->point, ray->origin);
	t0 = ft_vec4_dot_product(k, plane->normal) / dot;
	if (t0 > NEAR && t0 < ray->t)
	{
		ray->t = t0;
		return (1);
	}
	return (0);
}

static t_vec4	ft_get_plane_normal(t_ray *ray, t_plane *pl)
{
	return (ft_vec4_dot_product(ray->dir,
				pl->normal) < 0 ?
			pl->normal : ft_vec4_scalar(pl->normal, -1));
}

unsigned int	ft_plane_shader(t_data *data, t_ray *ray, t_plane *pl)
{
	t_shader_x	sh_x;
	t_list		*l_lst;
	t_vec4		pl_nor;
	t_vec4		ds[2];
	int			c;
	t_vec4		p;

	c = 0;
	sh_x.diff = ft_create_vec4(0.0, 0.0, 0.0, 0.0);
	sh_x.spec = ft_create_vec4(0.0, 0.0, 0.0, 0.0);
	l_lst = data->light_list;
	pl_nor = ft_get_plane_normal(ray, pl);
	ds[0] = pl->diffuse;
	ds[1] = ft_create_vec4(pl->specular, pl->specular,
			pl->specular, pl->specular);
	if (pl->refl.w == 1 && ray->refl_depth > 0)
	{
		ray->refl_depth--;
		return (ft_reflected_ray(data, pl_nor, ray, pl->refl));
	}
	sh_x = ft_ray_inter_lights(data, pl_nor, ray, ds);
	if (pl->refl.w == 2)
	{
		p = ft_vec4_add(ray->origin, ft_vec4_scalar(ray->dir, ray->t));
		/*double t = 1 + (sin(4 * p.x));
		int c = ft_color_add(ft_color_rgb_scalar(0xFF00, (1 - t), (1 - t), (1 - t)), ft_color_rgb_scalar(pl->color, t, t, t));*/
		c = ((((int)(100 * sin(2 * p.x)) ^ (int)(100 * sin(2 * p.z))) > 0)) ? pl->color : 0x0;
		/*ft_init_fractal(data);
		int c;
		c = ft_checkif_in_set(data, p.x + pl->point.x, p.z + pl->point.z);
		ft_color_change(&c);*/
	}
	return (ft_compute_shader(ft_color_add(pl->color, c), &sh_x));
}
