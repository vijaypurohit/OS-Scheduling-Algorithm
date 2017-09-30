// C++ Program to demonstrate the working of Shortest Remaining Time First Scheduling Algorithm
// it consider the arrival time in and out order
// by Vijay Purohit
// working and tested on Dev-C++ 5.11 

#include<stdio.h>

#include<iostream>
#include<cstdlib>
#include<cstdio>
using namespace std;

typedef struct process
{
	int id;  // process id
	int at;  // process arrival time
	int bt;  // process burst time
	int rt;  // process remaining time after completing time quantum
	int st;  // process starting time
	int ft;  // process finish time
	float wt,tat;   // process waiting time and time quantum
}process;
 
process p[20],ps[20],temp;            	// main process and ps= process sorted.

int accept()  							//functions for accepting inputs from the user
{
	int i,n;
	cout<<"Enter total number of processes(maximum 20):";
    	cin>>n;
	if(n==0){
		cout<<"\nInvalid no. of process";  exit(1);
	}
	for(i=1;i<=n;i++) 
	{ 
		cout<<"\nEnter Arrival Time and Burst Time for Process P["<<i<<"] : Ar :";
		 p[i].id=i; 																	// storing process id or no
			cin>>p[i].at;												
		    	cout<<"\t\t\t\t\t\t Ex: ";
		  	cin>>p[i].bt;
		 p[i].rt=p[i].bt; 																// copying burst time to remaining time
	
		ps[i]=p[i];																		// copying of one process into another process(dummy process)
	} 		
	return n;
}

void sort_arrival(int n)      
{
	int i,j;
	for(i=2;i<=n;i++)
		for(j=1;j<i;j++)
			if(ps[j].at>ps[i].at)
			{
				temp=ps[i];
				ps[i]=ps[j];
				ps[j]=temp;
			}
			else if(ps[j].at==ps[i].at) //if both the arrival time are equal then sort on the basis of process burst time
				if(ps[j].bt>ps[i].bt)
				{
					temp=ps[i];
					ps[i]=ps[j];
					ps[j]=temp;
				}
}

main()
{
	int i, j=1, k, l, n, m, count=0, min=9999, time=0,tq=1;
    float sum_waittime=0, sum_turnaround=0; 
    int ganttP[50],ganttStartTime[50], ganttStopTime[50];
  	cout << fixed;
  	cout.precision(2);
  
     n = accept(); 
  	sort_arrival(n);

	time = ps[1].at;	   			// starting time is equal to arrival time for first process
//     m = ps[1].id;
     
	while(count!=n) 
	{
		min=9999;
		for(k=1;k<=n;k++)
		{
			if(ps[k].at <= time && ps[k].rt < min && ps[k].rt>0 )
			{
				min = ps[k].rt;
				m=ps[k].id;
				l=k;
			}
		}
		
		if(time < ps[n].at)									// if all process are not arrived
		{
			ganttP[j] = m ;									// process no
			ganttStartTime[j] = time;						
							
		 p[m].rt -= tq;										// remaining time is decrease to one unit
		 time += tq;										
			ganttStopTime[j++] = p[m].ft =  time;
			
			if( ps[k].at > time )								// if next process arrival time is greater than current process finish time
				time = ps[k].at;
		}
		else												// if all the process are arrived
		{
			ganttP[j] = m ;								
			ganttStartTime[j] = time;				
			
		  time += p[m].rt;										// it will execute till its burst time
		  p[m].rt = 0;	
			ganttStopTime[j++] = p[m].ft = time;
			
		}
		ps[l].rt = p[m].rt;									// updating sorted process remaining time
		//calculating waiting time	
		if(p[m].rt == 0)
		{
			count++;
			p[m].tat	=	p[m].ft - p[m].at;
			p[m].wt		=	p[m].tat - p[m].bt;
			sum_turnaround += p[m].tat;
			sum_waittime += p[m].wt;
		}
	}
	 
	
	cout<<"\n Gantt Chart is = P[NO](start time, stop time) : \n";
	for(i=1;i<j;i++)
	{
	  	printf("p[%d](%d,%d) || ", ganttP[i], ganttStartTime[i], ganttStopTime[i]);
	}	
			
 	printf("\n===========================/=================================");
  
    printf("\n\nProcess\t | Arrival Time | Waiting Time | Completion T  | Turnaround T |  \n\n"); 
	for(i=1;i<=n;i++) 
	{ 
		printf("  P[%d] \t|\t %d\t|\t %.2f\t|\t %d \t|\t %.2f |\n",p[i].id, p[i].at, p[i].wt, p[i].ft, p[i].tat); 
	} 
 
	cout<<"\nAverage Waiting Time = "<<sum_waittime/n; 
	cout<<"\nAvg TurnAround Time =  "<<sum_turnaround/n; 
 
}
