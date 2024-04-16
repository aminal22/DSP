#include "dsk6713_aic23.h"

Uint32 input_left_sample();
void output_left_sample(int out_data);
void comm_intr();

Uint32 fs = DSK6713_AIC23_FREQ_8KHZ;

#define		N		128

short XnBuffer[N];
short Xn;
Uint16 i;

interrupt void c_int11()
{
	Xn = input_left_sample();
	XnBuffer[i] = Xn;
	i = (i + 1) % N;
	output_left_sample(Xn);
	return;
}

main()
{
	i = 0;
	comm_intr();
	while(1);
}
