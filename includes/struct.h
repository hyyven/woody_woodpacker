/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afont <afont@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 11:15:30 by afont             #+#    #+#             */
/*   Updated: 2026/01/12 15:02:13 by afont            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

typedef struct s_data			t_data;
typedef struct s_ptload_data	t_ptload_data;

struct	s_data
{
	int				fd;
	char			*f_path;
	off_t			map_size;
	unsigned char	*base_map;
	unsigned char	*injected_map;
};

struct	s_ptload_data
{
	Elf64_Addr	vaddr;
	Elf64_Off	offset;
	Elf64_Xword	size;
};

#endif