/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrix_operations.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msidqi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/18 16:29:15 by msidqi            #+#    #+#             */
/*   Updated: 2019/06/18 16:29:16 by msidqi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libgl.h"


#define SPECULAR_POW 30

// free matrix with ft_destroy_matrix
t_matrix    *ft_create_matrix(unsigned int rows, unsigned int cols) 
{
	t_matrix		*mat;
	unsigned int	i;
	unsigned int	j;

	i = -1;
	if (rows != cols || rows * cols < 2 || !(mat = malloc(sizeof(t_matrix))))
		return (NULL);
	if(!(mat->v = (double **)malloc(sizeof(double*) * rows)))
		return (NULL);
	mat->cols = cols;
	mat->rows = rows;
	while (++i < rows)
	{
		mat->v[i] = (double *)malloc(sizeof(double) * cols);
		j = -1;
		while (++j < cols)
		{
			if (j == i)
				mat->v[i][j] = 1;
			else
				mat->v[i][j] = 0;
		}
	}
    return (mat);
}

int		ft_destroy_matrix(t_matrix *mat)
{
	unsigned int	i;

	i = -1;
	if (!mat)
		return (0);
	while (++i < mat->rows)
		free(mat->v[i]);
	free(mat->v);
	free(mat);
	return (1);
}

void		ft_putmatrix(t_matrix *mat)
{
	unsigned int	i;
	unsigned int	j;

	i = -1;
	write (1, "\n", 1);
	while (++i < mat->rows)
	{
		j = -1;
		while (++j < mat->cols)
		{
			if (j == mat->cols - 1)
			{
				ft_putnbr(mat->v[i][j]);
				write(1, " |\n", 3);
			}
			else
			{
				ft_putnbr(mat->v[i][j]);
				write(1, " ", 1);
			}
		}
	}
	write (1, "\n", 1);
}

t_matrix4		ft_create_matrix4()
{
	unsigned int	i;
	unsigned int	j;
	t_matrix4		mat;
	i = -1;
	while (++i < 4)
	{
		j = -1;
		while (++j < 4)
		{
			if (j == i)
				mat.v[i][j] = 1;
			else
				mat.v[i][j] = 0;
		}
	}
    return (mat);
}

t_vector4		ft_create_vector4(double x, double y, double z, double w) 
{
	t_vector4	vec;

	// vec = malloc(sizeof(t_vector4));
	vec.x = x;
    vec.y = y;
    vec.z = z;
	vec.w = w;
	return (vec);
}

void		ft_putvector4(t_vector4 *vec)
{
	write(1, "Vector( ", 8);
	ft_putnbr(vec->x);
	write(1, ", ", 2);
	ft_putnbr(vec->y);
	write(1, ", ", 2);
	ft_putnbr(vec->z);
	write(1, ", ", 2);
	ft_putnbr(vec->w);
	write(1, " )\n", 3);
}

void		ft_printvector4(t_vector4 *vec)
{
	printf("Vector(%f, %f, %f, %f)\n", vec->x, vec->y, vec->z, vec->w);
}

void		ft_printmatrix4(t_matrix4 *mat)
{
	unsigned int	i;
	unsigned int	j;

	i = -1;
	write (1, "\n", 1);
	while (++i < 4)
	{
		j = -1;
		while (++j < 4)
		{
			if (j == 3)
				printf("% .2f|\n", mat->v[i][j]);
			else
				printf("% .2f ", mat->v[i][j]);
		}
	}
	write (1, "\n", 1);
}

void		ft_putmatrix4(t_matrix4 *mat)
{
	unsigned int	i;
	unsigned int	j;

	i = -1;
	write (1, "\n", 1);
	while (++i < 4)
	{
		j = -1;
		while (++j < 4)
		{
			if (j == 3)
			{
				ft_putnbr(mat->v[i][j]);
				write(1, " |\n", 3);
			}
			else
			{
				ft_putnbr(mat->v[i][j]);
				write(1, " ", 1);
			}
		}
	}
	write (1, "\n", 1);
}

double    ft_vec4_magnitude(t_vector4 a)
{
    return (sqrt(a.x * a.x + a.y * a.y + a.z * a.z));
}

t_vector4    ft_vec4_normalize(t_vector4 a)
{
    t_vector4   ret;
    double      hold;

    hold = ft_vec4_magnitude(a);
    ret.x = a.x / hold;
    ret.y = a.y / hold;
    ret.z = a.z / hold;
	ret.w = a.w / hold;
    return (ret);
}

double    ft_vec4_dot_product(t_vector4 a, t_vector4 b)
{
    return (a.x * b.x + a.y * b.y + a.z * b.z);
}

t_vector4    ft_vec4_cross_product(t_vector4 vec1, t_vector4 vec2)
{
	t_vector4 ret;

    ret.x = vec1.y * vec2.z - vec1.z * vec2.y;
    ret.y = vec1.z * vec2.x - vec1.x * vec2.z;
    ret.z = vec1.x * vec2.y - vec1.y * vec2.x;
	ret.w = 0;
    return (ret);
}

t_vector4    ft_vec4_scalar(t_vector4 a, double factor)
{
    t_vector4 ret;

    ret.x = a.x * factor;
    ret.y = a.y * factor;
    ret.z = a.z * factor;
	ret.w = 0;
    return (ret);
}

t_vector4    ft_vec4_add(t_vector4 vec1, t_vector4 vec2)
{
    t_vector4 ret;

    ret.x = vec1.x + vec2.x;
    ret.y = vec1.y + vec2.y;
    ret.z = vec1.z + vec2.z;
	ret.w = 0;
    return (ret);
}

t_vector4    ft_vec4_sub(t_vector4 vec1, t_vector4 vec2)
{
    t_vector4 ret;

    ret.x = vec1.x - vec2.x;
    ret.y = vec1.y - vec2.y;
    ret.z = vec1.z - vec2.z;
	ret.w = 0;
    return (ret);
}

t_vector4		ft_matrix_x_vector(t_matrix4 mat, t_vector4 vec)
{
	return(ft_create_vector4(mat.v[0][0] * vec.x + mat.v[0][1] * vec.y
	+ mat.v[0][2] * vec.z + mat.v[0][3] * vec.w,
	mat.v[1][0] * vec.x + mat.v[1][1] * vec.y + mat.v[1][2] * vec.z
	+ mat.v[1][3] * vec.w,
	mat.v[2][0] * vec.x + mat.v[2][1] * vec.y + mat.v[2][2] * vec.z
	+ mat.v[2][3] * vec.w,
	mat.v[3][0] * vec.x + mat.v[3][1] * vec.y + mat.v[3][2] * vec.z
	+ mat.v[3][3] * vec.w));
}

t_matrix4		ft_get_translation_matrix4(t_matrix4 mat, double x, double y, double z)
{
	mat.v[0][3] = x;
	mat.v[1][3] = y;
	mat.v[2][3] = z;
	return (mat);
}

t_matrix4		ft_get_scaling_matrix4(t_matrix4 mat, double x, double y, double z) // pass identity matrix in mat for default value
{
	mat.v[0][0] *= x;
	mat.v[1][1] *= y;
	mat.v[2][2] *= z;
	return (mat);
}

t_matrix4		ft_get_rotation_matrix4(t_matrix4 mat, double x, double y, double z) // pass identity matrix in mat for default value
{
	mat.v[0][0] *= x;
	mat.v[1][1] *= y;
	mat.v[2][2] *= z;
	return (mat);
}

t_vector4		ft_translate_vector4(t_vector4 vec, double x, double y, double z)
{
	t_matrix4 tr_mat;

	tr_mat = ft_create_matrix4();
	tr_mat.v[0][3] = x;
	tr_mat.v[1][3] = y;
	tr_mat.v[2][3] = z;
	return (ft_matrix_x_vector(tr_mat, vec));
}

int	ft_plane_intersection(t_ray *ray, t_plane *plane)
{
	/*
	a plane is defined by a normal and a point1.
	if dot product between the vector(point1 - point2)
	and the normal == 0 then that point2 is part of the plane.
	(p1 − p2)⋅n=0

	if we assume that a ray and the plane intersects in point2
	((origin + t * dir) − p2)⋅n = 0
	and calculate t(the distance from the ray's origin and point2)
	we can calculate t for point2.
	t = (p0 − origin)⋅n / (dir⋅n)
	*/

	t_vector4 k = ft_vec4_sub(plane->point, ray->origin);

	double t0;
	t0 = ft_vec4_dot_product(k, plane->normal) / ft_vec4_dot_product(ray->dir, plane->normal);

	if (t0 > NEAR && t0 < ray->t)
	{
		ray->t = t0;
		return (1);
	}
	return (0);
}

