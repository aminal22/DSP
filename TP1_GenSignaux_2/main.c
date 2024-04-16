#include "dsk6713_aic23.h"

Uint32 input_left_sample();
void output_left_sample(int out_data);
void comm_intr();

#define		N		64

short SinTable[N] = {0, 401, 799, 1189, 1567, 1931, 2276, 2598, 2896, 3166, 3406, 3612, 3784, 3920, 4017, 4076, 4096, 4076, 4017, 3920, 3784, 3612, 3406, 3166, 2896, 2598, 2276, 1931, 1567, 1189, 799, 401, 0, -401, -799, -1189, -1567, -1931, -2276, -2598, -2896, -3166, -3406, -3612, -3784, -3920, -4017, -4076, -4096, -4076, -4017, -3920, -3784, -3612, -3406, -3166, -2896, -2598, -2276, -1931, -1567, -1189, -799, -401};

Uint32 fs = DSK6713_AIC23_FREQ_8KHZ;
short Xn;
short XnBuffer[N];
Uint16 i, j, GAIN = 1, STEP = 1;

interrupt void c_int11()
{
	Xn = GAIN * SinTable[j];
	XnBuffer[i] = Xn;
	i = (i + 1) % N;
	j = (i * STEP) % N;
	output_left_sample(Xn);
	return;
}

main()
{
	i = 0; GAIN = 1; STEP = 1;
	comm_intr();
	while(1);
}
