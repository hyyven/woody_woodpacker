/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   woody.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afont <afont@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 10:31:26 by afont             #+#    #+#             */
/*   Updated: 2026/01/13 08:42:42 by afont            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/syscall.h>
#include <elf.h>

#include "struct.h"
#include "define.h"
#include "../_libft/libft.h"

#ifndef WOODY_H
# define WOODY_H

void		is_elf64(t_data *data);
int			is_file(char *f_path);
void		ft_error(t_data *data, char *msg);
void		check_malloc(t_data *data, void *ptr);
t_data		*init_data(char **av);
void		printf_map(unsigned char *map, size_t size);
void		ft_clean(t_data *data);
off_t		init_f_size(t_data *data);
void		inject_payload(t_data *data);
Elf64_Addr	get_new_vaddr(t_data *data, Elf64_Ehdr *ehdr, Elf64_Phdr *phdr);
void		write_to_file(t_data *data);
int			find_jmp_offset();
void		encrypt_binary(t_data *data, Elf64_Addr new_vaddr);

#endif