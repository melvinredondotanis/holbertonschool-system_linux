bits 64

section .text
	global asm_strcmp	; Export the function

asm_strcmp:
	; Configure stack frame
	push rbp         ; Save the value of the base register (rbp) on the stack
	mov rbp, rsp     ; Set rbp equal to rsp (the current stack pointer)

	; Parameter management
	mov rdi, rdi     ; rdi contains s1 (this step does nothing)
	mov rsi, rsi     ; rdi contains s2 (this step does nothing)

	; Compare strings in a loop
.compare_loop:
	; Load characters from s1 and s2 into registers al and bl
	mov al, byte [rdi]  ; Load the byte at the address pointed to by rdi in al
	mov bl, byte [rsi]  ; Load the byte at the address pointed to by rsi in bl

	; Compare characters
	cmp al, bl       ; Compare the characters in al and bl
	je .equal_chars   ; Jump to .equal_chars if they are equal
	jl .less_chars    ; Jump to .less_chars if al is less than bl
	jg .greater_chars ; Jump to greater_chars if al is greater than bl

.equal_chars:
	; The characters are the same, check if it is a null character
	cmp al, 0        ; Compares character in al with null (0)
	je .strings_equal ; If they are equal, the strings are equal

	; Move to next characters
	inc rdi          ; Increment the rdi pointer to point to the next character of s1
	inc rsi          ; Increment the rsi pointer to point to the next character of s2
	jmp .compare_loop ; Return to .compare_loop to continue the comparison

.less_chars:
	; Return a negative value (s1 < s2)
	mov rax, -1        ; Load -1 on rax to indicate that s1 is less than s2
	jmp .end_comparison ; Jump to .end_comparison to end the comparison

.greater_chars:
	; Return a positive value (s1 > s2)
	mov rax, 1         ; Load 1 in rax to indicate that s1 is greater than s2
	jmp .end_comparison ; Jump to .end_comparison to end the comparison

.strings_equal:
	; Return 0 (s1 == s2)
	xor rax, rax    ; Set rax to 0 to indicate that the strings are equal

.end_comparison:
	;clear stack frame
	pop rbp          ; Restores the rbp value from the stack
	ret              ; Return from the function, returning the value in rax
