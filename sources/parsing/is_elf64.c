/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_elf64.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afont <afont@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 10:38:09 by afont             #+#    #+#             */
/*   Updated: 2026/01/05 15:25:13 by afont            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/woody.h"

int	is_elf64(t_data *data)
{
	// unsigned char	*map;
	unsigned char	elf_magic[6];
	
	data->map = mmap(NULL, data->map_size, PROT_READ | PROT_WRITE, MAP_PRIVATE, data->fd, 0);
	if (data->map == MAP_FAILED)
	{
		perror("[ERROR] mmap");
		ft_clean(data);
		exit(1);
	}
	ft_strlcpy((char *)elf_magic, (const char *)data->map, 6);
	printf("[DEBUG] elf magic of file: "); printf_map(elf_magic, 6);
	// printf("[DEBUG] elf magic to compare to: "); printf_map((unsigned char *)ELF64_MAGIC, 6);
	if (ft_strcmp((const char *)elf_magic, (const char *)ELF64_MAGIC) != 0)
	{
		fprintf(stderr, "[ERROR] not a valid ELF64 file\n");
		ft_clean(data);
		exit(1);
	}
	printf("[INFO] valid ELF64 file detected\n");
	return (0);
}
