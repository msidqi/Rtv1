/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sphere_functions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msidqi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/17 15:20:01 by msidqi            #+#    #+#             */
/*   Updated: 2019/07/17 15:21:43 by msidqi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libgl.h"

/*static void			ft_init_fractal(t_data *data)
{
	data->set = 'm';
	data->movex = 0;
	data->movey = 0;
	data->zoom = 20;
	data->max_iter = MAX_ITER;
	data->color.red = 0;
	data->color.green = 255;
	data->color.blue = 222;
}

static int			mandelbrot_set(t_data *data, double c_x, double c_y)
{
	double	real;
	double	imaginary;
	double	tmpreal;
	int		i;

	i = 0;
	imaginary = 0;
	real = 0;
	while (i < data->max_iter)
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

static int	ft_checkif_in_set(t_data *data, double a, double b)
{
	if (data->set == 'm')
		return (mandelbrot_set(data, a / data->zoom,b / data->zoom));
	return (0);
}

static void	ft_color_change(int *col, t_data *data)
{
	int				tmp;
	unsigned char	*ptr;

	tmp = *col;
	ptr = (unsigned char*)col;
	ptr[0] = data->color.blue * (tmp) / MAX_ITER;
	ptr[1] = data->color.green * (tmp) / MAX_ITER;
	ptr[2] = data->color.red * (tmp) / MAX_ITER;
}*/

/*
** a=dot(B,B)
** b=2⋅dot(B,A−C)
** c=dot(A−C,A−C)−r2
** With the above parameterization, the quadratic formula is:
** t = (−b±b2−4ac) / (√2a)
*/

int				ft_sphere_inter(t_ray *ray, t_sphere *sp)
{
	double t[2];
	double discr;
	double abc[3];
	t_vec4 k;

	k = ft_vec4_sub(ray->origin, sp->center);
	abc[0] = ft_vec4_dot_product(ray->dir, ray->dir);
	abc[1] = 2 * ft_vec4_dot_product(ray->dir, k);
	abc[2] = ft_vec4_dot_product(k, k) - sp->radius * sp->radius;
	discr = abc[1] * abc[1] - 4 * abc[0] * abc[2];
	if (discr < 0)
		return (0);
	t[0] = (-abc[1] + sqrt(discr)) / (2 * abc[0]);
	t[1] = (-abc[1] - sqrt(discr)) / (2 * abc[0]);
	t[0] = t[0] < t[1] && t[0] > NEAR ? t[0] : t[1];
	if (t[0] > NEAR && t[0] < ray->t)
	{//if (sp->ref == 1)printf("%f\n", t[0]);
		ray->t = t[0];
		return (1);
	}
	return (0);
}

/*
** called foreach pixel
**	foreach light
**	get r_light and normal_sphere(calculate once)
**	check intersection with all objects,
** 		if : (hidden from light source by an obj) then :(its spec/diffuse += 0)
**	else : computed specular,
**		diffuse (light pixel, if : distance to light < (distance to obj == t))
**	ADD to return value
**
**	after foreach loop, add ambient
*/

static t_vec4	ft_get_sphere_normal(t_ray *ray, t_sphere *sp)
{
	return (ft_vec4_normalize(
		ft_vec4_sub(ft_vec4_add(ray->origin,
			ft_vec4_scalar(ray->dir, ray->t)), sp->center)));
}


int	ft_sphere_shader(t_data *data, t_ray *ray, t_sphere *sp)
{
	t_shader_x	sh_x;
	t_vec4		sp_nor;
	t_vec4		ds[2];
	int			c;

	c = 0x0;
	sp_nor = ft_get_sphere_normal(ray, sp);
	ds[0] = sp->diffuse;
	ds[1] = ft_create_vec4(sp->specular, sp->specular,
			sp->specular, sp->specular);
	if (sp->ref.w == 1 && ray->refl_depth > 0)
	{
		ray->refl_depth--;
		c = ft_reflected_ray(data, sp_nor, ray, sp->ref);
		if (false) // 100% reflectant, and no shading
			return (c);
	}
	if (sp->ref.w == 2)
		c = ft_refracted_ray(data, sp_nor, ray, sp->ref);
	sh_x = ft_ray_inter_lights(data, sp_nor, ray, ds);
	if (sp->texture.id > -1)
		return (ft_compute_shader(ft_texture_sphere(ray, sp), &sh_x));

	/*t_vec4 p = ft_vec4_add(ray->origin, ft_vec4_scalar(ray->dir, ray->t));
	// double t = 1 + (sin(20 * p.y) / 2);
	// int c = ft_color_add(ft_color_rgb_scalar(0x0, (1 - t), (1 - t), (1 - t)), ft_color_rgb_scalar(sp->color, t, t, t));
	ft_init_fractal(data);
	int c;
	c = ft_checkif_in_set(data, p.x + sp->center.x, p.z + sp->center.z);
	ft_color_change(&c, data);
	return (ft_compute_shader(ft_color_add(sp->color, c), &sh_x));*/
	// printf("compute\n");
	return (ft_compute_shader(ft_color_add(sp->color, c), &sh_x));
}
