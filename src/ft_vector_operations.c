/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector_operations.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msidqi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/11 18:39:09 by msidqi            #+#    #+#             */
/*   Updated: 2019/05/11 18:39:12 by msidqi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libgl.h"

void   vec2_init(t_vector2 *a, double x, double y)
{
    a->x = x;
    a->y = y;
}

void   vec3_init(t_vector3 *a, double x, double y, double z)
{
    a->x = x;
    a->y = y;
    a->z = z;
}

t_vector2    vec2_add(t_vector2 a, t_vector2 b)
{
    t_vector2 ret;

    ret.x = a.x + b.x;
    ret.y = a.y + b.y;
    return (ret);
}

t_vector3    vec3_add(t_vector3 a, t_vector3 b)
{
    t_vector3 ret;

    ret.x = a.x + b.x;
    ret.y = a.y + b.y;
    ret.z = a.z + b.z;
    return (ret);
}

t_vector2    vec2_sub(t_vector2 a, t_vector2 b)
{
    t_vector2 ret;

    ret.x = a.x - b.x;
    ret.y = a.y - b.y;
    return (ret);
}

t_vector3    vec3_sub(t_vector3 a, t_vector3 b)
{
    t_vector3 ret;

    ret.x = a.x - b.x;
    ret.y = a.y - b.y;
    ret.z = a.z - b.z;
    return (ret);
}

t_vector2    vec2_scalar_multi(t_vector2 a, double factor)
{
    t_vector2 ret;

    ret.x = a.x * factor;
    ret.y = a.y * factor;
    return (ret);
}

t_vector3    vec3_scalar_multi(t_vector3 a, double factor)
{
    t_vector3 ret;

    ret.x = a.x * factor;
    ret.y = a.y * factor;
    ret.z = a.z * factor;
    return (ret);
}

double    vec2_magnitude(t_vector2 a)
{
    return (sqrt(a.x * a.x + a.y * a.y));
}

double    vec3_magnitude(t_vector3 a)
{
    return (sqrt(a.x * a.x + a.y * a.y + a.z * a.z));
}

double    vec2_magnitude_cmp(t_vector2 a, t_vector2 b)
{
    return ((a.x * a.x + a.y * a.y) - (b.x * b.x + b.y * b.y));
}

double    vec3_magnitude_cmp(t_vector3 a, t_vector3 b)
{
    return ((a.x * a.x + a.y * a.y + a.z * a.z)
                        - (b.x * b.x + b.y * b.y + b.z * b.z));
}

t_vector2    vec2_normalize(t_vector2 a)
{
    t_vector2   ret;
    double      hold;

    hold = vec2_magnitude(a);
    ret.x = a.x / hold;
    ret.y = a.y / hold;
    return (ret);
}

t_vector3    vec3_normalize(t_vector3 a)
{
    t_vector3   ret;
    double      hold;

    hold = vec3_magnitude(a);
    ret.x = a.x / hold;
    ret.y = a.y / hold;
    ret.z = a.z / hold;
    return (ret);
}

double    vec2_dot_product(t_vector2 a, t_vector2 b)
{
    return (a.x * b.x + a.y * b.y);
}

/*
** For normalized vectors Dot returns 1 if they point in exactly 
** the same direction, -1 if they point in completely opposite directions
** and zero if the vectors are perpendicular.
** Angle between them θ = acos([A•B]/[|A||B|]) && if A B are normalized θ = acos(AB).
**  A • B = |A||B|cos(θ) ==> (|B|cos(θ) how much do they move together).
** ==> the extent to which the vectors are pointing in the same direction.
*/

double    vec3_dot_product(t_vector3 a, t_vector3 b)
{
    return (a.x * b.x + a.y * b.y + a.z * b.z);
}

t_vector2   vec2_rotate_byangle(t_vector2 a, double angle)//y_axis (-0.75, 0.66) (1, 0)
{
    t_vector2 ret;
    ret.x = a.x * cos(angle) - a.y * sin(angle);
    ret.y = a.x * sin(angle) + a.y * cos(angle);
    return (ret);
}


/*
** To avoid cos && sin 's computational cost.
**
** Rotate the x-axis (1,0) and y-axis (0,1) using vec2_rotate_cosin()
** x_axis = vec2_rotate_cosin((1,0), 49 degrees)
** y_axis = vec2_rotate_cosin((0,1), 49 degrees)
** then use the following function on all 
** the object's points(passing the rotated axises as param).
** instead of applying vec2_rotate_cosin() on each point.
**
** formula x(a,b) + y(c,d)
** x and y are the original point's position,
** (a,b)(c,d) are the rotated axis.
** vec2_add(vec2_scalar_multi(x_axis, a.x), vec2_scalar_multi(y_axis, a.y))
**
** exmpl: x_axis (0.66,0.75) y_axis (-0.75, 0.66)
** 0*(0.66,0.75) + 2*(-0.75, 0.66) = (-1.5, 1.3)
*/

t_vector2   vec2_rotate_byaxis(t_vector2 a, t_vector2 x_axis, t_vector2 y_axis)
{
    x_axis.x *= a.x;
    x_axis.y *= a.x;
    y_axis.x *= a.y;
    y_axis.y *= a.y;
    return (vec2_add(x_axis, y_axis));
}