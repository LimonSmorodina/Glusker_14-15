segment .text
        global _calc
_calc:
        mov  rcx, rdx ; rcx = z
        mov  rax, rdi ; rax = x
        mov  rbx, 5   ; rbx = 5

        xor  rdx, rdx
        div  rbx      ; rdx = x%5, rax = x/5
        mov  rdi, rdx ; rdi = x%5
        
        mov  rax, rcx ; rax = z
        xor  rdx, rdx
        div  rsi      ; rdx = z/y, rax = z/y
   
        add  rax, rdi ; rax = z/y + x%5

        shr  rax, 2   ; rax = (z/y + x%5) >> 2

        ret
