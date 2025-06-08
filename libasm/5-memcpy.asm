bits 64

section .text
    global asm_memcpy

asm_memcpy:
    push rbp                ; Save current RBP value
    mov rbp, rsp            ; Set RBP as the new frame pointer
    xor rcx, rcx            ; Initialize RCX to zero (counter)

    ; Check if n (RDX) is zero and, if so, return dest (RDI)
    cmp rdx, 0
    je .done

.copy_loop:
    ; Compare counter (RCX) with n (RDX)
    cmp rcx, rdx
    je .done                ; If RCX equals RDX, end the loop

    mov al, byte [rsi + rcx] ; Load current byte from src (RSI) into AL
    mov byte [rdi + rcx], al ; Store the byte in dest (RDI)

    inc rcx                 ; Increase counter
    jmp .copy_loop          ; Jump to start of loop to copy next byte

.done:
    mov rax, rdi            ; Return the pointer the destination address (dest)
    pop rbp                 ; Restore previous RBP value
    ret                     ; Return
