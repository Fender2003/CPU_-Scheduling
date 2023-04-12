#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#define MAX_SIZE 250
#define INT_MAX 2147483647

struct process{
 char process_id;
 int arrival_time;
 int burst_time;
 int completion_time;
 int turnaround_time;
 int waiting_time;
 int priority;
 int quantum;
 int type;
 int remaining_time;
};

void fcfs(struct process p[], int n);
void sjf(struct process p[], int n);
void rr(struct process p[], int n, int quantum);
void prio(struct process p[], int n, int choice);
void srtf(struct process p[], int n);
void lrtf(struct process p[], int n,int choice);

void queueUpdation(int queue[],int timer,int arrival[],int n, int maxProccessIndex){
    int zeroIndex;
    for(int i = 0; i < n; i++){
        if(queue[i] == 0){
            zeroIndex = i;
            break;
        }
    }  
    queue[zeroIndex] = maxProccessIndex + 1;
}

void queueMaintainence(int queue[], int n){
    for(int i = 0; (i < n-1) && (queue[i+1] != 0) ; i++){
        int temp = queue[i];
        queue[i] = queue[i+1];
        queue[i+1] = temp;
    }
}

void checkNewArrival(int timer, int arrival[], int n, int maxProccessIndex,int queue[]){
    if(timer <= arrival[n-1]){
       bool newArrival = false;
       for(int j = (maxProccessIndex+1); j < n; j++){
             if(arrival[j] <= timer){
              if(maxProccessIndex < j){
                 maxProccessIndex = j;
                 newArrival = true;
              }
           }
       }
       //adds the incoming process to the ready queue
       //(if any arrives)
       if(newArrival)
          queueUpdation(queue,timer,arrival,n, maxProccessIndex);
    }
}
void swap(struct process *a, struct process *b) {
    struct process temp = *a;
    *a = *b;
    *b = temp;
}

void print_gantt_chart(struct process p[], int n)
{
    int i, j;
    // print top bar
    printf(" ");
    for(i=0; i<n; i++) {
        for(j=0; j<p[i].burst_time; j++) printf("--");
        printf(" ");
    }
    printf("\n|");
 
    // printing process id in the middle
    for(i=0; i<n; i++) {
        for(j=0; j<p[i].burst_time - 1; j++) printf(" ");
        printf("P%c", p[i].process_id);
        for(j=0; j<p[i].burst_time - 1; j++) printf(" ");
        printf("|");
    }
    printf("\n ");
    // printing bottom bar
    for(i=0; i<n; i++) {
        for(j=0; j<p[i].burst_time; j++) printf("--");
        printf(" ");
    }
    printf("\n");
 
    // printing the time line
    printf("0");
    for(i=0; i<n; i++) {
        for(j=0; j<p[i].burst_time; j++) printf("  ");
        if(p[i].completion_time > 9) printf("\b"); // backspace : remove 1 space
        printf("%d", p[i].completion_time);
 
    }
    printf("\n");
}
void sort_from_index_ind(struct process p[], int n, int starting_ind)
{
        int i, j;
        struct process temp;
        for(i = starting_ind; i < n - 1; i++)
        {
            for(j = i + 1; j < n; j++)
            {
                if(p[i].burst_time > p[j].burst_time) {
                    temp = p[i];
                    p[i] = p[j];
                    p[j] = temp;
                }
            }
        }
        return;
}

void sort_arrival_time(struct process p[], int n)
{
        int i, j;
        struct process temp;
        for(i = 0; i < n; i++)
        {
            for(j = i + 1; j < n; j++)
            {
                if(p[i].arrival_time > p[j].arrival_time)
                {
                    temp = p[i];
                    p[i] = p[j];
                    p[j] = temp;
                }
            }
        }
        return;
}

void sort_pid(struct process p[], int n)
{
        int i, j;
        struct process temp;
        for(i = 0; i < n; i++)
        {
            for(j = i + 1; j < n; j++)
            {
                if(p[i].process_id > p[j].process_id)
                {
                    temp = p[i];
                    p[i] = p[j];
                    p[j] = temp;
                }
            }
        }
        return;
}

