///sjfs non pre-emptive without arrival time

#include<stdio.h>
#include<stdlib.h>

struct process{
    int pid, burst_time, waiting_time, turnaround_time;
}*p,temp;

void sort_process_with_burst_time(int n){
    int i,j;
    ///Bubble Sort..
    for(i=0;i<n-1;i++){
        for(j=0;j<n-1-i;j++){
            if(p[j].burst_time > p[j+1].burst_time){
                temp = p[j];
                p[j] = p[j+1];
                p[j+1] = temp;
            }
        }
    }
}

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
    int i;
    p[0].waiting_time = 0;
    for(i=1;i<n;i++){
        p[i].waiting_time = p[i-1].waiting_time + p[i-1].burst_time;
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

    sort_process_with_burst_time(n);

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

