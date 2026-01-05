/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afont <afont@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 11:15:30 by afont             #+#    #+#             */
/*   Updated: 2026/01/05 15:14:01 by afont            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

typedef struct s_data	t_data;

struct	s_data
{
	int				fd;
	char			*f_path;
	off_t			map_size;
	unsigned char	*map;
};

#endif