void sort(struct process p[], int n){
    int i, j;
    for (i = 0; i < n-1; i++) {
        for (j = i+1; j < n; j++) {
            if (p[j].arrival_time < p[i].arrival_time) {
                swap(&p[j], &p[i]);
            }
            else if(p[j].arrival_time == p[i].arrival_time){
                if(p[j].priority<p[i].priority ){
                    swap(&p[j], &p[i]);
                }
            }
            else{
                continue;
            }
        }
    }
}

void reverse_sort(struct process p[], int n, int starting_ind)
{
        int i, j;
        struct process temp;
        for(i = starting_ind; i < n - 1; i++)
        {
            for(j = i + 1; j < n; j++)
            {
                if(p[i].burst_time < p[j].burst_time) {
                    temp = p[i];
                    p[i] = p[j];
                    p[j] = temp;
                }
            }
        }
        return;
}

int main(){
    int i,n;
    char algo[100];
    FILE *fp;
    
    fp = fopen("input.txt","r");
    
    fscanf(fp, "%s",algo);
    fscanf(fp, "%d",&n);

    struct process p[n];

    if(strcmp(algo, "fcfs")==0){
        for(int i=0;i<n;i++){
            fscanf(fp, "%s",&p[i].process_id);
            fscanf(fp, "%d",&p[i].arrival_time);
            fscanf(fp, "%d",&p[i].burst_time);
        }
        fcfs(p,n);
    }
    else if(strcmp(algo, "sjf")==0){
        for(int i=0;i<n;i++){
        fscanf(fp, "%s",&p[i].process_id);
        fscanf(fp, "%d",&p[i].arrival_time);
        fscanf(fp, "%d",&p[i].burst_time);
        }
        sjf(p,n);
    }
    else if(strcmp(algo, "rr")==0){
         for(int i=0;i<n;i++){
        fscanf(fp, "%s",&p[i].process_id);
        fscanf(fp, "%d",&p[i].arrival_time);
        fscanf(fp, "%d",&p[i].burst_time);
        }
        int quantum;
        fscanf(fp, "%d",&quantum);
        rr(p,n,quantum);
    }
    else if(strcmp(algo, "priority")==0){
        for(int i=0;i<n;i++){
            fscanf(fp, "%s",&p[i].process_id);
            fscanf(fp, "%d",&p[i].arrival_time);
            fscanf(fp, "%d",&p[i].burst_time);
            fscanf(fp, "%d",&p[i].priority);
        }
        int choice;
        printf("Select: 1 for preemptive and 2 for non preemptive.\n");
        scanf("%d",&choice);
        prio(p,n,choice);
    }
    else if (strcmp(algo, "srtf")==0){
         for(int i=0;i<n;i++){
        fscanf(fp, "%s",&p[i].process_id);
        fscanf(fp, "%d",&p[i].arrival_time);
        fscanf(fp, "%d",&p[i].burst_time);
        }
        srtf(p,n);
    } 
    else if (strcmp(algo, "lrtf")==0){
         for(int i=0;i<n;i++){
        fscanf(fp, "%s",&p[i].process_id);
        fscanf(fp, "%d",&p[i].arrival_time);
        fscanf(fp, "%d",&p[i].burst_time);
        }
        int choice;
        printf("Select: 1 for preemptive and 2 for non preemptive.\n");
        scanf("%d",&choice);
        lrtf(p,n,choice);
    }
    return 0;
}


