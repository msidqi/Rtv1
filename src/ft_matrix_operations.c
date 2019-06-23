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
	vec.v[0] = x;
    vec.v[1] = y;
    vec.v[2] = z;
	vec.v[3] = w;
	return (vec);
}

void		ft_putvector4(t_vector4 *vec)
{
	write(1, "Vector( ", 8);
	ft_putnbr(vec->v[0]);
	write(1, ", ", 2);
	ft_putnbr(vec->v[1]);
	write(1, ", ", 2);
	ft_putnbr(vec->v[2]);
	write(1, ", ", 2);
	ft_putnbr(vec->v[3]);
	write(1, " )\n", 3);
}

void		ft_printvector4(t_vector4 *vec)
{
	printf("Vector(%f, %f, %f, %f)\n", vec->v[0], vec->v[1], vec->v[2], vec->v[3]);
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

double    ft_vec4_magnitude(t_vector4 *a)
{
    return (sqrt(a->v[X] * a->v[X] + a->v[Y] * a->v[Y] + a->v[Z] * a->v[Z]));
}

t_vector4    ft_vec4_normalize(t_vector4 *a)
{
    t_vector4   ret;
    double      hold;

    hold = ft_vec4_magnitude(a);
    ret.v[X] = a->v[X] / hold;
    ret.v[Y] = a->v[Y] / hold;
    ret.v[Z] = a->v[Z] / hold;
	ret.v[W] = a->v[W] / hold;
    return (ret);
}

double    ft_vec4_dot_product(t_vector4 *a, t_vector4 *b)
{
    return (a->v[X] * b->v[X] + a->v[Y] * b->v[Y] + a->v[Z] * b->v[Z] + a->v[W] * b->v[W]);
}

t_vector4    ft_vec4_cross_product(t_vector4 *vec1, t_vector4 *vec2)
{
	t_vector4 ret;

    ret.v[X] = vec1->v[Y] * vec2->v[Z] - vec1->v[Z] * vec2->v[Y];
    ret.v[Y] = vec1->v[Z] * vec2->v[X] - vec1->v[X] * vec2->v[Z];
    ret.v[Z] = vec1->v[X] * vec2->v[Y] - vec1->v[Y] * vec2->v[X];
	ret.v[W] = 0;
    return (ret);
}

t_vector4    ft_vec4_sub(t_vector4 *vec1, t_vector4 *vec2)
{
    t_vector4 ret;

    ret.v[X] = vec1->v[X] - vec2->v[X];
    ret.v[Y] = vec1->v[Y] - vec2->v[Y];
    ret.v[Z] = vec1->v[Z] - vec2->v[Z];
	ret.v[W] = vec1->v[W] - vec2->v[W];
    return (ret);
}

t_vector4		ft_matrix_x_vector(t_matrix4 *mat, t_vector4 *vec)
{
	return(ft_create_vector4(mat->v[0][0] * vec->v[0] + mat->v[0][1] * vec->v[1]
	+ mat->v[0][2] * vec->v[2] + mat->v[0][3] * vec->v[3],
	mat->v[1][0] * vec->v[0] + mat->v[1][1] * vec->v[1] + mat->v[1][2] * vec->v[2]
	+ mat->v[1][3] * vec->v[3],
	mat->v[2][0] * vec->v[0] + mat->v[2][1] * vec->v[1] + mat->v[2][2] * vec->v[2]
	+ mat->v[2][3] * vec->v[3],
	mat->v[3][0] * vec->v[0] + mat->v[3][1] * vec->v[1] + mat->v[3][2] * vec->v[2]
	+ mat->v[3][3] * vec->v[3]));
}

t_matrix4		ft_get_translation_matrix4(double x, double y, double z)
{
	t_matrix4 mat;

	mat = ft_create_matrix4();
	mat.v[0][3] = x;
	mat.v[1][3] = y;
	mat.v[2][3] = z;
	return (mat);
}

t_matrix4		ft_get_scaling_matrix4(double x, double y, double z)
{
	t_matrix4 mat;

	mat = ft_create_matrix4();
	mat.v[0][0] *= x;
	mat.v[1][1] *= y;
	mat.v[2][2] *= z;
	return (mat);
}

t_vector4		ft_translate_vector4(t_vector4 *vec, double x, double y, double z)
{
	t_matrix4 tr_mat;

	tr_mat = ft_create_matrix4();
	tr_mat.v[0][3] = x;
	tr_mat.v[1][3] = y;
	tr_mat.v[2][3] = z;
	return (ft_matrix_x_vector(&tr_mat, vec));
}




int	ft_sphere_intersection(t_ray *ray)
{
	t_vector4	c = ft_create_vector4(0, 0, 20, 0);
	double		r = 0.5;
	double t0;
	double t1;
	double discr;
/*
a=dot(B,B)
b=2⋅dot(B,A−C)
c=dot(A−C,A−C)−r2
With the above parameterization, the quadratic formula is:

t= (−b±b2−4ac) / (√2a)
*/
	t_vector4 k = ft_vec4_sub(&ray->origin, &c);
	double a = ft_vec4_dot_product(&ray->dir, &ray->dir);
	double b = 2 * ft_vec4_dot_product(&ray->dir, &k);
	
	double m = ft_vec4_dot_product(&k, &k) - r * r;
	discr = b * b - 4 * a * m;
	if (discr < 0)
		return (0);
	t0 = (-b + sqrt(discr)) / (2 * a);
	t1 = (-b - sqrt(discr)) / (2 * a);
	ray->t = t0 > t1 ? t1 : t0;
	return (1);
}