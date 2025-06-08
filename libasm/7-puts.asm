bits 64

section .text
    extern asm_strlen
    global asm_puts

asm_puts:
    push rbp              ; Save the rbp value on the stack
    mov rbp, rsp          ; Set rbp as the new stack pointer
    push rdi              ; Save the rdi value on the stack

    ; Call the asm_strlen function
    call asm_strlen       ; Call the asm_strlen function
    mov rdx, rax          ; Result from asm_strlen (string length) to rdx
    mov rax, 1            ; Set rax value to 1 (syscall to console)
    mov rdi, 1            ; Set the file descriptor (stdout) to rdi
    mov rsi, [rsp]        ; From string (pointer) from stack to rsi

    ; Make the system call to write to the console
    syscall

    mov rax, rdx          ; Value of rdx (original length) back to rax
    pop rdi               ; Restores the rdi value from the stack
    mov rsp, rbp          ; Restores the original stack pointer
    pop rbp               ; Restores the original rbp value

    ; Return asm_puts
    ret