void fcfs(struct process p[], int n){
    float total_turn_around_time=0, total_waiting_time=0;
    
    sort_arrival_time(p,n);
    p[0].completion_time =  p[0].burst_time;
    p[0].turnaround_time = p[0].completion_time - p[0].arrival_time;
    p[0].waiting_time = p[0].turnaround_time - p[0].burst_time;
    total_turn_around_time += p[0].turnaround_time;
    total_waiting_time += p[0].waiting_time;

    for(int i=1;i<n;i++){
        p[i].completion_time = p[i-1].completion_time+ p[i].burst_time;
        p[i].turnaround_time = p[i].completion_time - p[i].arrival_time;
        p[i].waiting_time = p[i].turnaround_time - p[i].burst_time;
        total_turn_around_time += p[i].turnaround_time;
        total_waiting_time += p[i].waiting_time;
    }

    float avg_turn_around_time = total_turn_around_time/n;  
    float avg_waiting_time = total_waiting_time/n;
    print_gantt_chart(p,n);
    sort_pid(p, n);
    printf("\n\n\t\t<------- FIRST COME FIRST SERVED SCHEDULING ------->\n\n");

    printf("PROCESS ID\tARRIVAL TIME\tBURST TIME\tCOMPLETION TIME\t\tTURN-AROUND TIME\tWAITING TIME\n");
    // printf("%d\n",p[0].process_id);
    for(int i=0;i<n;i++){
        printf("%c\t\t%d\t\t%d\t\t%d\t\t\t%d\t\t\t%d\n",p[i].process_id,p[i].arrival_time,p[i].burst_time,p[i].completion_time,p[i].turnaround_time,p[i].waiting_time);
    }

    printf("\nAVERAGE TURNAROUND TIME : %.2f\n", avg_turn_around_time);
    printf("AVERAGE WAITING TIME : %.2f\n", avg_waiting_time);
    FILE *fw;
    fw = fopen("output.txt","w");
    fprintf(fw,"%s","\n\n\t\t<------- FIRST COME FIRST SERVED SCHEDULING ------->\n\n");
    fprintf(fw,"%s","ID\t\tAT\t\tBT\t\tCT\t\t\tTAT\t\t\tWT\n");
    for(int i=0;i<n;i++){
        fprintf(fw,"%c\t\t%d\t\t%d\t\t%d\t\t\t%d\t\t\t%d\n",p[i].process_id,p[i].arrival_time,p[i].burst_time,p[i].completion_time,p[i].turnaround_time,p[i].waiting_time);
    }
    fprintf(fw,"\nAVERAGE TURNAROUND TIME : %.2f\n",avg_turn_around_time);
    fprintf(fw,"\nAVERAGE WAITING TIME : %.2f\n",avg_waiting_time);
    fclose(fw);
}

void sjf(struct process p[], int n){
     sort_arrival_time(p, n);
    float total_turn_around_time=0, total_waiting_time=0;
    

    p[0].completion_time =  p[0].burst_time;
    p[0].turnaround_time = p[0].completion_time - p[0].arrival_time;
    p[0].waiting_time = p[0].turnaround_time - p[0].burst_time;
    total_turn_around_time += p[0].turnaround_time;
    total_waiting_time += p[0].waiting_time;

    sort_from_index_ind(p, n, 1);

    for(int i=1;i<n;i++)
    {
        struct process temp1;
        int j=i;

        if(p[i].arrival_time > p[i-1].completion_time)
        {
            while(1)
            {
    
                if(p[j].arrival_time <= p[i-1].completion_time)
                {
                    temp1 = p[i];
                    p[i] = p[j];
                    p[j] = temp1;
                    // printf("%d %d", j, i);
                    
                    sort_from_index_ind(p, n, i+1);
                    break;
                }
                
                j++;
                if(j==n)
                    break;
            }
        }
        
        p[i].completion_time = p[i-1].completion_time+ p[i].burst_time;
        p[i].turnaround_time = p[i].completion_time - p[i].arrival_time;
        p[i].waiting_time = p[i].turnaround_time - p[i].burst_time;
        total_turn_around_time += p[i].turnaround_time;
        total_waiting_time += p[i].waiting_time;

    }

    float avg_turn_around_time = total_turn_around_time/n;  
    float avg_waiting_time = total_waiting_time/n;
    print_gantt_chart(p,n);
    sort_pid(p, n);
    printf("\n\n\t\t<------- SHORTEST JOB FIRST ------->\n\n");

    printf("PROCESS ID\tARRIVAL TIME\tBURST TIME\tCOMPLETION TIME\t\tTURN-AROUND TIME\tWAITING TIME\n");
    // printf("%d\n",p[0].process_id);
    for(int i=0;i<n;i++){
        printf("%c\t\t%d\t\t%d\t\t%d\t\t\t%d\t\t\t%d\n",p[i].process_id,p[i].arrival_time,p[i].burst_time,p[i].completion_time,p[i].turnaround_time,p[i].waiting_time);
    }

    printf("\nAVERAGE TURNAROUND TIME : %.2f\n", avg_turn_around_time);
    printf("AVERAGE WAITING TIME : %.2f\n", avg_waiting_time);
    
    FILE *fw;
    fw = fopen("output.txt","w");
    fprintf(fw,"%s","\n\n\t\t<------- SHORTEST JOB FIRST ------->\n\n");
    fprintf(fw,"%s","ID\t\tAT\t\tBT\t\tCT\t\t\tTAT\t\t\tWT\n");
    for(int i=0;i<n;i++){
        fprintf(fw,"%c\t\t%d\t\t%d\t\t%d\t\t\t%d\t\t\t%d\n",p[i].process_id,p[i].arrival_time,p[i].burst_time,p[i].completion_time,p[i].turnaround_time,p[i].waiting_time);
    }
    fprintf(fw,"\nAVERAGE TURNAROUND TIME : %.2f\n",avg_turn_around_time);
    fprintf(fw,"\nAVERAGE WAITING TIME : %.2f\n",avg_waiting_time);
    fclose(fw);
}