/*
** a=dot(B,B)
** b=2⋅dot(B,A−C)
** c=dot(A−C,A−C)−r2
** With the above parameterization, the quadratic formula is:
** 
** t = (−b±b2−4ac) / (√2a)
*/
int	ft_sphere_intersection(t_ray *ray, t_sphere *sphere)
{
	double t0;
	double t1;
	double discr;

	t_vector4 k = ft_vec4_sub(ray->origin, sphere->center);
	double a = ft_vec4_dot_product(ray->dir, ray->dir);
	double b = 2 * ft_vec4_dot_product(ray->dir, k);

	double m = ft_vec4_dot_product(k, k) - sphere->radius * sphere->radius;
	discr = b * b - 4 * a * m;
	if (discr < 0)
		return (0);
	t0 = (-b + sqrt(discr)) / (2 * a);
	t1 = (-b - sqrt(discr)) / (2 * a);

	t0 = t0 < t1 ? t0 : t1;
	if (t0 > NEAR && t0 < ray->t)
	{
		ray->t = t0;
		return (1);
	}
	return (0);
}

/*
** const = ray.origin - cylinder.point;
** a = ray.dir ⋅ ray.dir - (ray.dir ⋅ axis)**2
** 
** b/2 = ray.dir ⋅ const - (ray.dir ⋅ axiis) * (const ⋅ axis)
** 
** c = const ⋅ const - (const ⋅ axis)**2 - radius**2
*/
int	ft_cylinder_intersection(t_ray *ray, t_cylinder *cylinder)
{
	double t0;
	double t1;
	double discr;

	t_vector4 tmp = ft_vec4_sub(ray->origin, cylinder->point);
	double a = ft_vec4_dot_product(ray->dir, ray->dir) - pow(ft_vec4_dot_product(ray->dir, cylinder->axis), 2);
	double b = (ft_vec4_dot_product(ray->dir, tmp) - ft_vec4_dot_product(ray->dir, cylinder->axis) * ft_vec4_dot_product(tmp, cylinder->axis)) * 2;
	double c = ft_vec4_dot_product(tmp, tmp) - pow(ft_vec4_dot_product(tmp, cylinder->axis), 2) - cylinder->radius * cylinder->radius;
	discr = b * b - 4 * a * c;
	if (discr < 0)
		return (0);
	t0 = (-b + sqrt(discr)) / (2 * a);
	t1 = (-b - sqrt(discr)) / (2 * a);

	t0 = t0 < t1 ? t0 : t1;
	if (t0 > NEAR && t0 < ray->t)
	{
		ray->t = t0;
		return (1);
	}
	return (0);
}

