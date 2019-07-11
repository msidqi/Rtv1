/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_config.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaou <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/01 12:39:37 by kdaou             #+#    #+#             */
/*   Updated: 2019/07/03 08:58:00 by kdaou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "libgl.h"
#include <sys/uio.h>
#include <unistd.h>
#include <fcntl.h>

typedef struct s_function
{
	char *type;
	void	(*call)();
}			t_function;

int	get_next_line(int fd, char **line)
{
	int				ret;
	char			buf[BUFF_SIZE + 1];
	static char		*dest;
	int				i;
	char			*tmp;

	i = 0;
	if (fd < 0 || BUFF_SIZE <= 0 || !line)
		return (-1);
	dest = dest == NULL ? ft_strnew(0) : dest;
	while ((ret = read(fd, buf, BUFF_SIZE)) > 0)
	{
		buf[ret] = '\0';
		tmp = dest;
		dest = ft_strjoin(dest, buf);
		free(tmp);
	}
	if (ret == -1)
		return (-1);
	while (dest[i] != '\n' && dest[i])
		i++;
	if (ret == 0 && (dest == NULL || dest[0] == '\0'))
		return (0);
	*line = ft_strsub(dest, 0, i);
	dest = &dest[i] + 1;
	return (1);
}

static double	ft_atof(char *nbr)
{
	double res;
	double dec;
	size_t	len;
	int	i;
	if (nbr == NULL)
		return(0.0);
	i = 0;
	len  = ft_strlen(nbr);
	res = ft_atoi(nbr);
	while(nbr[i] != '.' && nbr[i])
		i++;

	dec = ft_atoi(nbr + i + 1);
	while (dec > 1)
		dec = dec /10;
	return (res += dec);
}
void	ft_free_table(char ***tab)
{
	int i;

	i = 0;
	while((*tab)[i])
	{
		free((*tab)[i]);
		(*tab)[i] = NULL;
		i++;
	}
	free(*tab);
	*tab = NULL;
}

static void ft_get_camera_config(char *line, t_data *data)
{
	char **tab;
	int i;

	i = 0;
	tab = ft_strsplit(line, ' ');
	while(tab[i])
		i++;
	if (tab == NULL || i < 8)
	{
		data->cam.position = ft_create_vector4(0, 0, 0, 1);
		data->cam.to = ft_create_vector4(0, 0, 0, 1);
		ft_free_table(&tab);
		return ;
	}
	data->cam.position = ft_create_vector4(ft_atof(tab[1] + 1),
			ft_atof(tab[2]), ft_atof(tab[3]), 1);
	data->cam.to = ft_create_vector4(ft_atof(tab[5] + 1),
			ft_atof(tab[6]), ft_atof(tab[7]), 1);
	ft_free_table(&tab);
}

static void	ft_get_sphere_config(char *line, t_list **list)
{
	char		**tab;
	t_sphere	*sphere;
	int			i;

	i = 0;
	tab = ft_strsplit(line, ' ');
	while(tab[i])
		i++;
	if (tab == NULL || i < 14)
	{
		ft_free_table(&tab);
		return ;
	}
	if (!(sphere = (t_sphere *)malloc(sizeof(t_sphere))))
		return ;
	sphere->center = ft_create_vector4(ft_atof(tab[1] + 1), ft_atof(tab[2]),
			ft_atof(tab[3]), 1);
	sphere->radius = ft_atof(tab[5] + 1);
	sphere->specular = ft_atof(tab[7] + 1);
	sphere->diffuse_r = ft_atof(tab[9] + 1);
	sphere->diffuse_g = ft_atof(tab[10] + 1);
	sphere->diffuse_b = ft_atof(tab[11] + 1);
	sphere->color = (ft_atoi(tab[13] + 1) << 16) |  (ft_atoi(tab[14]) << 8) | (ft_atoi(tab[15]));
	ft_lstadd(list, ft_lstnew((void *)sphere, SPHERE));
	ft_free_table(&tab);
}

static void	ft_get_plane_config(char *line , t_list **list)
{
	char **tab;
	t_plane *plane;
	int i;

	i = 0;
	tab = ft_strsplit(line, ' ');
	while(tab[i])
		i++;
	if (tab == NULL || i < 12)
	{
		ft_free_table(&tab);
		return ;
	}
	if (!(plane = (t_plane *)malloc(sizeof(t_plane))))
		return ;
	plane->point = ft_create_vector4(ft_atof(tab[1] + 1), ft_atof(tab[2]), ft_atof(tab[3]), 1);
	plane->normal = ft_vec4_normalize(ft_create_vector4(ft_atof(tab[5] + 1), ft_atof(tab[6]), ft_atof(tab[7]), 0));
	plane->specular = ft_atof(tab[9] + 1);
	plane->diffuse_r = ft_atof(tab[11] + 1);
	plane->diffuse_g = ft_atof(tab[12]);
	plane->diffuse_b = ft_atof(tab[13]);
	plane->color = (ft_atoi(tab[15] + 1) << 16) |  (ft_atoi(tab[16]) << 8) | (ft_atoi(tab[17]));

	ft_lstadd(list, ft_lstnew((void *)plane, PLANE));
	ft_free_table(&tab);
}

static void	ft_get_cone_config(char *line , t_list **list)
{
	char **tab;
	t_cone *cone;
	int i;

	i = 0;
	tab = ft_strsplit(line, ' ');
	while(tab[i])
		i++;
	if (tab == NULL || i < 12)
	{
		ft_free_table(&tab);
		return ;
	}
	if (!(cone = (t_cone *)malloc(sizeof(t_cone))))
		return ;
	cone->center = ft_create_vector4(ft_atof(tab[1] + 1), ft_atof(tab[2]), ft_atof(tab[3]), 1);
	cone->axis = ft_vec4_normalize(ft_create_vector4(ft_atof(tab[5] + 1), ft_atof(tab[6]), ft_atof(tab[7]), 0));
	cone->specular = ft_atof(tab[9] + 1);
	cone->diffuse_r = ft_atof(tab[11] + 1);
	cone->diffuse_g = ft_atof(tab[12]);
	cone->diffuse_b = ft_atof(tab[13]);
	cone->color = (ft_atoi(tab[15] + 1) << 16) |  (ft_atoi(tab[16]) << 8) | (ft_atoi(tab[17]));
	cone->half_angle = ft_atof(tab[19] + 1);

	ft_lstadd(list, ft_lstnew((void *)cone, CONE));
	ft_free_table(&tab);
}


static void	ft_get_cylinder_config(char *line , t_list **list)
{
	char **tab;
	t_cylinder *cylinder;
	int i;

	i = 0;
	tab = ft_strsplit(line, ' ');
	while(tab[i])
		i++;
	if (tab == NULL || i < 12)
	{
		ft_free_table(&tab);
		return ;
	}
	if (!(cylinder = (t_cylinder *)malloc(sizeof(t_cylinder))))
		return ;
	cylinder->point = ft_create_vector4(ft_atof(tab[1] + 1), ft_atof(tab[2]), ft_atof(tab[3]), 1);
	cylinder->axis = ft_vec4_normalize(ft_create_vector4(ft_atof(tab[5] + 1), ft_atof(tab[6]), ft_atof(tab[7]), 0));
	cylinder->specular = ft_atof(tab[7] + 1);
	cylinder->diffuse_r = ft_atof(tab[11] + 1);
	cylinder->diffuse_g = ft_atof(tab[12]);
	cylinder->diffuse_b = ft_atof(tab[13]);
	cylinder->color = (ft_atoi(tab[15] + 1) << 16) |  (ft_atoi(tab[16]) << 8) | (ft_atoi(tab[17]));
	cylinder->radius = ft_atof(tab[19] + 1);
	ft_lstadd(list, ft_lstnew((void *)cylinder, CYLINDER));
	ft_printvector4(&cylinder->axis);
	ft_free_table(&tab);
}

static void	ft_get_light_config(char *line ,t_data *data)
{
	char	**tab;
	int		i;
	t_light	*light;

	i = 0;
	tab = ft_strsplit(line, ' ');
	while(tab[i])
		i++;
	if (tab == NULL || i < 10)
	{
		ft_free_table(&tab);
		return ;
	}
	if (!(light = (t_light *)malloc(sizeof(t_light))))
		return;
	light->origin = ft_create_vector4(ft_atof(tab[1] + 1),
			ft_atof(tab[2]), ft_atof(tab[3]), 1);
	light->i_r = ft_atof(tab[5] + 1);
	light->i_g = ft_atof(tab[7] + 1);
	light->i_b =  ft_atof(tab[9] + 1);
	ft_lstadd(&(data->light_list), ft_lstnew((void *)light, sizeof(t_light *)));
	ft_free_table(&tab);
}

const t_function g_t_function[6] =
{
	{ "=>camera",  &ft_get_camera_config },
	{ "=>light",   &ft_get_light_config },
	{ "=>sphere",  &ft_get_sphere_config },
	{ "=>plane",   &ft_get_plane_config },
	{ "=>cone",   &ft_get_cone_config },
	{ "=>cylinder",   &ft_get_cylinder_config }
};

t_list	*ft_get_config(char *conf_file, t_data *data)
{
	int fd;
	char *line;
	int	i;
	t_list	*list_of_objects;

	list_of_objects = NULL;
	fd = open(conf_file, O_RDONLY);
	while (get_next_line(fd, &line))
	{
		i = 0;
		while (i < 6)
		{
			if (!ft_strncmp(g_t_function[i].type, line, ft_strlen(g_t_function[i].type)))
				g_t_function[i].call(line + 15, i >= 2 ? (void*)&list_of_objects : (void*)data);
			i++;
		}
		free(line);
		line = NULL;
	}
	close(fd);
	return (list_of_objects);
}
