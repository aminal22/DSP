#include "dsk6713_aic23.h" 			 					//support file for codec,DSK

void output_sample(int out_data);

void DSK6713_LED_init();
void DSK6713_LED_on(short num);
void DSK6713_LED_off(short num);

void DSK6713_DIP_init();
int DSK6713_DIP_get(short num);

void comm_poll();

Uint32 fs = DSK6713_AIC23_FREQ_8KHZ; 		 			//set sampling rate
short loop = 0; 				 						//table index
short gain = 32; 				 						//gain factor
short sine_table[8]={0,724,1024,724,0,-724,-1024,-724};	//sine values F = 1 KHz en Q10
void main()
{
   comm_poll(); 				 						//init DSK, codec, McBSP
   DSK6713_LED_init(); 			 						//init LED from BSL
   DSK6713_DIP_init(); 			 						//init DIP from BSL
   while(1) 					 						//infinite loop
  {
	if(DSK6713_DIP_get(0)==0) 		 					//=0 if switch #0 pressed
	{
	   DSK6713_LED_on(0); 		 						//turn LED #0 ON
	   output_sample(sine_table[loop]*gain);			//output every Ts (SW0 on)
	   if (++loop > 7) loop = 0; 		 				//check for end of table
	}
	else DSK6713_LED_off(0); 			 				//LED #0 off
   } 					 								//end of while (1)
}
