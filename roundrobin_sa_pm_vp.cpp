// C++ Program to demonstrate the working of Round Robin Scheduling Algorithm
// by Vijay Purohit
// working and tested on Dev-C++ 5.11 


#include<stdio.h> 

#include<iostream>
#include<cstdlib>
#include<queue>
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
 
process p[20],ps[20],temp;            // main process and process sorted.
queue<int> rq;							// ready queue


int accept()  //functions for accepting inputs from the user
{
	int i,n;
	cout<<"Enter total number of processes(maximum 20):";
    	cin>>n;
	if(n==0){
		cout<<"\nInvalid no. of process";	exit(1);
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
  int i, j=1;
  int n, time, flag=0, tq, m, nextarr; 
  float sum_waittime=0, sum_turnaround=0; 
	
  int ganttP[50],ganttStartTime[50], ganttStopTime[50], ganttRemTime[50];
  cout << fixed;
  cout.precision(2);
  
  cout<<"Enter Time Quantum of Round Robin:\t"; 
  	cin>>tq; 
  	
  n=accept(); 
  sort_arrival(n);
  
	i=1;
	rq.push(ps[i].id);					// push first process id with minimum arrival time from sorted process array	
  	time=ps[i].at;						// starting time is equal to arrival time of first process.
  	nextarr=ps[++i].at;					// saving the next arrival time of the process
  
  while( !rq.empty() ) 					// continue until queue is empty
  { 
  	
  	m=rq.front();       				// m=process id of front element in the queue
  	rq.pop();							// pop first element
    
	if(p[m].rt<=tq && p[m].rt>0) 		// if burst time or remaining time is less than time quantum
    { 
    	ganttP[j]=m;
      	ganttStartTime[j]=time;
      	
	  time+=p[m].rt; 					// add remaining time to total time
      p[m].rt=0; 						// then remaining time of process will become zero
       flag=1; 
      	
      	ganttRemTime[j]=p[m].rt;
      	ganttStopTime[j++]=time;
    } 
    else if(p[m].rt>0)  				// else it it greater than time quantum
    { 
    	ganttP[j]=m;
      	ganttStartTime[j]=time;
      
      time+=tq; 						// add time quantum into total time
	  p[m].rt-=tq; 						// minus the time quantum from remaining time
      	
		ganttRemTime[j]=p[m].rt;
      	ganttStopTime[j++]=time;
    } 
    if(p[m].rt==0 && flag==1) 
    { 
      // turn around time = completion time - arrival time
      // waiting time = turn around time - burst time = completion time - arrival time - burst time
      p[m].ft = time;
      p[m].wt = time-p[m].at-p[m].bt;
      p[m].tat = time-p[m].at;
      
      sum_turnaround += p[m].tat;     // sum of all turn around time
      sum_waittime += p[m].wt;   // sum of all wait time
      flag=0; 
    }
	
	// for loop continuation 
	while(i<=n&&ps[i].at<=time)				// if arrival time of next process in sorted process array is less than total time completed
	{
	        rq.push(ps[i].id);
		i++;
	}
	
	if(i<=n)							
		nextarr=ps[i].at;					// next arrival time of process after pushing selected elements into queue
		
	if(p[m].rt>0)							// push the process if remaining time exist and which is just completed into the queue
		rq.push(m);
  } 
  
  
  
  cout<<"\n Gantt Chart is = P[NO](start time, stop time)remaining time : \n";
  for(i=1;i<j;i++)
  	{
      printf("p[%d](%d,%d)%d || ",ganttP[i],ganttStartTime[i], ganttStopTime[i],ganttRemTime[i]);
  	}
  	
  printf("\n===========================/=================================");
  
  printf("\n\nProcess\t | Arrival Time | Waiting Time | Completion T  | Turnaround T |  \n\n"); 
  for(i=1;i<=n;i++) 
  { 
    printf(" P[%d] \t|\t %d\t|\t %.2f\t|\t %d \t|\t %.2f|\n",p[i].id, p[i].at, p[i].wt, p[i].ft, p[i].tat); 
  } 
  
  cout<<"\nAverage Waiting Time = "<<sum_waittime/n; 
  cout<<"\nAvg TurnAround Time =  "<<sum_turnaround/n; 
 
}
