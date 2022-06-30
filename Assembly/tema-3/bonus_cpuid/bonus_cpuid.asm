section .text
	global cpu_manufact_id
	global features
	global l2_cache_info

;; void cpu_manufact_id(char *id_string);
;
;  reads the manufacturer id string from cpuid and stores it in id_string
cpu_manufact_id:

	enter 	0, 0
	push ebx

	mov esi,[ebp + 8] ; id_string
	
	; eax trebuie sa fie 0
	xor eax,eax
	cpuid
	
	; datele se vor stoca intr-un string format din
	; 12 caractere in registrele ebx,edx si ecx
	
	mov [esi], ebx
	mov [esi + 4], edx
	mov [esi + 8], ecx

	pop ebx
	leave
	ret

;; void features(char *vmx, char *rdrand, char *avx)
;
;  checks whether vmx, rdrand and avx are supported by the cpu
;  if a feature is supported, 1 is written in the corresponding variable
;  0 is written otherwise
features:

	enter 	0, 0
	push ebx	

	mov esi,[ebp + 8] ; vmx
	mov edi,[ebp + 12] ; rdrand

	; eax trebuie sa fie 1
	mov eax,1
	cpuid

	; Toate cele trei feature-uri se pot afla din registrul ECX
	; Pe bitul 5, se afla informatia despre vmx
	mov eax,1
	shl eax,5
	and eax,ecx
	shr eax,5
	mov [esi],eax

	; Pe bitul 30, se afla informatia despre rdrand
	mov eax,1
	shl eax,30
	and eax,ecx
	shr eax,30
	mov [edi],eax
	
	; Pe bitul 28, se afla informatia despre avx
	mov eax,1
	shl eax,28
	and eax,ecx
	shr eax,28

	mov edi,[ebp + 16] ; avx
	mov [edi],eax

	pop ebx
	leave
	ret

;; void l2_cache_info(int *line_size, int *cache_size)
;
;  reads from cpuid the cache line size, and total cache size for the current
;  cpu, and stores them in the corresponding parameters
l2_cache_info:
	enter 	0, 0
	push ebx

	mov esi,[ebp + 8] ; line_size
	mov edi,[ebp + 12] ; cache_size

	; eax trebuie sa fie 0x80000006
	mov eax,0x80000006
	cpuid

	; Dimensiunea liniei se afla pe bitii 07-00 (primul octet)
	mov eax,0b11111111
	and eax,ecx
	mov [esi],eax


	; Dimensiunea cache-ului de nivel 2 de gasesete pe bitii 16-31
	shr ecx,16
	mov [edi],ecx

	pop ebx
	leave
	ret
