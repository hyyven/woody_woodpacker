/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afont <afont@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 13:26:22 by afont             #+#    #+#             */
/*   Updated: 2026/01/13 11:06:33 by afont            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINE_H
# define DEFINE_H

#define ELF64_MAGIC "\x7f\x45\x4c\x46\x02"
#define PAYLOAD "\x50\x57\x56\x52\x51\x41\x53\x48\x8d\x35\x52\x00\x00\x00\x48\x8b\x3e\x48\x8b\x4e\x08\x48\x8b\x56\x10\x48\x85\xc9\x74\x0e\x30\x17\x48\xc1\xca\x08\x48\xff\xc7\x48\xff\xc9\x75\xf2\xba\x0a\x00\x00\x00\x48\x8d\x35\x1a\x00\x00\x00\xe8\x0c\x00\x00\x00\x41\x5b\x59\x5a\x5e\x5f\x58\xe9\x00\x00\x00\x00\x6a\x01\x58\x48\x89\xc7\x0f\x05\xc3\x2e\x2e\x57\x4f\x4f\x44\x59\x2e\x2e\x0a\x90\x90\x90\x90\x11\x11\x11\x11\x11\x11\x11\x11\x22\x22\x22\x22\x22\x22\x22\x22\x33\x33\x33\x33\x33\x33\x33\x33"
#define PAYLOAD_SIZE sizeof(PAYLOAD) - 1

#endif