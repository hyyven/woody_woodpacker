/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afont <afont@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 10:31:37 by afont             #+#    #+#             */
/*   Updated: 2026/01/13 09:05:04 by afont            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/woody.h"

int	main(int ac, char **av)
{
	t_data	*data;
	
	if (ac != 2)
	{
		ft_error(NULL, "Usage: ./woody_woodpacker <binary>");
	}
	data = init_data(av);
	is_elf64(data);
	inject_payload(data);
	ft_clean(data);
	return (0);
}