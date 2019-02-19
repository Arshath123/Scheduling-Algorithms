///Priority pre-emptive with arrival time

#include<stdio.h>
#include<stdlib.h>
#include<limits.h>

struct process{
    int pid, burst_time, arrival_time, priority, waiting_time, turnaround_time,remaining_time;
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
    int pc = 0,time = 0,process,selected = 0,prior = INT_MAX; /// pc - process completed, time - current time that the processes are executing in

    for(int i=0;i<n;i++){
        p[i].remaining_time = p[i].burst_time;
    }

    while(pc < n){
        int j;

        for(j=0;j<n;j++){
            if(p[j].arrival_time <= time && p[j].remaining_time > 0 && p[j].priority < prior){
                process = j;///process that has minimum remaining time
                selected = 1;
                prior = p[j].priority;
            }
        }

        if(selected == 0){
            printf("\n%d is Idle Time\n",time);
            time++;
            continue;
        }

        p[process].remaining_time--;

        if(p[process].remaining_time == 0){
            pc++;
            selected = 0;
            prior = INT_MAX;
            p[process].waiting_time = time + 1 - p[process].burst_time - p[process].arrival_time;
            if(p[process].waiting_time < 0){
                p[process].waiting_time = 0;
            }
        }
        time++;
    }
}

int main(){
    int n,i;

    printf("Enter the number of processess");
    scanf("%d",&n);

    p = (struct process *)malloc(n*sizeof(struct process));
    for(i=0;i<n;i++){
        printf("\nEnter the process id,burst time,priority,arrival time of %d th process\n",i+1);
        scanf("%d%d%d%d",&p[i].pid,&p[i].burst_time,&p[i].priority,&p[i].arrival_time);
    }

    waiting_time_calculation(n);
    turnaround_time_calculation(n);

    float average_waiting_time = average_wt_calculate(n);
    float average_turnaround_time = average_tat_calculate(n);

    printf("PID\tBURST-TIME\tARRIVAL-TIME\tWAITING-TIME\tTURN-AROUND-TIME\n");
    for(i=0;i<n;i++){
        printf("%3d\t%10d\t%12d\t%12d\t%16d\t\n",p[i].pid,p[i].burst_time,p[i].arrival_time,p[i].waiting_time,p[i].turnaround_time);
    }

    printf("\nThe Average Waiting Time is %f seconds\n",average_waiting_time);
    printf("\nThe Average Turn Around Time is %f seconds\n",average_turnaround_time);

    return 0;
}