/*
** 1/ Vec1 ⋅ Vec2 = ||Vec1| * ||Vec2|| * cosθ ; where θ is angle between the vectors
** Vec1 == Vector from cone center to intersection point which is the vector (P - Center);
** Vec2 == normalized Axis;
** 2/ P = Origin + t * Dir;
** 3/ Solve for t; 
** 
** a = (Dir ⋅ Axis)**2 - cos**2(θ)
** b = 2 * ((Dir ⋅ Axis)(CO ⋅ Axis) - Dir ⋅ CO * cos**2(θ))
** c = (CO ⋅ Axis)**2 - CO ⋅ CO * cos**2(θ)
*/
int	ft_cone_intersection(t_ray *ray, t_cone *cone)
{
	double t0;
	double t1;
	double discr;

	t_vector4 k = ft_vec4_sub(ray->origin, cone->center);
	double a = pow(ft_vec4_dot_product(ray->dir, cone->axis), 2) - pow(cos(cone->half_angle), 2);
	double b = 2 * (ft_vec4_dot_product(ray->dir, cone->axis) * ft_vec4_dot_product(k, cone->axis) - ft_vec4_dot_product(ray->dir, k) * pow(cos(cone->half_angle), 2));
	double c = pow(ft_vec4_dot_product(k, cone->axis), 2) - ft_vec4_dot_product(k, k) * pow(cos(cone->half_angle), 2);

	discr = b * b - 4 * a * c;
	if (discr < 0)
		return (0);
	t0 = (-b + sqrt(discr)) / (2 * a);
	t1 = (-b - sqrt(discr)) / (2 * a);

	t0 = t0 < t1 ? t0 : t1;
	if (t0 > NEAR && t0 < ray->t)
	{
		ray->t = t0;
		return (1);
	}
	return (0);
}

