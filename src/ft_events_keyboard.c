/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_events_keyboard.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msidqi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 13:27:08 by msidqi            #+#    #+#             */
/*   Updated: 2019/05/14 13:28:57 by msidqi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libgl.h"

int     no_event_mouse_move(int x, int y, t_data *data)
{
    (void)y;
    // ft_refresh_image(data);
    if (x > (0.8 * WIDTH) && x < (WIDTH))
        data->cam.position.x -= 0.5;
    else if (x < (0.2 * WIDTH) && x > (0))
        data->cam.position.x += 0.5;

    t_vector4 cam_pos = ft_create_vector4(data->cam.position.x, data->cam.position.y, data->cam.position.z, 1);
	t_vector4 look_at_pos = ft_create_vector4(0, 0, -1, 1);

    ft_camera(data, cam_pos, look_at_pos, 2);
    ft_draw(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img_ptr, 0, 0);
    return (0);
}

int     mouse_move(int x, int y, t_data *data)
{
    (void)y;
    ft_refresh_image(data);
    if (x > (0.8 * WIDTH) && x < (WIDTH) && y > 0 && y < HEIGHT)
        data->cam.position.x -= 0.5;
    else if (x < (0.2 * WIDTH) && x > 0 && y > 0 && y < HEIGHT)
        data->cam.position.x += 0.5;

    // printf("x : %d y : %d\n", x, y);

    t_vector4 cam_pos = ft_create_vector4(data->cam.position.x, data->cam.position.y, data->cam.position.z, 1);
	t_vector4 look_at_pos = ft_create_vector4(0, 0, -1, 1);

    ft_camera(data, cam_pos, look_at_pos, 2);
    ft_draw(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img_ptr, 0, 0);
    return (0);
}

int     key_press(int key_code, t_data *data)
{
    if (key_code == 53)
    {
        mlx_destroy_image(data->mlx, data->img_ptr);
        mlx_destroy_window(data->mlx, data->win);
        // free(data);
        // data = NULL;
        exit(0);
    }
    ft_refresh_image(data);
    if (key_code == LEFT_ARROW)
        data->cam.position.x += 0.5;
    if (key_code == RIGHT_ARROW)
        data->cam.position.x -= 0.5;
    if (key_code == UP_ARROW)
        data->cam.position.z -= 0.5;
    if (key_code == DOWN_ARROW)
        data->cam.position.z += 0.5;

   /* if (key_code == NUM_LOCK_8)
        data->light.origin.z -= 0.2;
    if (key_code == NUM_LOCK_5)
        data->light.origin.z += 0.2;
    if (key_code == NUM_LOCK_4)
        data->light.origin.x += 0.2;
    if (key_code == NUM_LOCK_6)
        data->light.origin.x -= 0.2;
    if (key_code == NUM_LOCK_7)
        data->light.origin.y -= 0.2;
    if (key_code == NUM_LOCK_9)
        data->light.origin.y += 0.2;*/
    t_vector4 cam_pos = ft_create_vector4(data->cam.position.x, data->cam.position.y, data->cam.position.z, 1);
	t_vector4 look_at_pos = ft_create_vector4(0, 0, -1, 1);

	ft_camera(data, cam_pos, look_at_pos, 2);
    ft_draw(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img_ptr, 0, 0);
    return (0);
}

int     mouse_press(int button, int x, int y, t_data *data)
{
	ft_refresh_image(data);
    (void)x;
    (void)y;
	if (button == LEFT_CLICK)
    {
        // data->cam.focal_length -= 1;
		data->cam.position.y -= 1;
    }
	if (button == RIGHT_CLICK)
    {
        // data->cam.focal_length += 1;
		data->cam.position.y += 1;
    }
    t_vector4 cam_pos = ft_create_vector4(data->cam.position.x, data->cam.position.y, data->cam.position.z, 1);
	t_vector4 look_at_pos = ft_create_vector4(0, 0, -1, 1);

	ft_camera(data, cam_pos, look_at_pos, 2);
    ft_draw(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img_ptr, 0, 0);

    return (0);
}
