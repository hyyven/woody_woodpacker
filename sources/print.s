bits 64
default rel
global _start
strr db "..WOODY..",10

_start:
	; write(1, msg, 10)
	push 1				; push 1 sur stack
	pop rax				; rax = 1 (sys_write)
	; mov edi, eax		; rdi = 1 (stdout) / copie rax dans rdi
	pop rdi				; rdi = 1 (stdout) / marche que si argc = 1 car je pop le '1' de argc qui est sur la stack
	cdq					; rdx = 0 (car rax est positif)
	mov dl, 10			; rdx = 10 (len)
	lea rsi, [rel strr]	; rsi = strr
	syscall

	; exit(0)
	xor edi, edi		; rdi = 0
	mov al, 60			; rax = 60 (sys_exit) - Note: on assume que write a réussi et rax est petit
	syscall
