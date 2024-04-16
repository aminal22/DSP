#include "dsk6713_aic23.h"

Uint32 input_left_sample();
void output_left_sample(int out_data);
void comm_intr();

extern int FIR_asm(short XnBuffer[], short h[], short format_Qk, short count);

#define    N     128      // Nombre de coefficients du filtre

#define    k     17      // representation en virgule fixe en k

// Frequence d'echantillonnage Fs = 8000

short h[128] = {0,0,-1,0,1,2,3,2,-2,-8,-10,-5,6,19,24,12,
-14,-42,-50,-24,29,81,94,45,-52,-145,-167,-79,90,246,278,130,
-146,-396,-443,-205,228,614,682,313,-347,-927,-1025,-469,518,1381,1526,699,
-773,-2069,-2299,-1061,1187,3222,3647,1725,-1992,-5642,-6763,-3464,4496,15305,25629,31923,
31923,25629,15305,4496,-3464,-6763,-5642,-1992,1725,3647,3222,1187,-1061,-2299,-2069,-773,
699,1526,1381,518,-469,-1025,-927,-347,313,682,614,228,-205,-443,-396,-146,
130,278,246,90,-79,-167,-145,-52,45,94,81,29,-24,-50,-42,-14,
12,24,19,6,-5,-10,-8,-2,2,3,2,1,0,-1,0,0 };

Uint32 fs = DSK6713_AIC23_FREQ_8KHZ;
short Xn, i, count = N, format_Qk = k;
short XnBuffer[N+1], YnBuffer[N];
Uint16 j;
int Yn;

interrupt void c_int11()
{
	Xn = input_left_sample();
	XnBuffer[0] = Xn;

//	Yn = 0;
//	for(i = N-1; i >= 0; i--){
//		Yn = Yn + h[i] * XnBuffer[i];
//		XnBuffer[i+1] = XnBuffer[i];
//	}

//	YnBuffer[j] = (short) (Yn >> k);

	YnBuffer[j] =  (short) FIR_asm(XnBuffer, h, format_Qk, count);

	output_left_sample(YnBuffer[j]);

	j = (j + 1) % N;

	return;
}

main()
{
	j = 0; count = N, format_Qk = k;

	for(i = 0; i <= N-1; i++){
		XnBuffer[i] = 0;
		YnBuffer[i] = 0;
	}

	comm_intr();
	while(1);
}
