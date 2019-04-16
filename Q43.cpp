#include<stdio.h>
#include<stdlib.h>
void SJF(int p[],int arrival[],int burst[],int l){
	int temp,total=0,tat[10],wt[10];	
	float avg_wt,avg_tat;
 for(int i=0;i<l;i++)
    {
      int pos=i;
        for(int j=i+1;j<l;j++)
        {
            if(burst[j]<burst[pos])
                pos=j;
        }
 
        temp=burst[i];
        burst[i]=burst[pos];
        burst[pos]=temp;
 
        temp=p[i];
        p[i]=p[pos];
        p[pos]=temp;
    }
 
    wt[0]=0;            //waiting time for first process will be zero
 
    //calculate waiting time
    for(int i=1;i<l;i++)
    {
        wt[i]=0;
        for(int j=0;j<i;j++)
            wt[i]+=burst[j];
 
        total+=wt[i];
    }
 
    avg_wt=(float)total/l;      //average waiting time
    total=0;
 
    printf("\nProcess\t    Burst Time    \tWaiting Time\tTurnaround Time");
    for(int i=0;i<l;i++)
    {
        tat[i]=burst[i]+wt[i];     //calculate turnaround time
        total+=tat[i];
        printf("\np%d\t\t  %d\t\t    %d\t\t\t%d",p[i],burst[i],wt[i],tat[i]);
    }
 
    avg_tat=(float)total/l;     //average turnaround time
    printf("\n\nAverage Waiting Time=%f",avg_wt);
    printf("\nAverage Turnaround Time=%f\n",avg_tat);
	}
void roundRobin(int p[], int a[],int b[],int l) 
	{  int  n;
		int res = 0; 
		int resc = 0; 

		// copy the burst array and arrival array 
		// for not effecting the actual array 
		int res_b[l]; 
		int res_a[l];

		for (int i = 0; i <l; i++) { 
			res_b[i] = b[i]; 
			res_a[i] = a[i]; 
		} 

		// critical time of system 
		int t = 0; 

		// for store the waiting time 
		int w[l];

		// for store the Completion time 
		int comp[l]; 
		int flag=0;
		int counter =1;
		while (1) { 
		flag = 1; 
			for (int i = 0; i < l; i++) { 
				if(counter==1){
					n=3;
				}
				else if(counter==2){
					n=6;
				}
				else{
					SJF(p,a,res_b,l);
				}
				// these condition for if 
				// arrival is not on zero 

				// check that if there come before qtime 
				if (res_a[i] <= t) { 
					if (res_a[i] <= n) { 
						if (res_b[i] > 0) { 
							flag = 0; 
							if (res_b[i] > n) { 

								// make decrease the b time 
								t = t + n; 
								res_b[i] = res_b[i] - n; 
								res_a[i] = res_a[i] + n; 
								} 
							else { 

								// for last time 
								t = t + res_b[i]; 

								// store comp time 
								comp[i] = t - a[i]; 

								// store wait time 
								w[i] = t - b[i] - a[i]; 
								res_b[i] = 0; 

				
							} 
						} 
					} 
					else if (res_a[i] > n) { 

						// is any have less arrival time 
						// the coming process then execute them 
						for (int j = 0; j <l; j++) { 

							// compare 
							if (res_a[j] < res_a[i]) { 
								if (res_b[j] > 0) { 
									flag = 1; 
									if (res_b[j] > n) { 
										t = t + n; 
										res_b[j] = res_b[j] - n; 
										res_a[j] = res_a[j] + n; 
									} 
									else { 
										t = t + res_b[j]; 
										comp[j] = t - a[j]; 
										w[j] = t - b[j] - a[j]; 
										res_b[j] = 0; 
									} 
								} 
							} 
						} 

						// now the previous porcess according to 
						// ith is process 
						if (res_b[i] > 0) { 
							flag = 1; 

							// Check for greaters 
							if (res_b[i] > n) { 
								t = t + n; 
								res_b[i] = res_b[i] - n; 
								res_a[i] = res_a[i] + n; 
							} 
							else { 
								t = t + res_b[i]; 
								comp[i] = t - a[i]; 
								w[i] = t - b[i] - a[i]; 
								res_b[i] = 0; 
							} 
						} 
					} 
				} 

				// if no process is come on thse critical 
				else if (res_a[i] > t) { 
					t++; 
					i--; 
				} 
			} 
			// for exit the while loop 
			if (flag) { 
				break; 
			}
			else{
				counter++;
			} 
		} 

		printf("\n\t\t\tname atime ctime wtime Tntime\n"); 
		for (int i = 0; i < l; i++) { 
			printf(" \t\t\t %d",p[i]);
            printf("   %d  ",a[i]);
			printf("   %d ",comp[i]);
			printf("    %d ",w[i]);                
             printf("    %d\n",abs(comp[i]-a[i]));                
            

			res = res + w[i]; 
			resc = resc + comp[i]; 
		} 

	printf("\n\t\t\tAverage waiting time is %f\n",(float)res /l); 
		printf("\n\t\t\tAverage compilation time is %f",(float)resc /l);
		}
	int main()
	{ 
		int pn[20],arrivaltime[20],bursttime[20];
		int q,l;
		 printf("Enter Total Process:\t "); 
  scanf("%d",&l); 
  for(int i=0;i<l;i++) 
  { pn[i]=i+1;
    printf("Enter Arrival Time for Process Process Number %d :",pn[i]); 
	scanf("%d",&arrivaltime[i]); 
    printf("Enter Burst Time for Process Process Number %d :",pn[i]);
	scanf("%d",&bursttime[i]);  
  	}	  
  
		roundRobin(pn, arrivaltime, bursttime,l); 
	} 

