bits 64

section .text
	global asm_strpbrk

asm_strpbrk:
	push rbp         ; Save the value of RBP on the stack
	mov rbp, rsp     ; Set RBP as the stack pointer

	mov rax, rdi     ; Copy the pointer of string 's' to RAX
	xor rcx, rcx     ; Clear RCX (will be used to traverse string 's')

.loop_s:
	movzx r8, byte [rax + rcx]  ; Load the current character of string 's' into R8
	test r8, r8                 ; Check if the character is null (end of string)
	jz .not_found               ; If it's null, no character from 'accept' was found

	mov rsi, rsi                ; Copy the pointer of string 'accept' to RSI
	xor r9, r9                  ; Clear R9 (will be used to traverse string 'accept')

.loop_accept:
	movzx r10, byte [rsi + r9] ; Load the current character of string 'accept' into R10
	test r10, r10              ; Check if the character is null (end of string)
	jz .next_character         ; If it's null, move to the next character of 's'

	cmp r8, r10                ; Compare the character from 's' with the character from 'accept'
	je .found                  ; If they are equal, a character from 'accept' was found

	inc r9                     ; Increment the index of 'accept'
	jmp .loop_accept           ; Return to the beginning of the 'accept' loop

.found:
	mov rax, rax                ; Copy the pointer of string 's' to RAX (found result)
	add rax, rcx                ; Add the current position in 's' to the pointer of 's'
	pop rbp                     ; Restore the value of RBP
	ret                         ; Return the result (pointer to the found character)

.next_character:
	inc rcx                      ; Increment the index of 's'
	jmp .loop_s                  ; Return to the beginning of the 's' loop

.not_found:
	xor rax, rax                ; If no character from 'accept' is found, return NULL
	pop rbp                     ; Restore the value of RBP
	ret                         ; Return NULL