t_ray			ft_get_ray_to_light(t_ray *ray, t_light *light)
{
	t_vector4 inter_point;
	t_ray ray_to_light;

	//tmp, calculating position vector from camera to inter_point
	inter_point = ft_vec4_add(ray->origin , ft_vec4_scalar(ray->dir, ray->t)); // intersection point calculated (pos vec of cam + cam_to_inter = inter_vec_pos)
	
	ray_to_light.origin = inter_point;
	ray_to_light.dir = ft_vec4_normalize(ft_vec4_sub(light->origin, ray_to_light.origin));
	return (ray_to_light);
	}

unsigned int 	ft_color_rgb_scalar(unsigned int color, double r, double g, double b)
{
	unsigned char	*ptr;

	ptr = (unsigned char *)&color;
	ptr[0] = (ptr[0] * r) > 255 ? 255 : (ptr[0] * r);
	ptr[1] = (ptr[1] * g) > 255 ? 255 : (ptr[1] * g);
	ptr[2] = (ptr[2] * b) > 255 ? 255 : (ptr[2] * b);
	return (color);
}

int		ft_color_add(unsigned int color1, unsigned int color2)
{
	unsigned int r;
	unsigned int g;
	unsigned int b;

	r = ((color2 >> 16) & 0xff) + ((color1 >> 16) & 0xff);
	g = ((color2 >> 8) & 0xff) + ((color1 >> 8) & 0xff);
	b = (color2 & 0xff) + (color1 & 0xff);
	r = r > 255 ? 255 : r;
	g = g > 255 ? 255 : g;
	b = b > 255 ? 255 : b;
	return ((r << 16) | (g << 8) | b);
}

