/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merras <merras@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 08:48:50 by abiri             #+#    #+#             */
/*   Updated: 2020/03/02 15:21:06 by merras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "master_raytracer.h"

int	ft_init_window(t_mlx *mlx)
{
	mlx->mlx_ptr = mlx_init();
	if (!(mlx->img.img_ptr = mlx_new_image(mlx->mlx_ptr,
			WIDTH, HEIGHT)))
		return (0);
	if (!(mlx->img.data = (int*)mlx_get_data_addr(mlx->img.img_ptr,
			&mlx->img.bpp, &mlx->img.size_l, &mlx->img.endian)))
		return (0);
	if (!(mlx->win = mlx_new_window(mlx->mlx_ptr, WIDTH,
		HEIGHT, "RAYTRACER\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\tMASTER")))
		return (0);
	mlx->img.height = HEIGHT;
	mlx->img.width = WIDTH;
	return (1);
}

int	ft_send_scene(t_cluster *cluster, char *filename)
{
	t_packet	packet;

	if (!(packet.data = read_file(open(filename, O_RDONLY), &packet.size)))
		return (0);
	packet.type = TYPE_T_REQUEST_SCENE;
	queue_task(cluster, create_packet(packet, NULL));
	return (1);
}

int	ft_send_tasks(t_cluster *cluster)
{
	int			index;
	int			*height_interval;
	t_packet	packet;

	index = 0;
	while (index < cluster->size)
	{
		if (!(height_interval = malloc(sizeof(int) * 2)))
			return (0);
		height_interval[0] = (HEIGHT / cluster->size) * index;
		height_interval[1] = height_interval[0] + (HEIGHT / cluster->size);
		printf("\e[31minterval for node %d is [%d-%d]\e[0m\n", index, height_interval[0], height_interval[1]);
		packet.data = height_interval;
		packet.size = sizeof(int) * 2;
		packet.type = TYPE_T_REQUEST_COMPUTATION;
		queue_task(cluster, create_packet(packet, NULL));
		index++;
	}
	return (1);
}

int	ft_display_loop(void *content)
{
	t_master_env *env;

	env = content;
	mlx_put_image_to_window(env->mlx.mlx_ptr,
		env->mlx.win, env->mlx.img.img_ptr, 0, 0);
	return (0);
}

int	computation_compare_middleware(void *first, void *second)
{
	(void)first;
	(void)second;
	return (0);
}

int	tasks_sorting_middleware(void *t1, void *t2)
{
	int offset1;
	int offset2;

	ft_memcpy(&offset1, CAST(t1, t_task *)->request->data, sizeof(int));
	ft_memcpy(&offset2, CAST(t2, t_task *)->request->data, sizeof(int));
	return (offset1 < offset2);
}

int	ft_show_results(t_cluster *cluster, t_master_env *env)
{
	void	**results;

	results = fetch_computation_blob(cluster, tasks_sorting_middleware);
	if (results && results[0])
	{
		dprintf(2, "size of image is : %d\n", CAST((results[0]), t_task *)->response->size);
		dprintf(2, "size of image is : %d\n", env->mlx.img.width * env->mlx.img.height * 4);
		int i = -1;
		int offset = 0;
		while (results[++i])
		{
			int range[2];
			ft_memcpy(range, CAST((results[i]), t_task *)->request->data, sizeof(int) * 2);
			LOG_INFO("appending result of range %d %d.", range[0], range[1]);
			ft_memcpy((void *)env->mlx.img.data + offset, CAST((results[i]), t_task *)->response->data, CAST((results[i]), t_task *)->response->size);
			offset += CAST((results[i]), t_task *)->response->size;
		}
		LOG_DEBUG("=%d.", offset);
		mlx_put_image_to_window(env->mlx.mlx_ptr, env->mlx.win, env->mlx.img.img_ptr, 0, 0);
		return (1);
	}
	return (0);
}

int main(int argc, char **argv)
{
	t_master_env	env;
	t_cluster		cluster;

	if (argc != 3)
		return (1);
	if (!(ft_init_window(&env.mlx)))
		return (2);
	if ((init_cluster(argv[1], &cluster)))
	{
		return (3);
	}
	if (!ft_send_scene(&cluster, argv[2]))
	{
		return (5);
	}
	if (!ft_send_tasks(&cluster))
	{
		return (-1);
	}
	if (!ft_show_results(&cluster, &env))
	{
		return (-1);
	}
	ft_display_loop(&env);
	mlx_loop(env.mlx.mlx_ptr);
	return (0);
}