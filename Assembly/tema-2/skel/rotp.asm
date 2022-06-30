section .text
    global rotp
;; void rotp(char *ciphertext, char *plaintext, char *key, int len);
rotp:
    ;; DO NOT MODIFY
    push    ebp
    mov     ebp, esp
    pusha

    mov     edx, [ebp + 8]  ; ciphertext
    mov     esi, [ebp + 12] ; plaintext
    mov     edi, [ebp + 16] ; key
    mov     ecx, [ebp + 20] ; len
    ;; DO NOT MODIFY

    ;; TODO: Implment rotp
    ;; FREESTYLE STARTS HERE
go: 
    ;;Preluam caracter cu caracter din string
    mov al, byte [esi]
    mov bl, byte [edi + ecx - 1]

    ;;Facem xor si puntem noul caracter in stringul criptat
    xor al,bl
    mov byte[edx],al

    ;;Incrementam registrele, practric mutam indexul din string
    inc esi
    inc edx
    dec ecx
    cmp ecx,0
    jne go

    ;; FREESTYLE ENDS HERE
    ;; DO NOT MODIFY
    popa
    leave
    ret
    ;; DO NOT MODIFY