#include "dsk6713_aic23.h"

Uint32 input_left_sample();
void output_left_sample(int out_data);
void comm_intr();

Uint32 fs = DSK6713_AIC23_FREQ_8KHZ;
short Xn;

interrupt void c_int11()
{
	Xn = input_left_sample();
	output_left_sample(Xn);
	return;
}

main()
{
	comm_intr();
	while(1);
}
