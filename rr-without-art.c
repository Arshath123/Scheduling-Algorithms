///Round Robin without arrival time

#include<stdio.h>
#include<stdlib.h>
#include<limits.h>

int quantum;

struct process{
    int pid, burst_time, waiting_time, turnaround_time,remaining_time;
}*p,temp;

float average_wt_calculate(int n){
    int i;
    float sum = 0;
    for(i=0;i<n;i++){
        sum += p[i].waiting_time;
    }
    return sum/n;
}

float average_tat_calculate(int n){
    int i;
    float sum = 0;
    for(i=0;i<n;i++){
        sum += p[i].turnaround_time;
    }
    return sum/n;
}

void turnaround_time_calculation(int n){
    int i;
    for(i=0;i<n;i++){
        p[i].turnaround_time = p[i].burst_time + p[i].waiting_time;
    }
}

void waiting_time_calculation(int n){
    int time = 0,process;

    for(int i=0;i<n;i++){
        p[i].remaining_time = p[i].burst_time;
    }

    while(1){
        int completed = 1;
        for(process=0;process<n;process++){
            if(p[process].remaining_time > 0){
                printf("P %d %d \n",process+1,p[process].remaining_time);
                completed = 0;
                if(p[process].remaining_time > quantum){
                    time += quantum;
                    p[process].remaining_time -= quantum;
                }
                else{
                    time += p[process].remaining_time;
                    p[process].waiting_time = time - p[process].burst_time;
                    p[process].remaining_time = 0;
                }
            }
        }
        if(completed == 1){
            break;
        }
    }
}

int main(){
    int n,i;

    printf("Enter the number of processess");
    scanf("%d",&n);

    p = (struct process *)malloc(n*sizeof(struct process));
    for(i=0;i<n;i++){
        printf("\nEnter the process id,burst time of %d th process\n",i+1);
        scanf("%d%d",&p[i].pid,&p[i].burst_time);
    }

    printf("Enter the quantum for the processes\n");
    scanf("%d",&quantum);

    waiting_time_calculation(n);
    turnaround_time_calculation(n);

    float average_waiting_time = average_wt_calculate(n);
    float average_turnaround_time = average_tat_calculate(n);

    printf("PID\tBURST-TIME\tWAITING-TIME\tTURN-AROUND-TIME\n");
    for(i=0;i<n;i++){
        printf("%3d\t%10d\t%12d\t%16d\t\n",p[i].pid,p[i].burst_time,p[i].waiting_time,p[i].turnaround_time);
    }

    printf("\nThe Average Waiting Time is %f seconds\n",average_waiting_time);
    printf("\nThe Average Turn Around Time is %f seconds\n",average_turnaround_time);

    return 0;
}
