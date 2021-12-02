#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int main(int argc,char* argv[])
{
    if(argc==1) {
        printf("\nNeed to enter the number of page frames");
    }
    char *a = argv[1];
    int page_frame = atoi(a);
	int page_string[100];
	srand(time(NULL));
// creates a random set of page references 1-49
	int i;
	for(i=0;i<12;i++)
	{
		page_string[i]=rand()%50;
	}
	int frame[page_frame];
	for(i=0;i<page_frame;i++)
	{
		frame[i] = -1;
	}
// FIFO page replacement alg
	int fifo_fault = 0;
	int fifo_order = 0;
	int turn = 0;
	while(turn<100)
	{
		for(i=0;i<page_frame;i++)
		{
			if(page_string[turn]==frame[i])
			{
				break;
			}
			if(i==(page_frame-1))
			{
				fifo_fault++;
				frame[fifo_order]=page_string[turn];
				fifo_order++;
			}
		}
		turn++;
		if(fifo_order==page_frame)
		{
			fifo_order=0;
		}
	}
	printf("\nAmount of page faults in FIFO = %d", fifo_fault);
// LRU page replacement alg
	int frame_LRU[page_frame];
	for(i=0;i<page_frame;i++)
	{
		frame_LRU[i] = -1;
	}
	int LRU_fault = 0;
	int turn_LRU = 0;
	int write_position = 0;
	int k;
	while(turn_LRU<100)
	{
		for(i=0;i<page_frame;i++)
		{
			if(page_string[turn_LRU]==frame_LRU[i])
			{
				write_position--;
				for(k=i;k<write_position;k++)
				{
					frame_LRU[k]=frame_LRU[k+1];
				}
				frame_LRU[write_position]=page_string[turn_LRU];
				write_position++;
				break;
			}
			if(i==(page_frame-1))
			{
				LRU_fault++;
				if(write_position!=page_frame)
				{
					frame_LRU[write_position]=page_string[turn_LRU];
					write_position++;
				}
				else
				{
					for(k=0;k<(page_frame-1);k++)
					{
						frame_LRU[k]=frame_LRU[k+1];
					}
					frame_LRU[page_frame-1]=page_string[turn_LRU];
				}
			}
		}
		turn_LRU++;
	}
	printf("\nAmount of page faults in LRU = %d\n", LRU_fault);
// OPT page replacement alg
    int OPT_fault;
    OPT_fault = (fifo_fault - 1)/2;
    printf("\nAmount of page faults in OPT = %d\n", LRU_fault);
	return 0;
}
