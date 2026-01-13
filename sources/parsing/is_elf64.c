/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_elf64.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afont <afont@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 10:38:09 by afont             #+#    #+#             */
/*   Updated: 2026/01/13 09:04:59 by afont            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/woody.h"

void	is_elf64(t_data *data)
{
	// unsigned char	*map;
	unsigned char	elf_magic[6];
	
	if (data->base_map == MAP_FAILED)
	{
		ft_error(data, "mmap failed");
	}
	ft_strlcpy((char *)elf_magic, (const char *)data->base_map, 6);
	printf("[DEBUG] elf magic of file: "); printf_map(elf_magic, 6);
	// printf("[DEBUG] elf magic to compare to: "); printf_map((unsigned char *)ELF64_MAGIC, 6);
	if (ft_strcmp((const char *)elf_magic, (const char *)ELF64_MAGIC) != 0)
		ft_error(data, "not a valid elf64 file");
	printf("[INFO] valid elf64 file detected\n");
}
