/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afont <afont@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 11:21:37 by afont             #+#    #+#             */
/*   Updated: 2026/01/13 09:04:09 by afont            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/woody.h"

t_data	*init_data(char **av)
{
	t_data	*data;
	
	data = ft_calloc(1, sizeof(t_data));
	check_malloc(NULL, data);
	data->f_path = av[1];
	data->fd = init_fd(data->f_path);
	data->map_size = init_f_size(data);
	
	// __addr: let kernel choose where to store the map in ram
	// __len: size of the file to map
	// __prot: read/write permissions
	// __flags: changes not written to the file
	// __fd: fd...
	// __offset: where to start the mapping
	data->base_map = mmap(NULL, data->map_size, PROT_READ | PROT_WRITE, MAP_PRIVATE, data->fd, 0);
	return (data);
}

off_t	init_f_size(t_data *data)
{
	off_t	map_size;

	// move the file position to the end of the file / return size in bytes
	map_size = lseek(data->fd, 0, SEEK_END);
	if (map_size == -1)
	{
		ft_error(data, "lseek failed");
	}
	return (map_size);
}