bits 64
default rel
global _start

_start:
	; write(1, msg, 10)
	push 1				; push 1 sur stack
	pop rax				; rax = 1 (sys_write)
	mov rdi, rax		; rdi = 1 (stdout)
	cdq					; rdx = 0 (car rax est positif)
	mov dl, 10			; rdx = 10 (len)
	lea rsi, [rel strr]	; rsi = strr
	syscall

	;placeholder JMP (5 bytes)
	db 0xe9			; opcode JMP
	dd 0x00000000	; placeholder offset

strr db "..WOODY..",10
