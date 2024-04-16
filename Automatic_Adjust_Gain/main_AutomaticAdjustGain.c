#include "dsk6713_aic23.h"

Uint32 input_sample();
void output_sample(int out_data);
void comm_intr();

extern FindGain();

#define		N	128

Uint32 fs = DSK6713_AIC23_FREQ_8KHZ;
short Xn, Yn;
short XnBuffer[N], YnBuffer[N];
unsigned i, AAG = 0;

interrupt void c_int11()
{
	Xn = input_sample();
	XnBuffer[i] = Xn;
	Yn = (short) (Xn << AAG);
	YnBuffer[i] = Yn;
	i = (i + 1) % N;
	if(i == 0){
		AAG = FindGain(XnBuffer, N);
	}
	output_sample(Yn);
	return;
}

main()
{
	i = 0;
	AAG = 0;
	comm_intr();
	while(1);
}
