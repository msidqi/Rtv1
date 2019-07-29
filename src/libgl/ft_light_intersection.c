/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_light_intersection.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msidqi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/17 15:23:03 by msidqi            #+#    #+#             */
/*   Updated: 2019/07/24 18:12:36 by kdaou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libgl.h"

static double	ft_specular(t_ray *ray, double dot_prod,
									t_vec4 normal, t_vec4 vec_to_light)
{
	t_vec4	v;
	t_vec4	r;

	if (dot_prod == 0)
		return (0);
	v = ft_vec4_scalar(ray->dir, -1);
	r = ft_vec4_sub(ft_vec4_scalar(normal, 2 * dot_prod), vec_to_light);
	return (pow(ft_min(ft_vec4_dot_product(r, v), 0), SPECULAR_POW));
}

static void		ft_diffuse(t_shader_x *shx, double dot_prod,
		t_vec4 *ds, t_light *li, double area_i)
{
	shx->diff.x += dot_prod * ds[0].x * li->i_r * area_i;
	shx->diff.y += dot_prod * ds[0].y * li->i_g * area_i;
	shx->diff.z += dot_prod * ds[0].z * li->i_b * area_i;
}

unsigned int	ft_compute_shader(unsigned int color, t_shader_x *sh_x)
{
	t_shader shader;

	shader.specular = ft_color_rgb_scalar(0xFFFFFF,
			sh_x->spec.x, sh_x->spec.y, sh_x->spec.z);
	shader.diffuse = ft_color_rgb_scalar(color,
			sh_x->diff.x, sh_x->diff.y, sh_x->diff.z);
	shader.ambient = ft_color_rgb_scalar(color,
			AMBIENT_R, AMBIENT_G, AMBIENT_B);
	return (ft_color_add(shader.specular,
						ft_color_add(shader.diffuse, shader.ambient)));
}

static const	t_obj_function g_t_obj_functions[4] =
{
	{SPHERE, &ft_sphere_inter, &ft_sphere_shader},
	{PLANE, &ft_plane_inter, &ft_plane_shader},
	{CONE, &ft_cone_inter, &ft_cone_shader},
	{CYLINDER, &ft_cylinder_inter, &ft_cylinder_shader}
};

double	ft_light_intensity(t_list *scene, t_light *li, t_vec4 inter_point)
{
	if (li->type == POINT_LIGHT)
		return (1);
	else if (li->type == DIRECTIONAL_LIGHT)
		return (1);
	else if (li->type == AREA_LIGHT)
	{
		// if ray intersected with 1 point of the area light,
		// check how many vertices of the area intersects with that intersection point.
		// depending on that number return a value from 0.0 to 1.0;
		t_vec4 u = ft_create_vec4(0, -1, 0, 0);
		t_vec4 v = ft_create_vec4(1, 0, 0, 0);
		double	v_nodes = 10;
		double	u_nodes = 10;
		t_list	*new_light_list = NULL;
		t_light *new_light;

		int i = -1, j;
		while (++i < v_nodes)
		{
			j = -1;
			while (++j < u_nodes)
			{
				new_light = (t_light *)malloc(sizeof(t_light));
				new_light->origin = ft_vec4_add(li->origin, ft_vec4_add(ft_vec4_scalar(u, j * 0.1), ft_vec4_scalar(v, i * 0.1)));
				new_light->type = POINT_LIGHT;
				ft_lstadd(&new_light_list, ft_lstnew((void *)new_light, 0));
			}
		}
		double num = 0;
		t_ray ray_to_each_uv;
		t_list *tofree;
		tofree = new_light_list;
		while (new_light_list)
		{
			ray_to_each_uv.origin = inter_point;
			ray_to_each_uv.dir = ft_vec4_normalize(ft_vec4_sub(((t_light *)new_light_list->content)->origin, inter_point));
			num += ft_ray_inter_objs(scene, &ray_to_each_uv,
						ft_distance_to_light(new_light_list->content, &ray_to_each_uv),
																new_light_list->content);
			new_light_list = new_light_list->next;
		}
		ft_lstdel(&tofree, &ft_del);
		return (num / (v_nodes * u_nodes));
	}
	else
		return (0);
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

/*
** 3-loop to see if ray is blocked by any another
** 							object in scene, towards light source.
*/

double				ft_ray_inter_objs(t_list *list, t_ray *r_light,
		double distance_to_light, t_light *li)
{
	t_list			*scene;
	unsigned int	i;

	scene = list;
	while (scene != NULL)
	{
		r_light->t = FAR;
		i = -1;
		while (++i < (unsigned int)STATIC_ARRAY_SIZE(g_t_obj_functions))
		{
			if (g_t_obj_functions[i].type == scene->content_size &&
					g_t_obj_functions[i].call(r_light, scene->content) &&
					distance_to_light > ft_vec4_mag(ft_vec4_scalar(r_light->dir,
							r_light->t)))
				return (0);
		}
		scene = scene->next;
	}
	return (ft_light_intensity(list, li, r_light->origin));
}

double			ft_distance_to_light(t_light *li, t_ray *rl)
{
	if (li->type == POINT_LIGHT)
		return (ft_vec4_mag(ft_vec4_sub(li->origin, rl->origin)));
	else if (li->type == DIRECTIONAL_LIGHT)
		return (DISTANT_LIGHT);
	return (0);
}

/*
** rl : ray_to_light
** dp : dot_product
** ds diffuse && specular
** send ray to light
** loop through all lights
** if ray reached light, add value to shader
*/

t_shader_x		ft_ray_inter_lights(t_data *data,
										t_vec4 nr, t_ray *ray, t_vec4 *ds)
{
	t_ray			rl;
	t_shader_x		shx;
	t_list			*l;
	double			dp;
	t_light			*li;
	double			area_i;

	l = data->light_list;
	shx.diff = ft_create_vec4(0.0, 0.0, 0.0, 0.0);
	shx.spec = ft_create_vec4(0.0, 0.0, 0.0, 0.0);
	while (l)
	{
		li = l->content;
		rl = ft_get_ray_to_light(ray, l->content);
		dp = ft_min(ft_vec4_dot_product(rl.dir, nr), 0);
		if ((area_i = ft_ray_inter_objs(data->scene, &rl,
										ft_distance_to_light(li, &rl), li)))
		{
			ft_diffuse(&shx, dp, ds, li, area_i);
			shx.spec.x += ft_specular(ray, dp, nr, rl.dir) * ds[1].x * li->i_r * area_i;
			shx.spec.y += ft_specular(ray, dp, nr, rl.dir) * ds[1].y * li->i_g * area_i;
			shx.spec.z += ft_specular(ray, dp, nr, rl.dir) * ds[1].z * li->i_b * area_i;
		}
		l = l->next;
	}
	return (shx);
}
