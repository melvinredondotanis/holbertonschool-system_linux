bits 64

section .text
    global asm_strncasecmp

asm_strncasecmp:
    push rbp           ; save base pointer before mov
    mov rbp, rsp       ; move top of stack to base pointer
    xor rbx, rbx       ; init rbx (that will contain single char of second string) to 0
    xor rax, rax       ; init rax (that will contain return value) to 0
    xor rcx, rcx       ; init rcx (that will contain loop counter) to 0
    cmp rdx, 1         ; check n with 1
    jl .end            ; if less than 1 then n <= 0

.loop:
;.fst_str_check:
    mov al, byte [rdi + rcx] ; Load the byte at the address pointed to by rdi in al
    cmp al, 'A'        ; compare letter of first string with first uppercase alphabet letter
    jl .sec_str_check  ; if lower it's not a uppercase letter
    cmp al, 'Z'        ; compare letter of first string with last uppercase alphabet letter
    jg .sec_str_check  ; if higher it's not a uppercase letter
    add al, 32         ; if not uppercase letter convert to uppercase (or int + 32 if not a letter)

.sec_str_check:
	mov bl, byte [rsi + rcx] ; same comment as previous reference for second string
    cmp bl, 'A'        ;
    jl .compare_chars  ;
    cmp bl, 'Z'        ;
    jg .compare_chars  ;
    add bl, 32         ;

.compare_chars:
    sub bl, al         ; bl = bl - al
    cmp bl, 0          ; result stored in bl must be 0 if equal
    je .equal          ; if result is equal jump equal
    jmp .end           ; else if different jump to end

.equal:
    cmp al, 0          ; check if end of first string
    je .end            ; if equal jump to end
    inc rcx            ; increment loop counter
    cmp rcx, rdx       ; compare loop counter with third argument
    jnz .loop          ; back to loop

.end:
    mov al, bl         ; copy result of sub (line 29) in al (return value registry)

    mov rsp, rbp       ; move base pointer to top of stack
    pop rbp            ; free rbp pointer
    ret                ; return value of rax