int			ft_ray_intersect_obj(t_list *list, t_ray *ray_to_light, double distance_to_light)
{
	t_list *scene = list;
	while (scene != NULL) // 3-loop to see if ray is blocked by any another object in scene, towards light source.
	{
		if (0)// sphere with itself )
		{
			scene = scene->next;
			continue ;
		}
		if (scene->content_size == SPHERE)
		{
			ray_to_light->t = FAR;
			// check if ray_to_light intersects with the sphere (if the obj is a sphere)
			if (ft_sphere_intersection(ray_to_light, (t_sphere *)scene->content) && distance_to_light > ray_to_light->t) // to cast shadow, distance to obj must be < distance_to_light
				return (1);
		}
		else if (scene->content_size == PLANE)
		{
			ray_to_light->t = FAR;
			// check if ray_to_light intersects with the plane (if the obj is a plane)
			if (ft_plane_intersection(ray_to_light, (t_plane *)scene->content) && distance_to_light > ray_to_light->t) // to cast shadow, distance to obj must be < distance_to_light
				return (1);
		}
		else if (scene->content_size == CONE)
		{
			ray_to_light->t = FAR;
			// check if ray_to_light intersects with the plane (if the obj is a plane)
			if (ft_cone_intersection(ray_to_light, (t_cone *)scene->content) && distance_to_light > ray_to_light->t) // to cast shadow, distance to obj must be < distance_to_light
				return (1);
		}
		else if (scene->content_size == CYLINDER)
		{
			ray_to_light->t = FAR;
			// check if ray_to_light intersects with the plane (if the obj is a plane)
			if (ft_cylinder_intersection(ray_to_light, (t_cylinder *)scene->content) && distance_to_light > ray_to_light->t) // to cast shadow, distance to obj must be < distance_to_light
				return (1);
		}
		scene = scene->next;
	}
	return (0);
}

double		ft_compute_specular(t_ray *ray, double dot_prod, t_vector4 sphere_normal, t_vector4 vec_to_light)
{
	t_vector4 v;
	t_vector4 r;

	v =  ft_vec4_normalize(ft_create_vector4(-ray->dir.x, -ray->dir.y, -ray->dir.z, -ray->dir.w)); // specular
	r = ft_vec4_sub(ft_vec4_scalar(sphere_normal, 2 * dot_prod), vec_to_light);
	// printf("pow : %f\n", pow(ft_vec4_dot_product(r, v), SPECULAR_POW));
	return (pow(ft_vec4_dot_product(r, v), SPECULAR_POW));
}

/* called foreach pixel
**	foreach light
**	get ray_to_light and normal_sphere(calculate once)
**	check intersection with all objects, if : (hidden from light source by an obj) then :(its spec/diffuse += 0)
**	else : computed specular, diffuse (light pixel, if : distance to light < (distance to obj == t) )
**	ADD to return value
**
**	after foreach loop, add ambient
*/
t_shader	ft_compute_sphere_shader(t_data *data, t_ray *ray, t_sphere *sphere)
{
	t_shader pixel_shader;
	t_shader_x shader_x;
	t_list *light_list;
	t_ray ray_to_light;
	t_vector4 sphere_normal;

	shader_x.diffuse_r = 0.0;
	shader_x.diffuse_g = 0.0;
	shader_x.diffuse_b = 0.0;
	shader_x.specular_r = 0.0;
	shader_x.specular_g = 0.0;
	shader_x.specular_b = 0.0;
	light_list = data->light_list;
	sphere_normal = ft_vec4_normalize(ft_vec4_sub(ft_vec4_add(ray->origin , ft_vec4_scalar(ray->dir, ray->t)), sphere->center));
	while (light_list)
	{
		ray_to_light = ft_get_ray_to_light(ray, light_list->content);
		double distance_to_light = ft_vec4_magnitude(ft_vec4_sub(((t_light *)light_list->content)->origin, ray_to_light.origin));
		double dot_prod = ft_vec4_dot_product(ray_to_light.dir, sphere_normal);
		dot_prod = dot_prod < 0 ? 0 : dot_prod;
		if (!ft_ray_intersect_obj(data->scene, &ray_to_light, distance_to_light))
		{//if ray reached light, add value to shader
			shader_x.diffuse_r += dot_prod * sphere->diffuse_r * ((t_light *)light_list->content)->i_r;
			shader_x.diffuse_g += dot_prod * sphere->diffuse_g * ((t_light *)light_list->content)->i_g;
			shader_x.diffuse_b += dot_prod * sphere->diffuse_b * ((t_light *)light_list->content)->i_b;
			shader_x.specular_r += ft_compute_specular(ray, dot_prod, sphere_normal, ray_to_light.dir) * sphere->specular * ((t_light *)light_list->content)->i_r;
			shader_x.specular_g += ft_compute_specular(ray, dot_prod, sphere_normal, ray_to_light.dir) * sphere->specular * ((t_light *)light_list->content)->i_g;
			shader_x.specular_b += ft_compute_specular(ray, dot_prod, sphere_normal, ray_to_light.dir) * sphere->specular * ((t_light *)light_list->content)->i_b;
			// printf("%f | %f | %f\n", shader_x.specular_r, shader_x.specular_g, shader_x.specular_b);
		}
		light_list = light_list->next;
	}

	pixel_shader.specular = ft_color_rgb_scalar(/*sphere->color*/0xFFFFFF, shader_x.specular_r, shader_x.specular_g, shader_x.specular_b);
	// printf("%x\n", pixel_shader.specular);
	pixel_shader.diffuse = ft_color_rgb_scalar(sphere->color, shader_x.diffuse_r, shader_x.diffuse_g, shader_x.diffuse_b);
	pixel_shader.ambient = ft_color_rgb_scalar(sphere->color, AMBIENT_R, AMBIENT_G, AMBIENT_B);
	return (pixel_shader);
}

