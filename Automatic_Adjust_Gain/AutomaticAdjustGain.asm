; Registre A4 contient l'adresse de XnBuffer
; Registre B4 contient le nombre d'échantillons N
; Registre B3 contient l'adresse de retour au main

;*** Nombre de cycle de loop: 15 cycles * 128 = 1920 cycles

	.def	_FindGain
_FindGain:
		MVK		.S1		31, A10			; A10 = Maximum redondance du bit de signe = 31 pour FFFF FFFFh
		MV		.L2		B4, B0			; nombre d'échantillons N --> registre A1
loop:
		LDH		.D1		*A4++, A11		; Lecture d'un échantillons Xn "short" (16 bits) --> registre A11
		NOP				4				; 4 delay slot pour l'instruction LDH
		NORM	.L1		A11, A12		; Redondance du bit de signe de l'échantillon Xn --> registre A12
		CMPLT	.L1		A12, A10, A2	; Si (Redondance du bit de signe de l'échantillon Xn) < A10  --> A2 = 1
  [A2]	MV		.S1		A12, A10		; Si oui, Redondance du bit de signe de l'échantillon Xn --> registre A10
  		SUB		.S2		B0, 1, B0		; Décrementation du compteur d'itération
  [B0]	B		.S1		loop			; Boucle pour faire 128 itérations
  		NOP				5				; 5 delay slot pour l'instruction B

  		SUB		.S1		A10, 16 , A4	; Les échantillons sont "short" donc 16 bits uniquement or A11 est un registre de 32 bits (16 bits de plus)
		B       .S2		B3				; B3 contient l'adresse de retour vers le programme C --> Retour du sous programme
		NOP				5				; 5 delay slot pour l'instruction B


