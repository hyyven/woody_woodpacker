/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afont <afont@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 13:26:22 by afont             #+#    #+#             */
/*   Updated: 2026/01/06 15:08:12 by afont            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINE_H
# define DEFINE_H

#define ELF64_MAGIC "\x7f\x45\x4c\x46\x02"
#define PAYLOAD "\x6a\x01\x58\x48\x89\xc7\x99\xb2\x0a\x48\x8d\x35\x07\x00\x00\x00\x0f\x05\xe9\x00\x00\x00\x00\x2e\x2e\x57\x4f\x4f\x44\x59\x2e\x2e\x0a"
#define PAYLOAD_SIZE sizeof(PAYLOAD) - 1
#define PAYLOAD_JMP_POS 18

#endif