#include<stdio.h>
void main()
{
    int n,bt[100],wt[100],tat[100];
    float avgtat,avgwt;
    printf("Enter the number of processes:");
    scanf("%d",&n);
    printf("Enter the burst time for each process:\n");
    for(int i=0;i<n;i++){
        scanf("%d",&bt[i]);
    }
    avgwt=0.0;
    avgtat=bt[0];
    wt[0]=0;
    tat[0]=bt[0];
    for(int i=1;i<n;i++){
        wt[i]=wt[i-1]+bt[i-1];
        tat[i]=wt[i]+bt[i];
        avgwt+=wt[i];
        avgtat+=tat[i];
    }
    printf("The times after computation is:\n");
    printf("\tPROCESS\tBT\tTAT\tWT");
    for(int i=0;i<n;i++){
        printf("\n\tP%d\t%d\t%d\t%d",i,bt[i],tat[i],wt[i]);
    }
    printf("\nAverage wait time = %f",avgwt/n);
    printf("\nAverage turn around time = %f",avgtat/n);
}