static t_vector4 ft_get_cone_normal(t_ray *ray, t_vector4 axis, t_vector4 c, double half_angle)
{
	t_vector4 p_sub_c;

	p_sub_c = ft_vec4_sub(ft_vec4_add(ray->origin, ft_vec4_scalar(ray->dir, ray->t)), c);
	return (ft_vec4_normalize(ft_vec4_sub(p_sub_c,
	ft_vec4_scalar(axis, (1 + half_angle * half_angle) *ft_vec4_dot_product(p_sub_c, axis)))));
}

t_shader	ft_compute_cone_shader(t_data *data, t_ray *ray, t_cone *cone)
{
	t_shader pixel_shader;
	t_shader_x shader_x;
	t_list *light_list;
	t_ray ray_to_light;
	t_vector4 cone_normal;

	shader_x.diffuse_r = 0.0;
	shader_x.diffuse_g = 0.0;
	shader_x.diffuse_b = 0.0;
	shader_x.specular_r = 0.0;
	shader_x.specular_g = 0.0;
	shader_x.specular_b = 0.0;
	light_list = data->light_list;
	cone_normal = ft_get_cone_normal(ray, cone->axis, cone->center, cone->half_angle);
	while (light_list)
	{
		ray_to_light = ft_get_ray_to_light(ray, light_list->content);
		double distance_to_light = ft_vec4_magnitude(ft_vec4_sub(((t_light *)light_list->content)->origin, ray_to_light.origin));
		double dot_prod = ft_vec4_dot_product(ray_to_light.dir, cone_normal);
		dot_prod = dot_prod < 0 ? 0 : dot_prod;
		if (!ft_ray_intersect_obj(data->scene, &ray_to_light, distance_to_light))
		{//if ray reached light, add value to shader
			shader_x.diffuse_r += dot_prod * cone->diffuse_r * ((t_light *)light_list->content)->i_r;
			shader_x.diffuse_g += dot_prod * cone->diffuse_g * ((t_light *)light_list->content)->i_g;
			shader_x.diffuse_b += dot_prod * cone->diffuse_b * ((t_light *)light_list->content)->i_b;
			shader_x.specular_r += ft_compute_specular(ray, dot_prod, cone_normal, ray_to_light.dir) * cone->specular * ((t_light *)light_list->content)->i_r;
			shader_x.specular_g += ft_compute_specular(ray, dot_prod, cone_normal, ray_to_light.dir) * cone->specular * ((t_light *)light_list->content)->i_g;
			shader_x.specular_b += ft_compute_specular(ray, dot_prod, cone_normal, ray_to_light.dir) * cone->specular * ((t_light *)light_list->content)->i_b;
		}
		light_list = light_list->next;
	}
	pixel_shader.specular = ft_color_rgb_scalar(0xFFFFFF, shader_x.specular_r, shader_x.specular_g, shader_x.specular_b);
	pixel_shader.diffuse = ft_color_rgb_scalar(cone->color, shader_x.diffuse_r, shader_x.diffuse_g, shader_x.diffuse_b);
	pixel_shader.ambient = ft_color_rgb_scalar(cone->color, AMBIENT_R, AMBIENT_G, AMBIENT_B);
	return (pixel_shader);
}


