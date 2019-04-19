#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<conio.h>

struct process
{
	char name;
	int pri;
	int b_time;
	int pid;
	int w_time;
	int t_time;
	int r_time;
	int a_time;
	int completed=0;
}p[10];


int n;
int q[10];  //declaring queue
int f=-1,r=-1;

void enqueue(int i)
{
if(r==10)
printf("overflow");
r++;
q[r]=i;
if(f==-1)
f=0;
}

int dequeue()
{
if(f==-1)
printf("underflow");
int temp=q[f];
if(f==r)
f=r=-1;
else
f++;
return temp;
}

void sortByArrival()
{
struct process temp;
int i,j;
for(i=0;i<n-1;i++)
for(j=i+1;j<n;j++)
{
if(p[i].a_time>p[j].a_time)
{
temp=p[i];
p[i]=p[j];
p[j]=temp;
}
}
}


void getIn();
void calcWaTime(struct process *q,int);
void calcTurnArTime(struct process *q,int);
void Queue(struct process *q,int si);
void RR();
void PS();
void FCFS();
void QueueI(struct process);
void Queue(struct process *,int);


//Queues
//Q1 = Batch Process having Low Priority with FCFS Algorithm(Priority ranges from 1-3)
//Q2 = Interactive Process having Medium Priority with Priority Based Sorting(Priority ranges from 4-6)
//Q3 = System Process having High Priority with Round Robin Algorith Quantum Time=4(Priority ranges from 7-9)

int qu1_n=0,qu2_n=0,qu3_n=0; //N=Total Process
struct process *qu1,*qu2,*qu3;
//Time Quantum
int tq = 10,count=0;


void getIn()
{
	printf("\n Total Number of Process:\t");
	scanf("%d",&n);
	//Allocatig Memory
	qu1 = (struct process *)malloc(n*sizeof(struct process));
    qu2 = (struct process *)malloc(n*sizeof(struct process));
	qu3 = (struct process *)malloc(n*sizeof(struct process));
	for(int i=0;i<n;i++)
	{
		struct process p;
		printf("\n\t\tProcess %d\n\n\n",i+1);			
		printf("PId:\t");
		scanf("%d",&p.pid);
		printf("Priority (1-9):\t");
		scanf("%d",&p.pri);
		printf("Arrival Time: \t");
		scanf("%d",&p.a_time);	
		printf("Burst Time: \t");
		scanf("%d",&p.b_time);
		p.r_time = p.b_time;
		if(p.pri>0 && p.pri<=3)
		{
			qu1[qu1_n++]  = p;
		}
		else if(p.pri>3 && p.pri<=6)
		{
			qu2[qu2_n++] = p;
		}
		else
		{
			qu3[qu3_n++] = p;
			count++;
		}		
	}
}


void Queue(struct process *q,int si)
{	
	calcWaTime(q,si);
	calcTurnArTime(q,si);
	printf("\nPId\t\tPriority\t\tBurst Time\t\tWaiting Time\t\tTurnAround Time\t\tArrival");
	printf("\n**************************************************************************\n");
	for(int i=0;i<si;i++)
	{
		QueueI(q[i]);
	}
	printf("\n\n");
}


void QueueI(struct process p)
{
	printf("\n%d\t\t%d\t\t\t%d\t\t\t%d\t\t\t%d\t\t\t%d",p.pid,p.pri,p.b_time,p.w_time,p.t_time,p.a_time);
}


void calcWaTime(struct process *q,int si)
{
	q[0].w_time = 0;
	for(int i=1;i<si;i++)
	{
		q[i].w_time = q[i-1].w_time + q[i-1].b_time;
	}
}


void calcTurnArTime(struct process *q,int si)
{
	q[0].w_time = 0;
	for(int i=0;i<si;i++)
	{
		q[i].t_time = q[i].w_time + q[i].b_time;
	}
}

void RRAlgo(struct process *q,int si)
{
 int i,j,time=0,sum_bt=0,tqa;
 char c;
 float avgwt=0,avgtt=0;
 struct process p = q[i];  
printf("\nEnter TIME QUANTUM:");
scanf("%d",&tqa);
sortByArrival();
enqueue(0);               //first process enqueuing here
printf("\n\nPROCESS\t  ARRIVAL TIME\tBURST TIME\tWAITING TIME\tTURNAROUND TIME");
for(i=0;i<count;i++)
{avgwt+=q[i].w_time;
 avgtt+=q[i].t_time;
printf("\n%c\t%d\t%d\t%d\t%d",q[i].name,q[i].a_time,q[i].b_time,q[i].w_time,q[i].t_time);
}
printf("\nAverage waiting time:%f",avgwt/n);
printf("\nAverage Turnaround time:%f",avgtt/n);
getch();
}

void RR()
{
	printf("\n\n***************************************************************************");
	printf("\n\t\tRound Robin\t");
	printf("\n****************************************************************************\n\n");
	calcWaTime(qu3,qu3_n);
	calcTurnArTime(qu3,qu3_n);
	RRAlgo(qu3,qu3_n);
}


void PSAlgorithm(struct process *q,int si)
{
	for(int i=0;i<si;i++)
	{
		for(int j=0;j<si;j++)
		{
			if(q[j].pri>q[i].pri)
			{
				struct process t = q[i];
				q[i] = q[j];
				q[j] = t;
			}
		}
	}
}


void PS()
{
	printf("\n\n**************************************************************************");
	printf("\n\t\tPriority Sorting\t");
	printf("\n****************************************************************************\n\n");
	PSAlgorithm(qu2,qu2_n);
	Queue(qu2,qu2_n);
}


void FCFSAlgorithm(struct process *q,int si)
{
	for(int i=0;i<si;i++)
	{
		for(int j=0;j<si;j++)
		{
			if(q[j].a_time>q[i].a_time)
			{
				struct process t = q[i];
				q[i] = q[j];
				q[j] = t;
			}
		}
	}
}


void FCFS()
{
	printf("\n\n***************************************************************************");
	printf("\n\t\tFirst Come First Serve\t");
	printf("\n*****************************************************************************\n\n");
	FCFSAlgorithm(qu1,qu1_n);
	Queue(qu1,qu1_n);
}


int main()
{
	
	getIn();
	system("CLS");
    int i=1;
	while(n>0)
	{
		switch(i)
		{
			case 1:
				FCFS();
				break;
			case 2:
				PS();
				break;
			case 3:
				RR();
				break;
            default:
            	continue;

		}
		i++;
	}
	printf("\n\n\n");
	return 0;
}