void prio(struct process p[], int n, int choice){
    if(choice == 2){
        float total_turn_around_time=0, total_waiting_time=0;
        int wt[100], tat[100];
        sort(p,n);
        int ser[100];
        ser[0] = p[0].arrival_time;
        wt[0]=0;

        for(int i=1;i<n;i++){
            ser[i]=p[i-1].burst_time+ser[i-1];
            wt[i]=ser[i]-p[i].arrival_time;
            if(wt[i]<0){
                wt[i]=0;
            }
        }
        for(int i=0;i<n;i++){
            tat[i]=p[i].burst_time+wt[i];
        }
        for(int i=0;i<n;i++){
                total_waiting_time += wt[i];
                total_turn_around_time += tat[i];
        }
        total_turn_around_time /= n;
        total_waiting_time /= n;
        int stime[50];
        stime[0] = p[0].arrival_time;
        p[0].completion_time=stime[0]+tat[0];
        for(int i=1;i<n;i++)
            {
                // stime[i]=ctime[i-1];
                // ctime[i]=stime[i]+tat[i]-wt[i];
                stime[i] = p[i-1].completion_time;
                p[i].completion_time = stime[i]+tat[i]-wt[i];
            }
            print_gantt_chart(p,n);
            sort_pid(p, n);
            
            printf("\n\n\t\t<------- NON-PREEMPTIVE PRIORITY CPU SCHEDULING ------->\n\n");

            printf("PROCESS ID\tARRIVAL TIME\tBURST TIME\tCOMPLETION TIME\t\tTURN-AROUND TIME\tWAITING TIME\n");
            for(int i=0;i<n;i++){
                printf("%c\t\t%d\t\t%d\t\t%d\t\t\t%d\t\t\t%d\n",p[i].process_id,p[i].arrival_time,p[i].burst_time,p[i].completion_time,tat[i],wt[i]);
            }

            printf("\nAVERAGE TURNAROUND TIME : %.2f\n", total_turn_around_time);
            printf("AVERAGE WAITING TIME : %.2f\n", total_waiting_time);
            
            FILE *fw;
            fw = fopen("output.txt","w");
            fprintf(fw,"%s","\n\n\t\t<------- NON-PREEMPTIVE PRIORITY CPU SCHEDULING ------->\n\n");
            fprintf(fw,"%s","ID\t\tAT\t\tBT\t\tCT\t\t\tTAT\t\t\tWT\n");
            for(int i=0;i<n;i++){
                fprintf(fw,"%c\t\t%d\t\t%d\t\t%d\t\t\t%d\t\t\t%d\n",p[i].process_id,p[i].arrival_time,p[i].burst_time,p[i].completion_time,tat[i],wt[i]);
            }
            fprintf(fw,"\nAVERAGE TURNAROUND TIME : %.2f\n",total_turn_around_time);
            fprintf(fw,"\nAVERAGE WAITING TIME : %.2f\n",total_waiting_time);
            fclose(fw);

    }
    // preemptive priority
    else if(choice==1){
    int temp[n],t,count=0,short_p;
    float total_turn_around_time=0, total_waiting_time=0;
    float Avg_WT,Avg_TAT;
    int c=n-1;
    int tt=0;
    //temp[i]=p[i].burst_time;
    p[c].priority=1000;
    for(int i=0;i<n;i++){
            temp[i]=p[i].burst_time;
    }
    printf("Gantt Chart:\n");
    printf("|");
    for(t=0;count!=n;t++)
    {
        short_p=c;
        for(int i=0;i<n;i++)
        {
            if(p[short_p].priority>p[i].priority && p[i].arrival_time<=t && p[i].burst_time>0)
            {
                short_p=i;
            }
        }
        

        p[short_p].burst_time=p[short_p].burst_time-1;
        // printf("%d |",)
        printf("P%d |",short_p+1);

        // if any process is completed
        if(p[short_p].burst_time==0)
        {
            // one process is completed
            // so count increases by 1
            count++;
            
            p[short_p].turnaround_time=t+1-p[short_p].arrival_time;
            p[short_p].waiting_time=p[short_p].turnaround_time-temp[short_p];

            // total calculation
            total_waiting_time= total_waiting_time+p[short_p].waiting_time;
            total_turn_around_time=total_turn_around_time+p[short_p].turnaround_time;

        }
    }
    printf("\n");
    for(int i=0;i<t;i++){
        printf("%d   ",tt);
        tt++;
    }
    Avg_WT= total_waiting_time/n;
    Avg_TAT=total_turn_around_time/n;

    // printing of the answer
    printf("\n\n\t\t<------- PREEMPTIVE PRIORITY CPU SCHEDULING ------->\n\n");
    printf("PROCESS ID\tARRIVAL TIME\tBURST TIME\tWAITING TIME\tTURN-AROUND TIME\n");
    for(int i=0;i<n;i++){
        printf("%c\t\t%d\t\t%d\t\t%d\t\t\t%d\n",p[i].process_id,p[i].arrival_time,temp[i],p[i].waiting_time,p[i].turnaround_time);
            }
        printf("\nAVERAGE TURNAROUND TIME : %.2f\n",Avg_TAT);
        printf("AVERAGE WAITING TIME : %.2f\n", Avg_WT);
        FILE *fw;
        fw = fopen("output.txt","w");
        fprintf(fw,"%s","\n\n\t\t<------- PREEMPTIVE PRIORITY CPU SCHEDULING ------->\n\n");
        fprintf(fw,"%s","ID\t\tAT\t\tBT\t\tWT\t\t\tTAT\n");
        for(int i=0;i<n;i++){
            fprintf(fw,"%c\t\t%d\t\t%d\t\t%d\t\t\t%d\n",p[i].process_id,p[i].arrival_time,temp[i],p[i].turnaround_time,p[i].waiting_time);
        }
        fprintf(fw,"\nAVERAGE TURNAROUND TIME : %.2f\n",Avg_TAT);
        fprintf(fw,"\nAVERAGE WAITING TIME : %.2f\n", Avg_WT);
        fclose(fw);
    }
    else{
        int ch;
        printf("Entered invalid choice\n");
        printf("Enter valid choice:\n");
        scanf("%d",&ch);
        lrtf(p,n,ch);
    }
}

