/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_light_intersection.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msidqi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/17 15:23:03 by msidqi            #+#    #+#             */
/*   Updated: 2019/07/17 16:42:57 by msidqi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libgl.h"

static double	ft_specular(t_ray *ray, double dot_prod, t_vec4 nr, t_vec4 sh_ray)
{
	t_vec4 v;
	t_vec4 r;

	if (dot_prod == 0)
		return (0);
	v = ft_vec4_scalar(ray->dir, -1);
	r = ft_vec4_sub(ft_vec4_scalar(nr, 2 * dot_prod), sh_ray);
	return (pow(ft_min(ft_vec4_dot_product(r, v), 0), SPECULAR_POW));
}

static	void	ft_diffuse(t_shader_x *shx, double *dp_a, t_vec4 *ds, t_light *li)
{
	shx->diff.x += dp_a[0] * ds[0].x * li->r * dp_a[1];
	shx->diff.y += dp_a[0] * ds[0].y * li->g * dp_a[1];
	shx->diff.z += dp_a[0] * ds[0].z * li->b * dp_a[1];
}

int	ft_compute_shader(int color, t_shader_x *sh_x)
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

double			ft_distance_to_light(t_light *li, t_ray *sh_ray)
{
	if (li->type == POINT_LIGHT)
		return (ft_vec4_mag(ft_vec4_sub(li->origin, sh_ray->origin)));
	else if (li->type == SPOT_LIGHT)
		return (ft_vec4_mag(ft_vec4_sub(li->origin, sh_ray->origin)));
	else if (li->type == DIRECTIONAL_LIGHT)
		return (DISTANT_LIGHT);
	return (0);
}

/*
** rl : shadow_ray
** dp_a : 0 => dot_product, 1 => area_intensity
** ds diffuse && specular
** send ray to light
** loop through all lights
** if ray reached light, add value to shader
*/

t_shader_x		ft_ray_inter_lights(t_data *data, t_vec4 nr, t_ray *r, t_vec4 *ds)
{
	t_ray			rl;
	t_shader_x		shx;
	t_list			*l;
	double			dp_a[2]; 
	t_light			*li;

	l = data->light_list;
	shx.diff = ft_create_vec4(0.0, 0.0, 0.0, 0.0);
	shx.spec = ft_create_vec4(0.0, 0.0, 0.0, 0.0);
	while (l)
	{
		li = l->content;
		rl = ft_get_shadow_ray(r, l->content);
		dp_a[0] = ft_min(ft_vec4_dot_product(rl.dir, nr), 0);
		if ((dp_a[1] = ft_ray_inter_objs(data->scene, &rl,
										ft_distance_to_light(li, &rl), li)))
		{
			ft_diffuse(&shx, dp_a, ds, li);
			shx.spec.x += ft_specular(r, dp_a[0], nr, rl.dir) * ds[1].x * li->r * dp_a[1];
			shx.spec.y += ft_specular(r, dp_a[0], nr, rl.dir) * ds[1].y * li->g * dp_a[1];
			shx.spec.z += ft_specular(r, dp_a[0], nr, rl.dir) * ds[1].z * li->b * dp_a[1];
		}
		l = l->next;
	}
	return (shx);
}

// AABB INTERSECTION
// bool intersection(box b, ray r) {
//     double tmin = -INFINITY, tmax = INFINITY;

//     if (ray.n.x != 0.0) {
//         double tx1 = (b.min.x - r.x0.x)/r.n.x;
//         double tx2 = (b.max.x - r.x0.x)/r.n.x;

//         tmin = max(tmin, min(tx1, tx2));
//         tmax = min(tmax, max(tx1, tx2));
//     }

//     if (ray.n.y != 0.0) {
//         double ty1 = (b.min.y - r.x0.y)/r.n.y;
//         double ty2 = (b.max.y - r.x0.y)/r.n.y;

//         tmin = max(tmin, min(ty1, ty2));
//         tmax = min(tmax, max(ty1, ty2));
//     }

//     return tmax >= tmin;
// }
