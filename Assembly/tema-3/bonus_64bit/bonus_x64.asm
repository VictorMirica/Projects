section .text
	global intertwine

;; void intertwine(int *v1, int n1, int *v2, int n2, int *v);
;
;  Take the 2 arrays, v1 and v2 with varying lengths, n1 and n2,
;  and intertwine them
;  The resulting array is stored in v
intertwine:
	enter 0, 0

	; rdi = v1
	; rsi = n1
	; rdx = v2
	; rcx = n2
	; r8 = v

	xor rax,rax
	
while:
			
	mov ebx, dword[rdi + 4 * rax]
	mov dword[r8 + 2 * 4 * rax], ebx


	mov ebx, dword[rdx + 4 * rax]
	mov dword[r8 + 2 * 4 * rax + 4], ebx
	
	inc rax
	cmp rax, rsi
	je first
	cmp rax, rcx 
	je second	
	jmp while

first:

	mov rsi,rax
	add rsi,rax

first2:

	cmp rax, rcx 
	je end
	
	mov ebx, dword[rdx + 4 * rax]
	mov dword[r8 + 4 * rsi], ebx
	inc rax
	inc rsi
	jmp first2

second:

	mov rcx,rax
	add rcx,rax

second2:

	mov ebx, dword[rdi + 4 * rax]
	mov dword[r8 + 4 * rcx ], ebx
	inc rax 
	inc rcx
	cmp rax, rsi
	je end
	jmp second2

end:

	mov rax, r8
	leave
	ret