void lrtf(struct process p[], int n,int choice){
    if(choice==2){
    sort_arrival_time(p, n);
    float total_turn_around_time=0, total_waiting_time=0;
    

    p[0].completion_time =  p[0].burst_time;
    p[0].turnaround_time = p[0].completion_time - p[0].arrival_time;
    p[0].waiting_time = p[0].turnaround_time - p[0].burst_time;
    total_turn_around_time += p[0].turnaround_time;
    total_waiting_time += p[0].waiting_time;

    reverse_sort(p, n, 1);

    for(int i=1;i<n;i++)
    {
        struct process temp1;
        int j=i;

        if(p[i].arrival_time > p[i-1].completion_time)
        {
            while(1)
            {
    
                if(p[j].arrival_time <= p[i-1].completion_time)
                {
                    temp1 = p[i];
                    p[i] = p[j];
                    p[j] = temp1;
                    // printf("%d %d", j, i);
                    
                    reverse_sort(p, n, i+1);
                    break;
                }
                
                j++;
                if(j==n)
                    break;
            }
        }
        
        p[i].completion_time = p[i-1].completion_time+ p[i].burst_time;
        p[i].turnaround_time = p[i].completion_time - p[i].arrival_time;
        p[i].waiting_time = p[i].turnaround_time - p[i].burst_time;
        total_turn_around_time += p[i].turnaround_time;
        total_waiting_time += p[i].waiting_time;

    }

    float avg_turn_around_time = total_turn_around_time/n;  
    float avg_waiting_time = total_waiting_time/n;
    print_gantt_chart(p,n);
    sort_pid(p, n);
    printf("\n\n\t\t<------- NON - PREEMPTIVE LONGEST REMAINING TIME FIRST ------->\n\n");

    printf("PROCESS ID\tARRIVAL TIME\tBURST TIME\tCOMPLETION TIME\t\tTURN-AROUND TIME\tWAITING TIME\n");
    // printf("%d\n",p[0].process_id);
    for(int i=0;i<n;i++){
        printf("%c\t\t%d\t\t%d\t\t%d\t\t\t%d\t\t\t%d\n",p[i].process_id,p[i].arrival_time,p[i].burst_time,p[i].completion_time,p[i].turnaround_time,p[i].waiting_time);
    }

    printf("\nAVERAGE TURNAROUND TIME : %.2f\n", avg_turn_around_time);
    printf("AVERAGE WAITING TIME : %.2f\n", avg_waiting_time);
    

        FILE *fw;
        fw = fopen("output.txt","w");
        fprintf(fw,"%s","\n\n\t\t<------- NON - PREEMPTIVE LONGEST REMAINING TIME FIRST ------->\n\n");
        fprintf(fw,"%s","ID\t\tAT\t\tBT\t\tCT\t\t\tTAT\t\t\tWT\n");
        for(int i=0;i<n;i++){
            fprintf(fw,"%c\t\t%d\t\t%d\t\t%d\t\t\t%d\t\t\t%d\n",p[i].process_id,p[i].arrival_time,p[i].burst_time,p[i].completion_time,p[i].turnaround_time,p[i].waiting_time);
        }
        fprintf(fw,"\nAVERAGE TURNAROUND TIME : %.2f\n",avg_turn_around_time);
        fprintf(fw,"\nAVERAGE WAITING TIME : %.2f\n",avg_waiting_time);
        fclose(fw);
    }
    else if(choice ==1){
        int current_time = 0;
    int completed = 0;
    int i, j;
    struct process *current_process;
    int a[100];
    for (i = 0; i < n; i++) {
        p[i].remaining_time = p[i].burst_time;
    }
    printf("\n\n\t\t<------- LONGEST REMAINING TIME FIRST SCHEDULING ------->\n\n");
    // printf("|");
    int v=0;
    while (completed < n) {
        // Find process with longest remaining time
        current_process = NULL;
        int selected_process = 0;
        for (i = 0; i < n; i++) {
            if (p[i].arrival_time <= current_time && p[i].remaining_time > 0) {
                if (current_process == NULL || p[i].remaining_time > current_process->remaining_time) {
                    current_process = &p[i];
                    selected_process = i;
                }
            }
        }
        
        // If no process found, increment time and continue
        if (current_process == NULL) {
            // printf(" Idle |");
            current_time++;
            a[v] = 99;
            v++;
            continue;
        }
        
        // Execute the current process for 1 unit of time
        current_process->remaining_time--;
        a[v] = selected_process;
        // printf("  P%c  |", p[selected_process].process_id);
        current_time++;
        v++;
        // Check if current process is completed
        if (current_process->remaining_time == 0) {
            completed++;
            current_process->completion_time = current_time;
            current_process->turnaround_time = current_process->completion_time - current_process->arrival_time;
            current_process->waiting_time = current_process->turnaround_time - current_process->burst_time;
        }
    }
    float avg_turnaround_time = 0;
    float avg_waiting_time = 0;

    for (i = 0; i < n; i++) {
    avg_turnaround_time += p[i].turnaround_time;
    avg_waiting_time += p[i].waiting_time;
    }
    avg_turnaround_time /= n;
    avg_waiting_time /= n;


    printf("PROCESS ID\tARRIVAL TIME\tBURST TIME\tCOMPLETION TIME\t\tTURN-AROUND TIME\tWAITING TIME\n");
    for(int i=0;i<n;i++){
        printf("%c\t\t%d\t\t%d\t\t%d\t\t\t%d\t\t\t%d\n",p[i].process_id,p[i].arrival_time,p[i].burst_time,p[i].completion_time,p[i].turnaround_time,p[i].waiting_time);
    }
    printf("\nAVERAGE TURNAROUND TIME : %.2f\n", avg_turnaround_time);
    printf("AVERAGE WAITING TIME : %.2f\n", avg_waiting_time);
    FILE *fw;
    fw = fopen("output.txt","w");
    fprintf(fw,"%s","\n\n\t\t<------- LONGEST REMAINING TIME FIRST SCHEDULING ------->\n\n");
    fprintf(fw,"%s","ID\t\tAT\t\tBT\t\tCT\t\t\tTAT\t\t\tWT\n");
    for(int i=0;i<n;i++){
        fprintf(fw,"%c\t\t%d\t\t%d\t\t%d\t\t\t%d\t\t\t%d\n",p[i].process_id,p[i].arrival_time,p[i].burst_time,p[i].completion_time,p[i].turnaround_time,p[i].waiting_time);
    }
    fprintf(fw,"\nAVERAGE TURNAROUND TIME : %.2f\n",avg_turnaround_time);
    fprintf(fw,"\nAVERAGE WAITING TIME : %.2f\n",avg_waiting_time);
    fclose(fw);
    int s,s1;
    printf("\n ");
    // for(int s=0;s<current_time;s++){
    //     printf("------ ");
    // }
    printf("\n|");

    for(int s=0;s<current_time;s++){
        if(a[s]==99){
            printf("      |");
        }else
            printf("  P%c  |", p[a[s]].process_id);
    }
    printf("\n");

    // for(int s=0;s<current_time;s++){
    //     printf("------ ");
    // }
    // printf("\n");
    
    printf("0");
    for(int s=0;s<current_time;s++){
        printf("      ");
        if(s > 9) printf("\b");
        printf("%d",s+1);
    }
    printf("\n");

    }

    else{
        int ch;
        printf("Entered invalid choice\n");
        printf("Enter valid choice:\n");
        scanf("%d",&ch);
        lrtf(p,n,ch);
    }
}

