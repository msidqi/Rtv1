/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_events_keyboard.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msidqi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 13:27:08 by msidqi            #+#    #+#             */
/*   Updated: 2019/07/17 16:54:25 by msidqi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libgl.h"



int		no_event_mouse_move(t_data *data)
{
	ft_refresh_image(data);
	ft_camera(data, data->cam.pos, data->cam.to);
	ft_draw_scene(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img_ptr, 0, 0);
	return (0);
}

int		mouse_move(int x, int y, t_data *data)
{
	(void)y;
	ft_refresh_image(data);
	if (!data->islocked)
	{
		data->juliapos.x = (double)(x * 1.5) / data->winwidth;
		data->juliapos.y = (double)(y * 1.5) / data->winheight;
	}
	ft_camera(data, data->cam.pos, data->cam.to);
	ft_draw_scene(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img_ptr, 0, 0);
	if (x > (0.9 * WIDTH) && x < (WIDTH))
	{
		int i = -1, j;
		while (++i < HEIGHT)
		{
			j = (0.9 * WIDTH) - 1;
			while (++j < WIDTH)
			{
				mlx_pixel_put(data->mlx, data->win, j, i, 0xAAFF0000);
			}
		}
	}
	return (0);
}

int		key_press(int key_code, t_data *data)
{
	if (key_code == 53)
	{
		mlx_destroy_image(data->mlx, data->img_ptr);
		mlx_destroy_window(data->mlx, data->win);
		ft_lstdel(&data->scene, &ft_del);
		ft_lstdel(&data->light_list, &ft_del);
		exit(0);
	}
	ft_refresh_image(data);
	if (key_code == LEFT_ARROW)
		data->cam.pos.x += 1;
	if (key_code == RIGHT_ARROW)
		data->cam.pos.x -= 1;
	if (key_code == UP_ARROW)
		data->cam.pos.z -= 1;
	if (key_code == DOWN_ARROW)
		data->cam.pos.z += 1;
	ft_camera(data, data->cam.pos, data->cam.to);
	ft_draw_scene(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img_ptr, 0, 0);
	return (0);
}

int		mouse_press(int button, int x, int y, t_data *data)
{
	ft_refresh_image(data);
	(void)x;
	(void)y;
	if (button == LEFT_CLICK)
		data->cam.pos.y -= 5;
	if (button == RIGHT_CLICK)
		data->cam.pos.y += 5;
	ft_camera(data, data->cam.pos, data->cam.to);
	ft_draw_scene(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img_ptr, 0, 0);
	return (0);
}
