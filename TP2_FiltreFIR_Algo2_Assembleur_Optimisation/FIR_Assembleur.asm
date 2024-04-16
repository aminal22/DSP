		.def	_FIR_asm
		.ref	_Xn_buffer, _h, _format_Qk, _count

		.text
_FIR_asm:
		MV		.L2		B6, B0			; A4: Xn_buffer,   B4 = h, A6 = k, B6 = count = N,   B0 = N
   		SUB		.L2		B6, 1, B6		; N-1 --> A6
		SHL		.S2		B6, 1, B6		; (N-1)*2 --> B6 (Half Word = 2 memory byte)
		ADD		.L1x	A4, B6, A7		; Adr_Xn_buffer[0] + 2*(N-1) = Adr_Xn_buffer[N-1] --> A7
		ADD		.L2		B4, B6, B7		; Adr_h[0] + 2*(N-1) = Adr_h[N-1] --> B7
	||	ZERO	.L1		A4				; A4 = Yn = 0

;************************* LOOP ***************************************
LOOP:
		LDH		.D1		*A7--, A5		; Xn(i) --> A5
  	||	LDH		.D2		*B7--, B5		; h(i) --> B5
		NOP								; delay slot de LDH
		SUB		.L2		B0, 1, B0		; i - 1 --> i
  [B0]	B		.S1		LOOP			; Branchement a LOOP si B0 != 0
  		NOP
		MPY		.M1x	A5, B5, A3		; Xn(i) * h(i) --> A3
		NOP
		ADD		.L1		A4, A3, A4		; Yn = Yn + Xn(i) * h(i) --> A4
		STH		.D1		A5, *+A7[2]		; Xn(i) --> Xn(i+1)
;************************* LOOP ***************************************

		B		.S2		B3				; Return vers C
  		SHR		.S1		A4, A6, A4		; [Yn = Xn(N-1)*h(N-1) + Xn(N-2)*h(N-2) + ... + X(0)*h(0)] >> k --> A4
		NOP				4