void srtf(struct process p[], int n){
    int wt[n], tat[n], total_wt = 0, total_tat = 0,rt[n];
    for(int i=0;i<n;i++){
        rt[i]=p[i].burst_time;
    }
    int complete = 0, t = 0, minm = INT_MAX;
    int shortest = 0, finish_time;
    bool check = false;
    FILE *fw;
    fw = fopen("output.txt","w");
    // fprintf(fw,"%s","Gantt chart : ");
    printf("Gantt Chart : \n");
    printf("|");
    int tt=0;
    while (complete != n) {
        for (int j = 0; j < n; j++) {
            if ((p[j].arrival_time <= t) && (rt[j] < minm) && rt[j] > 0) {
                minm = rt[j];
                shortest = j;
                check = true;
            }
        }
        if (check == false) {
            t++;
            continue;
        }
        rt[shortest]--;
        printf("P%d |",shortest+1);
        
        minm = rt[shortest];
        if (minm == 0)
            minm = INT_MAX;
        if (rt[shortest] == 0) {
            complete++;
            check = false;
            finish_time = t + 1;
            wt[shortest] = finish_time -p[shortest].burst_time -p[shortest].arrival_time;
            if (wt[shortest] < 0)
                wt[shortest] = 0;
        }
        t++;
    }
    printf("\n");
    for(int i=0;i<t;i++){
        printf("%d   ",tt);
        tt++;
    }
    
    for (int i = 0; i < n; i++)
        tat[i] = p[i].burst_time + wt[i];
    printf("\n\n\t\t<------- SHORTEST REMAINING TIME FIRST SCHEDULING ------->\n\n");
    printf("PROCESS ID\tARRIVAL TIME\tBURST TIME\t\tTURN-AROUND TIME\tWAITING TIME\n");
    for(int i=0;i<n;i++){
        printf("%c\t\t%d\t\t%d\t\t\t%d\t\t\t%d\n",p[i].process_id,p[i].arrival_time,p[i].burst_time,tat[i],wt[i]);
    }
    for(int i = 0; i < n; i++){
        total_wt = total_wt + wt[i];
        total_tat = total_tat + tat[i];
    }
    printf("\nAverage waiting time = %.2f\n",((float)total_wt / n));
    printf("Average turn around time = %.2f\n",((float)total_tat / n));

    
    fprintf(fw,"%s","\n\n\t\t<------- SHORTEST REMAINING TIME FIRST SCHEDULING ------->\n\n");
    fprintf(fw,"%s","ID\t\tAT\t\tBT\t\tTAT\t\t\tWT\n");
    for(int i=0;i<n;i++){
        fprintf(fw,"%c\t\t%d\t\t%d\t\t%d\t\t\t%d\n",p[i].process_id,p[i].arrival_time,p[i].burst_time,tat[i],wt[i]);
    }
    fprintf(fw,"\nAVERAGE TURNAROUND TIME : %.2f\n",((float)total_wt / n));
    fprintf(fw,"\nAVERAGE WAITING TIME : %.2f\n",((float)total_tat / n));
    fclose(fw);
}

