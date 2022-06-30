section .text
	global sort

; struct node {
;     	int val;
;    	struct node* next;
; };

;; struct node* sort(int n, struct node* node);
; 	The function will link the nodes in the array
;	in ascending order and will return the address
;	of the new found head of the list
; @params:
;	n -> the number of nodes in the array
;	node -> a pointer to the beginning in the array
; @returns:
;	the address of the head of the sorted list

struc node
	.val: resd 1
	.next: resd 1

endstruc

sort:

	enter 0, 0

	; functia intoarce un pointer
	sub esp, 4
	mov dword [ebp - 4],0 ; echivalent [esp]

	; [ebp + 4] - adresa de retur
	mov ebx, [ebp + 8] ; n
	mov ecx, [ebp + 12] ; node
	
 	xor eax,eax

go:

	; cautam elementul minim din array 
	xor edx,edx
	mov edi, 0 	; edi va fi folosit ca iterator
	mov dx, bx	; dx va pastra minimul
	inc dx
	jmp while

; Testam daca am mai intalnit acest minim
; in iterarile anterioare 
testmin:

	cmp eax,0
	je newmin

	; compar val la care ne aflam cu ultima val minima verificata
	cmp bx,[eax + node.val]
	jle incr

; Pastram indexul si valoarea minimului
newmin:

	mov dx, bx
	mov esi, edi	; esi va pastra indexul minimului
	jmp incr

while:
	push ebx
	mov bx, [ecx + edi * node_size + node.val] ; bx va pastra valorile care trebuie comparate cu min

	cmp bx,dx
	jl testmin

incr:
	pop ebx
	inc edi
	cmp edi,ebx
	jne while
	cmp eax,0
	je first

; schimbam valoarea campului next
next:

	xor edx,edx
add1:

	add edx,node_size
	cmp esi,0
	dec esi
	jne add1

	add edx,ecx
	
	; Dupa aceste operatii, in edx o sa am valoare pt next
	mov [eax + node.next],edx

	; Schimb valoarea lui eax la adresa noului nod
	mov eax,edx 

	; Testam daca am terminat sortarea
	; (valoarea nodului la care ne aflam trebuie sa
	;	fie egala cu ebx)
	cmp [eax + node.val],ebx
	je end
	jmp go

; aici am gasit primul minim
; pun in eax adresa celui mai mic nr
first:
		
	add eax,node_size
	cmp esi,0
	dec esi
	jne first

	add eax,ecx

	mov dword [ebp - 4],eax

	jmp go

end:

 	mov eax, dword [ebp - 4]
	 
	leave
	ret