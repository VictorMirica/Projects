global get_words
global compare_func
global sort

extern qsort

section .text

;; sort(char **words, int number_of_words, int size)
;  functia va trebui sa apeleze qsort pentru soratrea cuvintelor 
;  dupa lungime si apoi lexicografix

; functie pentru comparare, data ca argument lui qsort
compare_func:

    enter 0,0

    sub esp, 4
	mov dword [esp], esi 
    sub esp, 4
	mov dword [esp], ebx
    sub esp, 4
    mov dword [esp], ecx
    sub esp, 4
    mov dword [esp], edx
    sub esp, 4
    mov dword [esp], edi


    ; [ebp + 4] - adresa de retur
	mov eax, [ebp + 8] ; elem 1
	mov ebx, [ebp + 12] ; elem 2

    mov edx, [eax] 
    mov edi, [ebx]

    xor esi, esi
go:

    ; Vom testa litera cu litera cuvantul
    ; Observam care este cel mai scurt

    
    cmp byte[edx + esi],0
    je first
    cmp byte[edi + esi],0
    je second
    inc esi
    jmp go

first:
    
    ; primul cuvant este mai scurt sau egal decat al doilea
    cmp byte[edi + esi],0
    je eq

first2:

    xor eax,eax
    dec eax
    jmp end

second:

    ; al doilea cuvant este mai scurt decat primul
    mov eax,1
    jmp end

eq:

    xor esi, esi
    
equal:

    ; cele doua cuvinte sunt egale
    ; le vom sorta lexicografic
    mov cl, byte[edx+esi]
    mov ch, byte[edi+esi]
    inc esi
    
    cmp cl,0  ; am ajuns la finalul cuvantului
    je  eqend ; cuvintele sunt identice
    
    cmp cl,ch
    jl first2
    jg second
    jmp equal

eqend:    

    xor eax,eax
end:

	mov esi, dword [esp+16]
    mov ebx, dword [esp+12]
    mov ecx, dword [esp+8] 
    mov edx, dword [esp+4]
    mov edi, dword [esp]  

    leave 
    ret


sort:

    enter 0, 0

    ; [ebp + 4] - adresa de retur
	mov eax, [ebp + 8] ; words
	mov ebx, [ebp + 12] ; number_of_words
    mov ecx, [ebp + 16] ; size

    push dword compare_func
    push ecx
    push ebx
    push eax
    call qsort
    add esp,16

    leave
    ret


;; get_words(char *s, char **words, int number_of_words)
;  separa stringul s in cuvinte si salveaza cuvintele in words
;  number_of_words reprezinta numarul de cuvinte
get_words:

    enter 0, 0

    ; [ebp + 4] - adresa de retur
	mov ebx, [ebp + 8] ; s
	mov eax, [ebp + 12] ; words
    mov ecx, [ebp + 16] ; number_of_words
    

    xor edx,edx ; iterator pentru cuvinte
    ; in esi vom tine cuvantul
   
start:

    xor edi,edi ; in edi vom tine interatorul de litere
    mov byte[esi],0
while:

    ; vad daca am ajuns la finalul cuvantului
    cmp byte[ebx], 0x2E ; '.'
    je  placeword
    cmp byte[ebx], 0x2C ; ','
    je  placeword
    cmp byte[ebx], 0x20 ; ' '
    je  placeword
    cmp byte[ebx], 0x0A ; \n
    je  placeword

    ; plasez o litera in esi
    push edx
    mov dl, byte[ebx]
    mov byte[esi + edi],dl
    inc ebx
    inc edi
    pop edx

    jmp while
    
    ; plasez un cuvant in vector
placeword:

    inc ebx
    cmp byte[esi],0 ; testez daca trebuie sa plasez cuvantul, 
                    ; sau daca au fost 2 delimitatori succesivi
    je start

    mov byte[esi+edi],0 ; plasez null terminator la final de cuvant

    mov [eax + 4 * edx], esi ; plasez in vector

    add esi, edi ; schimb locul in memorie unde se va salva
    inc esi      ; urmatorul cuvant
    
    inc edx
    loop start

    leave
    ret

