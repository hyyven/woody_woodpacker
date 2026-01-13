/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   encryption.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afont <afont@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 12:00:00 by afont             #+#    #+#             */
/*   Updated: 2026/01/13 11:07:06 by afont            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/woody.h"
#include <fcntl.h>
#include <unistd.h>

#define KEY_SIZE 8
#define TEXT_ADDR_PLACEHOLDER 0x1111111111111111
#define TEXT_SIZE_PLACEHOLDER 0x2222222222222222
#define KEY_PLACEHOLDER       0x3333333333333333

static uint64_t	generate_key(void)
{
	int			fd;
	uint64_t	key;

	fd = open("/dev/urandom", O_RDONLY);
	if (fd < 0)
	{
		return (0xDEADBEEFCAFEBABE);
	}
	if (read(fd, &key, KEY_SIZE) != KEY_SIZE)
		key = 0xDEADBEEFCAFEBABE;
	close(fd);
	printf("[INFO] generated key: 0x%lx\n", key);
	return (key);
}

static void	patch_value(unsigned char *buffer, size_t size, uint64_t placeholder, uint64_t new_value)
{
	size_t		i;
	uint64_t	*ptr;

	for (i = 0; i <= size - 8; i++)
	{
		ptr = (uint64_t *)(buffer + i);
		if (*ptr == placeholder)
		{
			printf("[DEBUG] found placeholder 0x%lx at offset %lu. replacing with 0x%lx\n", placeholder, i, new_value);
			*ptr = new_value;
			return ;
		}
	}
	printf("[WARNING] placeholder 0x%lx not found in payload!\n", placeholder);
}

t_ptload_data	*find_ptload(t_data *data, Elf64_Ehdr *ehdr, Elf64_Phdr *phdr)
{
	int	i;
	t_ptload_data *ptload;

	ptload = ft_calloc(1, sizeof(t_ptload_data));
	check_malloc(data, ptload);
	for (i = 0; i < ehdr->e_phnum; i++)
	{
		if (phdr[i].p_type == PT_LOAD && (phdr[i].p_flags & PF_X))
		{
			ptload->vaddr = phdr[i].p_vaddr;
			ptload->offset = phdr[i].p_offset;
			ptload->size = phdr[i].p_filesz;
			printf("[INFO] found text segment: vaddr=0x%lx, offset=0x%lx, size=0x%lx\n", ptload->vaddr, ptload->offset, ptload->size);
			phdr[i].p_flags |= PF_W;
			printf("[INFO] added PF_W flag to segment for runtime decryption.\n");
			return (ptload);
		}
	}
	ft_error(data, "PT_LOAD not found");
	return (NULL);
}

uint64_t	*find_entry_point(t_data *data, Elf64_Ehdr *ehdr, t_ptload_data *ptload)
{
	uint64_t	*entry_info; // [0] start_offset, [1] size
	
	entry_info = ft_calloc(2, sizeof(uint64_t));
	check_malloc(data, entry_info);
	if (ehdr->e_entry >= ptload->vaddr && ehdr->e_entry < (ptload->vaddr + ptload->size))
	{
		uint64_t entry_offset = ehdr->e_entry - ptload->vaddr + ptload->offset;
		if (entry_offset >= ptload->offset)
		{
			entry_info[0] = entry_offset;
			entry_info[1] = (ptload->offset + ptload->size) - entry_offset;
			printf("[INFO] starting encryption at entry point (offset 0x%lx)\n", entry_info[0]);
			return (entry_info);
		}
	}
	ft_error(data, "e_entry not found");
	return (NULL);
}

void	encrypt_binary(t_data *data)
{
	Elf64_Ehdr		*ehdr;
	Elf64_Phdr		*phdr;
	uint64_t		key;
	uint64_t		i;
	uint64_t		*entry;		// [0] start_offset, [1] size
	t_ptload_data	*ptload;
	unsigned char	*payload_ptr;

	ehdr = (Elf64_Ehdr *)data->injected_map;
	phdr = (Elf64_Phdr *)(data->injected_map + ehdr->e_phoff);
	ptload = find_ptload(data, ehdr, phdr);
	key = generate_key();
	entry = find_entry_point(data, ehdr, ptload);
	printf("[INFO] encrypting text segment...\n");
	for (i = 0; i < entry[1]; i++)
	{
		data->injected_map[entry[0] + i] ^= ((unsigned char *)&key)[i % 8];
	}
	payload_ptr = data->injected_map + data->map_size;
	// virtual address corresponding to the start of encryption
	Elf64_Addr encrypted_start_vaddr = ptload->vaddr + (entry[0] - ptload->offset);
	patch_value(payload_ptr, PAYLOAD_SIZE, TEXT_ADDR_PLACEHOLDER, encrypted_start_vaddr);
	patch_value(payload_ptr, PAYLOAD_SIZE, TEXT_SIZE_PLACEHOLDER, entry[1]);
	patch_value(payload_ptr, PAYLOAD_SIZE, KEY_PLACEHOLDER, key);
	free(ptload);
	free(entry);
}
