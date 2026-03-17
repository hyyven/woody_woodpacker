/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inject_payload.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afont <afont@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 10:36:39 by afont             #+#    #+#             */
/*   Updated: 2026/01/13 09:04:53 by afont            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/woody.h"

// find a memory address to add the payload
// address must be:
//	at the end of the file (offset = file size)
//	aligned on a linux page (4096 bytes)
// 
// address will be used as the new entry point of the elf file
Elf64_Addr	get_new_vaddr(t_data *data, Elf64_Ehdr *ehdr, Elf64_Phdr *phdr)
{
	Elf64_Addr		max_vaddr;	
	Elf64_Addr		new_vaddr;
	
	max_vaddr = 0;
	for (int i = 0; i < ehdr->e_phnum; i++)
	{
		printf("[DEBUG] phdr[i].p_type: %u, p_vaddr: 0x%lx, p_memsz: 0x%lx\n", phdr[i].p_type, phdr[i].p_vaddr, phdr[i].p_memsz);
		if (phdr[i].p_type == PT_LOAD)
		{
			Elf64_Addr seg_end = phdr[i].p_vaddr + phdr[i].p_memsz;	// end address of segment
			if (seg_end > max_vaddr)								// find highest vaddr used
				max_vaddr = seg_end;
		}
	}
	
	// pour tout nouveau segement pt_load on veux que: offset % align = vaddr % align
	// offset = taille du fichier
	// vaddr = addresse ou on va mettre le shell code
	// align = 4096 ou 0x1000 sur linux 64 bit   
	printf("\n------------- new vaddr calcul -------------\n");
	printf("[DEBUG] max vaddr found in phdr			: 0x%lx\n", max_vaddr);
	printf("[DEBUG] current file size (offset)		: %lu (0x%lx)\n", data->map_size, data->map_size);

	new_vaddr = (max_vaddr + 0x1000) & ~0xFFF; // align to next page ()
	printf("[DEBUG] -> step 1 (next page start)		: 0x%lx\n", new_vaddr);

	size_t alignment = (data->map_size % 0x1000); // offset is the size of the file -> because we're adding the payload at the end of the file
	printf("[DEBUG] -> step 2 (offset modulo 4096)		: %lu (0x%lx)\n", alignment, alignment);

	new_vaddr += alignment;    // add offset remainder
	printf("[DEBUG] -> resulting new vaddr			: 0x%lx\n", new_vaddr);
	printf("[DEBUG] verification: (0x%lx %% 4096) == (0x%lx %% 4096)\n", new_vaddr, data->map_size);
	printf("[DEBUG]                           %lu == %lu\n", new_vaddr % 4096, data->map_size % 4096);
	printf("--------------------------------------------\n\n");

	return (new_vaddr);
}

void	patch_placeholder(char *payload_buffer, Elf64_Addr old_entry, Elf64_Addr new_vaddr, unsigned long int payload_jmp_pos)
{
	int				jmp_offset;

	printf("[INFO] patching payload placeholders\n");
	jmp_offset = (int)(old_entry - (new_vaddr + payload_jmp_pos + 5));
	printf("\n--------------- jump offset calcul ---------------\n");
	printf("[DEBUG] target (old_entry)                   	: 0x%lx\n", old_entry);
	printf("[DEBUG] source (new_vaddr + jmp_position + 5) 	: 0x%lx\n", (new_vaddr + payload_jmp_pos + 5));
	printf("[DEBUG] new_vaddr                         	: 0x%lx\n", new_vaddr);
	printf("[DEBUG] payload_jmp_pos                   	: %ld (0x%lx)\n", payload_jmp_pos, payload_jmp_pos);
	printf("[DEBUG] 5 (size of jmp instruction (1 byte) + offset of 'where to jump'(4 bytes))\n");
	printf("[DEBUG] offset = target - source\n");
	printf("[DEBUG]        = 0x%lx - 0x%lx\n", old_entry, (new_vaddr + payload_jmp_pos + 5));
	printf("[DEBUG]        = %d (0x%x)\n", jmp_offset, (unsigned int)jmp_offset);
	printf("--------------------------------------------------\n\n");

	// write offset into payload (little endian, bytes reversed)
	// write 4 bytes at position of jmp offset
	printf("[DEBUG] *(int *)(payload_buffer + payload_jmp_pos + 1) = %d\n", *(int *)(payload_buffer + payload_jmp_pos + 1));
	*(int *)(payload_buffer + payload_jmp_pos + 1) = jmp_offset;
	printf("[DEBUG] *(int *)(payload_buffer + payload_jmp_pos + 1) = %d\n", *(int *)(payload_buffer + payload_jmp_pos + 1));
}

void	append_payload(t_data *data, Elf64_Addr old_entry, Elf64_Addr new_vaddr, unsigned long int payload_jmp_pos)
{
	unsigned char	*map;
	char			payload_buffer[PAYLOAD_SIZE];

	printf("[INFO] appending payload to the elf file\n");
	ft_memcpy(payload_buffer, PAYLOAD, PAYLOAD_SIZE);
	patch_placeholder(payload_buffer, old_entry, new_vaddr, payload_jmp_pos);
	printf("[DEBUG] basepayload: "); printf_map((unsigned char *)PAYLOAD, PAYLOAD_SIZE);
	printf("[DEBUG] new payload: "); printf_map((unsigned char *)payload_buffer, PAYLOAD_SIZE);
	printf("[DEBUG] old entry: 0x%lx, new vaddr: 0x%lx\n", old_entry, new_vaddr);

	// append to new map
	map = ft_calloc(1, data->map_size + PAYLOAD_SIZE);
	check_malloc(data, map);
	ft_memcpy(map, data->base_map, data->map_size);
	ft_memcpy(map + data->map_size, payload_buffer, PAYLOAD_SIZE);
	data->injected_map = map;
}

void	patch_entry(t_data *data, Elf64_Addr new_vaddr)
{
	Elf64_Ehdr		*ehdr;

	printf("[INFO] patching elf entry point to new payload vaddr\n");
	ehdr = (Elf64_Ehdr *)data->injected_map;
	printf("[DEBUG] old entry: 0x%lx\n", ehdr->e_entry);
	ehdr->e_entry = new_vaddr;
	printf("[DEBUG] new entry: 0x%lx\n", ehdr->e_entry);
}

void	patch_note_segment(t_data *data, Elf64_Addr new_vaddr)
{
	Elf64_Ehdr		*ehdr;
	Elf64_Phdr		*phdr;

	ehdr = (Elf64_Ehdr *)data->injected_map;
	phdr = (Elf64_Phdr *)(data->injected_map + ehdr->e_phoff);
	for (int i = 0; i < ehdr->e_phnum; i++)
	{
		if (phdr[i].p_type == PT_NOTE)
		{
			printf("[DEBUG] phdr[i].p_type: %u, phdr[i].p_offset: %lu, phdr[i].p_vaddr: 0x%lx, phdr[i].p_filesz: %lu, phdr[i].p_memsz: %lu, phdr[i].p_flags: %u\n",
				phdr[i].p_type,
				phdr[i].p_offset,
				phdr[i].p_vaddr,
				phdr[i].p_filesz,
				phdr[i].p_memsz,
				phdr[i].p_flags);
			phdr[i].p_type = PT_LOAD; // segment type = PT_LOAD (eg. execut segment)
			phdr[i].p_offset = data->map_size; // offset = end of file (where payload is in the file)
			phdr[i].p_vaddr = new_vaddr; // where payload will be load in memory ???
			phdr[i].p_filesz = PAYLOAD_SIZE; // size of payload in the file
			phdr[i].p_memsz = PAYLOAD_SIZE; // size of payload in memory (same as file because we want to load the whole payload in memory)
			phdr[i].p_flags = PF_R | PF_X; // read and execute permissions for the payload segment
			phdr[i].p_align = 0x1000; // align on page size (4096 bytes) for linux
		}
	}
}

// find the offset of the oppcode jmp in the payload
// to patch it with the correct offset
// to jump to the old entry point of the executable after executing the payload
int	find_jmp_offset()
{
	long unsigned int	i;

	i = -1;
	while (++i <= PAYLOAD_SIZE)
	{
		if (PAYLOAD[i] == '\xe9')
		{
			// printf("i + 1: %ld", i);
			return (i);
		}
	}
	return (-1);
}

void	inject_payload(t_data *data)
{
	Elf64_Ehdr		*ehdr;
	Elf64_Phdr		*phdr;
	Elf64_Addr		old_entry;
	Elf64_Addr		new_vaddr;
	
	printf("[INFO] injecting payload into the elf file\n");
	ehdr = (Elf64_Ehdr *)data->base_map;						// pointer to elf header
	old_entry = ehdr->e_entry;									// virt addr of first part of exe
	phdr = (Elf64_Phdr *)(data->base_map + ehdr->e_phoff);		// program header offset / list of "LOAD, NOTE etc"
	new_vaddr = get_new_vaddr(data, ehdr, phdr);
	append_payload(data, old_entry, new_vaddr, find_jmp_offset());
	// printf("[DEBUG] pre map: ");printf_map(data->injected_map, data->map_size + PAYLOAD_SIZE);
	encrypt_binary(data, new_vaddr);
	// printf("[DEBUG] post map: ");printf_map(data->injected_map, data->map_size + PAYLOAD_SIZE);
	patch_entry(data, new_vaddr);
	patch_note_segment(data, new_vaddr);
	write_to_file(data);
}