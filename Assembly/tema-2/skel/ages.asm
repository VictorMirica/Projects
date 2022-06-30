; This is your structure
struc  my_date
    .day: resw 1
    .month: resw 1
    .year: resd 1
endstruc

section .text
    global ages
; void ages(int len, struct my_date* present, struct my_date* dates, int* all_ages);
ages:
    ;; DO NOT MODIFY
    push    ebp
    mov     ebp, esp
    pusha

    mov     edx, [ebp + 8]  ; len
    mov     esi, [ebp + 12] ; present
    mov     edi, [ebp + 16] ; dates
    mov     ecx, [ebp + 20] ; all_ages
    ;; DO NOT MODIFY

    ;; TODO: Implement ages
    ;; FREESTYLE STARTS HERE
    mov     eax,0
    push    eax
go: 

    pop     eax
    cmp     eax,edx
    je      end
    ;; Testam daca am ajuns la finalul vectorului

    mov     ebx, [edi + my_date_size * eax + my_date.year] 
    push    eax
    mov     eax, [esi + my_date.year]  
    ;; Mutam in eax anul curent si in ebx anul datii de nastere
    ;;Pastram in eax indexul vectorului

    cmp     eax,ebx
    jg      gryear
    jle     leyear
    
leyear:
    ;;anul curent < anul nasterii => return 0
    pop     eax
    mov     dword [ecx+eax*4],0
    inc     eax
    push    eax
    jmp     go

gryear:
    ;;cazul uzual
    sub     eax,ebx
    mov     ebx,eax
    pop     eax
    push    ebx
    ;;am pastrat varsta in ebx, testam luna
    
    mov     bx, [edi + my_date_size * eax + my_date.month]
    push    eax
    mov     ax, [esi + my_date.month]   
    ;; Mutam in eax luna curenta si in ebx luna datii de nastere
    cmp     ax,bx
    jg      grmonth
    jl      lemonth
    je      eqmonth

grmonth:
    ;;luna curenta este mai mare ca cea a nasterii
    pop     eax
    pop     ebx
    mov     dword [ecx+eax*4],ebx
    inc     eax
    push    eax
    jmp     go

lemonth:
    ;;luna curenta este mai mica ca cea a nasterii, asadar decrementam varsta
    pop     eax 
    pop     ebx
    dec     ebx      
    mov     dword [ecx+eax*4],ebx
    inc     eax
    push    eax  
    jmp     go

eqmonth:
    ;;lunile sunt egale, comparam zilele
    pop     eax
    mov     bx, [edi + my_date_size * eax + my_date.day]
    push    eax
    mov     ax, [esi + my_date.day]   
    ;; Mutam in eax ziua curenta si in ebx ziua datii de nastere

    cmp     ax,bx
    jge     grmonth
    jl      lemonth

end:
    ;; FREESTYLE ENDS HERE
    ;; DO NOT MODIFY
    popa
    leave
    ret
    ;; DO NOT MODIFY