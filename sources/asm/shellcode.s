bits 64							; pour proc 64 bits
default rel						; force adressage relatif / rend position independant / peu importe ou le code est injecte il va retrouver ses var
global _start					; ld voit _start comme point d'entre 

; rien avant _start sinon segfault

_start:
	; saving state of registers
	push rax
	push rdi
	push rsi
	push rdx
	push rcx
	push r11

	; mov rdx, 10					;
	; lea rsi, [rel strr]			; debug print
	; call ft_write					;

	; decrypt start
	lea rsi, [rel v_start_addr]	; load address of v_start_addr / rsi point to v_start_addr
	mov rdi, [rsi]				; read 8 first bytes of v_start_addr / rdi = relative offset to decrypt
	lea r8, [rel _start]		; load absolute memory address of shellcode base
	add rdi, r8					; rdi = absolute vaddr to decrypt
	mov rcx, [rsi + 8]			; read 8 next bytes of v_start_addr / rcx = rsi + 8 = v_start_addr + 8 = v_size
	mov rdx, [rsi + 16]			; read 16 next bytes of v_start_addr / rdx = rsi + 16 = v_start_addr + 16 = v_key

	test rcx, rcx				; check if rcx size is zero 
	jz end_decrypt				; if size is zero, JMP to end_decrypt / jz = jmp if not 0

decrypt_loop:
	xor byte [rdi], dl			; XOR memory byte with low byte of key / dl = 8 last bits of rdx
	ror rdx, 8					; rotate key to use next byte / 
	inc rdi						; increment to next memory address of v_start_addr
	dec rcx						; decrement counter (v_size)
	jnz decrypt_loop			; jnz = jmp if not 0 / to decrypt_loop / if (!rcx)

end_decrypt:
	mov rdx, 10					; rdx = 10 (length)
	lea rsi, [rel strr]			; rsi = strr
	call ft_write				; ft_write(strr, 10) / appel a l'etiquette ft_write

	; restoring state of registers
	pop r11
	pop rcx
	pop rdx
	pop rsi
	pop rdi
	pop rax

	;placeholder JMP (5 bytes)
	db 0xe9						; opcode JMP / db : define byte (1 byte, 8 bits)
	dd 0x00000000				; placeholder offset / dd : define double word (4 bytes, 32 bits)

ft_write:
	push 1
	pop rax
	mov rdi, rax
	syscall
	ret

	; exit(0)
	; mov eax, 1
	; mov ebx, 0;remove before prod
	; int 0x80

strr db "..WOODY..",10

; placeholders
align 8
v_start_addr: dq 0x1111111111111111	; dq : define quad word (8 bytes, 64 bits)
v_size:       dq 0x2222222222222222
v_key:        dq 0x3333333333333333
