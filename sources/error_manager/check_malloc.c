/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_malloc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afont <afont@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 11:29:52 by afont             #+#    #+#             */
/*   Updated: 2026/01/05 13:56:28 by afont            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/woody.h"

void	check_malloc(t_data *data, void *ptr)
{
	if (!ptr)
	{
		fprintf(stderr, "[ERROR] malloc failed\n");
		ft_clean(data);
		exit(1);
	}
}