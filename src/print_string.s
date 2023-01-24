print_string:
    pusha
next_char:
    mov al, [bx]        
    or al, al
    je exit             
    mov ah, 0x0e        
    int 0x10            
    inc bx              
    jmp next_char   
exit: 
    mov ah, 0x0e       
    mov al, 13          
    int 0x10            
    mov al, 10          
    int 0x10            
    popa
    ret   