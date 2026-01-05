/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afont <afont@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 10:31:37 by afont             #+#    #+#             */
/*   Updated: 2026/01/05 13:56:23 by afont            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/woody.h"

int	main(int ac, char **av)
{
	t_data	*data;
	
	if (ac != 2)
	{
		fprintf(stderr, "[ERROR] invalid number of arguments\n");
		exit(1);
	}
	data = init_data(av);
	is_elf64(data);
	ft_clean(data);
	return (0);
}