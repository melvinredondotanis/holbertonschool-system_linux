bits 64

section .text
    global asm_strstr

asm_strstr:
    ; Preparation of the function
    push rbp
    mov rbp, rsp
    push rcx
    push rbx
    push rdx
    push r9
    push r8

    ; Initialize records
    xor rax, rax
    xor rcx, rcx
    xor r9, r9
    xor r8, r8


.search_loop:
    ; Copy current index to RDX
    mov rdx, rcx
    xor rbx, rbx

.search_match:
    ; Load current haystack character into R8B
    ; Load current needle character into R9B
    mov r8b, [rdi + rcx]
    mov r9b, [rsi + rbx]

    ; Check if we have reached the end of needle (null character)
    cmp r9b, 0
    jz .found_needle

    ; Compare the current character of haystack with that of needle
    cmp r8b, r9b
    jne .search_end

    ; Increase indexes and continue searching
    inc rcx
    inc rbx
    jmp .search_match

.search_end:
    ; Load next character into haystack
    mov r8b, [rdi + rcx]

    ; Check if it is the end of haystack (null character)
    cmp r8b, 0
    jz .end

    ; Increase index in haystack and continue searching
    inc rcx
    jmp .search_loop

.found_needle:
    ; Calculate the address of the start of needle in haystack
    mov rax, rdi
    add rax, rdx

.end:
    ; Restore records and return
    pop r9
    pop r8
    pop rdx
    pop rbx
    pop rcx
    mov rsp, rbp
    pop rbp
    ret
