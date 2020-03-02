/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   master_middlewares.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merras <merras@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/02 00:56:49 by merras            #+#    #+#             */
/*   Updated: 2020/03/02 10:23:12 by merras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "master_middlewares.h"

int	init_slaves(t_cluster *cluster)
{
	t_packet	request;
	int			err;

	LOG_INFO("initializing slaves, sending INIT, TEXTURES, SCENE requests.");
	err = 0;
	request.type = TYPE_T_REQUEST_INIT;
	if (!(request.data = read_file(cluster->program, &request.size)))
		err = 1;
	if (!err)
		queue_task(cluster, create_packet(request, NULL));
	return (err);
}

int	init_cluster(char *configuration_file, t_cluster *cluster)
{
	int	err;

	err = 0;
	LOG_INFO("initiating cluster.");
	ft_bzero(cluster, sizeof(t_cluster));
	err = ERROR_WRAPPER(get_configuration(configuration_file, cluster) != 0);
	err = ERROR_WRAPPER(connect_slaves(cluster) != 0);
	err = ERROR_WRAPPER(init_computation(cluster));
	err = ERROR_WRAPPER(init_slaves(cluster) != 0);
	err = ERROR_WRAPPER(pthread_create(&cluster->loadbalancer_routine, NULL,
		cluster_loadbalancer, cluster) != 0);
	return (err);
}