/*
** 1- P = intersection point = O + t * D;
** 
** 2- A = C + m * axis; => where vector (P - A) is perpendicular to normal = the point where ((P - A) ⋅ axis) is 0;
** 
** 3- (P - (C + m * axis)) ⋅ axis == 0
** (P - C - m * axis) ⋅ axis == 0
** (P - C) ⋅ axis == m * (axis ⋅ axis)     &&    (axis ⋅ axis == 1)
** m == (P - C) ⋅ axis;
** 
** ==> A == C + ((P - C) ⋅ axis) * axis
** 
** 
** normal == P - A;
** normal == O + t * D - (C + ((P - C) ⋅ axis) * axis)
** 
** normal == O + t * D - C - ((P - C) ⋅ axis) * axis)
** normal = P - C - ((P - C) . axe ) * axe;
** 
** => normal = (ray_to_light.origin) - (cylinder.point + ft_vec4_dot_product(ft_vec4_sub(ray_to_light.origin, cylinder.point), cylinder.axis) * cylinder.axis)
*/
static t_vector4 ft_get_cylinder_normal(t_ray *ray, t_vector4 axis, t_vector4 c)
{
	t_vector4 p_sub_c;

	p_sub_c = ft_vec4_sub(ft_vec4_add(ray->origin, ft_vec4_scalar(ray->dir, ray->t)), c);
	return (ft_vec4_normalize(ft_vec4_sub(p_sub_c, ft_vec4_scalar(axis, ft_vec4_dot_product(p_sub_c, axis)))));
}

t_shader	ft_compute_cylinder_shader(t_data *data, t_ray *ray, t_cylinder *cylinder)
{
	t_shader pixel_shader;
	t_shader_x shader_x;
	t_list *light_list;
	t_ray ray_to_light;
	t_vector4 cylinder_normal;

	shader_x.diffuse_r = 0.0;
	shader_x.diffuse_g = 0.0;
	shader_x.diffuse_b = 0.0;
	shader_x.specular_r = 0.0;
	shader_x.specular_g = 0.0;
	shader_x.specular_b = 0.0;
	light_list = data->light_list;
	cylinder_normal = ft_get_cylinder_normal(ray, cylinder->axis, cylinder->point);
	while (light_list)
	{
		ray_to_light = ft_get_ray_to_light(ray, light_list->content);
		double distance_to_light = ft_vec4_magnitude(ft_vec4_sub(((t_light *)light_list->content)->origin, ray_to_light.origin));
		double dot_prod = ft_vec4_dot_product(ray_to_light.dir, cylinder_normal);
		dot_prod = dot_prod < 0 ? 0 : dot_prod;
		if (!ft_ray_intersect_obj(data->scene, &ray_to_light, distance_to_light))
		{//if ray reached light, add value to shader
			shader_x.diffuse_r += dot_prod * cylinder->diffuse_r * ((t_light *)light_list->content)->i_r;
			shader_x.diffuse_g += dot_prod * cylinder->diffuse_g * ((t_light *)light_list->content)->i_g;
			shader_x.diffuse_b += dot_prod * cylinder->diffuse_b * ((t_light *)light_list->content)->i_b;
			shader_x.specular_r += ft_compute_specular(ray, dot_prod, cylinder_normal, ray_to_light.dir) * cylinder->specular * ((t_light *)light_list->content)->i_r;
			shader_x.specular_g += ft_compute_specular(ray, dot_prod, cylinder_normal, ray_to_light.dir) * cylinder->specular * ((t_light *)light_list->content)->i_g;
			shader_x.specular_b += ft_compute_specular(ray, dot_prod, cylinder_normal, ray_to_light.dir) * cylinder->specular * ((t_light *)light_list->content)->i_b;
		}
		light_list = light_list->next;
	}
	pixel_shader.specular = ft_color_rgb_scalar(/*cylinder->color*/0xFFFFFF, shader_x.specular_r, shader_x.specular_g, shader_x.specular_b);
	pixel_shader.diffuse = ft_color_rgb_scalar(cylinder->color, shader_x.diffuse_r, shader_x.diffuse_g, shader_x.diffuse_b);
	pixel_shader.ambient = ft_color_rgb_scalar(cylinder->color, AMBIENT_R, AMBIENT_G, AMBIENT_B);
	return (pixel_shader);
}

