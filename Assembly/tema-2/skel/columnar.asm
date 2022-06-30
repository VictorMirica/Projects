section .data
    extern len_cheie, len_haystack

section .text
    global columnar_transposition
;; void columnar_transposition(int key[], char *haystack, char *ciphertext);
columnar_transposition:
    ;; DO NOT MODIFY
    push    ebp
    mov     ebp, esp
    pusha 

    mov edi, [ebp + 8]   ;key
    mov esi, [ebp + 12]  ;haystack
    mov ebx, [ebp + 16]  ;ciphertext
    ;; DO NOT MODIFY

    ;; TODO: Implment columnar_transposition
    ;; FREESTYLE STARTS HERE

    ;;Pentru inceput vom calcula ceil(len_haystack/len_cheie), acesta va fi tinut in al
    mov     ecx,-1
    mov     eax,0
    mov     ax,[len_haystack]
    mov     dl,[len_cheie]    
    div     dl
    ;;Dupa impartire, daca restul nu este 0, trebuie sa incrementam catul

    cmp     ah, 0
    je      go
    inc     al
    
go: 
    mov     ah,0
    mov     dl,0
    ;;Verificam daca am ajuns la finalul criptarii, adica la pasul len_cheie
    ;;In ecx vom tine pasul
    inc     ecx
    cmp     ecx,[len_cheie]
    je      end   

while:   
    ;;verificam daca am ajuns la finalul pasului curent
    cmp     dl,al
    je      go
    push    eax
    push    edx
    ;;Am linia pe care ma aflu in eax
    ;;Plasam in edx key[pas]

    mov     al,[len_cheie]  
    mul     dl 
    mov     edx,[edi + 4*ecx]
    add     edx,eax
    mov     al,byte[esi+edx]
    cmp     al,0
    je      terminator
    cmp     al,0x20
    jl      terminator
    cmp     al,0x7A
    jg      terminator
    mov     byte[ebx],al
    inc     ebx

terminator:
    ;;in cazul in care dam de null terminator (sau de alt caracter nedorit), sarim peste acesta
    pop     edx
    pop     eax 
    inc     dl
    jmp     while

end:
    ;; FREESTYLE ENDS HERE
    ;; DO NOT MODIFY
    popa
    leave
    ret
    ;; DO NOT MODIFY