/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_to_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afont <afont@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 08:20:37 by afont             #+#    #+#             */
/*   Updated: 2026/01/13 09:04:13 by afont            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/woody.h"

void	write_to_file(t_data *data)
{
	int	fd;
	
	fd = open("woody", O_WRONLY | O_TRUNC | O_CREAT);
	if (fd < 0)
		ft_error(data, "open failed");
	write(fd, data->injected_map, data->map_size + PAYLOAD_SIZE);
	free(data->injected_map);
}