;; defining constants, you can use these as immediate values in your code
CACHE_LINES  EQU 100
CACHE_LINE_SIZE EQU 8
OFFSET_BITS  EQU 3
TAG_BITS EQU 29 ; 32 - OFSSET_BITS


section .text
    global load
    extern printf
;; void load(char* reg, char** tags, char cache[CACHE_LINES][CACHE_LINE_SIZE], char* address, int to_replace);
load:
    ;; DO NOT MODIFY
    push ebp
    mov ebp, esp
    pusha

    mov eax, [ebp + 8]  ; address of reg
    mov ebx, [ebp + 12] ; tags
    mov ecx, [ebp + 16] ; cache
    mov edx, [ebp + 20] ; address
    mov edi, [ebp + 24] ; to_replace (index of the cache line that needs to be replaced in case of a cache MISS)
    ;; DO NOT MODIFY

    ;; TODO: Implment load
    ;; FREESTYLE STARTS HERE

    push    edx
    shr     edx,OFFSET_BITS
    ;;acum avem tagul in edx
    
    mov     esi,0

tag:
    cmp     edx,[ebx+esi]
    je      found
    cmp     esi,CACHE_LINES
    je      notfound
    inc     esi
    jmp     tag

    

found:
    ;;Am gasit tagul
    ;;Plasam in registru

    pop     edx
    shl     edx,TAG_BITS
    shr     edx,TAG_BITS
    add     ecx,edx

    push    eax
    push    edx
    xor     eax,eax
    mov     eax,CACHE_LINE_SIZE
    mul     esi
    mov     esi,eax
    pop     edx
    pop     eax
    
    add     ecx,esi
    mov     dl,byte[ecx]
    mov     byte[eax],dl
    jmp     end

notfound:
    ;; calculam indexul cache-ului

    pop     edx
    push    edx
    shr     edx,OFFSET_BITS
    shl     edx,OFFSET_BITS

    push    edi
    push    eax
    push    edx   
    xor     eax,eax
    mov     eax,CACHE_LINE_SIZE
    mul     edi
    mov     edi,eax
    pop     edx
    pop     eax
    
    mov     esi, 0
    push    ebx

whilenotfound:
    ;;Nu am gasit tagul in tags
    ;;Trebuie sa scriu cei 8 octeti cu adrese incepand de la edx

    cmp     esi,8
    je      writenotfound
    xor     ebx,ebx
    mov     bl,byte[edx]
    mov     byte[ecx + edi],bl
    inc     edx
    inc     esi
    inc     edi
    jmp     whilenotfound

writenotfound:
    ;;Am scris linia in cache
    ;;Scriem in tags
    pop     ebx
    pop     edi
    pop     edx
    push    edx
    shr     edx,OFFSET_BITS
    mov     dword[ebx + edi],edx
    ;;Acum va trebui sa scriem si in registru

    pop     edx
    shl     edx,TAG_BITS
    shr     edx,TAG_BITS

    push    eax
    push    edx
    xor     eax,eax
    mov     eax,CACHE_LINE_SIZE
    mul     edi
    mov     edi,eax
    pop     edx
    pop     eax

    push    ebx
    add     edi,edx
    mov     bl,byte[ecx + edi]
    mov     byte[eax],bl
    pop     ebx

end:
    ;; FREESTYLE ENDS HERE
    ;; DO NOT MODIFY
    popa
    leave
    ret
    ;; DO NOT MODIFY