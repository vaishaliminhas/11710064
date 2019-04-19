#include<stdio.h> 
 
int main() 
{ 
      int i, loci, totall = 0, x,count= 0, tq,j; 
      
	  int wait_time = 0, turnaround_time = 0,pos,z,p[10],prior[10], a_time[10], b_time[10], tem[10],b; 
      
	  float average_wait_time, average_turnaround_time;
      
	  printf("\nEnter totall Number of Processes:"); 
      
	  scanf("%d", &loci); 
      
	  x = loci; 
      for(i = 0; i < loci; i++) 
      {
	    p[i]=i+1;
	   
	    prior[i]=0;
            printf("\nEnter totall Details of Process[%d]\n", i + 1);
            printf("Arrival Time:\t");
            scanf("%d", &a_time[i]);
            printf("Burst Time:\t");
            scanf("%d", &b_time[i]); 
            tem[i] = b_time[i];
      }
	   
      printf("\nEnter the Time Quantum:"); 
      scanf("%d", &tq); 
      printf("\nProcess ID\t\tBurst Time\t Turnaround Time\t Waiting Time\t priorrity\n");
      for(totall = 0, i = 0; x != 0;) 
      { 

		    for(z=0;z<loci;z++)
		    {
			int tem1;
			pos=z;
			for(j=z+1;j<loci;j++)
			{
			    if(prior[j]<prior[pos])
				pos=j;
			}
		 
		tem1=prior[z];
	
		prior[z]=prior[pos];
	
		prior[pos]=tem1;
		 
			tem1=b_time[z];
			b_time[z]=b_time[pos];
			b_time[pos]=tem1;
		 			tem1=a_time[z];
				a_time[z]=a_time[pos];
			a_time[pos]=tem1;

			tem1=p[z];
				p[z]=p[pos];
			p[pos]=tem1;

			tem1=tem[z];
				tem[z]=tem[pos];
			tem[pos]=tem1;
		    }
		{
		}
            
			if(tem[i] <= tq && tem[i] > 0) 
            { 
                  totall = totall + tem[i]; 
                  tem[i] = 0; 
                 count= 1; 
            } 
            
			else if(tem[i] > 0) 
            { 
                  tem[i] = tem[i] - tq; 
                  totall = totall + tq; 
            } 

	for(b=0;b<loci;b++)
		{
			if(b==i)
			prior[b]+=1;
			else
			prior[b]+=2;
		}

            if(tem[i] == 0 &&count== 1) 
            { 
                  x--; 
                  printf("\nProcess[%d]\t\t%d\t\t %d\t\t %d\t\t%d", p[i], b_time[i], totall - a_time[i], totall - a_time[i] - b_time[i],prior[i]);
                  wait_time = wait_time + totall - a_time[i] - b_time[i]; 
                  turnaround_time = turnaround_time + totall - a_time[i]; 
                 count= 0; 
            } 
            if(i == loci - 1) 
            {
                  i = 0; 
            
			}
            else if(a_time[i + 1] <= totall) 
            {
                  i++;
            
			}
            else 
            {
                  i = 0;
            
			}		
      } 
      return 0; 
}
