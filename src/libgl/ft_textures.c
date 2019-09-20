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
#ifndef PI
# define PI 3.14159265358979323846
#endif

int		ft_texture_sphere(int id, t_ray *ray, t_sphere *sp)
{
	double phi = 0, theta = 0, u, v;(void)id;

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

int		ft_texture_plane(int id, t_ray *ray, t_plane *pl)
{
	(void)id;
	double	u;
	double	v;
	int		x;
	int		y;
	t_vec4 inter_point;
	
	inter_point = ft_vec4_add(ft_vec4_scalar(ray->dir, ray->t), ray->origin);
	if (inter_point.x > 10 || inter_point.z > 10 || inter_point.x < 0 || inter_point.z < 0)
		return (0x00);
	if (inter_point.x > 10) // repeating texture
		inter_point.x -= 10;
	if (inter_point.z > 10)
		inter_point.z -= 10;
	if (inter_point.x < 0)
		inter_point.x += 10;
	if (inter_point.z < 0)
		inter_point.z += 10;
	u = inter_point.x / 10;
	v = inter_point.z / 10;
	x = u * pl->texture.width;
	y = v * pl->texture.height;
	return (pl->texture.buff[x + y * pl->texture.width]);
}