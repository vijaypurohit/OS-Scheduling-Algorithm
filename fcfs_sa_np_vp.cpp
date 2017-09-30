// C++ Program to demonstrate the working of First Come First Serve Scheduling Algorithm
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
			else if(ps[j].at==ps[i].at) //if both the arrival time are equal then sort on the basis of process no
				if(ps[j].id>ps[i].id)
				{
					temp=ps[i];
					ps[i]=ps[j];
					ps[j]=temp;
				}
}

main()
{
	int i, j=1, n, m,time=0;
    float sum_waittime=0, sum_turnaround=0; 
    int ganttP[50],ganttStartTime[50], ganttStopTime[50];
  	cout << fixed;
  	cout.precision(2);
  
    n=accept(); 
  	sort_arrival(n);

	 time = ps[1].at;	   			// starting time is equal to arrival time for first process
     
	for(i=1;i<=n;i++) 
	{
		ganttP[j] = m = ps[i].id;							// process no
		
//	  	ps[i].st = ps[i-1].st + ps[i-1].bt;
		ganttStartTime[j] = p[m].st = ps[i].st = time;			// process (unsorted) and process sorted
		  
//		time = p[m].ft = ps[i].ft = ps[i].st + ps[i].bt;
		time += ps[i].bt;										// it will execute till its burst time
		ganttStopTime[j++] = p[m].ft = ps[i].ft = time;
		
		if( ps[i+1].at > ps[i].ft )								// if next process arrival time is greater than current process finish time
			time = ps[i+1].at;
		
		//calculating waiting time	
		p[m].tat=p[m].ft-p[m].at;
		p[m].wt=p[m].tat-p[m].bt;
		sum_turnaround += p[m].tat;
		sum_waittime += p[m].wt;
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
