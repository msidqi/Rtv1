/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_reflected_ray.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msidqi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/17 15:23:03 by msidqi            #+#    #+#             */
/*   Updated: 2019/07/17 16:42:57 by msidqi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libgl.h"

const t_obj_function g_t_obj_functions[4] =
{
	{SPHERE, &ft_sphere_inter, &ft_sphere_shader},
	{PLANE, &ft_plane_inter, &ft_plane_shader},
	{CONE, &ft_cone_inter, &ft_cone_shader},
	{CYLINDER, &ft_cylinder_inter, &ft_cylinder_shader}
};

/*
** 3-loop to see if ray is blocked by any another
** 							object in scene, towards light source.
*/

double				ft_ray_inter_objs(t_list *list, t_ray *sh_ray,
		double distance_to_light, t_light *li)
{
	t_list			*scene;
	unsigned int 	i;

	scene = list;
	while (scene != NULL)
	{
		sh_ray->t = FAR;
		i = -1;
		while (++i < (unsigned int)STATIC_ARRAY_SIZE(g_t_obj_functions))
		{
			if (g_t_obj_functions[i].type == scene->content_size &&
					g_t_obj_functions[i].call(sh_ray, scene->content) &&
					distance_to_light > ft_vec4_mag(ft_vec4_scalar(sh_ray->dir, sh_ray->t))){
				return (0);
				}
		}
		scene = scene->next;
	}
	return (ft_light_intensity(list, li, &sh_ray->origin, &sh_ray->dir)); // ray reached the light
}

int ft_reflected_ray(t_data *data, t_vec4 nr, t_ray *ray, t_vec4 refl)
{
	unsigned int	i;
	t_list			*s;
	int	color;
	t_ray			refl_ray;

	color = 0x222222;
	refl_ray.origin = ft_vec4_add(ft_vec4_scalar(ray->dir, ray->t), ray->origin);
	// r = -2 * (V.N) * N + V;
	refl_ray.dir = ft_vec4_normalize(ft_vec4_add(ft_vec4_scalar(nr, -2 * ft_vec4_dot_product(ray->dir, nr)), ray->dir));
	refl_ray.t = FAR;
	refl_ray.refl_depth = ray->refl_depth;
	s = data->scene;
	while (s != NULL)
	{
		i = -1;
		while (++i < (unsigned int)STATIC_ARRAY_SIZE(g_t_obj_functions))
			if (g_t_obj_functions[i].type == s->content_size
					&& g_t_obj_functions[i].call(&refl_ray, s->content))
					color = g_t_obj_functions[i].call2(data, &refl_ray, s->content);
		s = s->next;
	}
	return (ft_color_rgb_scalar(color, refl.x, refl.y, refl.z));
}