#include "dsk6713_aic23.h"

Uint32 input_left_sample();
void output_left_sample(int out_data);
void comm_poll();

Uint32 fs = DSK6713_AIC23_FREQ_8KHZ;
short Xn;

main()
{
	comm_poll();
	while(1){
		Xn = input_left_sample();
		output_left_sample(Xn);
	}
}
