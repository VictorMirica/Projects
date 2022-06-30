section .text
	global cmmmc

;; int cmmmc(int a, int b)
;
;; calculate least common multiple fow 2 numbers, a and b
cmmmc:
	push ebp ;enter 0,0
	push esp
	pop ebp

	; functia intoarce un int
	; [ebp + 4] - adresa de retur
	push dword[ebp+8]	; a
	pop ebx

	push dword[ebp+12] ; b
	pop ecx

	push ebx ; eax =  a
	pop eax
	push ecx ; ecx = b
	pop edx

while:

	cmp eax,edx
	je done
	jl less
	jg greater

less:

	add eax,ebx
	jmp while

greater:

	add edx,ecx
	jmp while

done:

	push ebp ;leave
	pop esp
	pop ebp
	ret
