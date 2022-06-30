1.1 
---

get_bit:  Pentru masca am shiftat numarul 1 cu i biti. Daca nr si masca = 0, atunci bitul este 0, in caz contrar, bitul poate fi doar 1.

flip_bit: Pentru masca am shiftat numarul 1 cu i biti. Am aplicat operatorul xor intre nr si mask, acesta returneaza 1 daca bitul 
	  mastii era 0, si 1 in caz contrar.

activate_bit: Pentru masca am shiftat numarul 1 cu i biti. Am aplicat operatorul or intre nr si mask, acesta va returna 1 in orice caz.

clear_bit: Pentru masca am shiftat numarul 1 cu i biti, dupa care am negat tot numarul. Am aplicat operatorul and intre nr si mask, acesta
	   va returna 0 in orice caz.


1.2
---

and_gate: poarta AND este und NAND dintre doua NAND-uri: 
	  !(!(a*b)*!(a*b)) = !((!a + !b) * (!a + !b)) = (a*b + a*b) = a*b

not_gate: poarte NOT este doar un nand dintre a si el insusi:
	  !(a*a) = !a + !a = !a

or_gate: poarta OR este un NAND dintre un NAND(a,a) si NAND(b,b)
	 !(!(a*a)*!(b*b))= !(!a*!b)=a + b

xor_gate: poarta XOR: !(!(a*!(a*b))*!(b*!(a*b))) = !(!(a*(!a+!b))*!(b*(!a+!b)))=!((!a + a*b) * (!b + a*b))=
		      = (a * (!a+!b)) + (b * (!a+!b)) = a!b + !ab


1.3
---

full_adder: Suma va fi 1 decat in cazul in care unul din cei 3 biti este activ, sau toti cei 3 biti sunt activi, asadar
	    suma = (a ^ b) ^ c
	    Carry va fi 1 decat in cazul in care 2/3 biti sunt activi, sau toti cei 3 biti sunt activi, asadar
	    carry = (a&b) | (c & (a^b))
	    Am ales sa il implementez returnand valoare 0,1,2 sau 3 bazat pe bitul carry si pe cel suma.

ripple_carry_adder: Incepem cu bitul carry = 0. Vom trece prin toti cei 64 de biti. La inceputul fiecarui bit, voi 
	            verifica daca rezultatul este egal cu suma celor doua numere, caz in care voi opri loop-ul.
		    iau bitul 'i' de la ambele numere si, folosind cazurile full adder-ului, decid daca activez sau nu
	            bitul 'i' in rezultat, precum si daca bitul carry devine 1 sau 0.
		    Dupa ce se termina loop-ul, fie prin brake fie normal, fac un test de overflow simplu: daca la final
	            bitul carry este 1, va fi overflow, in cazul in care totul este OK, returnez res.


2.1
---

send_byte_message: am trimis numerele corespunzatoare literelor: R-18, I-9, C-3, K-11

recv_byte_message: Cu ajutorul unui for loop de 5, primesc 5 caractere codate, pentru a le decoda le compar cu fiecare 
		   numar de la 1 la 26, dupa care le voi printa cu ajutorul unui char c care incepe cu 'A' si creste 
		   odata cu contorul J. ('A'+ 1 = 'B' ; 'A' + 2 = 'C'  etc.)

comm_byte: Introduc cu ajutorul unui vector si al unui for loop 10 caractere. Le trimit utilizant un for loop de 2 inclus
	   in alt for loop de 10.


2.2
---

send_message: trimit lungimea codata in felul urmator: length = 10 -> 10 in baza 2 = 1010, codificat 11(1010)00 = 232
	      trimit cele 10 caractere, cum am facut si in send_byte_message.

recv_message: Primesc lungimea, o shiftez la stanga cu 2 si la dreapta cu 4 biti pentru a scapa de bitii in plus.
   	      Iau fiecare bit din len la rand. Daca acesta este 0 trec mai departe. Daca primul bit este 1 atunci inc
	      len cu 1. Iau variabila pow = 1, pe care o inmultesc cu 2 de fiecare data gasesc un 1, dupa care o adaug.

	      Cu ajutorul functiei sprintf(), transform lungimea (fie ea formata din una sau doua cifre), intr-un vector
	      care contine cele doua cifre, dupa aceeea le printez pe rand.
	      Odata ce stiu lungimea si o trimit, printez caracterele la fel ca si in recv_byte_message

comm_message: Primesc lungimea si o decodez precum in recv_message. Creez o variabila ignoredLetter, pe care o folosesc
	      ca un "dump" pentru literele care nu ma intereseaza (toate mai putin una). Cand ajung la ultima litera,
	      o asignez unei variabile lastLetter, pe care o decodez cum am facut mai sus. Verific daca litera aceasta
	      este P, si trimit lungimile (10 respectiv 11), dupa care si caracterele.


2.3
---

send_squanch2: Iau un for loop de 4, care citeste bitii din c1 si c2, de la bitul 3 la bitul 0. 
	       Daca bitul din c1 este activ, il voi activa in octetul nou format la pozitia (2*i)+1
	       Daca bitul din c2 este activ, il voi activa in octetul nou format la pozitia (2*i)

