bits 64

section .text
	global asm_strspn

asm_strspn:
	push rbp       ; Save the RBP value on the stack
	mov rbp, rsp   ; Set RBP as stack pointer

	push rcx       ; Save the value of RCX on the stack (it will be used to count the length)
	push r8        ; Save the value of R8 on the stack (it will be used to compare characters)
	push r9        ; Save the value of R9 on the stack (it will be used to load characters from strings)

	xor rax, rax   ; Clean RAX (will be used to count length)
	xor r8, r8     ; Clean R8 (will be used to compare characters)
	xor r9, r9     ; Clean R9 (will be used to load characters)

.loop_rdi:
	mov r8b, [rdi + rax] ; Load current character from string into RDI
	cmp r8b, 0         ; Checks if character is null (end of string)
	jz .end                ; If null, jump to 'end' tag (end of function)

	xor rcx, rcx   ; Clear RCX (will be used to traverse the chain in RSI)

.loop_rsi:  ; Inner loop label (loops through chain in RSI)
	mov r9b, [rsi + rcx] ; Load current character from string into RSI
	cmp r9b, 0         ; Checks if character is null (end of string)
	jz .end                ; If null, jump to 'end' tag

	cmp r8b, r9b    ; Compare the characters in R8 and R9
	je .jump         ; If they are the same, jump to the 'jump' tag

	inc rcx          ; Increase the chain index in RSI
	jmp .loop_rsi ; Return to the beginning of the inner loop

.jump:
	inc eax          ; Increase the length
	jmp .loop_rdi ; Return to the beginning of the outer loop

.end:
	pop r8           ; Restores the value of R8 from the stack
	pop r9           ; Restores the value of R9 from the stack
	pop rcx          ; Restores the RCX value from the stack
	mov rsp, rbp     ; Restores the original stack pointer
	pop rbp          ; Restores RBP value
	ret              ; Retun
