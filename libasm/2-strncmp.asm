bits 64

section .text
	global asm_strncmp

asm_strncmp:
	; Configure stack frame
	push rbp            ; Save the rbp value on the stack
	mov rbp, rsp        ; Set rbp as the current frame pointer
	mov rcx, 0          ; Initialize rcx (counter) to zero

compare:
	; Clear rax and rbx registers for use
	xor rax, rax        ; Clean rax (will be used for the result)
	xor rbx, rbx        ; Clean rbx (will be used to compare bytes)

	; Compare counter to length n
	cmp ecx, edx        ; Compare counter to length n
	je end_comparison   ; If they are equal, the comparison ends

	; Load the byte of s1 into AL and the byte of s2 into BL
	mov al, byte [rdi + rcx]  ; Load the byte of s1 into AL
	mov bl, byte [rsi + rcx]  ; Load the byte of s2 into BL

	; Compare the bytes
	cmp al, bl           ; Compara los bytes

	; Jump to different tags depending on the comparison results
	je equal_chars       ; If they are equal, jump to the equal tag
	jl less_chars        ; If they are not equal and al is less than bl, jump to less
	jg greater_chars     ; If they are not equal and al is greater than bl, jump to greater

equal_chars:
	; The characters are the same, check if it is a null character
	cmp al, 0            ; Checks if we have reached end of one of the chains
	je end_comparison    ; If so, end the comparison
	inc rcx              ; Increase the counter
	jmp compare          ; Return to the compare tag to compare the next byte

less_chars:
	; Return a negative value (s1 < s2)
	mov rax, -1          ; If al is less than bl, set the result to -1 (smaller)
	jmp end_comparison   ; Jump to end_comparison to end the comparison

greater_chars:
	; Return a positive value (s1 > s2)
	mov rax, 1           ; If al is greater than bl, set the result to 1 (greater)
	jmp end_comparison   ; Jump to end_comparison to end the comparison

end_comparison:
	; clear stack frame
	mov rsp, rbp         ; Restore rsp to original value
	pop rbp              ; Restore rbp from stack
	ret                  ; Returns with the result in rax