decode_squanch2: iau un for loop care va trece prin bitii impari (7,5,3,1), in cazul in care acesta este activ in c
	         il voi activa in res la pozitia (1 << {7,6,5,4}), in functie de i.
		 iau alt for loop care va trece prin bitii pari (6,4,2,0), in cazul in care acesta este activ in c
	         il voi activa in res la pozitia (1 << (i/2))


3.1
---

find_spell: iau o variabila count = 0. Cu un for loop, trec prin cei 64 de biti. De fiecare data cand gasesc un bit activ,
            cresc countul cu 1, resetez countul daca gasesc un bit 0. Odata ce count = 5, inseamna ca am gasit vraja.
 	    Stiu indexul din memory la care incepe vraja (i), intr-un loop cu contorul j de la 1 la 16, creez o masca2
	    shiftand 1 la stanga cu (i+j) biti. Pot compara acum mask2 cu memory, ca sa vad care dintre bitii vrajii sunt
	    activi, dupa care ii activez si in res.

find_key: Find key este foarte similar cu find spell, doar ca iau for loop-ul invers si astept sa ajunga count-ul la 3.
	  Urmez un algoritm similar cu cel de la spell.

decrypt_spell: Implementez xor intre key si spell, caut bit cu bit. Daca bitul din spell este egal cu cel din key, atunci
	       continui, in caz contrar, activez acel bit in res.


3.2
---

choose_sword: Incep cu tipul sabiei. Bit cu bit, cu un for loop si un int count, numar cati biti activi are enemy.
	      Testez daca count este par sau impar si asignez 1 variabilei respective, (human) sau (monster), 
	      dupa care activez bitii respectivi in res. 
	      Acum mai trebuie sa lucrez doar cu ultimii 16 biti din res.
	      Daca enemy este human, value este -enemy, adica este enemy negat, plus 1. (~enemy + 1)
	      Daca enemy este monster, calculez variabile oneMinusEnemy, care este -enemy + 1, sau (~enemy + 1 + 1).
	      Deoarece Value ^ (Enemy & oneMinusEnemy) = 0, inseamna ca Value = (enemy & oneMinusEnemy).
	      Dupa ce aflu value, activez bitii ei in ultimii 16 biti al lui res.


3.3
---

trial_of_the_grasses: (low & high) = 0 => daca low are 1, high are 0
					  daca high are 1, low are 0
	   	      (low | high) = cocktail => unde cocktail are 0, high si low au 0
	 	      (high & cocktail) ^ (low | cocktail) = 0 => (high & cocktail) = (low | cocktail) =>
	    	      Pentru ca aceasta sa fie adevarata, cand cocktail are bitul 1, este obligatoriu ca high sa are bitul 1.
		      Din ultimele doua remarci, observam ca antibodies_high = cocktail.
		      Antibodies_low poate sa aibe toti bitii nuli.
		      Aplicam antibodies_high(adica cocktail), ultimilor 16 biti din res, primii 16 lasandu-i nuli.

trial_of_forrest_eyes: Voi gasi padurile prin eliminare, incepand cu Wolven Glade.
	               Daca map are toti cei 64 de biti activi (UINT64_MAX), atunci return 2.

		       Continui cu  Brokilon. Iau o variabila count si una flag. flag va fi folosita ca sa vad daca testul 
	               pentru Brokilon a esuat sau nu. Iau fiecare bit din map iar daca acesta este 1,voi incrementa count si
 		       voi testa daca count (numarul de copaci (biti activi) fix din spatele lui) este mai mare decat 4, in 
	               cazul in care trec la urmatoarea padure.
		       Daca bitul este 0, testez daca inainte lui au fost fie 4 copaci(biti activi), fie un alt 0.
	               Daca testul esueaza, trec la urmatoarea padure, daca nu, resetez count.
		       Dupa ce testam toti cei 64 de biti, observam daca variabila flag a fost schimbata, in cazul
		       in care trecem la padurea 3, daca aceasta a ramas intacta, return 0.

		       Pentru  Hindar, map va avea doar doi biti activi, pe pozitiile 31 si 32. Putem afla usor
		       numarul int echivalent cu map, acesta fiind egal cu 2^31 + 2^32 = 6442450944. Un simplu test de 
		       egalitate ne va spune daca alegem sau nu aceasta padure, in caz afirmativ, return 1.

		       Daca nici una dintre cele 3 paduri testate nu a intors nicio valoare functiei, atunci ramanem doar cu
	 	       Caed Dhu, return 3.


trial_of_the_dreams: Incep cu doua variabile egale cu -1, indexWitcher si indexPortal. Iau la rand toti cei 32 de biti din map.
	             Stiu ca in map am doar doi biti activi asadar, de fiecare data cand gasesc un bit activ, prima oara voi
	 	     asigna i (indexul bitului) variabile indexWitcher. A doua oara cand voi gasi un bit activ, voi asigna i
	             variabilei indexPortal. Odata ce indexPortal isi schimba valoarea, ies din loop (break) si ii atribui lui
		     res indexPortal - indexWitcher (Portal fiind gasit la un index mai mare decat Witcher). return res.


























