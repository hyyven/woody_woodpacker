/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afont <afont@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 11:21:37 by afont             #+#    #+#             */
/*   Updated: 2026/01/06 10:49:05 by afont            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/woody.h"

t_data	*init_data(char **av)
{
	t_data	*data;
	
	data = ft_calloc(1, sizeof(t_data));
	check_malloc(NULL, data);
	data->f_path = av[1];
	data->fd = is_file(data->f_path);
	data->map_size = init_f_size(data);
	data->base_map = mmap(NULL, data->map_size, PROT_READ | PROT_WRITE, MAP_PRIVATE, data->fd, 0);
	return (data);
}

off_t	init_f_size(t_data *data)
{
	off_t	map_size;

	map_size = lseek(data->fd, 0, SEEK_END);
	if (map_size == -1)
	{
		perror("[ERROR] lseek");
		ft_clean(data);
		exit(1);
	}
	return (map_size);
}