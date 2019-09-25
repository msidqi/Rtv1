/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_textures.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msidqi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/17 15:20:01 by msidqi            #+#    #+#             */
/*   Updated: 2019/07/17 15:21:43 by msidqi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libgl.h"

const char txt_ids[8][20] =
{
	"textures/earth_.xpm",
	"textures/future.xpm",
	"textures/arezok.xpm",
	"textures/logo__.xpm",
	"textures/mario_.xpm",
	"textures/pepe__.xpm",
	"textures/plane_.xpm",
	"textures/wood__.xpm"
};

int ft_load_texture(int id, t_texture *t, t_data *data)
{
	int bpp;
	int size_l;
	int endian;
	if (id < 0 || id > STATIC_ARRAY_SIZE(txt_ids) || 
	!(t->img = mlx_xpm_file_to_image(data->mlx, (char *)txt_ids[id], &t->width, &t->height)))
		return (0);
	t->buff = (int *)mlx_get_data_addr(t->img, &bpp, &size_l, &endian);
	return (1);
}

int		ft_texture_sphere(t_ray *ray, t_sphere *sp)
{
	double phi = 0, theta = 0, u, v;

	t_vec4 X = ft_vec4_sub(sp->center, ft_vec4_add(ft_vec4_scalar(ray->dir, ray->t), ray->origin)); // intersection point relatively to sphere

	phi = atan2(X.z, X.x);				// angle between x axis and X around sphere's latitude
	theta = acos(-(X.y) / sp->radius);	// angle between y axis and X along the longtitude (s pole to n pole)
	u = ((phi + PI) / (2 * PI));	//
	v = 1 - theta / PI;

	if (u < 0)
		u = 0;
	if (v < 0)
		v = 0;
	if (u > 1.0)
		u = 1.0;
	if (v > 1.0)
		v = 1.0;
	int x = u * sp->texture.width;
	int y = v * sp->texture.height;
	return (sp->texture.buff[x + y * sp->texture.width]);
}

int		ft_texture_cylinder(t_ray *ray, t_cylinder *cyl)
{
	double phi = 0, theta = 0, u, v;

	t_vec4 X = ft_vec4_sub(ft_vec4_add(ft_vec4_scalar(ray->dir, ray->t), ray->origin), cyl->point); // intersection point relatively to sphere

	t_vec4 cross = ft_vec4_cross_product(cyl->axis, X);
	u = ft_vec4_dot_product(cross, cyl->left) / cyl->texture.stretch_x;

	v = ft_vec4_dot_product(X, cyl->axis) / cyl->texture.stretch_y;

	int x = (int)(u * (cyl->texture.width - 1));
	int y = (int)(v * (cyl->texture.height - 1));
	if (x >= cyl->texture.width) // repeating texture
		x = x % (cyl->texture.width - 1);
	if (x <= 0)
		x = (cyl->texture.width - 1) - (abs(x) % (cyl->texture.width - 1));
	if (y >= cyl->texture.height)
		y = y % (cyl->texture.height - 1);
	if (y <= 0)
		y = (cyl->texture.height - 1) - (abs(y) % (cyl->texture.height - 1)) ;
	if (x >= cyl->texture.width)
		x = cyl->texture.width - 1;
	if (y >= cyl->texture.height)
		y = cyl->texture.height - 1;
	return (cyl->texture.buff[x + y * cyl->texture.width]);
}

int		ft_texture_cone(t_ray *ray, t_cone *cone)
{
	double phi = 0, theta = 0, u, v;

	t_vec4 X = ft_vec4_sub(ft_vec4_add(ft_vec4_scalar(ray->dir, ray->t), ray->origin), cone->center); // intersection point relatively to sphere

	t_vec4 cross = ft_vec4_cross_product(cone->axis, X);
	u = ft_vec4_dot_product(cross, cone->left) / cone->texture.stretch_x;

	v = ft_vec4_dot_product(X, cone->axis) / cone->texture.stretch_y;

	int x = (int)(u * (cone->texture.width - 1));
	int y = (int)(v * (cone->texture.height - 1));
	if (x >= cone->texture.width) // repeating texture
		x = x % (cone->texture.width - 1);
	if (x <= 0)
		x = (cone->texture.width - 1) - (abs(x) % (cone->texture.width - 1));
	if (y >= cone->texture.height)
		y = y % (cone->texture.height - 1);
	if (y <= 0)
		y = (cone->texture.height - 1) - (abs(y) % (cone->texture.height - 1)) ;
	if (x >= cone->texture.width)
		x = cone->texture.width - 1;
	if (y >= cone->texture.height)
		y = cone->texture.height - 1;
	return (cone->texture.buff[x + y * cone->texture.width]);
}

int		ft_texture_plane(t_ray *ray, t_plane *pl)
{
	double	u;
	double	v;
	int		x;
	int		y;
	t_vec4 inter_point;
	t_vec4 dir;

	inter_point = ft_vec4_add(ft_vec4_scalar(ray->dir, ray->t), ray->origin);
	dir = ft_vec4_sub(inter_point, pl->point);
	u = ft_vec4_dot_product(pl->left, dir) / 10; // bigger division value to stretch texture
	v = ft_vec4_dot_product(pl->forw, dir) / 10;
	x = (int)(u * (pl->texture.width - 1));
	y = (int)(v * (pl->texture.height - 1));
	if (x >= pl->texture.width) // repeating texture
		x = x % (pl->texture.width - 1);
	if (x <= 0)
		x = (pl->texture.width - 1) - (abs(x) % (pl->texture.width - 1));
	if (y >= pl->texture.height)
		y = y % (pl->texture.height - 1);
	if (y <= 0)
		y = (pl->texture.height - 1) - (abs(y) % (pl->texture.height - 1)) ;
	// if (x >= pl->texture.width)
	// 	x = pl->texture.width - 1;
	// if (y >= pl->texture.height)
	// 	y = pl->texture.height - 1;
	return (pl->texture.buff[x + y * (pl->texture.width)]);
}
