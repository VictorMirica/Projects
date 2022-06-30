section .text
	global par

;; int par(int str_length, char* str)
;
; check for balanced brackets in an expression
par:
	push ebp ;enter 0,0
	push esp
	pop ebp

	; functia intoarce un int
	; [ebp + 4] - adresa de retur
	push dword[ebp+8]	; str_length
	pop ebx

	push dword[ebp+12] ; str
	pop ecx

	; edi va fi folosit ca si contor pentru '('
	; edx va fi folosit ca si contor pentru ')'
	; esi va fi folosit ca si index in string
	xor eax,eax
	xor edi,edi
	xor edx,edx
	xor esi,esi

while:

	cmp esi,ebx
	je compare
	
	push dword[ecx+esi]
	pop eax
	cmp al,0x28 ;0x28 = '('
	je open
	cmp al,0x29	;0x29 = ')'
	je close

open:

	inc edi
	inc esi
	jmp while

close:

	inc edx
	inc esi
	jmp while

compare:

	; testam daca avem acelasi numar de paranteze deschise si inchise
	cmp edi,edx
	je true

flase:

	xor eax,eax
	jmp end

true:

	xor eax,eax
	inc eax

end:

	push ebp ;leave
	pop esp
	pop ebp
	ret
