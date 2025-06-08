bits 64

section .text
    global asm_putc

asm_putc:
    ;Saves the current RBP value and sets RBP as the new frame pointer
    push rbp
    mov rbp, rsp

    ; Saves current RDI, RSI and RDX values
    push rdi
    push rsi
    push rdx

    ; syscall number for write
    mov rax, 1

    ; Places the character (passed in RDI) the memory address pointed to by RSI
    mov [rsi], rdi

    ; Arguments for the write syscall
    mov rdi, 1              ; Standard Output File Descriptor
    mov rdx, 1              ; Input data length (single character)

    ; Call the write syscall to print the character
    syscall

    ; Restores previous RDX, RSI and RDI values
    pop rdx
    pop rsi
    pop rdi

    ; Restores the value of RSP and RBP
    mov rsp, rbp
    pop rbp

    ; Return
    ret