t_shader	ft_compute_plane_shader(t_data *data, t_ray *ray, t_plane *plane)
{
	t_shader pixel_shader;
	t_shader_x shader_x;
	t_list *light_list;
	t_ray ray_to_light;
	t_vector4 plane_normal;

	shader_x.diffuse_r = 0.0;
	shader_x.diffuse_g = 0.0;
	shader_x.diffuse_b = 0.0;
	shader_x.specular_r = 0.0;
	shader_x.specular_g = 0.0;
	shader_x.specular_b = 0.0;
	light_list = data->light_list;
	plane_normal = ft_vec4_dot_product(ray->dir, plane->normal) < 0 ? plane->normal : ft_vec4_scalar(plane->normal, -1);
	// ft_printvector4(&plane_normal);
	while (light_list)
	{
		ray_to_light = ft_get_ray_to_light(ray, light_list->content);
		double distance_to_light = ft_vec4_magnitude(ft_vec4_sub(((t_light *)light_list->content)->origin, ray_to_light.origin));
		double dot_prod = ft_vec4_dot_product(ray_to_light.dir, plane_normal);
		dot_prod = dot_prod < 0 ? 0 : dot_prod;
		if (!ft_ray_intersect_obj(data->scene, &ray_to_light, distance_to_light))
		{//if ray reached light, add value to shader
			shader_x.diffuse_r += dot_prod * plane->diffuse_r * ((t_light *)light_list->content)->i_r;
			shader_x.diffuse_g += dot_prod * plane->diffuse_g * ((t_light *)light_list->content)->i_g;
			shader_x.diffuse_b += dot_prod * plane->diffuse_b * ((t_light *)light_list->content)->i_b;
			shader_x.specular_r += ft_compute_specular(ray, dot_prod, plane_normal, ray_to_light.dir) * plane->specular * ((t_light *)light_list->content)->i_r;
			shader_x.specular_g += ft_compute_specular(ray, dot_prod, plane_normal, ray_to_light.dir) * plane->specular * ((t_light *)light_list->content)->i_g;
			shader_x.specular_b += ft_compute_specular(ray, dot_prod, plane_normal, ray_to_light.dir) * plane->specular * ((t_light *)light_list->content)->i_b;
		}
		light_list = light_list->next;
	}
	pixel_shader.specular = ft_color_rgb_scalar(/*plane->color*/0xFFFFFF, shader_x.specular_r, shader_x.specular_g, shader_x.specular_b);
	pixel_shader.diffuse = ft_color_rgb_scalar(plane->color, shader_x.diffuse_r, shader_x.diffuse_g, shader_x.diffuse_b);
	pixel_shader.ambient = ft_color_rgb_scalar(plane->color, AMBIENT_R, AMBIENT_G, AMBIENT_B);
	return (pixel_shader);
}