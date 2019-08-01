/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_triangle_functions.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msidqi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/23 13:24:14 by msidqi            #+#    #+#             */
/*   Updated: 2019/07/23 13:24:15 by msidqi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libgl.h"

int				ft_triangle_inter(t_ray *ray, t_plane *plane)
{
	t_vec4 k;
	double t0;

    // Plane equation Ax+By+Cz+D=0
    // (Nplane=(A,B,C))
    // D = Distance from origin (0, 0, 0) to the plane (groing through a ray
    //                                                   parallel to pl_normal)
    // x y z coords of intersection point

  

	k = ft_vec4_sub(plane->point, ray->origin);
	t0 = ft_vec4_dot_product(k, plane->normal)
		/ ft_vec4_dot_product(ray->dir, plane->normal);
	if (t0 > NEAR && t0 < ray->t)
	{
        // Ix = a * Vertex0.x + b * Vertex1.x + c * Vertex2.x
        // Iy = a * Vertex0.y + b * Vertex1.y + c * Vertex2.y
        // Iz = a * Vertex0.z + b * Vertex1.z + c * Vertex2.z
        // if a b c are all positive, I is inside the tiranlge
        
//        I = t0 * D + O;
		ray->t = t0;
		return (1);
	}
	return (0);
}

static t_vec4	ft_get_triangle_normal(t_ray *ray, t_triangle *tr)
{
	return (ft_vec4_dot_product(ray->dir,
				tr->normal) < 0 ?
			tr->normal : ft_vec4_scalar(tr->normal, -1));
}

unsigned int	ft_triangle_shader(t_data *data, t_ray *ray, t_triangle *tr)
{
	t_shader_x	sh_x;
	t_vec4		tr_nor;
	t_vec4		ds[2];

	sh_x.diff = ft_create_vec4(0.0, 0.0, 0.0, 0.0);
	sh_x.spec = ft_create_vec4(0.0, 0.0, 0.0, 0.0);
	tr_nor = ft_get_triangle_normal(ray, tr);
	ds[0] = tr->diffuse;
	ds[1] = ft_create_vec4(tr->specular, tr->specular,
			tr->specular, tr->specular);
	sh_x = ft_ray_inter_lights(data, tr_nor, ray, ds);
	return (ft_compute_shader(tr->color, &sh_x));
}
