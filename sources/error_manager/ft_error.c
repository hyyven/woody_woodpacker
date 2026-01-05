/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afont <afont@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 11:13:12 by afont             #+#    #+#             */
/*   Updated: 2026/01/05 15:25:33 by afont            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/woody.h"

void	ft_error(t_data *data)
{
	perror("[ERROR] general error");
	ft_clean(data);
}

void	ft_clean(t_data *data)
{
	if (!data)
		exit(1);
	if (data->fd >= 0)
		close(data->fd);
	if (data->map)
		munmap(data->map, data->map_size);
	free(data);
}