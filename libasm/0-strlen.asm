bits 64

section .text
	global asm_strlen	; Export the function

asm_strlen:
	xor rax, rax		; Init the RAX at 0 (I use xor, is faster than MOV in this case)

.loop_count:
	cmp byte [rdi], 0	; Verify if the current character is NULL
	je .done			; If yes, it's done

	inc rax				; Increment the RAX
	inc rdi				; Move to the next character in the string
	jmp .loop_count

.done:
	ret