void rr(struct process p[], int n, int tq){
    int timer = 0, maxProccessIndex = 0;
    float avgWait = 0, avgTT = 0;
    int queue[n], temp_burst[n],arrival[n];
    bool complete[n];
    sort_arrival_time(p,n);
    for (int i = 0; i < n; i++) {
        temp_burst[i]=p[i].burst_time;
    }
    for (int i = 0; i < n; i++) {
        arrival[i]=p[i].arrival_time;
    }
    for(int i = 0; i < n; i++){
        complete[i] = false;
        queue[i] = 0;
    }
    while(timer < p[0].arrival_time)
        timer++;
    queue[0] = 1;
    int ind=0;
    printf("Gantt Chart:\n");
    printf("|");
    while(true){
        bool flag = true;
        for(int i = 0; i < n; i++){
            if(temp_burst[i] != 0){
                flag = false;
                break;
            }
        }
        if(flag)
            break;

        for(int i = 0; (i < n) && (queue[i] != 0); i++){
            int ctr = 0;
            while((ctr < tq) && (temp_burst[queue[0]-1] > 0)){
                temp_burst[queue[0]-1] -= 1;
                printf("P%d  |",queue[0]-1+1);
                ind++;
                timer += 1;
                ctr++;
                checkNewArrival(timer,arrival, n, maxProccessIndex, queue);
            }
            if((temp_burst[queue[0]-1] == 0) && (complete[queue[0]-1] == false)){
                p[queue[0]-1].turnaround_time = timer;  
                complete[queue[0]-1] = true;
            }
            bool idle = true;
            if(queue[n-1] == 0){
                for(int i = 0; i < n && queue[i] != 0; i++){
                    if(complete[queue[i]-1] == false){
                        idle = false;
                    }
                }
            }
            else
                idle = false;
            if(idle){
                timer++;
                checkNewArrival(timer, arrival, n, maxProccessIndex, queue);
            }
            queueMaintainence(queue,n);
        }
    }

    printf("\n");
    int tt=0;
    for(int i=0;i<ind+1;i++){
        printf("%d    ",tt);
        tt++;
    }
    for(int i = 0; i < n; i++){
        p[i].turnaround_time -= arrival[i];
        p[i].waiting_time = p[i].turnaround_time-p[i].burst_time;
    }
    printf("\n\n\t\t<------- ROUND ROBIN SCHEDULING------->\n\n");
    printf("PROCESS ID\tARRIVAL TIME\tBURST TIME\t\tTURN-AROUND TIME\tWAITING TIME\n");
    for(int i=0;i<n;i++){
        printf("%c\t\t%d\t\t%d\t\t\t%d\t\t\t%d\n",p[i].process_id,p[i].arrival_time,p[i].burst_time,p[i].turnaround_time,p[i].waiting_time);
    }
    for(int i =0; i< n; i++){
        avgWait += p[i].waiting_time;
        avgTT += p[i].turnaround_time;
    }
    printf("\nAverage wait time : %.2f",(avgWait/n));
    printf("\nAverage Turn Around Time : %.2f",(avgTT/n));
    FILE *fw;
    fw = fopen("output.txt","w");
    fprintf(fw,"%s","\n\n\t\t<------- ROUND ROBIN SCHEDULING------->\n\n");
    fprintf(fw,"%s","ID\t\tAT\t\tBT\t\tTAT\t\t\tWT\n");
    for(int i=0;i<n;i++){
        fprintf(fw,"%c\t\t%d\t\t%d\t\t%d\t\t\t%d\n",p[i].process_id,p[i].arrival_time,p[i].burst_time,p[i].turnaround_time,p[i].waiting_time);
    }
    fprintf(fw,"\nAVERAGE TURNAROUND TIME : %.2f\n",(avgWait/n));
    fprintf(fw,"\nAVERAGE WAITING TIME : %.2f\n",(avgTT/n));
    fclose(fw);
}